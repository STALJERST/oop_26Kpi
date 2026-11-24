#include <windows.h>
#include "main.h"

// єдиний екземпляр класу вікна
static MainWindow g_app;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        return g_app.OnCreate(hwnd);

    case WM_COMMAND:
        return g_app.OnCommand(hwnd, wParam, lParam);

    case WM_NOTIFY:
        return g_app.OnNotify(hwnd, wParam, lParam);

    case WM_LBUTTONDOWN:
        return g_app.OnLButtonDown(hwnd);

    case WM_MOUSEMOVE:
        return g_app.OnMouseMove(hwnd, lParam);

    case WM_LBUTTONUP:
        return g_app.OnLButtonUp(hwnd);

    case WM_PAINT:
        return g_app.OnPaint(hwnd);

    case WM_SIZE:
        return g_app.OnSize(hwnd, wParam, lParam);

    case WM_DESTROY:
        return g_app.OnDestroy(hwnd);
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"Lab3MainWindowClass";

    WNDCLASSW wc = {};
    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor       = LoadCursor(nullptr, IDC_CROSS);

    RegisterClassW(&wc);

    HWND hwnd = CreateWindowExW(
        0, CLASS_NAME,
        L"Лабораторна 3 (Ж=19)",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 900, 650,
        nullptr, nullptr, hInstance, nullptr
    );

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg = {};
    while (GetMessageW(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    return 0;
}
