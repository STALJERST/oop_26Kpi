#ifndef OOP_26KPI_MODULE1_H
#define OOP_26KPI_MODULE1_H

#include <windows.h>
#include "utils.h"

#define ID_MOD1_BTN_YES 1001
#define ID_MOD1_EDIT    1002

static LRESULT CALLBACK DialogWndProc1(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: {
            HWND hEdit = AddEdit(hWnd, ID_MOD1_EDIT, 20, 20, 260, 25);
            AddButton(hWnd, ID_MOD1_BTN_YES, L"Так",     50,  60, 80, 30);
            AddButton(hWnd, IDCANCEL,        L"Відміна", 170, 60, 80, 30);
            SetFocus(hEdit);
            return 0;
        }
        case WM_COMMAND: {
            WORD btnId = LOWORD(wParam);
            if (btnId == ID_MOD1_BTN_YES) {
                std::wstring text = GetItemText(hWnd, ID_MOD1_EDIT);

                HWND hParent = GetParent(hWnd);
                MessageBoxW(hParent, text.c_str(), L"Введений текст", MB_OK);

                DestroyWindow(hWnd);
                return 0;
            } else if (btnId == IDCANCEL) {
                DestroyWindow(hWnd);
                return 0;
            }
            break;
        }
    }
    return DefWindowProcW(hWnd, msg, wParam, lParam);
}

inline void StartModule1(HINSTANCE hInstance, HWND hParent) {
    HWND hDlg = CreateSimpleDialog(hInstance, hParent, DialogWndProc1, L"Робота 1 - Ввід", 300, 110);
    PositionDialogAtBase(NULL, hDlg);
}
#endif // OOP_26KPI_MODULE1_H