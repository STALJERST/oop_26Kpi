#pragma once
#include "shapeEditor.h"
#include "shape/rectShape.h"
#include <memory>
#include <algorithm>

class rectEditor : public shapeEditor {
    POINT ptPrev{};
    bool  hasPrev = false;

    void rubber(HDC hdc, POINT center, POINT corner) {
        long x1 = 2 * center.x - corner.x;
        long y1 = 2 * center.y - corner.y;
        long x2 = corner.x;
        long y2 = corner.y;
        int l = (int)std::min(x1, x2), t = (int)std::min(y1, y2);
        int r = (int)std::max(x1, x2), b = (int)std::max(y1, y2);
        drawRubberRect(hdc, l, t, r, b);
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

        auto s = std::make_unique<RectShape>();
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
