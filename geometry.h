#pragma once

#include <cmath>

template <typename T> 
class Vec3
{
public:
    union
    {
        struct { T x, y, z; };
        struct { T ivert, iuv, inorm; };
        T raw[3];
    };
    Vec3() : x(0), y(0), z(0) {}
    Vec3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}
    inline Vec3<T> operator +(const Vec3<T>& v) const
    {
        return Vec3<T>(x + v.x, y + v.y, z + v.z);
    }
    inline Vec3<T> operator -(const Vec3<T>& v) const
    {
        return Vec3<T>(x - v.x, y - v.y, z - v.z);
    }
    inline Vec3<T> operator *(double d) const
    {
        return Vec3<T>(x * d, y * d, z * d);
    }
};

typedef Vec3<double> Vec3d;
typedef Vec3<int>    Vec3i;