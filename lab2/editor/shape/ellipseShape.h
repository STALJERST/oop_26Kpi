#pragma once
#include "shape.h"
#include <windows.h>
#include <algorithm>


class EllipseShape : public shape {
public:
    EllipseShape() = default;
    ~EllipseShape() override = default;

    void show(HDC hdc) override {
      
        long x1 = 2*mx1 - mx2;
        long y1 = 2*my1 - my2;
        long x2 = mx2;
        long y2 = my2;

        int left   = (int)std::min(x1, x2);
        int top    = (int)std::min(y1, y2);
        int right  = (int)std::max(x1, x2);
        int bottom = (int)std::max(y1, y2);

        HBRUSH hNullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
        HBRUSH hOldBrush  = (HBRUSH)SelectObject(hdc, hNullBrush);

        HPEN hPen    = CreatePen(PS_SOLID, 1, RGB(0,0,0));
        HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

        Ellipse(hdc, left, top, right, bottom);

        SelectObject(hdc, hOldPen);
        SelectObject(hdc, hOldBrush);
        DeleteObject(hPen);
    }
};
