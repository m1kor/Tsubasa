#pragma once

namespace Tsubasa
{
    class Vector3;
    class Quaternion;

    class Matrix4x4
    {
    public:
        Matrix4x4();
        Matrix4x4(float v[16]);
        ~Matrix4x4();

        float Determinant() const;
        Matrix4x4 Inversed() const;
        Matrix4x4 Transposed() const;

        static float Determinant(const Matrix4x4 &matrix);
        static Matrix4x4 Frustum(const float &left, const float &right, const float &bottom, const float &top, const float &near, const float &far);
        static Matrix4x4 Inverse(const Matrix4x4 &matrix);
        static Matrix4x4 LookAt(const Vector3 &eye, const Vector3 &target, const Vector3 &up);
        static Matrix4x4 Ortho(const float &left, const float &right, const float &bottom, const float &top, const float &near, const float &far);
        static Matrix4x4 Perspective(const float &fovY, const float &aspect, const float &near, const float &far);
        static Matrix4x4 Rotate(const float &x, const float &y, const float &z);
        static Matrix4x4 Rotate(const Vector3 &euler);
        static Matrix4x4 Rotate(const Vector3 &axis, const float &angle);
        static Matrix4x4 Rotate(const Quaternion &quaternion);
        static Matrix4x4 Scale(const float &x, const float &y, const float &z);
        static Matrix4x4 Scale(const Vector3 &scale);
        static Matrix4x4 Translate(const float &x, const float &y, const float &z); 
        static Matrix4x4 Translate(const Vector3 &translation);
        static Matrix4x4 Transpose(const Matrix4x4 &matrix);
        static Matrix4x4 TRS(const Vector3 &position, const Quaternion &rotation, const Vector3 &scale);

        static const Matrix4x4 Identity, Zero;

        float &operator[](const int index);
        float operator[](const int index) const;
        Matrix4x4 operator*(const Matrix4x4 &other) const;
        Matrix4x4 operator*=(const Matrix4x4 &other);
        Vector3 operator*(const Vector3 &vector) const;
        Quaternion operator*(const Quaternion &quaternion) const;

        float m[16];
    };
}