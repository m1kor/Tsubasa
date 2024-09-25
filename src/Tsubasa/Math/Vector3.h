#pragma once

namespace Tsubasa
{
    class Vector3
    {
    public:
        float x, y, z;

        Vector3();
        Vector3(const float &x, const float &y, const float &z);
        ~Vector3();

        float Angle(const Vector3 &other) const;
        Vector3 Cross(const Vector3 &other) const;
        float Distance(const Vector3 &other) const;
        float Dot(const Vector3 &other) const;
        Vector3 Lerp(const Vector3 &other, float t) const;
        float Magnitude() const;
        Vector3 Max(const Vector3 &other) const;
        Vector3 Min(const Vector3 &other) const;
        void Normalize();
        Vector3 Normalized() const;
        Vector3 Project(const Vector3 &other) const;
        Vector3 Reflect(const Vector3 &normal) const;
        Vector3 Scale(const Vector3 &other) const;

        static Vector3 Cross(const Vector3 &a, const Vector3 &b);
        static float Distance(const Vector3 &a, const Vector3 &b);
        static float Dot(const Vector3 &a, const Vector3 &b);
        static Vector3 Lerp(const Vector3 &a, const Vector3 &b, float t);
        static float Magnitude(const Vector3 &v);
        static Vector3 Max(const Vector3 &a, const Vector3 &b);
        static Vector3 Min(const Vector3 &a, const Vector3 &b);
        static Vector3 Normalize(const Vector3 &v);
        static Vector3 Project(const Vector3 &a, const Vector3 &b);
        static Vector3 Reflect(const Vector3 &a, const Vector3 &normal);
        static Vector3 Scale(const Vector3 &a, const Vector3 &b);

        static const Vector3 Zero, One, Back, Down, Forward, Left, Right, Up;

        Vector3 operator+(const Vector3 &other) const;
        Vector3 operator+=(const Vector3 &other);
        Vector3 operator-(const Vector3 &other) const;
        Vector3 operator-() const;
        Vector3 operator-=(const Vector3 &other);
        Vector3 operator*(const float &number) const;
        Vector3 operator*=(const float &number);
        Vector3 operator*(const Vector3 &other) const;
        Vector3 operator*=(const Vector3 &other);
        Vector3 operator/(const float &number) const;
        Vector3 operator/=(const float &number);
        Vector3 operator/(const Vector3 &other) const;
        Vector3 operator/=(const Vector3 &other);
        bool operator==(const Vector3 &other) const;
        bool operator!=(const Vector3 &other) const;
    };
}