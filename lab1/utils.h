#ifndef OOP_26KPI_UTILS_H
#define OOP_26KPI_UTILS_H

#include <windows.h>
#include <string>

inline LRESULT CALLBACK BaseDlgDispatcher(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_NCCREATE) {
        auto* cs = reinterpret_cast<CREATESTRUCTW*>(lParam);
        auto realProc = reinterpret_cast<WNDPROC>(cs->lpCreateParams);
        SetWindowLongPtrW(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(realProc));
        return CallWindowProcW(realProc, hWnd, msg, wParam, lParam);
    }
    return DefWindowProcW(hWnd, msg, wParam, lParam);
}

inline HWND CreateSimpleDialog(
    HINSTANCE hInstance,
    HWND hwndParent,
    WNDPROC wndProc,
    const wchar_t* title,
    int clientW = 300,
    int clientH = 110
) {
    const wchar_t* DLG_CLASS = L"Lab1SimpleDialogClass";

    static bool isRegistered = false;
    if (!isRegistered) {
        WNDCLASSW wc = {};
        wc.lpfnWndProc = BaseDlgDispatcher;
        wc.hInstance = hInstance;
        wc.lpszClassName = DLG_CLASS;
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
        RegisterClassW(&wc);
        isRegistered = true;
    }

    DWORD style = WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_VISIBLE;
    DWORD exStyle = WS_EX_DLGMODALFRAME;

    RECT rc = {0, 0, clientW, clientH};
    AdjustWindowRectEx(&rc, style, FALSE, exStyle);

    return CreateWindowExW(
        exStyle,
        DLG_CLASS,
        title,
        style,
        CW_USEDEFAULT, CW_USEDEFAULT,
        rc.right - rc.left,
        rc.bottom - rc.top,
        hwndParent,
        NULL,
        hInstance,
        reinterpret_cast<LPVOID>(wndProc)
    );
}

inline void PositionDialogAtBase(HWND hOldDlg, HWND hNewDlg) {
    if (hOldDlg && IsWindow(hOldDlg)) {
        RECT rc;
        GetWindowRect(hOldDlg, &rc);
        SetWindowPos(hNewDlg, NULL, rc.left, rc.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
        DestroyWindow(hOldDlg);
    } else {
        RECT rc;
        GetWindowRect(hNewDlg, &rc);
        int screenW = GetSystemMetrics(SM_CXSCREEN);
        int screenH = GetSystemMetrics(SM_CYSCREEN);
        int dlgW = rc.right - rc.left;
        int dlgH = rc.bottom - rc.top;
        SetWindowPos(hNewDlg, NULL, (screenW - dlgW) / 2, (screenH - dlgH) / 2, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
    }
}

inline void SetControlFont(HWND hCtrl) {
    SendMessageW(hCtrl, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);
}

inline HWND AddButton(HWND hParent, int id, const wchar_t* text, int x, int y, int w = 80, int h = 30) {
    HINSTANCE hInst = (HINSTANCE)GetWindowLongPtrW(hParent, GWLP_HINSTANCE);
    HWND hBtn = CreateWindowW(
        L"BUTTON", text,
        WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON,
        x, y, w, h,
        hParent, (HMENU)(INT_PTR)id, hInst, NULL
    );
    SetControlFont(hBtn);
    return hBtn;
}

inline HWND AddEdit(HWND hParent, int id, int x, int y, int w = 260, int h = 25, const wchar_t* defaultText = L"") {
    HINSTANCE hInst = (HINSTANCE)GetWindowLongPtrW(hParent, GWLP_HINSTANCE);
    HWND hEdit = CreateWindowW(
        L"EDIT", defaultText,
        WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP | ES_AUTOHSCROLL,
        x, y, w, h,
        hParent, (HMENU)(INT_PTR)id, hInst, NULL
    );
    SetControlFont(hEdit);
    return hEdit;
}

inline std::wstring GetItemText(HWND hDlg, int id) {
    int len = GetWindowTextLengthW(GetDlgItem(hDlg, id));
    if (len == 0) return L"";
    std::wstring text(len, L'\0');
    GetDlgItemTextW(hDlg, id, &text[0], len + 1);
    return text;
}

#endif //OOP_26KPI_UTILS_H