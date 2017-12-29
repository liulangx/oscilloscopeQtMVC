#pragma once
/*该头文件包含了各种预先设定好的变量、结构体*/
typedef unsigned short u_short;

typedef float LLFLOAT;
typedef u_short LLUSHORT;
struct vector2f
{
    LLFLOAT _x, _y;
};
struct vector3uint
{
    LLUSHORT _x, _y, _z;
};

struct vector3f
{
    LLFLOAT _x, _y, _z;
};
struct vector4f
{
    LLFLOAT _r, _g, _b, _a;
public:
    void operator =(vector4f b)
    {
        _r = b._r;
        _g = b._g;
        _b = b._b;
        _a = b._a;
    }
};
