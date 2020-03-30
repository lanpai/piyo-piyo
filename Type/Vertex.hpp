#pragma once

#include "Vector.hpp"
#include "Color.hpp"

namespace piyo {
    struct Vertex3 {
        Vertex3()
            : position(Vec3()), color(Color()), uv(Vec2()), normal(Vec3()) {}
        Vertex3(const Vec3 &position, const Color &color, const Vec2 &uv, const Vec3& normal)
            : position(position), color(color), uv(uv), normal(normal) {}

        Vec3 position;
        Color color;
        Vec2 uv;
        Vec3 normal;
    };
}
