#pragma once

namespace piyo {
    struct Vector3 {
        Vector3()
            : x(0), y(0), z(0) {}
        Vector3(float a)
            : x(a), y(a), z(a) {}
        Vector3(float x, float y, float z)
            : x(x), y(y), z(z) {}

        float x, y, z;

        static const Vector3 up, down, left, right, forward, backward;

        float GetMagnitude() const;
        Vector3 Normalize() const;
    };

    struct Vector2 {
        Vector2() : x(0), y(0) {};
        Vector2(float a) : x(a), y(a) {};
        Vector2(float x, float y) : x(x), y(y) {};

        float x, y;

        static const Vector2 up, down, left, right;

        float GetMagnitude() const;
        Vector2 Normalize() const;
    };
}
