#include <windows.h>
#include "resource.h"
#include "shapeObjEditor.h"
#include "editor/pointEditor.h"
#include "editor/lineEditor.h"
#include "editor/rectEditor.h"
#include "editor/ellipseEditor.h"

// Глобальний менеджер фігур
shapeObjEditor g_manager;

// Поточний тип: 0=нічого,1=точка,2=лінія,3=прямокутник,4=еліпс
int g_currentType = 0;

//Дескриптори пунктів меню "Об'єкти"
HMENU g_hSubMenuO = nullptr;

void UpdateMenuCheck(HWND hwnd) {
    if (!g_hSubMenuO) return;
    CheckMenuItem(g_hSubMenuO, IDM_CREATE_POINT,   MF_BYCOMMAND | MF_UNCHECKED);
    CheckMenuItem(g_hSubMenuO, IDM_CREATE_LINE,    MF_BYCOMMAND | MF_UNCHECKED);
    CheckMenuItem(g_hSubMenuO, IDM_CREATE_RECT,    MF_BYCOMMAND | MF_UNCHECKED);
    CheckMenuItem(g_hSubMenuO, IDM_CREATE_ELLIPSE, MF_BYCOMMAND | MF_UNCHECKED);
    // Ставимо потрібну
    switch (g_currentType) {
        case 1: CheckMenuItem(g_hSubMenuO, IDM_CREATE_POINT,   MF_BYCOMMAND | MF_CHECKED); break;
        case 2: CheckMenuItem(g_hSubMenuO, IDM_CREATE_LINE,    MF_BYCOMMAND | MF_CHECKED); break;
        case 3: CheckMenuItem(g_hSubMenuO, IDM_CREATE_RECT,    MF_BYCOMMAND | MF_CHECKED); break;
        case 4: CheckMenuItem(g_hSubMenuO, IDM_CREATE_ELLIPSE, MF_BYCOMMAND | MF_CHECKED); break;
    }
    DrawMenuBar(hwnd);
}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {

    // Створення меню при ініціалізації вікна
    case WM_CREATE: {
        HMENU hMenu     = CreateMenu();
        HMENU hSubMenuF = CreatePopupMenu();   // Файл
        g_hSubMenuO     = CreatePopupMenu();   // Об'єкти
        HMENU hSubMenuH = CreatePopupMenu();   // Довідка

        // Меню Файл
        AppendMenuW(hSubMenuF, MF_STRING, IDM_FILE_CLEAR, L"Очистити");
        AppendMenuW(hSubMenuF, MF_SEPARATOR, 0, nullptr);
        AppendMenuW(hSubMenuF, MF_STRING, IDM_FILE_EXIT,  L"Вихід");

        // Меню Об'єкти
        AppendMenuW(g_hSubMenuO, MF_STRING, IDM_CREATE_POINT,   L"Крапка");
        AppendMenuW(g_hSubMenuO, MF_STRING, IDM_CREATE_LINE,    L"Лінія");
        AppendMenuW(g_hSubMenuO, MF_STRING, IDM_CREATE_RECT,    L"Прямокутник");
        AppendMenuW(g_hSubMenuO, MF_STRING, IDM_CREATE_ELLIPSE, L"Еліпс");

        // Меню Довідка
        AppendMenuW(hSubMenuH, MF_STRING | MF_GRAYED, 0, L"Про програму");

        // головне меню: Файл  Об'єкти  Довідка
        AppendMenuW(hMenu, MF_POPUP, (UINT_PTR)hSubMenuF,  L"Файл");
        AppendMenuW(hMenu, MF_POPUP, (UINT_PTR)g_hSubMenuO, L"Об'єкти");
        AppendMenuW(hMenu, MF_POPUP, (UINT_PTR)hSubMenuH,  L"Довідка");
        SetMenu(hwnd, hMenu);
        break;
    }

    //OnInitMenuPopup: оновити позначку перед показом меню
    case WM_INITMENUPOPUP: {
        HMENU hOpenMenu = (HMENU)wParam;
        if (hOpenMenu == g_hSubMenuO)
            UpdateMenuCheck(hwnd);
        break;
    }

    //Команди меню
    case WM_COMMAND: {
        int id = LOWORD(wParam);
        switch (id) {
        case IDM_CREATE_POINT:
            g_currentType = 1;
            g_manager.setEditor(std::make_unique<pointEditor>());
            break;
        case IDM_CREATE_LINE:
            g_currentType = 2;
            g_manager.setEditor(std::make_unique<lineEditor>());
            break;
        case IDM_CREATE_RECT:
            g_currentType = 3;
            g_manager.setEditor(std::make_unique<rectEditor>());
            break;
        case IDM_CREATE_ELLIPSE:
            g_currentType = 4;
            g_manager.setEditor(std::make_unique<ellipseEditor>());
            break;
        case IDM_FILE_CLEAR:
            g_manager.clear();
            InvalidateRect(hwnd, nullptr, TRUE);
            break;
        case IDM_FILE_EXIT:
            DestroyWindow(hwnd);
            break;
        }
        break;
    }

    //Мишка
    case WM_LBUTTONDOWN:
        g_manager.OnLBdown(hwnd);
        return 0;

    case WM_MOUSEMOVE:
        g_manager.OnMouseMove(hwnd, lParam);
        return 0;

    case WM_LBUTTONUP:
        g_manager.OnLBup(hwnd);
        InvalidateRect(hwnd, nullptr, TRUE);
        return 0;

    //Малювання
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        g_manager.OnPaint(hdc);
        EndPaint(hwnd, &ps);
        return 0;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"Lab2GraphEditor";

    WNDCLASSW wc      = {};
    wc.lpfnWndProc    = WindowProc;
    wc.hInstance      = hInstance;
    wc.lpszClassName  = CLASS_NAME;
    wc.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor        = LoadCursor(nullptr, IDC_CROSS);
    RegisterClassW(&wc);

    HWND hwnd = CreateWindowExW(
        0, CLASS_NAME,
        L"Графічний редактор  –  Варіант Ж=18",
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
