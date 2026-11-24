#pragma once
#include <windows.h>
#include <commctrl.h>
#include <memory>

#include "resource.h"
#include "shapeObjEditor.h"
#include "toolbar.h"
#include "editor/pointEditor.h"
#include "editor/lineEditor.h"
#include "editor/rectEditor.h"
#include "editor/ellipseEditor.h"


class MainWindow {
private:
    HWND m_hwnd = nullptr;
    shapeObjEditor m_shapeManager;
    Toolbar m_toolbar;
    int m_currentType = 0; // 0=none, 1=point, 2=line, 3=rect, 4=ellipse

    void updateTitle() {
        const wchar_t* shapeName = L"Не обрано";
        switch (m_currentType) {
        case 1: shapeName = L"Крапка"; break;
        case 2: shapeName = L"Лінія"; break;
        case 3: shapeName = L"Прямокутник"; break;
        case 4: shapeName = L"Еліпс"; break;
        }

        wchar_t title[256];
        wsprintfW(title, L"Лабораторна 3 (Ж=19) - Поточний об'єкт: %s", shapeName);
        SetWindowTextW(m_hwnd, title);
    }

    void selectShapeType(int type) {
        m_currentType = type;
        switch (type) {
        case 1:
            m_shapeManager.setEditor(std::make_unique<pointEditor>());
            m_toolbar.checkButton(IDM_CREATE_POINT);
            break;
        case 2:
            m_shapeManager.setEditor(std::make_unique<lineEditor>());
            m_toolbar.checkButton(IDM_CREATE_LINE);
            break;
        case 3:
            m_shapeManager.setEditor(std::make_unique<rectEditor>());
            m_toolbar.checkButton(IDM_CREATE_RECT);
            break;
        case 4:
            m_shapeManager.setEditor(std::make_unique<ellipseEditor>());
            m_toolbar.checkButton(IDM_CREATE_ELLIPSE);
            break;
        }
        updateTitle();
    }

public:
    MainWindow() = default;

    HWND getHwnd() const { return m_hwnd; }

    LRESULT OnCreate(HWND hwnd) {
        m_hwnd = hwnd;

        // Меню
        HMENU hMenu = CreateMenu();
        HMENU hSubMenuFile = CreatePopupMenu();
        HMENU hSubMenuObjects = CreatePopupMenu();
        HMENU hSubMenuHelp = CreatePopupMenu();

        AppendMenuW(hSubMenuFile, MF_STRING, IDM_FILE_CLEAR, L"Очистити");
        AppendMenuW(hSubMenuFile, MF_SEPARATOR, 0, nullptr);
        AppendMenuW(hSubMenuFile, MF_STRING, IDM_FILE_EXIT, L"Вихід");

        AppendMenuW(hSubMenuObjects, MF_STRING, IDM_CREATE_POINT,   L"Крапка");
        AppendMenuW(hSubMenuObjects, MF_STRING, IDM_CREATE_LINE,    L"Лінія");
        AppendMenuW(hSubMenuObjects, MF_STRING, IDM_CREATE_RECT,    L"Прямокутник");
        AppendMenuW(hSubMenuObjects, MF_STRING, IDM_CREATE_ELLIPSE, L"Еліпс");

        AppendMenuW(hSubMenuHelp, MF_STRING | MF_GRAYED, 0, L"Про програму");

        AppendMenuW(hMenu, MF_POPUP, (UINT_PTR)hSubMenuFile,    L"Файл");
        AppendMenuW(hMenu, MF_POPUP, (UINT_PTR)hSubMenuObjects, L"Об'єкти");
        AppendMenuW(hMenu, MF_POPUP, (UINT_PTR)hSubMenuHelp,    L"Довідка");
        SetMenu(hwnd, hMenu);

        //Toolbar
        m_toolbar.create(hwnd);

        // Початковий заголовок
        updateTitle();
        return 0;
    }

    LRESULT OnCommand(HWND hwnd, WPARAM wParam, LPARAM lParam) {
        int id = LOWORD(wParam);
        switch (id) {
        case IDM_CREATE_POINT:
            selectShapeType(1);
            break;
        case IDM_CREATE_LINE:
            selectShapeType(2);
            break;
        case IDM_CREATE_RECT:
            selectShapeType(3);
            break;
        case IDM_CREATE_ELLIPSE:
            selectShapeType(4);
            break;
        case IDM_FILE_CLEAR:
            m_shapeManager.clear();
            InvalidateRect(hwnd, nullptr, TRUE);
            break;
        case IDM_FILE_EXIT:
            DestroyWindow(hwnd);
            break;
        }
        return 0;
    }

    //
    LRESULT OnNotify(HWND hwnd, WPARAM wParam, LPARAM lParam) {
        LPNMHDR lpnm = (LPNMHDR)lParam;

        //Tooltips
        if (lpnm->code == TTN_GETDISPINFOW) {
            LPNMTTDISPINFOW lpdi = (LPNMTTDISPINFOW)lParam;
            switch (lpdi->hdr.idFrom) {
            case IDM_CREATE_POINT:   lpdi->lpszText = (LPWSTR)L"Крапка"; break;
            case IDM_CREATE_LINE:    lpdi->lpszText = (LPWSTR)L"Лінія"; break;
            case IDM_CREATE_RECT:    lpdi->lpszText = (LPWSTR)L"Прямокутник"; break;
            case IDM_CREATE_ELLIPSE: lpdi->lpszText = (LPWSTR)L"Еліпс"; break;
            }
            return 0;
        }

        if (lpnm->code == NM_CUSTOMDRAW && lpnm->hwndFrom == m_toolbar.getHwnd()) {
            LPNMTBCUSTOMDRAW lpNMCustomDraw = (LPNMTBCUSTOMDRAW)lParam;
            switch (lpNMCustomDraw->nmcd.dwDrawStage) {
            case CDDS_PREPAINT:
                return CDRF_NOTIFYITEMDRAW;

            case CDDS_ITEMPREPAINT:
                return CDRF_NOTIFYPOSTPAINT;

            case CDDS_ITEMPOSTPAINT: {
                int cmdId = (int)lpNMCustomDraw->nmcd.dwItemSpec;
                m_toolbar.drawButtonGlyph(lpNMCustomDraw->nmcd.hdc, cmdId, lpNMCustomDraw->nmcd.rc);
                return CDRF_DODEFAULT;
            }
            }
        }

        return 0;
    }

    LRESULT OnLButtonDown(HWND hwnd) {
        m_shapeManager.OnLBdown(hwnd);
        return 0;
    }

    LRESULT OnMouseMove(HWND hwnd, LPARAM lParam) {
        m_shapeManager.OnMouseMove(hwnd, lParam);
        return 0;
    }

    LRESULT OnLButtonUp(HWND hwnd) {
        m_shapeManager.OnLBup(hwnd);
        InvalidateRect(hwnd, nullptr, TRUE);
        return 0;
    }

    LRESULT OnPaint(HWND hwnd) {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        m_shapeManager.OnPaint(hdc);
        EndPaint(hwnd, &ps);
        return 0;
    }

    LRESULT OnSize(HWND hwnd, WPARAM wParam, LPARAM lParam) {
        m_toolbar.onResize();
        return 0;
    }

    LRESULT OnDestroy(HWND hwnd) {
        PostQuitMessage(0);
        return 0;
    }
};
