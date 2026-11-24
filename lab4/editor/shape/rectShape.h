#pragma once
#include "shape.h"
#include <algorithm>

class RectShape : virtual public shape {
public:
    RectShape() = default;
    ~RectShape() override = default;

    // Допоміжний метод: встановити габарити за кутами
    void setCorners(long x1, long y1, long x2, long y2) {
        long cx = (x1 + x2) / 2;
        long cy = (y1 + y2) / 2;
        set(cx, cy, x2, y2);
    }

    void show(HDC hdc) override {
        long left   = 2 * mx1 - mx2;
        long top    = 2 * my1 - my2;
        long right  = mx2;
        long bottom = my2;

        int l = (int)std::min(left,  right);
        int t = (int)std::min(top,   bottom);
        int r = (int)std::max(left,  right);
        int b = (int)std::max(top,   bottom);

        HBRUSH hNullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
        HBRUSH hOldBrush  = (HBRUSH)SelectObject(hdc, hNullBrush);
        HPEN   hPen       = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
        HPEN   hOldPen    = (HPEN)SelectObject(hdc, hPen);

        Rectangle(hdc, l, t, r, b);

        SelectObject(hdc, hOldPen);
        SelectObject(hdc, hOldBrush);
        DeleteObject(hPen);
    }
};
