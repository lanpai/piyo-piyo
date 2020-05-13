#pragma once

#include <string>

#include "Vector.hpp"

namespace piyo {
    struct Mat4x4 {
        Mat4x4();
        Mat4x4(const Vec4 vectors[4]);
        Mat4x4(const Vec4 &a, const Vec4 &b, const Vec4 &c, const Vec4 &d);
        Mat4x4(const float data[4][4]);

        Vec4 data[4];

        std::string ToString() const;

        Mat4x4 Translate(const Vec3 &translation) const;

        Vec4 &operator[](size_t n);
        const Vec4 &operator[](size_t n) const;
        Mat4x4 operator*(const Mat4x4 &rhs) const;
        Vec4 operator*(const Vec4 &rhs) const;

        static Mat4x4 Perspective(float fov, float aspect, float near, float far);
    };
}
