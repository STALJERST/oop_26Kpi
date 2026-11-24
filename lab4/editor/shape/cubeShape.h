#pragma once
#include "rectShape.h"
#include "lineShape.h"
#include <algorithm>

class CubeShape : public RectShape, public LineShape {
public:
    CubeShape() = default;
    ~CubeShape() override = default;

    void show(HDC hdc) override {
        long x1 = mx1, y1 = my1;
        long x2 = mx2, y2 = my2;

        long left   = std::min(x1, x2);
        long top    = std::min(y1, y2);
        long right  = std::max(x1, x2);
        long bottom = std::max(y1, y2);

        // Зсув для задньої грані
        long w = right - left;
        long h = bottom - top;
        long dx = w / 3;
        long dy = -h / 3;

        //  Передня грань куба
        RectShape::setCorners(left, top, right, bottom);
        RectShape::show(hdc);

        // Задня грань куба
        RectShape::setCorners(left + dx, top + dy, right + dx, bottom + dy);
        RectShape::show(hdc);

        //З'єднувальні бічні ребра
        // Верхнє ліве ребро
        LineShape::set(left, top, left + dx, top + dy);
        LineShape::show(hdc);

        // Верхнє праве ребро
        LineShape::set(right, top, right + dx, top + dy);
        LineShape::show(hdc);

        // Нижнє праве ребро
        LineShape::set(right, bottom, right + dx, bottom + dy);
        LineShape::show(hdc);

        // Нижнє ліве ребро
        LineShape::set(left, bottom, left + dx, bottom + dy);
        LineShape::show(hdc);

        // Відновлюємо координати
        shape::set(x1, y1, x2, y2);
    }
};
