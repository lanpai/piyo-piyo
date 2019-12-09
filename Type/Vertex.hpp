#pragma once

#include "Vector.hpp"
#include "Color.hpp"

namespace piyo {
    struct Vertex3 {
        Vertex3()
            : position(Vector3()), color(Color()), uv(Vector2()), normal(Vector3()) {}
        Vertex3(const Vector3 &position, const Color &color, const Vector2 &uv, const Vector3& normal)
            : position(position), color(color), uv(uv), normal(normal) {}

        Vector3 position;
        Color color;
        Vector2 uv;
        Vector3 normal;
    };
}
