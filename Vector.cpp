#include "Type/Vector.hpp"

#include <cmath>
#include <stdexcept>

namespace piyo {
    float Vec4::GetMagnitude() const {
        return sqrt((x * x) + (y * y) + (z * z) + (w * w));
    }

    Vec4 Vec4::Normalize() const {
        float magnitude = this->GetMagnitude();
        return Vec4(x / magnitude, y / magnitude, z / magnitude, w / magnitude);
    }

    const Vec4 Vec4::up = Vec4(0, 1, 0, 0);
    const Vec4 Vec4::down = Vec4(0, -1, 0, 0);
    const Vec4 Vec4::left = Vec4(-1, 0, 0, 0);
    const Vec4 Vec4::right = Vec4(1, 0, 0, 0);
    const Vec4 Vec4::forward = Vec4(0, 0, 1, 0);
    const Vec4 Vec4::backward = Vec4(0, 0, -1, 0);
    const Vec4 Vec4::kata = Vec4(0, 0, 0, 1);
    const Vec4 Vec4::ana = Vec4(0, 0, 0, -1);

    float &Vec4::operator[](unsigned int n) {
        switch (n) {
            case 0:
                return this->x;
            case 1:
                return this->y;
            case 2:
                return this->z;
            case 3:
                return this->w;
            default:
                throw std::out_of_range("");
        }
    }
    const float &Vec4::operator[](unsigned int n) const {
        switch (n) {
            case 0:
                return this->x;
            case 1:
                return this->y;
            case 2:
                return this->z;
            case 3:
                return this->w;
            default:
                throw std::out_of_range("");
        }
    }
    Vec4 Vec4::operator*(float n) const {
        return Vec4(x * n, y * n, z * n, w * n);
    }
    Vec4 Vec4::operator+(const Vec4 &rhs) const {
        return Vec4(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z, this->w + rhs.w);
    }

    float Vec3::GetMagnitude() const {
        return sqrt((x * x) + (y * y) + (z * z));
    }

    Vec3 Vec3::Normalize() const {
        float magnitude = this->GetMagnitude();
        return Vec3(x / magnitude, y / magnitude, z / magnitude);
    }

    const Vec3 Vec3::up = Vec3(0, 1, 0);
    const Vec3 Vec3::down = Vec3(0, -1, 0);
    const Vec3 Vec3::left = Vec3(-1, 0, 0);
    const Vec3 Vec3::right = Vec3(1, 0, 0);
    const Vec3 Vec3::forward = Vec3(0, 0, 1);
    const Vec3 Vec3::backward = Vec3(0, 0, -1);

    float &Vec3::operator[](unsigned int n) {
        switch (n) {
            case 0:
                return this->x;
            case 1:
                return this->y;
            case 2:
                return this->z;
            default:
                throw std::out_of_range("");
        }
    }
    const float &Vec3::operator[](unsigned int n) const {
        switch (n) {
            case 0:
                return this->x;
            case 1:
                return this->y;
            case 2:
                return this->z;
            default:
                throw std::out_of_range("");
        }
    }
    Vec3 Vec3::operator*(float n) const {
        return Vec3(x * n, y * n, z * n);
    }
    Vec3 Vec3::operator+(const Vec3 &rhs) const {
        return Vec3(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z);
    }

    float Vec2::GetMagnitude() const {
        return sqrt((x * x) + (y * y));
    }

    Vec2 Vec2::Normalize() const {
        float magnitude = this->GetMagnitude();
        return Vec2(x / magnitude, y / magnitude);
    }

    const Vec2 Vec2::up = Vec2(0, 1);
    const Vec2 Vec2::down = Vec2(0, -1);
    const Vec2 Vec2::left = Vec2(-1, 0);
    const Vec2 Vec2::right = Vec2(1, 0);

    float &Vec2::operator[](unsigned int n) {
        switch (n) {
            case 0:
                return this->x;
            case 1:
                return this->y;
            default:
                throw std::out_of_range("");
        }
    }
    const float &Vec2::operator[](unsigned int n) const {
        switch (n) {
            case 0:
                return this->x;
            case 1:
                return this->y;
            default:
                throw std::out_of_range("");
        }
    }
    Vec2 Vec2::operator*(float n) const {
        return Vec2(x * n, y * n);
    }
    Vec2 Vec2::operator+(const Vec2 &rhs) const {
        return Vec2(this->x + rhs.x, this->y + rhs.y);
    }
}
