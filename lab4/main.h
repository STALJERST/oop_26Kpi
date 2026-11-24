#pragma once
#include <windows.h>
#include <commctrl.h>
#include <memory>

#include "resource.h"
#include "myEditor.h"
#include "toolbar.h"
#include "editor/pointEditor.h"
#include "editor/lineEditor.h"
#include "editor/rectEditor.h"
#include "editor/ellipseEditor.h"
#include "editor/lineWithCirclesEditor.h"
#include "editor/cubeEditor.h"

class MainWindow {
private:
    HWND m_hwnd = nullptr;
    MyEditor* m_pMyEditor = nullptr;
    Toolbar m_toolbar;
    int m_currentType = 0; // 1..6

    void updateTitle() {
        const wchar_t* shapeName = L"Не обрано";
        switch (m_currentType) {
        case 1: shapeName = L"Крапка"; break;
        case 2: shapeName = L"Лінія"; break;
        case 3: shapeName = L"Прямокутник"; break;
        case 4: shapeName = L"Еліпс"; break;
        case 5: shapeName = L"Лінія з кружечками"; break;
        case 6: shapeName = L"Каркас куба"; break;
        }

        wchar_t title[256];
        wsprintfW(title, L"Лабораторна 4 (Ж=18, дин. MyEditor) - Поточний об'єкт: %s", shapeName);
        SetWindowTextW(m_hwnd, title);
    }

    void selectShapeType(int type) {
        if (!m_pMyEditor) return;
        m_currentType = type;
        switch (type) {
        case 1:
            m_pMyEditor->setEditor(std::make_unique<pointEditor>());
            m_toolbar.checkButton(IDM_CREATE_POINT);
            break;
        case 2:
            m_pMyEditor->setEditor(std::make_unique<lineEditor>());
            m_toolbar.checkButton(IDM_CREATE_LINE);
            break;
        case 3:
            m_pMyEditor->setEditor(std::make_unique<rectEditor>());
            m_toolbar.checkButton(IDM_CREATE_RECT);
            break;
        case 4:
            m_pMyEditor->setEditor(std::make_unique<ellipseEditor>());
            m_toolbar.checkButton(IDM_CREATE_ELLIPSE);
            break;
        case 5:
            m_pMyEditor->setEditor(std::make_unique<lineWithCirclesEditor>());
            m_toolbar.checkButton(IDM_CREATE_LINE_O_O);
            break;
        case 6:
            m_pMyEditor->setEditor(std::make_unique<cubeEditor>());
            m_toolbar.checkButton(IDM_CREATE_CUBE);
            break;
        }
        updateTitle();
    }

public:
    MainWindow() = default;

    ~MainWindow() {
        if (m_pMyEditor) {
            delete m_pMyEditor;
            m_pMyEditor = nullptr;
        }
    }

    HWND getHwnd() const { return m_hwnd; }

    LRESULT OnCreate(HWND hwnd) {
        m_hwnd = hwnd;
        m_pMyEditor = new MyEditor();

        HMENU hMenu = CreateMenu();
        HMENU hSubMenuFile = CreatePopupMenu();
        HMENU hSubMenuObjects = CreatePopupMenu();
        HMENU hSubMenuHelp = CreatePopupMenu();

        AppendMenuW(hSubMenuFile, MF_STRING, IDM_FILE_CLEAR, L"Очистити");
        AppendMenuW(hSubMenuFile, MF_SEPARATOR, 0, nullptr);
        AppendMenuW(hSubMenuFile, MF_STRING, IDM_FILE_EXIT, L"Вихід");

        AppendMenuW(hSubMenuObjects, MF_STRING, IDM_CREATE_POINT,      L"Крапка");
        AppendMenuW(hSubMenuObjects, MF_STRING, IDM_CREATE_LINE,       L"Лінія");
        AppendMenuW(hSubMenuObjects, MF_STRING, IDM_CREATE_RECT,       L"Прямокутник");
        AppendMenuW(hSubMenuObjects, MF_STRING, IDM_CREATE_ELLIPSE,    L"Еліпс");
        AppendMenuW(hSubMenuObjects, MF_STRING, IDM_CREATE_LINE_O_O,   L"Лінія з кружечками");
        AppendMenuW(hSubMenuObjects, MF_STRING, IDM_CREATE_CUBE,       L"Каркас куба");

        AppendMenuW(hSubMenuHelp, MF_STRING | MF_GRAYED, 0, L"Про програму");

        AppendMenuW(hMenu, MF_POPUP, (UINT_PTR)hSubMenuFile,    L"Файл");
        AppendMenuW(hMenu, MF_POPUP, (UINT_PTR)hSubMenuObjects, L"Об'єкти");
        AppendMenuW(hMenu, MF_POPUP, (UINT_PTR)hSubMenuHelp,    L"Довідка");
        SetMenu(hwnd, hMenu);

        m_toolbar.create(hwnd);
        updateTitle();
        return 0;
    }

