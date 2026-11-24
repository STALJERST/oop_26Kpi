#pragma once
#include "shapeEditor.h"
#include "shape/rectShape.h"
#include <memory>


class rectEditor : public shapeEditor {
    POINT ptPrev{};
    bool  hasPrev = false;

    // малює контур прямокутника як гумовий слід (XOR)
    void drawRubberRect(HDC hdc, POINT a, POINT b) {
        drawRubber(hdc, a.x, a.y, b.x, a.y);
        drawRubber(hdc, b.x, a.y, b.x, b.y);
        drawRubber(hdc, b.x, b.y, a.x, b.y);
        drawRubber(hdc, a.x, b.y, a.x, a.y);
    }

public:
    rectEditor() = default;
    ~rectEditor() override = default;

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

        auto s = std::make_unique<RectShape>();
        s->set(ptStart.x, ptStart.y, pt.x, pt.y);
        return s;
    }

    void OnMouseMove(HWND hwnd, LPARAM lParam) override {
        if (!isPainting) return;
        ptCurrent.x = LOWORD(lParam);
        ptCurrent.y = HIWORD(lParam);

        HDC hdc = GetDC(hwnd);
        if (hasPrev) drawRubberRect(hdc, ptStart, ptPrev);
        drawRubberRect(hdc, ptStart, ptCurrent);
        ReleaseDC(hwnd, hdc);
        ptPrev  = ptCurrent;
        hasPrev = true;
    }

    void OnPaint(HDC hdc) override {
        if (isPainting)
            drawRubberRect(hdc, ptStart, ptCurrent);
    }
};
