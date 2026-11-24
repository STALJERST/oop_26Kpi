#pragma once
#include <windows.h>
#include <memory>

#include "editor/shapeEditor.h"
#include "editor/shape/shape.h"


class shapeObjEditor {
    static const int N = 118;

    // Динамічний масив вказівників
    shape** pcshape;
    int     shapeCount;

    std::unique_ptr<shapeEditor> shEditor;

public:
    shapeObjEditor() : shapeCount(0), shEditor(nullptr) {
        pcshape = new shape*[N];
        for (int i = 0; i < N; i++) pcshape[i] = nullptr;
    }

    ~shapeObjEditor() {
        for (int i = 0; i < shapeCount; i++)
            delete pcshape[i];
        delete[] pcshape;
    }

    // Встановити редактор поточного типу
    void setEditor(std::unique_ptr<shapeEditor> newEditor) {
        shEditor = std::move(newEditor);
    }

    //Обробники подій миші
    void OnLBdown(HWND hwnd) {
        if (shEditor) shEditor->OnLBdown(hwnd);
    }

    void OnLBup(HWND hwnd) {
        if (!shEditor) return;
        std::unique_ptr<shape> s = shEditor->OnLBup(hwnd);
        if (s && shapeCount < N) {
            pcshape[shapeCount++] = s.release();
        }
    }

    void OnMouseMove(HWND hwnd, LPARAM lParam) {
        if (shEditor) shEditor->OnMouseMove(hwnd, lParam);
    }

    //Малювання
    void OnPaint(HDC hdc) {
        // Всі збережені фігури
        for (int i = 0; i < shapeCount; i++)
            pcshape[i]->show(hdc);

        // Гумовий слід поточного редактора
        if (shEditor) shEditor->OnPaint(hdc);
    }

    // Очищення полотна
    void clear() {
        for (int i = 0; i < shapeCount; i++) {
            delete pcshape[i];
            pcshape[i] = nullptr;
        }
        shapeCount = 0;
    }
};
