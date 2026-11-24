#pragma once
#include "shape.h"

class LineShape : virtual public shape {
public:
    LineShape() = default;
    ~LineShape() override = default;

    void show(HDC hdc) override {
        HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
        HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

        MoveToEx(hdc, (int)mx1, (int)my1, nullptr);
        LineTo  (hdc, (int)mx2, (int)my2);

        SelectObject(hdc, hOldPen);
        DeleteObject(hPen);
    }
};
