#pragma once
#include <windows.h>
#include "editor.h"
#include "shape/shape.h"
#include <memory>


class shapeEditor : public editor<shape> {
protected:
    POINT ptStart{};
    POINT ptCurrent{};
    bool  isPainting = false;

    void drawRubber(HDC hdc, int x1, int y1, int x2, int y2) {
        HPEN hPen    = CreatePen(PS_DOT, 1, RGB(0, 0, 0));  // пунктир чорний
        HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
        int oldROP   = SetROP2(hdc, R2_XORPEN);

        MoveToEx(hdc, x1, y1, nullptr);
        LineTo  (hdc, x2, y2);

        SetROP2(hdc, oldROP);
        SelectObject(hdc, hOldPen);
        DeleteObject(hPen);
    }

    void drawRubberEllipse(HDC hdc, int l, int t, int r, int b) {
        HPEN   hPen       = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
        HPEN   hOldPen    = (HPEN)SelectObject(hdc, hPen);
        HBRUSH hNullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
        HBRUSH hOldBrush  = (HBRUSH)SelectObject(hdc, hNullBrush);
        int    oldROP     = SetROP2(hdc, R2_XORPEN);

        Ellipse(hdc, l, t, r, b);

        SetROP2(hdc, oldROP);
        SelectObject(hdc, hOldBrush);
        SelectObject(hdc, hOldPen);
        DeleteObject(hPen);
    }

    void drawRubberRect(HDC hdc, int l, int t, int r, int b) {
        drawRubber(hdc, l, t, r, t);
        drawRubber(hdc, r, t, r, b);
        drawRubber(hdc, r, b, l, b);
        drawRubber(hdc, l, b, l, t);
    }

public:
    virtual ~shapeEditor() = default;
};
