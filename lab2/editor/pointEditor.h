#pragma once
#include "shapeEditor.h"
#include "shape/pointShape.h"
#include <memory>


class pointEditor : public shapeEditor {
public:
    pointEditor() = default;
    ~pointEditor() override = default;

    void OnLBdown(HWND hwnd) override {
        SetCapture(hwnd);
        GetCursorPos(&ptStart);
        ScreenToClient(hwnd, &ptStart);
        ptCurrent = ptStart;
        isPainting = true;
    }

    std::unique_ptr<shape> OnLBup(HWND hwnd) override {
        if (!isPainting) return nullptr;
        isPainting = false;
        ReleaseCapture();

        POINT pt;
        GetCursorPos(&pt);
        ScreenToClient(hwnd, &pt);

        auto s = std::make_unique<PointShape>();
        s->set(pt.x, pt.y, pt.x, pt.y);
        return s;
    }

    void OnMouseMove(HWND hwnd, LPARAM lParam) override {
        if (!isPainting) return;
        ptCurrent.x = LOWORD(lParam);
        ptCurrent.y = HIWORD(lParam);
    }

    void OnPaint(HDC hdc) override {
        // крапка  гумовий слід не потрібен
    }
};
