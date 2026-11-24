#pragma once
#include "shape.h"
#include <windows.h>

class RectShape : public shape {
public:
    RectShape() = default;
    ~RectShape() override = default;

    void show(HDC hdc) override {
       
        HBRUSH hNullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
        HBRUSH hOldBrush  = (HBRUSH)SelectObject(hdc, hNullBrush);

        HPEN hPen    = CreatePen(PS_SOLID, 1, RGB(0,0,0));
        HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

        Rectangle(hdc, (int)mx1, (int)my1, (int)mx2, (int)my2);

        SelectObject(hdc, hOldPen);
        SelectObject(hdc, hOldBrush);
        DeleteObject(hPen);
    }
};
