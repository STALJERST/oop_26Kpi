#pragma once
#include <windows.h>
#include <commctrl.h>
#include "resource.h"


class Toolbar {
private:
    HWND hwndToolbar = nullptr;

public:
    Toolbar() = default;
    ~Toolbar() = default;

    HWND getHwnd() const { return hwndToolbar; }

    HWND create(HWND hwndParent) {
        INITCOMMONCONTROLSEX icex;
        icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icex.dwICC = ICC_BAR_CLASSES;
        InitCommonControlsEx(&icex);

        hwndToolbar = CreateWindowExW(
            0,
            TOOLBARCLASSNAMEW,
            nullptr,
            WS_CHILD | WS_VISIBLE | TBSTYLE_FLAT | TBSTYLE_TOOLTIPS | CCS_TOP,
            0, 0, 0, 0,
            hwndParent,
            (HMENU)10001,
            GetModuleHandle(nullptr),
            nullptr
        );

        if (!hwndToolbar) return nullptr;

        SendMessage(hwndToolbar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
        // розмір кнопок 32x32 пікселі
        SendMessage(hwndToolbar, TB_SETBUTTONSIZE, 0, MAKELPARAM(36, 34));

        TBBUTTON tbButtons[4] = {};

        // 1. Point
        tbButtons[0].iBitmap   = -1; // Без бітмапу, малюємо через CustomDraw
        tbButtons[0].idCommand = IDM_CREATE_POINT;
        tbButtons[0].fsState   = TBSTATE_ENABLED;
        tbButtons[0].fsStyle   = BTNS_CHECKGROUP;

        // 2. Line
        tbButtons[1].iBitmap   = -1;
        tbButtons[1].idCommand = IDM_CREATE_LINE;
        tbButtons[1].fsState   = TBSTATE_ENABLED;
        tbButtons[1].fsStyle   = BTNS_CHECKGROUP;

        // 3. Rect
        tbButtons[2].iBitmap   = -1;
        tbButtons[2].idCommand = IDM_CREATE_RECT;
        tbButtons[2].fsState   = TBSTATE_ENABLED;
        tbButtons[2].fsStyle   = BTNS_CHECKGROUP;

        // 4. Ellipse
        tbButtons[3].iBitmap   = -1;
        tbButtons[3].idCommand = IDM_CREATE_ELLIPSE;
        tbButtons[3].fsState   = TBSTATE_ENABLED;
        tbButtons[3].fsStyle   = BTNS_CHECKGROUP;

        SendMessage(hwndToolbar, TB_ADDBUTTONS, 4, (LPARAM)&tbButtons);
        SendMessage(hwndToolbar, TB_AUTOSIZE, 0, 0);

        return hwndToolbar;
    }

    void checkButton(int cmdId) {
        if (!hwndToolbar) return;
        SendMessage(hwndToolbar, TB_CHECKBUTTON, IDM_CREATE_POINT,   (LPARAM)(cmdId == IDM_CREATE_POINT));
        SendMessage(hwndToolbar, TB_CHECKBUTTON, IDM_CREATE_LINE,    (LPARAM)(cmdId == IDM_CREATE_LINE));
        SendMessage(hwndToolbar, TB_CHECKBUTTON, IDM_CREATE_RECT,    (LPARAM)(cmdId == IDM_CREATE_RECT));
        SendMessage(hwndToolbar, TB_CHECKBUTTON, IDM_CREATE_ELLIPSE, (LPARAM)(cmdId == IDM_CREATE_ELLIPSE));
    }

    void onResize() {
        if (hwndToolbar) {
            SendMessage(hwndToolbar, TB_AUTOSIZE, 0, 0);
        }
    }

    //малювання значка фігури
    void drawButtonGlyph(HDC hdc, int cmdId, const RECT& rc) {
        int cx = (rc.left + rc.right) / 2;
        int cy = (rc.top + rc.bottom) / 2;

        HPEN pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
        HPEN oldPen = (HPEN)SelectObject(hdc, pen);

        switch (cmdId) {
        case IDM_CREATE_POINT: {
            //квадрат
            HBRUSH br = CreateSolidBrush(RGB(0, 0, 0));
            HBRUSH oldBr = (HBRUSH)SelectObject(hdc, br);
            Rectangle(hdc, cx - 3, cy - 3, cx + 4, cy + 4);
            SelectObject(hdc, oldBr);
            DeleteObject(br);
            break;
        }
        case IDM_CREATE_LINE: {
            // лінія
            MoveToEx(hdc, cx - 8, cy + 8, nullptr);
            LineTo(hdc, cx + 8, cy - 8);
            break;
        }
        case IDM_CREATE_RECT: {
            // Прямокутник без заповнення
            HBRUSH nullBr = (HBRUSH)GetStockObject(NULL_BRUSH);
            HBRUSH oldBr = (HBRUSH)SelectObject(hdc, nullBr);
            Rectangle(hdc, cx - 8, cy - 6, cx + 8, cy + 6);
            SelectObject(hdc, oldBr);
            break;
        }
        case IDM_CREATE_ELLIPSE: {
            // Жовтий еліпс
            HBRUSH yelBr = CreateSolidBrush(RGB(255, 255, 0));
            HBRUSH oldBr = (HBRUSH)SelectObject(hdc, yelBr);
            Ellipse(hdc, cx - 9, cy - 7, cx + 9, cy + 7);
            SelectObject(hdc, oldBr);
            DeleteObject(yelBr);
            break;
        }
        }

        SelectObject(hdc, oldPen);
        DeleteObject(pen);
    }
};
