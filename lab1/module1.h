#ifndef OOP_26KPI_MODULE1_H
#define OOP_26KPI_MODULE1_H

#include <windows.h>
#include "utils.h"

#define ID_BTN_YES 1001
#define ID_EDIT_TEXT 1002

static INT_PTR CALLBACK DialogWndProc1(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_INITDIALOG: {
            HINSTANCE hInst = (HINSTANCE)GetWindowLongPtrW(hWnd, GWLP_HINSTANCE);

            CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                          20, 20, 260, 25, hWnd, (HMENU)ID_EDIT_TEXT, hInst, NULL);

            CreateWindowW(L"BUTTON", L"Так", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                          50, 60, 80, 30, hWnd, (HMENU)ID_BTN_YES, hInst, NULL);

            CreateWindowW(L"BUTTON", L"Відміна", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                          170, 60, 80, 30, hWnd, (HMENU)IDCANCEL, hInst, NULL);
            return (INT_PTR)TRUE;
        }
        case WM_COMMAND: {
            WORD btnId = LOWORD(wParam);
            if (btnId == ID_BTN_YES) {
                wchar_t buffer[256];
                GetDlgItemTextW(hWnd, ID_EDIT_TEXT, buffer, 256);

                // Передаємо текст головному вікну через користувацьке повідомлення (наприклад, WM_USER + 10)
                HWND hParent = GetParent(hWnd);
                MessageBoxW(hParent, buffer, L"Введений текст", MB_OK); // Або SendMessage

                DestroyWindow(hWnd);
                return (INT_PTR)TRUE;
            } else if (btnId == IDCANCEL) {
                DestroyWindow(hWnd);
                return (INT_PTR)TRUE;
            }
            break;
        }
    }
    return (INT_PTR)FALSE;
}

void StartModule1(HINSTANCE hInstance, HWND hParent) {
    HWND hDlg = CreateInMemoryDialog(hInstance, hParent, DialogWndProc1, 0, L"Робота 1 - Ввід");
    PositionDialogAtBase(NULL, hDlg);
}
#endif // OOP_26KPI_MODULE1_H