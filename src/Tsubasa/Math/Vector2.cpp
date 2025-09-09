#include <Tsubasa/Math/Vector2.h>
#include <math.h>

namespace Tsubasa
{
    Vector2::Vector2() = default;

    Vector2::Vector2(const float &x, const float &y) : x(x), y(y) {}

    Vector2::~Vector2() = default;

    float Vector2::Angle(const Vector2 &other) const
    {
        float dot = x * other.x + y * other.y;
        float cross = x * other.y - y * other.x;

        return atan2f(cross, dot);
    }

    float Vector2::Distance(const Vector2 &other) const
    {
        float dx = other.x - x;
        float dy = other.y - y;

        return sqrtf(dx * dx + dy * dy);
    }

    float Vector2::Dot(const Vector2 &other) const
    {
        return x * other.x + y * other.y;
    }

    Vector2 Vector2::Lerp(const Vector2 &other, float t) const
    {
        return Vector2(x + (other.x - x) * t, y + (other.y - y) * t);
    }

    float Vector2::Magnitude() const
    {
        return sqrtf(x * x + y * y);
    }

    Vector2 Vector2::Max(const Vector2 &other) const
    {
        return Vector2(fmaxf(x, other.x), fmaxf(y, other.y));
    }

    Vector2 Vector2::Min(const Vector2 &other) const
    {
        return Vector2(fminf(x, other.x), fminf(y, other.y));
    }

    void Vector2::Normalize()
    {
        float length = sqrtf(x * x + y * y);
        if (length != 0.0f)
        {
            float ilength = 1.0f / length;

            x *= ilength;
            y *= ilength;
        }
    }

    Vector2 Vector2::Normalized() const
    {
        float length = sqrtf(x * x + y * y);
        if (length != 0.0f)
        {
            float ilength = 1.0f / length;

            return Vector2(x * ilength, y * ilength);
        }

        return Vector2::Zero;
    }

    Vector2 Vector2::Project(const Vector2 &other) const
    {
        float v1dv2 = x * other.x + y * other.y;
        float v2dv2 = other.x * other.x + other.y * other.y;

        float mag = v1dv2 / v2dv2;

        return Vector2(other.x * mag, other.y * mag);
    }

    Vector2 Vector2::Reflect(const Vector2 &normal) const
    {
        float dotProduct = x * normal.x + y * normal.y;

        return Vector2(x - (2.0f * normal.x) * dotProduct, y - (2.0f * normal.y) * dotProduct);
    }

    Vector2 Vector2::Scale(const Vector2 &other) const
    {
        return Vector2(x * other.x, y * other.y);
    }

    float Vector2::Distance(const Vector2 &a, const Vector2 &b)
    {
        float dx = b.x - a.x;
        float dy = b.y - a.y;

        return sqrtf(dx * dx + dy * dy);
    }

    float Vector2::Dot(const Vector2 &a, const Vector2 &b)
    {
        return a.x * b.x + a.y * b.y;
    }

    Vector2 Vector2::Lerp(const Vector2 &a, const Vector2 &b, float t)
    {
        return Vector2(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t);
    }

    float Vector2::Magnitude(const Vector2 &v)
    {
        return sqrtf(v.x * v.x + v.y * v.y);
    }

    Vector2 Vector2::Max(const Vector2 &a, const Vector2 &b)
    {
        return Vector2(fmaxf(a.x, b.x), fmaxf(a.y, b.y));
    }

    Vector2 Vector2::Min(const Vector2 &a, const Vector2 &b)
    {
        return Vector2(fminf(a.x, b.x), fminf(a.y, b.y));
    }

    Vector2 Vector2::Normalize(const Vector2 &v)
    {
        float length = sqrtf(v.x * v.x + v.y * v.y);
        if (length != 0.0f)
        {
            float ilength = 1.0f / length;

            return Vector2(v.x * ilength, v.y * ilength);
        }

        return Vector2::Zero;
    }

    Vector2 Vector2::Project(const Vector2 &a, const Vector2 &b)
    {
        float v1dv2 = a.x * b.x + a.y * b.y;
        float v2dv2 = b.x * b.x + b.y * b.y;

        float mag = v1dv2 / v2dv2;

        return Vector2(b.x * mag, b.y * mag);
    }

    Vector2 Vector2::Reflect(const Vector2 &a, const Vector2 &normal)
    {
        float dotProduct = a.x * normal.x + a.y * normal.y;

        return Vector2(a.x - (2.0f * normal.x) * dotProduct, a.y - (2.0f * normal.y) * dotProduct);
    }

    Vector2 Vector2::Scale(const Vector2 &a, const Vector2 &b)
    {
        return Vector2(a.x * b.x, a.y * b.y);
    }

    const Vector2 Vector2::Zero = Vector2(0.0f, 0.0f);
    const Vector2 Vector2::One = Vector2(1.0f, 1.0f);
    const Vector2 Vector2::Down = Vector2(0.0f, -1.0f);
    const Vector2 Vector2::Left = Vector2(-1.0f, 0.0f);
    const Vector2 Vector2::Right = Vector2(1.0f, 0.0f);
    const Vector2 Vector2::Up = Vector2(0.0f, 1.0f);

    Vector2 Vector2::operator+(const Vector2 &other) const
    {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 Vector2::operator+=(const Vector2 &other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector2 Vector2::operator-(const Vector2 &other) const
    {
        return Vector2(x - other.x, y - other.y);
    }

    Vector2 Vector2::operator-=(const Vector2 &other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vector2 Vector2::operator-() const
    {
        return Vector2(-x, -y);
    }

    Vector2 Vector2::operator*(const float &number) const
    {
        return Vector2(x * number, y * number);
    }

    Vector2 Vector2::operator*=(const float &number)
    {
        x *= number;
        y *= number;
        return *this;
    }

    Vector2 Vector2::operator*(const Vector2 &other) const
    {
        return Vector2(x * other.x, y * other.y);
    }

    Vector2 Vector2::operator*=(const Vector2 &other)
    {
        x *= other.x;
        y *= other.y;
        return *this;
    }

    Vector2 Vector2::operator/(const float &number) const
    {
        return Vector2(x / number, y / number);
    }

    Vector2 Vector2::operator/=(const float &number)
    {
        x /= number;
        y /= number;
        return *this;
    }

    Vector2 Vector2::operator/(const Vector2 &other) const
    {
        return Vector2(x / other.x, y / other.y);
    }

    Vector2 Vector2::operator/=(const Vector2 &other)
    {
        x /= other.x;
        y /= other.y;
        return *this;
    }

    bool Vector2::operator==(const Vector2 &other) const
    {
        return x == other.x && y == other.y;
    }

    bool Vector2::operator!=(const Vector2 &other) const
    {
        return x != other.x || y != other.y;
    }
}