#pragma once
#include "shapeEditor.h"
#include "shape/ellipseShape.h"
#include <memory>
#include <algorithm>


class ellipseEditor : public shapeEditor {
    POINT ptPrev{};
    bool  hasPrev = false;

    void drawRubberEllipse(HDC hdc, POINT center, POINT corner) {
        long x1 = 2 * center.x - corner.x;
        long y1 = 2 * center.y - corner.y;
        long x2 = corner.x;
        long y2 = corner.y;

        int left   = (int)std::min(x1, x2);
        int top    = (int)std::min(y1, y2);
        int right  = (int)std::max(x1, x2);
        int bottom = (int)std::max(y1, y2);

        HPEN hPen         = CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
        HPEN hOldPen      = (HPEN)SelectObject(hdc, hPen);
        HBRUSH hNullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
        HBRUSH hOldBrush  = (HBRUSH)SelectObject(hdc, hNullBrush);
        int oldROP        = SetROP2(hdc, R2_XORPEN);

        Ellipse(hdc, left, top, right, bottom);

        SetROP2(hdc, oldROP);
        SelectObject(hdc, hOldBrush);
        SelectObject(hdc, hOldPen);
        DeleteObject(hPen);
    }

public:
    ellipseEditor() = default;
    ~ellipseEditor() override = default;

    void OnLBdown(HWND hwnd) override {
        SetCapture(hwnd);
        GetCursorPos(&ptStart);
        ScreenToClient(hwnd, &ptStart);
        ptCurrent = ptStart;
        ptPrev    = ptStart;
        hasPrev   = false;
        isPainting = true;
    }

    std::unique_ptr<shape> OnLBup(HWND hwnd) override {
        if (!isPainting) return nullptr;
        isPainting = false;
        hasPrev    = false;
        ReleaseCapture();

        POINT pt;
        GetCursorPos(&pt);
        ScreenToClient(hwnd, &pt);

        // mx1,my1=центр; mx2,my2=кут
        auto s = std::make_unique<EllipseShape>();
        s->set(ptStart.x, ptStart.y, pt.x, pt.y);
        return s;
    }

    void OnMouseMove(HWND hwnd, LPARAM lParam) override {
        if (!isPainting) return;
        ptCurrent.x = LOWORD(lParam);
        ptCurrent.y = HIWORD(lParam);

        HDC hdc = GetDC(hwnd);
        if (hasPrev) drawRubberEllipse(hdc, ptStart, ptPrev);
        drawRubberEllipse(hdc, ptStart, ptCurrent);
        ReleaseDC(hwnd, hdc);
        ptPrev  = ptCurrent;
        hasPrev = true;
    }

    void OnPaint(HDC hdc) override {
        if (isPainting)
            drawRubberEllipse(hdc, ptStart, ptCurrent);
    }
};
