#pragma once
#include <windows.h>
#include "shape/shape.h"
#include <memory>

template <class T>
class editor {
public:
    virtual ~editor() = default;
    virtual void OnLBdown(HWND hwnd)              = 0;
    virtual std::unique_ptr<T> OnLBup(HWND hwnd) = 0;
    virtual void OnMouseMove(HWND hwnd, LPARAM lp)= 0;
    virtual void OnPaint(HDC hdc)                 = 0;
};
