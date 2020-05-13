#pragma once

namespace piyo {
    struct Vec4 {
        Vec4()
            : x(0), y(0), z(0), w(0) {}
        Vec4(float a)
            : x(a), y(a), z(a), w(a) {}
        Vec4(float x, float y, float z, float w)
            : x(x), y(y), z(z), w(w) {}

        float x, y, z, w;

        static const Vec4 up, down, left, right, forward, backward, kata, ana;

        float GetMagnitude() const;
        Vec4 Normalize() const;

        float &operator[](unsigned int n);
        const float &operator[](unsigned int n) const;
        Vec4 operator*(float n) const;
        Vec4 operator+(const Vec4 &rhs) const;
    };

    struct Vec3 {
        Vec3()
            : x(0), y(0), z(0) {}
        Vec3(float a)
            : x(a), y(a), z(a) {}
        Vec3(float x, float y, float z)
            : x(x), y(y), z(z) {}

        float x, y, z;

        static const Vec3 up, down, left, right, forward, backward;

        float GetMagnitude() const;
        Vec3 Normalize() const;

        float &operator[](unsigned int n);
        const float &operator[](unsigned int n) const;
        Vec3 operator*(float n) const;
        Vec3 operator+(const Vec3 &rhs) const;
    };

    struct Vec2 {
        Vec2() : x(0), y(0) {};
        Vec2(float a) : x(a), y(a) {};
        Vec2(float x, float y) : x(x), y(y) {};

        float x, y;

        static const Vec2 up, down, left, right;

        float GetMagnitude() const;
        Vec2 Normalize() const;

        float &operator[](unsigned int n);
        const float &operator[](unsigned int n) const;
        Vec2 operator*(float n) const;
        Vec2 operator+(const Vec2 &rhs) const;
    };
}
