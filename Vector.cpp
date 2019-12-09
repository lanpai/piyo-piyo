#include "Type/Vector.hpp"

#include <cmath>

namespace piyo {
    float Vector3::GetMagnitude() const {
        return sqrt((x * x) + (y * y) + (z * z));
    }

    Vector3 Vector3::Normalize() const {
        float magnitude = this->GetMagnitude();
        return Vector3(x / magnitude, y / magnitude, z / magnitude);
    }

    const Vector3 Vector3::up = Vector3(0, 1, 0);
    const Vector3 Vector3::down = Vector3(0, -1, 0);
    const Vector3 Vector3::left = Vector3(-1, 0, 0);
    const Vector3 Vector3::right = Vector3(1, 0, 0);
    const Vector3 Vector3::forward = Vector3(0, 0, 1);
    const Vector3 Vector3::backward = Vector3(0, 0, -1);

    float Vector2::GetMagnitude() const {
        return sqrt((x * x) + (y * y));
    }

    Vector2 Vector2::Normalize() const {
        float magnitude = this->GetMagnitude();
        return Vector2(x / magnitude, y / magnitude);
    }

    const Vector2 Vector2::up = Vector2(0, 1);
    const Vector2 Vector2::down = Vector2(0, -1);
    const Vector2 Vector2::left = Vector2(-1, 0);
    const Vector2 Vector2::right = Vector2(1, 0);
}
