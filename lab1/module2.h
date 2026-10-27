#ifndef OOP_26KPI_MODULE2_H
#define OOP_26KPI_MODULE2_H

#include "utils.h"

#define MSG_MOD2_NEXT (WM_USER + 101)
#define MSG_MOD2_BACK (WM_USER + 102)
#define MSG_MOD2_DONE (WM_USER + 103)

#define ID_BTN_NEXT 2001
#define ID_BTN_BACK 2002
#define ID_BTN_YES  2003

static INT_PTR CALLBACK DlgProc2_Win1(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_INITDIALOG: {
            HINSTANCE hInst = (HINSTANCE)GetWindowLongPtrW(hWnd, GWLP_HINSTANCE);
            CreateWindowW(L"BUTTON", L"Далі >", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                          40, 50, 100, 30, hWnd, (HMENU)ID_BTN_NEXT, hInst, NULL);
            CreateWindowW(L"BUTTON", L"Відміна", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                          160, 50, 100, 30, hWnd, (HMENU)IDCANCEL, hInst, NULL);
            return (INT_PTR)TRUE;
        }
        case WM_COMMAND: {
            if (LOWORD(wParam) == ID_BTN_NEXT) {
                HWND hParent = GetParent(hWnd);
                PostMessageW(hParent, MSG_MOD2_NEXT, (WPARAM)hWnd, 0); // Медіатору
                return (INT_PTR)TRUE;
            } else if (LOWORD(wParam) == IDCANCEL) {
                DestroyWindow(hWnd);
                return (INT_PTR)TRUE;
            }
            break;
        }
    }
    return (INT_PTR)FALSE;
}

static INT_PTR CALLBACK DlgProc2_Win2(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_INITDIALOG: {
            HINSTANCE hInst = (HINSTANCE)GetWindowLongPtrW(hWnd, GWLP_HINSTANCE);
            CreateWindowW(L"BUTTON", L"< Назад", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                          20, 50, 80, 30, hWnd, (HMENU)ID_BTN_BACK, hInst, NULL);
            CreateWindowW(L"BUTTON", L"Так", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                          110, 50, 80, 30, hWnd, (HMENU)ID_BTN_YES, hInst, NULL);
            CreateWindowW(L"BUTTON", L"Відміна", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                          200, 50, 80, 30, hWnd, (HMENU)IDCANCEL, hInst, NULL);
            return (INT_PTR)TRUE;
        }
        case WM_COMMAND: {
            if (LOWORD(wParam) == ID_BTN_BACK) {
                HWND hParent = GetParent(hWnd);
                PostMessageW(hParent, MSG_MOD2_BACK, (WPARAM)hWnd, 0);
                return (INT_PTR)TRUE;
            } else if (LOWORD(wParam) == ID_BTN_YES || LOWORD(wParam) == IDCANCEL) {
                DestroyWindow(hWnd);
                return (INT_PTR)TRUE;
            }
            break;
        }
    }
    return (INT_PTR)FALSE;
}

void StartModule2_Window1(HINSTANCE hInstance, HWND hParent, HWND hOldDlg) {
    HWND hDlg = CreateInMemoryDialog(hInstance, hParent, DlgProc2_Win1, 0, L"Робота 2 - Вікно 1");
    PositionDialogAtBase(hOldDlg, hDlg);
}

void StartModule2_Window2(HINSTANCE hInstance, HWND hParent, HWND hOldDlg) {
    HWND hDlg = CreateInMemoryDialog(hInstance, hParent, DlgProc2_Win2, 0, L"Робота 2 - Вікно 2");
    PositionDialogAtBase(hOldDlg, hDlg);
}
#endif // OOP_26KPI_MODULE2_H