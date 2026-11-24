#pragma once
#include "shapeEditor.h"
#include "shape/lineShape.h"
#include <memory>

class lineEditor : public shapeEditor {
    POINT ptPrev{};
    bool  hasPrev = false;
public:
    lineEditor() = default;
    ~lineEditor() override = default;

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

        auto s = std::make_unique<LineShape>();
        s->set(ptStart.x, ptStart.y, pt.x, pt.y);
        return s;
    }

    void OnMouseMove(HWND hwnd, LPARAM lParam) override {
        if (!isPainting) return;
        ptCurrent.x = LOWORD(lParam);
        ptCurrent.y = HIWORD(lParam);


        HDC hdc = GetDC(hwnd);
        if (hasPrev)
            drawRubber(hdc, ptStart.x, ptStart.y, ptPrev.x, ptPrev.y);
        drawRubber(hdc, ptStart.x, ptStart.y, ptCurrent.x, ptCurrent.y);
        ReleaseDC(hwnd, hdc);
        ptPrev  = ptCurrent;
        hasPrev = true;
    }

    void OnPaint(HDC hdc) override {
        if (isPainting)
            drawRubber(hdc, ptStart.x, ptStart.y, ptCurrent.x, ptCurrent.y);
    }
};
