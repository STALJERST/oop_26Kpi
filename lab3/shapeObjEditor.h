#pragma once
#include <windows.h>
#include <memory>

#include "editor/shapeEditor.h"
#include "editor/shape/shape.h"

class shapeObjEditor {
public:
    static const int N = 119;

private:
    shape* pcshape[N];
    int shapeCount;
    std::unique_ptr<shapeEditor> shEditor;

public:
    shapeObjEditor() : shapeCount(0), shEditor(nullptr) {
        for (int i = 0; i < N; i++) {
            pcshape[i] = nullptr;
        }
    }

    ~shapeObjEditor() {
        clear();
    }

    void setEditor(std::unique_ptr<shapeEditor> newEditor) {
        shEditor = std::move(newEditor);
    }

    bool hasEditor() const {
        return shEditor != nullptr;
    }

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

    void OnPaint(HDC hdc) {
        for (int i = 0; i < shapeCount; i++) {
            if (pcshape[i]) {
                pcshape[i]->show(hdc);
            }
        }
        if (shEditor) {
            shEditor->OnPaint(hdc);
        }
    }

    void clear() {
        for (int i = 0; i < shapeCount; i++) {
            delete pcshape[i];
            pcshape[i] = nullptr;
        }
        shapeCount = 0;
    }
};
