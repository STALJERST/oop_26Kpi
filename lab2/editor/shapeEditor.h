#pragma once
#include <windows.h>
#include "editor.h"
#include "shape/shape.h"
#include <memory>

class shapeEditor : public editor<shape> {
protected:
    POINT ptStart{};   // координата натискання LB
    POINT ptCurrent{}; // поточна координата миші
    bool  isPainting = false;


    void drawRubber(HDC hdc, int x1, int y1, int x2, int y2) {
        HPEN hPen    = CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
        HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
        int oldROP   = SetROP2(hdc, R2_XORPEN);

        MoveToEx(hdc, x1, y1, nullptr);
        LineTo  (hdc, x2, y2);

        SetROP2(hdc, oldROP);
        SelectObject(hdc, hOldPen);
        DeleteObject(hPen);
    }

public:
    virtual ~shapeEditor() = default;
};
