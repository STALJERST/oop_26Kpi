#pragma once
#include "lineShape.h"
#include "ellipseShape.h"

class LineWithCirclesShape : public LineShape, public EllipseShape {
public:
    LineWithCirclesShape() = default;
    ~LineWithCirclesShape() override = default;

    void show(HDC hdc) override {

        long x1 = mx1, y1 = my1;
        long x2 = mx2, y2 = my2;

        LineShape::set(x1, y1, x2, y2);
        LineShape::show(hdc);

        const long r = 6; // радіус кружечків

        EllipseShape::set(x1 - r, y1 - r, x1 + r, y1 + r);
        EllipseShape::show(hdc);

        EllipseShape::set(x2 - r, y2 - r, x2 + r, y2 + r);
        EllipseShape::show(hdc);

        shape::set(x1, y1, x2, y2);
    }
};
