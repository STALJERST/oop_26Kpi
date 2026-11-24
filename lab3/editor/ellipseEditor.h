#pragma once
#include "shapeEditor.h"
#include "shape/ellipseShape.h"
#include <memory>
#include <algorithm>


class ellipseEditor : public shapeEditor {
    POINT ptPrev{};
    bool  hasPrev = false;

    void rubber(HDC hdc, POINT p1, POINT p2) {
        int l = (int)std::min(p1.x, p2.x);
        int t = (int)std::min(p1.y, p2.y);
        int r = (int)std::max(p1.x, p2.x);
        int b = (int)std::max(p1.y, p2.y);
        drawRubberEllipse(hdc, l, t, r, b);
    }
public:
    void OnLBdown(HWND hwnd) override {
        SetCapture(hwnd);
        GetCursorPos(&ptStart);
        ScreenToClient(hwnd, &ptStart);
        ptCurrent = ptPrev = ptStart;
        hasPrev = false;
        isPainting = true;
    }

    std::unique_ptr<shape> OnLBup(HWND hwnd) override {
        if (!isPainting) return nullptr;
        isPainting = false;
        hasPrev = false;
        ReleaseCapture();

        POINT pt;
        GetCursorPos(&pt);
        ScreenToClient(hwnd, &pt);

        auto s = std::make_unique<EllipseShape>();
        s->set(ptStart.x, ptStart.y, pt.x, pt.y);
        return s;
    }

    void OnMouseMove(HWND hwnd, LPARAM lParam) override {
        if (!isPainting) return;
        ptCurrent = { LOWORD(lParam), HIWORD(lParam) };
        HDC hdc = GetDC(hwnd);
        if (hasPrev) rubber(hdc, ptStart, ptPrev);
        rubber(hdc, ptStart, ptCurrent);
        ReleaseDC(hwnd, hdc);
        ptPrev = ptCurrent;
        hasPrev = true;
    }

    void OnPaint(HDC hdc) override {
        if (isPainting) rubber(hdc, ptStart, ptCurrent);
    }
};
