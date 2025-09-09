#include <Tsubasa/Math/Vector4.h>
#include <math.h>

namespace Tsubasa
{
    Vector4::Vector4() = default;

    Vector4::Vector4(const float &x, const float &y, const float &z, const float &w) : x(x), y(y), z(z), w(w) {}

    Vector4::~Vector4() = default;

    float Vector4::Distance(const Vector4 &other) const
    {
        float dx = other.x - x;
        float dy = other.y - y;
        float dz = other.z - z;
        float dw = other.w - w;

        return sqrtf(dx * dx + dy * dy + dz * dz + dw * dw);
    }

    float Vector4::Dot(const Vector4 &other) const
    {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }

    Vector4 Vector4::Lerp(const Vector4 &other, float t) const
    {
        return Vector4(x + (other.x - x) * t, y + (other.y - y) * t, z + (other.z - z) * t, w + (other.w - w) * t);
    }

    float Vector4::Magnitude() const
    {
        return sqrtf(x * x + y * y + z * z + w * w);
    }

    Vector4 Vector4::Max(const Vector4 &other) const
    {
        return Vector4(fmaxf(x, other.x), fmaxf(y, other.y), fmaxf(z, other.z), fmaxf(w, other.w));
    }

    Vector4 Vector4::Min(const Vector4 &other) const
    {
        return Vector4(fminf(x, other.x), fminf(y, other.y), fminf(z, other.z), fminf(w, other.w));
    }

    void Vector4::Normalize()
    {
        float length = sqrtf(x * x + y * y + z * z + w * w);
        if (length != 0.0f)
        {
            float ilength = 1.0f / length;

            x *= ilength;
            y *= ilength;
            z *= ilength;
            w *= ilength;
        }
    }

    Vector4 Vector4::Normalized() const
    {
        float length = sqrtf(x * x + y * y + z * z + w * w);
        if (length != 0.0f)
        {
            float ilength = 1.0f / length;

            return Vector4(x * ilength, y * ilength, z * ilength, w * ilength);
        }

        return Vector4::Zero;
    }

    Vector4 Vector4::Scale(const Vector4 &other) const
    {
        return Vector4(x * other.x, y * other.y, z * other.z, w * other.w);
    }

    float Vector4::Distance(const Vector4 &a, const Vector4 &b)
    {
        float dx = b.x - a.x;
        float dy = b.y - a.y;
        float dz = b.z - a.z;
        float dw = b.w - a.w;

        return sqrtf(dx * dx + dy * dy + dz * dz + dw * dw);
    }

    float Vector4::Dot(const Vector4 &a, const Vector4 &b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
    }

    Vector4 Vector4::Lerp(const Vector4 &a, const Vector4 &b, float t)
    {
        return Vector4(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t, a.z + (b.z - a.z) * t, a.w + (b.w - a.w) * t);
    }

    float Vector4::Magnitude(const Vector4 &v)
    {
        return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
    }

    Vector4 Vector4::Max(const Vector4 &a, const Vector4 &b)
    {
        return Vector4(fmaxf(a.x, b.x), fmaxf(a.y, b.y), fmaxf(a.z, b.z), fmaxf(a.w, b.w));
    }

    Vector4 Vector4::Min(const Vector4 &a, const Vector4 &b)
    {
        return Vector4(fminf(a.x, b.x), fminf(a.y, b.y), fminf(a.z, b.z), fminf(a.w, b.w));
    }

    Vector4 Vector4::Normalize(const Vector4 &v)
    {
        float length = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
        if (length != 0.0f)
        {
            float ilength = 1.0f / length;

            return Vector4(v.x * ilength, v.y * ilength, v.z * ilength, v.w * ilength);
        }

        return Vector4::Zero;
    }

    Vector4 Vector4::Scale(const Vector4 &a, const Vector4 &b)
    {
        return Vector4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
    }

    const Vector4 Vector4::Zero = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
    const Vector4 Vector4::One = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

    Vector4 Vector4::operator+(const Vector4 &other) const
    {
        return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
    }

    Vector4 Vector4::operator+=(const Vector4 &other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
        return *this;
    }

    Vector4 Vector4::operator-(const Vector4 &other) const
    {
        return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
    }

    Vector4 Vector4::operator-=(const Vector4 &other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
        return *this;
    }

    Vector4 Vector4::operator-() const
    {
        return Vector4(-x, -y, -z, -w);
    }

    Vector4 Vector4::operator*(const float &number) const
    {
        return Vector4(x * number, y * number, z * number, w * number);
    }

    Vector4 Vector4::operator*=(const float &number)
    {
        x *= number;
        y *= number;
        z *= number;
        w *= number;
        return *this;
    }

    Vector4 Vector4::operator*(const Vector4 &other) const
    {
        return Vector4(x * other.x, y * other.y, z * other.z, w * other.w);
    }

    Vector4 Vector4::operator*=(const Vector4 &other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        w *= other.w;
        return *this;
    }

    Vector4 Vector4::operator/(const float &number) const
    {
        return Vector4(x / number, y / number, z / number, w / number);
    }

    Vector4 Vector4::operator/=(const float &number)
    {
        x /= number;
        y /= number;
        z /= number;
        w /= number;
        return *this;
    }

    Vector4 Vector4::operator/(const Vector4 &other) const
    {
        return Vector4(x / other.x, y / other.y, z / other.z, w / other.w);
    }

    Vector4 Vector4::operator/=(const Vector4 &other)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        w /= other.w;
        return *this;
    }

    bool Vector4::operator==(const Vector4 &other) const
    {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }

    bool Vector4::operator!=(const Vector4 &other) const
    {
        return x != other.x || y != other.y || z != other.z || w != other.w;
    }
}