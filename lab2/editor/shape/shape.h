#pragma once
#include <windows.h>

class shape {
protected:
    long mx1, my1, mx2, my2;
public:
    shape() : mx1(0), my1(0), mx2(0), my2(0) {}
    virtual ~shape() = default;

    virtual void set(long x1, long y1, long x2, long y2) {
        mx1 = x1; my1 = y1;
        mx2 = x2; my2 = y2;
    }
    virtual void show(HDC hdc) = 0;
};
