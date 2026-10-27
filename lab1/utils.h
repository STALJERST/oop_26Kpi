#ifndef OOP_26KPI_UTILS_H
#define OOP_26KPI_UTILS_H


HWND CreateInMemoryDialog(HINSTANCE hInstance, HWND hwndParent, DLGPROC dlgProc, LPARAM lParam, const wchar_t* title) {
    alignas(DWORD) BYTE buffer[1024] = {0};
    DLGTEMPLATE* pDlg = reinterpret_cast<DLGTEMPLATE*>(buffer);

    pDlg->style = WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_VISIBLE | DS_SETFONT | DS_MODALFRAME;
    pDlg->dwExtendedStyle = 0;
    pDlg->cdit = 0;
    pDlg->x = 0;
    pDlg->y = 0;
    pDlg->cx = 200;
    pDlg->cy = 100;

    wchar_t* pStr = reinterpret_cast<wchar_t*>(pDlg + 1);
    *pStr++ = 0;
    *pStr++ = 0;

    wcscpy_s(pStr, 50, title);
    pStr += wcslen(title) + 1;

    *reinterpret_cast<WORD*>(pStr) = 9;
    pStr = reinterpret_cast<wchar_t*>(reinterpret_cast<WORD*>(pStr) + 1);
    wcscpy_s(pStr, 50, L"Segoe UI");

    return CreateDialogIndirectParamW(hInstance, pDlg, hwndParent, dlgProc, lParam);
}

void PositionDialogAtBase(HWND hOldDlg, HWND hNewDlg) {
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

#endif //OOP_26KPI_UTILS_H