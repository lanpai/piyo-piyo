#include "Type/Matrix.hpp"

#include <cmath>

#include "Type/Vector.hpp"

namespace piyo {
    Mat4x4::Mat4x4() {
        for (int y = 0; y < 4; y++)
            for (int x = 0; x < 4; x++)
                this->data[y][x] = 0.0f;
    }

    Mat4x4::Mat4x4(const Vec4 vectors[4]) {
        for (int i = 0; i < 4; i++)
            this->data[i] = vectors[i];
    }

    Mat4x4::Mat4x4(const Vec4 &a, const Vec4 &b, const Vec4 &c, const Vec4 &d) {
        this->data[0] = a;
        this->data[1] = b;
        this->data[2] = c;
        this->data[3] = d;
    }

    Mat4x4::Mat4x4(const float data[4][4]) {
        for (int y = 0; y < 4; y++)
            for (int x = 0; x < 4; x++)
                this->data[y][x] = data[y][x];
    }

    std::string Mat4x4::ToString() const {
        std::string output;
        for (int y = 0; y < 4; y++) {
            for (int x = 0; x < 4; x++) {
                output += std::to_string(this->data[x][y]);
                if (x != 3)
                    output += " ";
            }
            output += "\n";
        }

        return output;
    }

    Mat4x4 Mat4x4::Translate(const Vec3 &translation) const {
        Vec4 translationVector =
            this->data[0] * translation.x +
            this->data[1] * translation.y +
            this->data[2] * translation.z +
            this->data[3];
        return Mat4x4(this->data[0], this->data[1], this->data[2], translationVector);
    }

    Vec4 &Mat4x4::operator[](size_t n) {
        return this->data[n];
    }
    const Vec4 &Mat4x4::operator[](size_t n) const {
        return this->data[n];
    }
    Mat4x4 Mat4x4::operator*(const Mat4x4 &rhs) const {
        float data[4][4];

        for (int y = 0; y < 4; y++) {
            for (int x = 0; x < 4; x++) {
                data[y][x] = 0.0f;
                for (int i = 0; i < 4; i++)
                    data[y][x] += this->data[y][i] * rhs.data[i][x];
            }
        }

        return Mat4x4(data);
    }
    Vec4 Mat4x4::operator*(const Vec4 &rhs) const {
        float newX = 0.0f;
        float newY = 0.0f;
        float newZ = 0.0f;
        float newW = 0.0f;

        for (int i = 0; i < 4; i++) {
            newX += rhs.x * this->data[i][0];
            newY += rhs.x * this->data[i][0];
            newZ += rhs.x * this->data[i][0];
            newW += rhs.x * this->data[i][0];
        }

        return Vec4(newX, newY, newZ, newW);
    }

    Mat4x4 Mat4x4::Perspective(float fov, float aspect, float near, float far) {
        float data[4][4];
        for (int y = 0; y < 4; y++)
            for (int x = 0; x < 4; x++)
                data[y][x] = 0.0f;
        float tanHalfFov = tan(fov / 2.0f);
        data[0][0] = 1.0f / (tanHalfFov * aspect);
        data[1][1] = 1.0f / tanHalfFov;
        data[2][2] = - (far + near)/(far - near);
        data[2][3] = - 1.0f;
        data[3][2] = - (2.0f * far * near)/(far - near);

        return Mat4x4(data);
    }
}
