#pragma once

namespace Tsubasa
{
    class Matrix4x4;
    class Vector3;

    class Quaternion
    {
    public:
        Quaternion();
        Quaternion(const float &x, const float &y, const float &z, const float &w);
        ~Quaternion();


        Vector3 Euler() const;
        Quaternion Inverse() const;
        Quaternion Lerp(const Quaternion &other, float t) const;
        Matrix4x4 Matrix() const;
        void Normalize();
        Quaternion Nlerp(const Quaternion &other, float t) const;
        Quaternion Normalized() const;
        Quaternion Slerp(const Quaternion &other, float t) const;

        static Quaternion AngleAxis(const Vector3 &axis, const float &angle);
        static Quaternion FromEuler(const float &pitch, const float &yaw, const float &roll);
        static Quaternion FromEuler(const Vector3 &euler);
        static Quaternion FromMatrix(const Matrix4x4 &matrix);
        static Quaternion FromTo(const Vector3 &from, const Vector3 &to);
        static Quaternion Inverse(const Quaternion &q);
        static Quaternion Lerp(const Quaternion &a, const Quaternion &b, float t);
        static Quaternion Look(const Vector3 &direction, const Vector3 &up);
        static Quaternion LookAt(const Vector3 &eye, const Vector3 &target, const Vector3 &up);
        static Quaternion Nlerp(const Quaternion &a, const Quaternion &b, float t);
        static Quaternion Normalize(const Quaternion &q);
        static Quaternion Slerp(const Quaternion &a, const Quaternion &b, float t);
        static Vector3 ToEuler(const Quaternion &q);
        static Matrix4x4 ToMatrix(const Quaternion &q);

        static const Quaternion Identity;

        Quaternion operator*(const Quaternion &other) const;
        Quaternion operator*=(const Quaternion &other);
        Vector3 operator*(const Vector3 &vector) const;

        float x, y, z, w;
    };
}