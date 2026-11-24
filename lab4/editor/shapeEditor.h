#pragma once
#include <windows.h>
#include "editor.h"
#include "shape/shape.h"
#include <memory>
#include <algorithm>


class shapeEditor : public editor<shape> {
protected:
    POINT ptStart{};
    POINT ptCurrent{};
    bool  isPainting = false;

    // Малює один пунктирний відрізок у режимі інвертування (XOR)
    void drawRubberLine(HDC hdc, int x1, int y1, int x2, int y2) {
        HPEN hPen    = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
        HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
        int oldROP   = SetROP2(hdc, R2_NOTXORPEN);

        MoveToEx(hdc, x1, y1, nullptr);
        LineTo  (hdc, x2, y2);

        SetROP2(hdc, oldROP);
        SelectObject(hdc, hOldPen);
        DeleteObject(hPen);
    }

    // Малює пунктирний прямокутник
    void drawRubberRect(HDC hdc, int l, int t, int r, int b) {
        drawRubberLine(hdc, l, t, r, t);
        drawRubberLine(hdc, r, t, r, b);
        drawRubberLine(hdc, r, b, l, b);
        drawRubberLine(hdc, l, b, l, t);
    }

    // Малює пунктирний еліпс
    void drawRubberEllipse(HDC hdc, int l, int t, int r, int b) {
        HPEN   hPen       = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
        HPEN   hOldPen    = (HPEN)SelectObject(hdc, hPen);
        HBRUSH hNullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
        HBRUSH hOldBrush  = (HBRUSH)SelectObject(hdc, hNullBrush);
        int    oldROP     = SetROP2(hdc, R2_NOTXORPEN);

        Ellipse(hdc, l, t, r, b);

        SetROP2(hdc, oldROP);
        SelectObject(hdc, hOldBrush);
        SelectObject(hdc, hOldPen);
        DeleteObject(hPen);
    }

    // Малює лінію з кружечками
    void drawRubberLineWithCircles(HDC hdc, int x1, int y1, int x2, int y2) {
        drawRubberLine(hdc, x1, y1, x2, y2);
        const int r = 6;
        drawRubberEllipse(hdc, x1 - r, y1 - r, x1 + r, y1 + r);
        drawRubberEllipse(hdc, x2 - r, y2 - r, x2 + r, y2 + r);
    }

    // Малює каркас куба
    void drawRubberCube(HDC hdc, int x1, int y1, int x2, int y2) {
        int left   = std::min(x1, x2);
        int top    = std::min(y1, y2);
        int right  = std::max(x1, x2);
        int bottom = std::max(y1, y2);

        int w = right - left;
        int h = bottom - top;
        int dx = w / 3;
        int dy = -h / 3;

        // Передня грань
        drawRubberRect(hdc, left, top, right, bottom);
        // Задня грань
        drawRubberRect(hdc, left + dx, top + dy, right + dx, bottom + dy);
        // Ребра
        drawRubberLine(hdc, left, top, left + dx, top + dy);
        drawRubberLine(hdc, right, top, right + dx, top + dy);
        drawRubberLine(hdc, right, bottom, right + dx, bottom + dy);
        drawRubberLine(hdc, left, bottom, left + dx, bottom + dy);
    }

public:
    virtual ~shapeEditor() = default;
};