    LRESULT OnCommand(HWND hwnd, WPARAM wParam, LPARAM lParam) {
        int id = LOWORD(wParam);
        switch (id) {
        case IDM_CREATE_POINT:      selectShapeType(1); break;
        case IDM_CREATE_LINE:       selectShapeType(2); break;
        case IDM_CREATE_RECT:       selectShapeType(3); break;
        case IDM_CREATE_ELLIPSE:    selectShapeType(4); break;
        case IDM_CREATE_LINE_O_O:   selectShapeType(5); break;
        case IDM_CREATE_CUBE:       selectShapeType(6); break;

        case IDM_FILE_CLEAR:
            if (m_pMyEditor) {
                m_pMyEditor->clear();
                InvalidateRect(hwnd, nullptr, TRUE);
            }
            break;
        case IDM_FILE_EXIT:
            DestroyWindow(hwnd);
            break;
        }
        return 0;
    }

    LRESULT OnNotify(HWND hwnd, WPARAM wParam, LPARAM lParam) {
        LPNMHDR lpnm = (LPNMHDR)lParam;

        // Tooltips
        if (lpnm->code == TTN_GETDISPINFOW) {
            LPNMTTDISPINFOW lpdi = (LPNMTTDISPINFOW)lParam;
            switch (lpdi->hdr.idFrom) {
            case IDM_CREATE_POINT:      lpdi->lpszText = (LPWSTR)L"Крапка"; break;
            case IDM_CREATE_LINE:       lpdi->lpszText = (LPWSTR)L"Лінія"; break;
            case IDM_CREATE_RECT:       lpdi->lpszText = (LPWSTR)L"Прямокутник"; break;
            case IDM_CREATE_ELLIPSE:    lpdi->lpszText = (LPWSTR)L"Еліпс"; break;
            case IDM_CREATE_LINE_O_O:   lpdi->lpszText = (LPWSTR)L"Лінія з кружечками"; break;
            case IDM_CREATE_CUBE:       lpdi->lpszText = (LPWSTR)L"Каркас куба"; break;
            }
            return 0;
        }

        // CustomDraw для кнопок
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
        if (m_pMyEditor) m_pMyEditor->OnLBdown(hwnd);
        return 0;
    }

    LRESULT OnMouseMove(HWND hwnd, LPARAM lParam) {
        if (m_pMyEditor) m_pMyEditor->OnMouseMove(hwnd, lParam);
        return 0;
    }

    LRESULT OnLButtonUp(HWND hwnd) {
        if (m_pMyEditor) {
            m_pMyEditor->OnLBup(hwnd);
            InvalidateRect(hwnd, nullptr, TRUE);
        }
        return 0;
    }

    LRESULT OnPaint(HWND hwnd) {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        if (m_pMyEditor) m_pMyEditor->OnPaint(hdc);
        EndPaint(hwnd, &ps);
        return 0;
    }

    LRESULT OnSize(HWND hwnd, WPARAM wParam, LPARAM lParam) {
        m_toolbar.onResize();
        return 0;
    }

    LRESULT OnDestroy(HWND hwnd) {
        if (m_pMyEditor) {
            delete m_pMyEditor;
            m_pMyEditor = nullptr;
        }
        PostQuitMessage(0);
        return 0;
    }
};
