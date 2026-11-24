#pragma once
#include "shape.h"

class PointShape : public shape {
public:
    PointShape() = default;
    ~PointShape() override = default;
    void show(HDC hdc) override {
        HBRUSH hBr  = CreateSolidBrush(RGB(0,0,0));
        HBRUSH hOld = (HBRUSH)SelectObject(hdc, hBr);
        Rectangle(hdc, (int)mx1-2, (int)my1-2, (int)mx1+2, (int)my1+2);
        SelectObject(hdc, hOld);
        DeleteObject(hBr);
    }
};
