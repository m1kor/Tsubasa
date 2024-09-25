#include <Tsubasa/Math/Vector3.h>
#include <math.h>

namespace Tsubasa
{
    Vector3::Vector3() {}

    Vector3::Vector3(const float &x, const float &y, const float &z) : x(x), y(y), z(z) {}

    Vector3::~Vector3() {}

    float Vector3::Angle(const Vector3 &other) const
    {
        Vector3 cross = {y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x};
        float len = sqrtf(cross.x * cross.x + cross.y * cross.y + cross.z * cross.z);
        float dot = (x * other.x + y * other.y + z * other.z);

        return atan2f(len, dot);
    }

    Vector3 Vector3::Cross(const Vector3 &other) const
    {
        return Vector3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
    }

    float Vector3::Distance(const Vector3 &other) const
    {
        float dx = other.x - x;
        float dy = other.y - y;
        float dz = other.z - z;

        return sqrtf(dx * dx + dy * dy + dz * dz);
    }

    float Vector3::Dot(const Vector3 &other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    Vector3 Vector3::Lerp(const Vector3 &other, float t) const
    {
        return Vector3(x + (other.x - x) * t, y + (other.y - y) * t, z + (other.z - z) * t);
    }

    float Vector3::Magnitude() const
    {
        return sqrtf(x * x + y * y + z * z);
    }

    Vector3 Vector3::Max(const Vector3 &other) const
    {
        return Vector3(fmaxf(x, other.x), fmaxf(y, other.y), fmaxf(z, other.z));
    }

    Vector3 Vector3::Min(const Vector3 &other) const
    {
        return Vector3(fminf(x, other.x), fminf(y, other.y), fminf(z, other.z));
    }

    void Vector3::Normalize()
    {
        float length = sqrtf(x * x + y * y + z * z);
        if (length != 0.0f)
        {
            float ilength = 1.0f / length;

            x *= ilength;
            y *= ilength;
            z *= ilength;
        }
    }

    Vector3 Vector3::Normalized() const
    {
        float length = sqrtf(x * x + y * y + z * z);
        if (length != 0.0f)
        {
            float ilength = 1.0f / length;

            return Vector3(x * ilength, y * ilength, z * ilength);
        }

        return Vector3::Zero;
    }

    Vector3 Vector3::Project(const Vector3 &other) const
    {
        float v1dv2 = (x * other.x + y * other.y + z * other.z);
        float v2dv2 = (other.x * other.x + other.y * other.y + other.z * other.z);

        float mag = v1dv2 / v2dv2;

        return Vector3(other.x * mag, other.y * mag, other.z * mag);
    }

    Vector3 Vector3::Reflect(const Vector3 &normal) const
    {
        float dotProduct = (x * normal.x + y * normal.y + z * normal.z);

        return Vector3(x - (2.0f * normal.x) * dotProduct, y - (2.0f * normal.y) * dotProduct, z - (2.0f * normal.z) * dotProduct);
    }

    Vector3 Vector3::Scale(const Vector3 &other) const
    {
        return Vector3(x * other.x, y * other.y, z * other.z);
    }

    Vector3 Vector3::Cross(const Vector3 &a, const Vector3 &b)
    {
        return Vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
    }

    float Vector3::Distance(const Vector3 &a, const Vector3 &b)
    {
        float dx = b.x - a.x;
        float dy = b.y - a.y;
        float dz = b.z - a.z;

        return sqrtf(dx * dx + dy * dy + dz * dz);
    }

    float Vector3::Dot(const Vector3 &a, const Vector3 &b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    Vector3 Vector3::Lerp(const Vector3 &a, const Vector3 &b, float t)
    {
        return Vector3(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t, a.z + (b.z - a.z) * t);
    }

    float Vector3::Magnitude(const Vector3 &v)
    {
        return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
    }

    Vector3 Max(const Vector3 &a, const Vector3 &b)
    {
        return Vector3(fmaxf(a.x, b.x), fmaxf(a.y, b.y), fmaxf(a.z, b.z));
    }

    Vector3 Min(const Vector3 &a, const Vector3 &b)
    {
        return Vector3(fminf(a.x, b.x), fminf(a.y, b.y), fminf(a.z, b.z));
    }

    Vector3 Vector3::Normalize(const Vector3 &v)
    {
        float length = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
        if (length != 0.0f)
        {
            float ilength = 1.0f / length;

            return Vector3(v.x * ilength, v.y * ilength, v.z * ilength);
        }

        return Vector3::Zero;
    }

    Vector3 Vector3::Project(const Vector3 &a, const Vector3 &b)
    {
        float v1dv2 = a.x * b.x + a.y * b.y + a.z * b.z;
        float v2dv2 = b.x * b.x + b.y * b.y + b.z * b.z;

        float mag = v1dv2 / v2dv2;

        return Vector3(b.x * mag, b.y * mag, b.z * mag);
    }

    Vector3 Vector3::Reflect(const Vector3 &a, const Vector3 &normal)
    {
        float dotProduct = a.x * normal.x + a.y * normal.y + a.z * normal.z;

        return Vector3(a.x - (2.0f * normal.x) * dotProduct, a.y - (2.0f * normal.y) * dotProduct, a.z - (2.0f * normal.z) * dotProduct);
    }

    Vector3 Vector3::Scale(const Vector3 &a, const Vector3 &b)
    {
        return Vector3(a.x * b.x, a.y * b.y, a.z * b.z);
    }

    const Vector3 Vector3::Zero = Vector3(0.0f, 0.0f, 0.0f);
    const Vector3 Vector3::One = Vector3(1.0f, 1.0f, 1.0f);
    const Vector3 Vector3::Back = Vector3(0.0f, 0.0f, 1.0f);
    const Vector3 Vector3::Down = Vector3(0.0f, -1.0f, 0.0f);
    const Vector3 Vector3::Forward = Vector3(0.0f, 0.0f, -1.0f);
    const Vector3 Vector3::Left = Vector3(-1.0f, 0.0f, 0.0f);
    const Vector3 Vector3::Right = Vector3(1.0f, 0.0f, 0.0f);
    const Vector3 Vector3::Up = Vector3(0.0f, 1.0f, 0.0f);

    Vector3 Vector3::operator+(const Vector3 &other) const
    {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    Vector3 Vector3::operator+=(const Vector3 &other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Vector3 Vector3::operator-(const Vector3 &other) const
    {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    Vector3 Vector3::operator-=(const Vector3 &other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    Vector3 Vector3::operator-() const
    {
        return Vector3(-x, -y, -z);
    }

    Vector3 Vector3::operator*(const float &number) const
    {
        return Vector3(x * number, y * number, z * number);
    }

    Vector3 Vector3::operator*=(const float &number)
    {
        x *= number;
        y *= number;
        z *= number;
        return *this;
    }

    Vector3 Vector3::operator*(const Vector3 &other) const
    {
        return Vector3(x * other.x, y * other.y, z * other.z);
    }

    Vector3 Vector3::operator*=(const Vector3 &other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        return *this;
    }

    Vector3 Vector3::operator/(const float &number) const
    {
        return Vector3(x / number, y / number, z / number);
    }

    Vector3 Vector3::operator/=(const float &number)
    {
        x /= number;
        y /= number;
        z /= number;
        return *this;
    }

    Vector3 Vector3::operator/(const Vector3 &other) const
    {
        return Vector3(x / other.x, y / other.y, z / other.z);
    }

    Vector3 Vector3::operator/=(const Vector3 &other)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        return *this;
    }

    bool Vector3::operator==(const Vector3 &other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }

    bool Vector3::operator!=(const Vector3 &other) const
    {
        return x != other.x || y != other.y || z != other.z;
    }
}