#pragma once

namespace Tsubasa
{
    class Vector2
    {
    public:
        float x, y;

        Vector2();
        Vector2(const float &x, const float &y);
        ~Vector2();

        float Angle(const Vector2 &other) const;
        float Distance(const Vector2 &other) const;
        float Dot(const Vector2 &other) const;
        Vector2 Lerp(const Vector2 &other, float t) const;
        float Magnitude() const;
        Vector2 Max(const Vector2 &other) const;
        Vector2 Min(const Vector2 &other) const;
        void Normalize();
        Vector2 Normalized() const;
        Vector2 Project(const Vector2 &other) const;
        Vector2 Reflect(const Vector2 &normal) const;
        Vector2 Scale(const Vector2 &other) const;

        static float Distance(const Vector2 &a, const Vector2 &b);
        static float Dot(const Vector2 &a, const Vector2 &b);
        static Vector2 Lerp(const Vector2 &a, const Vector2 &b, float t);
        static float Magnitude(const Vector2 &v);
        static Vector2 Max(const Vector2 &a, const Vector2 &b);
        static Vector2 Min(const Vector2 &a, const Vector2 &b);
        static Vector2 Normalize(const Vector2 &v);
        static Vector2 Project(const Vector2 &a, const Vector2 &b);
        static Vector2 Reflect(const Vector2 &a, const Vector2 &normal);
        static Vector2 Scale(const Vector2 &a, const Vector2 &b);

        static const Vector2 Zero, One, Down, Left, Right, Up;

        Vector2 operator+(const Vector2 &other) const;
        Vector2 operator+=(const Vector2 &other);
        Vector2 operator-(const Vector2 &other) const;
        Vector2 operator-() const;
        Vector2 operator-=(const Vector2 &other);
        Vector2 operator*(const float &number) const;
        Vector2 operator*=(const float &number);
        Vector2 operator*(const Vector2 &other) const;
        Vector2 operator*=(const Vector2 &other);
        Vector2 operator/(const float &number) const;
        Vector2 operator/=(const float &number);
        Vector2 operator/(const Vector2 &other) const;
        Vector2 operator/=(const Vector2 &other);
        bool operator==(const Vector2 &other) const;
        bool operator!=(const Vector2 &other) const;
    };
}