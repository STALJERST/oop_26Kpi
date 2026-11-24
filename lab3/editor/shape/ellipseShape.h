#pragma once
#include "shape.h"
#include <algorithm>

class EllipseShape : public shape {
public:
    EllipseShape() = default;
    ~EllipseShape() override = default;
    void show(HDC hdc) override {
        int l = (int)std::min(mx1, mx2);
        int t = (int)std::min(my1, my2);
        int r = (int)std::max(mx1, mx2);
        int b = (int)std::max(my1, my2);

        HBRUSH hBrush   = CreateSolidBrush(RGB(255, 255, 0)); // жовтий
        HBRUSH hOldBr   = (HBRUSH)SelectObject(hdc, hBrush);
        HPEN   hPen     = CreatePen(PS_SOLID, 1, RGB(0,0,0));
        HPEN   hOldPen  = (HPEN)SelectObject(hdc, hPen);

        Ellipse(hdc, l, t, r, b);

        SelectObject(hdc, hOldPen);
        SelectObject(hdc, hOldBr);
        DeleteObject(hPen);
        DeleteObject(hBrush);
    }
};
