#pragma once

namespace Tsubasa
{
    class Vector4
    {
    public:
        float x, y, z, w;

        Vector4();
        Vector4(const float &x, const float &y, const float &z, const float &w);
        ~Vector4();

        float Distance(const Vector4 &other) const;
        float Dot(const Vector4 &other) const;
        Vector4 Lerp(const Vector4 &other, float t) const;
        float Magnitude() const;
        Vector4 Max(const Vector4 &other) const;
        Vector4 Min(const Vector4 &other) const;
        void Normalize();
        Vector4 Normalized() const;
        Vector4 Scale(const Vector4 &other) const;

        static float Distance(const Vector4 &a, const Vector4 &b);
        static float Dot(const Vector4 &a, const Vector4 &b);
        static Vector4 Lerp(const Vector4 &a, const Vector4 &b, float t);
        static float Magnitude(const Vector4 &v);
        static Vector4 Max(const Vector4 &a, const Vector4 &b);
        static Vector4 Min(const Vector4 &a, const Vector4 &b);
        static Vector4 Normalize(const Vector4 &v);
        static Vector4 Scale(const Vector4 &a, const Vector4 &b);

        static const Vector4 Zero, One;

        Vector4 operator+(const Vector4 &other) const;
        Vector4 operator+=(const Vector4 &other);
        Vector4 operator-(const Vector4 &other) const;
        Vector4 operator-() const;
        Vector4 operator-=(const Vector4 &other);
        Vector4 operator*(const float &number) const;
        Vector4 operator*=(const float &number);
        Vector4 operator*(const Vector4 &other) const;
        Vector4 operator*=(const Vector4 &other);
        Vector4 operator/(const float &number) const;
        Vector4 operator/=(const float &number);
        Vector4 operator/(const Vector4 &other) const;
        Vector4 operator/=(const Vector4 &other);
        bool operator==(const Vector4 &other) const;
        bool operator!=(const Vector4 &other) const;
    };
}