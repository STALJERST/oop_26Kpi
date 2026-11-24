#pragma once
#include "shape.h"

class LineShape : public shape {
public:
    LineShape() = default;
    ~LineShape() override = default;
    void show(HDC hdc) override {
        MoveToEx(hdc, (int)mx1, (int)my1, nullptr);
        LineTo  (hdc, (int)mx2, (int)my2);
    }
};
