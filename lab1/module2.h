#ifndef OOP_26KPI_MODULE2_H
#define OOP_26KPI_MODULE2_H

#include "utils.h"

#define MSG_MOD2_NEXT (WM_USER + 101)
#define MSG_MOD2_BACK (WM_USER + 102)
#define MSG_MOD2_DONE (WM_USER + 103)

#define ID_MOD2_BTN_NEXT 2001
#define ID_MOD2_BTN_BACK 2002
#define ID_MOD2_BTN_YES  2003

static LRESULT CALLBACK DlgProc2_Win1(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE:
            AddButton(hWnd, ID_MOD2_BTN_NEXT, L"Далі >",  40,  40, 100, 30);
            AddButton(hWnd, IDCANCEL,         L"Відміна", 160, 40, 100, 30);
            return 0;

        case WM_COMMAND: {
            if (LOWORD(wParam) == ID_MOD2_BTN_NEXT) {
                HWND hParent = GetParent(hWnd);
                PostMessageW(hParent, MSG_MOD2_NEXT, (WPARAM)hWnd, 0);
                return 0;
            } else if (LOWORD(wParam) == IDCANCEL) {
                DestroyWindow(hWnd);
                return 0;
            }
            break;
        }
    }
    return DefWindowProcW(hWnd, msg, wParam, lParam);
}

static LRESULT CALLBACK DlgProc2_Win2(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE:
            AddButton(hWnd, ID_MOD2_BTN_BACK, L"< Назад", 20,  40, 80, 30);
            AddButton(hWnd, ID_MOD2_BTN_YES,  L"Так",     110, 40, 80, 30);
            AddButton(hWnd, IDCANCEL,         L"Відміна", 200, 40, 80, 30);
            return 0;

        case WM_COMMAND: {
            if (LOWORD(wParam) == ID_MOD2_BTN_BACK) {
                HWND hParent = GetParent(hWnd);
                PostMessageW(hParent, MSG_MOD2_BACK, (WPARAM)hWnd, 0);
                return 0;
            } else if (LOWORD(wParam) == ID_MOD2_BTN_YES || LOWORD(wParam) == IDCANCEL) {
                DestroyWindow(hWnd);
                return 0;
            }
            break;
        }
    }
    return DefWindowProcW(hWnd, msg, wParam, lParam);
}

inline void StartModule2_Window1(HINSTANCE hInstance, HWND hParent, HWND hOldDlg) {
    HWND hDlg = CreateSimpleDialog(hInstance, hParent, DlgProc2_Win1, L"Робота 2 - Вікно 1", 300, 110);
    PositionDialogAtBase(hOldDlg, hDlg);
}

inline void StartModule2_Window2(HINSTANCE hInstance, HWND hParent, HWND hOldDlg) {
    HWND hDlg = CreateSimpleDialog(hInstance, hParent, DlgProc2_Win2, L"Робота 2 - Вікно 2", 300, 110);
    PositionDialogAtBase(hOldDlg, hDlg);
}
#endif // OOP_26KPI_MODULE2_H