#include <windows.h>
#include "module1.h"
#include "module2.h"

#define IDM_WORK1 101
#define IDM_WORK2 102

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: {
            HMENU hMenu = CreateMenu();
            HMENU hSubMenu = CreatePopupMenu();
            AppendMenuW(hSubMenu, MF_STRING, IDM_WORK1, L"Робота1");
            AppendMenuW(hSubMenu, MF_STRING, IDM_WORK2, L"Робота2");
            AppendMenuW(hMenu, MF_POPUP, (UINT_PTR)hSubMenu, L"Варіанти");
            SetMenu(hwnd, hMenu);
            return 0;
        }

        case WM_COMMAND: {
            HINSTANCE hInst = (HINSTANCE)GetWindowLongPtrW(hwnd, GWLP_HINSTANCE);
            if (LOWORD(wParam) == IDM_WORK1) {
                StartModule1(hInst, hwnd);
            }
            else if (LOWORD(wParam) == IDM_WORK2) {
                StartModule2_Window1(hInst, hwnd, NULL);
            }
            return 0;
        }

        case MSG_MOD2_NEXT: {
            HWND hOldDlg = (HWND)wParam;
            HINSTANCE hInst = (HINSTANCE)GetWindowLongPtrW(hwnd, GWLP_HINSTANCE);
            StartModule2_Window2(hInst, hwnd, hOldDlg);
            return 0;
        }

        case MSG_MOD2_BACK: {
            HWND hOldDlg = (HWND)wParam;
            HINSTANCE hInst = (HINSTANCE)GetWindowLongPtrW(hwnd, GWLP_HINSTANCE);
            StartModule2_Window1(hInst, hwnd, hOldDlg);
            return 0;
        }

        case WM_DESTROY: {
            PostQuitMessage(0);
            return 0;
        }
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"Lab2MainWindow";

    WNDCLASSW wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClassW(&wc);

    HWND hwnd = CreateWindowExW(
        0, CLASS_NAME, L"Лабораторна 1 - Головне Вікно",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        nullptr, nullptr, hInstance, nullptr
    );

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};
    while (GetMessageW(&msg, NULL, 0, 0)) {
        if (!IsDialogMessage(GetActiveWindow(), &msg)) {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    }

    return 0;
}