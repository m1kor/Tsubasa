#include <Tsubasa/Math/Quaternion.h>
#include <Tsubasa/Math/Matrix4x4.h>
#include <Tsubasa/Math/Vector3.h>
#include <math.h>

namespace Tsubasa
{
    Quaternion::Quaternion() {}

    Quaternion::Quaternion(const float &x, const float &y, const float &z, const float &w)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    Quaternion::~Quaternion() {}

    void Quaternion::Normalize()
    {
        float length = sqrtf(x * x + y * y + z * z + w * w);
        if (length == 0.0f)
            length = 1.0f;
        float ilength = 1.0f / length;

        x *= ilength;
        y *= ilength;
        z *= ilength;
        w *= ilength;
    }

    Vector3 Quaternion::Euler() const
    {
        Vector3 result;

        // Roll (x-axis rotation)
        float x0 = 2.0f * (w * x + y * z);
        float x1 = 1.0f - 2.0f * (x * x + y * y);
        result.x = atan2f(x0, x1);

        // Pitch (y-axis rotation)
        float y0 = 2.0f * (w * y - z * x);
        y0 = y0 > 1.0f ? 1.0f : y0;
        y0 = y0 < -1.0f ? -1.0f : y0;
        result.y = asinf(y0);

        // Yaw (z-axis rotation)
        float z0 = 2.0f * (w * z + x * y);
        float z1 = 1.0f - 2.0f * (y * y + z * z);
        result.z = atan2f(z0, z1);

        return result;
    }

    Quaternion Quaternion::Inverse() const
    {
        Quaternion result(x, y, z, w);

        float lengthSq = x * x + y * y + z * z + w * w;

        if (lengthSq != 0.0f)
        {
            float invLength = 1.0f / lengthSq;

            result.x *= -invLength;
            result.y *= -invLength;
            result.z *= -invLength;
            result.w *= invLength;
        }

        return result;
    }

    Quaternion Quaternion::Lerp(const Quaternion &other, float t) const
    {
        Quaternion result;

        result.x = x + t * (other.x - x);
        result.y = y + t * (other.y - y);
        result.z = z + t * (other.z - z);
        result.w = w + t * (other.w - w);

        return result;
    }

    Matrix4x4 Quaternion::Matrix() const
    {
        Matrix4x4 result = Matrix4x4::Identity;

        float a2 = x * x;
        float b2 = y * y;
        float c2 = z * z;
        float ac = x * z;
        float ab = x * y;
        float bc = y * z;
        float ad = w * x;
        float bd = w * y;
        float cd = w * z;

        result.m[0] = 1 - 2 * (b2 + c2);
        result.m[1] = 2 * (ab + cd);
        result.m[2] = 2 * (ac - bd);

        result.m[4] = 2 * (ab - cd);
        result.m[5] = 1 - 2 * (a2 + c2);
        result.m[6] = 2 * (bc + ad);

        result.m[8] = 2 * (ac + bd);
        result.m[9] = 2 * (bc - ad);
        result.m[10] = 1 - 2 * (a2 + b2);

        return result;
    }

    Quaternion Quaternion::Nlerp(const Quaternion &other, float t) const
    {
        Quaternion result;

        // this->Lerp(q2, amount)
        result.x = x + t * (other.x - x);
        result.y = y + t * (other.y - y);
        result.z = z + t * (other.z - z);
        result.w = w + t * (other.w - w);

        // q.Normalize()
        Quaternion q = result;
        float length = sqrtf(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
        if (length == 0.0f)
            length = 1.0f;
        float ilength = 1.0f / length;

        result.x = q.x * ilength;
        result.y = q.y * ilength;
        result.z = q.z * ilength;
        result.w = q.w * ilength;

        return result;
    }

    Quaternion Quaternion::Normalized() const
    {
        Quaternion result;

        float length = sqrtf(x * x + y * y + z * z + w * w);
        if (length == 0.0f)
            length = 1.0f;
        float ilength = 1.0f / length;

        result.x = x * ilength;
        result.y = y * ilength;
        result.z = z * ilength;
        result.w = w * ilength;

        return result;
    }

    Quaternion Quaternion::Slerp(const Quaternion &other, float t) const
    {
        Quaternion result;
        Quaternion b = other;

        const float epsilon = 0.000001f;

        float cosHalfTheta = x * b.x + y * b.y + z * b.z + w * b.w;

        if (cosHalfTheta < 0)
        {
            b.x = -b.x;
            b.y = -b.y;
            b.z = -b.z;
            b.w = -b.w;
            cosHalfTheta = -cosHalfTheta;
        }

        if (fabsf(cosHalfTheta) >= 1.0f)
            result = *this;
        else if (cosHalfTheta > 0.95f)
            result = Nlerp(b, t);
        else
        {
            float halfTheta = acosf(cosHalfTheta);
            float sinHalfTheta = sqrtf(1.0f - cosHalfTheta * cosHalfTheta);

            if (fabsf(sinHalfTheta) < epsilon)
            {
                result.x = (x * 0.5f + b.x * 0.5f);
                result.y = (y * 0.5f + b.y * 0.5f);
                result.z = (z * 0.5f + b.z * 0.5f);
                result.w = (w * 0.5f + b.w * 0.5f);
            }
            else
            {
                float ratioA = sinf((1 - t) * halfTheta) / sinHalfTheta;
                float ratioB = sinf(t * halfTheta) / sinHalfTheta;

                result.x = (x * ratioA + b.x * ratioB);
                result.y = (y * ratioA + b.y * ratioB);
                result.z = (z * ratioA + b.z * ratioB);
                result.w = (w * ratioA + b.w * ratioB);
            }
        }

        return result;
    }

    Quaternion Quaternion::AngleAxis(const Vector3 &_axis, const float &_angle)
    {
        Quaternion result;
        Vector3 axis = _axis;
        float angle = _angle;

        float axisLength = sqrtf(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z);

        if (axisLength != 0.0f)
        {
            angle *= 0.5f;

            float length = 0.0f;
            float ilength = 0.0f;

            // Vector3Normalize(axis)
            Vector3 v = axis;
            length = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
            if (length == 0.0f)
                length = 1.0f;
            ilength = 1.0f / length;
            axis.x *= ilength;
            axis.y *= ilength;
            axis.z *= ilength;

            float sinres = sinf(angle);
            float cosres = cosf(angle);

            result.x = axis.x * sinres;
            result.y = axis.y * sinres;
            result.z = axis.z * sinres;
            result.w = cosres;

            // QuaternionNormalize(q);
            Quaternion q = result;
            length = sqrtf(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
            if (length == 0.0f)
                length = 1.0f;
            ilength = 1.0f / length;
            result.x = q.x * ilength;
            result.y = q.y * ilength;
            result.z = q.z * ilength;
            result.w = q.w * ilength;
        }

        return result;
    }

    Quaternion Quaternion::FromEuler(const float &pitch, const float &yaw, const float &roll)
    {
        Quaternion result;

        float x0 = cosf(pitch * 0.5f);
        float x1 = sinf(pitch * 0.5f);
        float y0 = cosf(yaw * 0.5f);
        float y1 = sinf(yaw * 0.5f);
        float z0 = cosf(roll * 0.5f);
        float z1 = sinf(roll * 0.5f);

        result.x = x1 * y0 * z0 - x0 * y1 * z1;
        result.y = x0 * y1 * z0 + x1 * y0 * z1;
        result.z = x0 * y0 * z1 - x1 * y1 * z0;
        result.w = x0 * y0 * z0 + x1 * y1 * z1;

        return result;
    }

    Quaternion Quaternion::FromEuler(const Vector3 &euler)
    {
        Quaternion result;

        float x0 = cosf(euler.x * 0.5f);
        float x1 = sinf(euler.x * 0.5f);
        float y0 = cosf(euler.y * 0.5f);
        float y1 = sinf(euler.y * 0.5f);
        float z0 = cosf(euler.z * 0.5f);
        float z1 = sinf(euler.z * 0.5f);

        result.x = x1 * y0 * z0 - x0 * y1 * z1;
        result.y = x0 * y1 * z0 + x1 * y0 * z1;
        result.z = x0 * y0 * z1 - x1 * y1 * z0;
        result.w = x0 * y0 * z0 + x1 * y1 * z1;

        return result;
    }

    Quaternion Quaternion::FromMatrix(const Matrix4x4 &matrix)
    {
        Quaternion result;

        float fourWSquaredMinus1 = matrix.m[0] + matrix.m[5] + matrix.m[10];
        float fourXSquaredMinus1 = matrix.m[0] - matrix.m[5] - matrix.m[10];
        float fourYSquaredMinus1 = matrix.m[5] - matrix.m[0] - matrix.m[10];
        float fourZSquaredMinus1 = matrix.m[10] - matrix.m[0] - matrix.m[5];

        int biggestIndex = 0;
        float fourBiggestSquaredMinus1 = fourWSquaredMinus1;
        if (fourXSquaredMinus1 > fourBiggestSquaredMinus1)
        {
            fourBiggestSquaredMinus1 = fourXSquaredMinus1;
            biggestIndex = 1;
        }

        if (fourYSquaredMinus1 > fourBiggestSquaredMinus1)
        {
            fourBiggestSquaredMinus1 = fourYSquaredMinus1;
            biggestIndex = 2;
        }

        if (fourZSquaredMinus1 > fourBiggestSquaredMinus1)
        {
            fourBiggestSquaredMinus1 = fourZSquaredMinus1;
            biggestIndex = 3;
        }

        float biggestVal = sqrtf(fourBiggestSquaredMinus1 + 1.0f) * 0.5f;
        float mult = 0.25f / biggestVal;

        switch (biggestIndex)
        {
        case 0:
            result.w = biggestVal;
            result.x = (matrix.m[6] - matrix.m[9]) * mult;
            result.y = (matrix.m[8] - matrix.m[2]) * mult;
            result.z = (matrix.m[1] - matrix.m[4]) * mult;
            break;
        case 1:
            result.x = biggestVal;
            result.w = (matrix.m[6] - matrix.m[9]) * mult;
            result.y = (matrix.m[1] + matrix.m[4]) * mult;
            result.z = (matrix.m[8] + matrix.m[2]) * mult;
            break;
        case 2:
            result.y = biggestVal;
            result.w = (matrix.m[8] - matrix.m[2]) * mult;
            result.x = (matrix.m[1] + matrix.m[4]) * mult;
            result.z = (matrix.m[6] + matrix.m[9]) * mult;
            break;
        case 3:
            result.z = biggestVal;
            result.w = (matrix.m[1] - matrix.m[4]) * mult;
            result.x = (matrix.m[8] + matrix.m[2]) * mult;
            result.y = (matrix.m[6] + matrix.m[9]) * mult;
            break;
        }

        return result;
    }

    Quaternion Quaternion::FromTo(const Vector3 &from, const Vector3 &to)
    {
        auto const crossProduct = from.Cross(to);
        return Quaternion(
                   std::sqrt(std::pow(from.Magnitude(), 2.0f) * std::pow(to.Magnitude(), 2.0f)) + from.Dot(to),
                   crossProduct.x,
                   crossProduct.y,
                   crossProduct.z)
            .Normalized();
    }

    Quaternion Quaternion::Inverse(const Quaternion &q)
    {
        Quaternion result(q.x, q.y, q.z, q.w);

        float lengthSq = q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;

        if (lengthSq != 0.0f)
        {
            float invLength = 1.0f / lengthSq;

            result.x *= -invLength;
            result.y *= -invLength;
            result.z *= -invLength;
            result.w *= invLength;
        }

        return result;
    }

    Quaternion Quaternion::Lerp(const Quaternion &a, const Quaternion &b, float t)
    {
        Quaternion result;

        result.x = a.x + t * (b.x - a.x);
        result.y = a.y + t * (b.y - a.y);
        result.z = a.z + t * (b.z - a.z);
        result.w = a.w + t * (b.w - a.w);

        return result;
    }

    Quaternion Quaternion::Look(const Vector3 &direction, const Vector3 &up)
    {
        return FromMatrix(Matrix4x4::LookAt(Vector3::Zero, direction, up));
    }

    Quaternion Quaternion::LookAt(const Vector3 &eye, const Vector3 &target, const Vector3 &up)
    {
        return FromMatrix(Matrix4x4::LookAt(eye, target, up));
    }

    Quaternion Quaternion::Nlerp(const Quaternion &a, const Quaternion &b, float t)
    {
        Quaternion result;

        // a.Lerp(b, amount)
        result.x = a.x + t * (b.x - a.x);
        result.y = a.y + t * (b.y - a.y);
        result.z = a.z + t * (b.z - a.z);
        result.w = a.w + t * (b.w - a.w);

        // q.Normalize()
        Quaternion q = result;
        float length = sqrtf(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
        if (length == 0.0f)
            length = 1.0f;
        float ilength = 1.0f / length;

        result.x = q.x * ilength;
        result.y = q.y * ilength;
        result.z = q.z * ilength;
        result.w = q.w * ilength;

        return result;
    }

    Quaternion Quaternion::Normalize(const Quaternion &q)
    {
        Quaternion result;

        float length = sqrtf(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
        if (length == 0.0f)
            length = 1.0f;
        float ilength = 1.0f / length;

        result.x = q.x * ilength;
        result.y = q.y * ilength;
        result.z = q.z * ilength;
        result.w = q.w * ilength;

        return result;
    }

    Quaternion Quaternion::Slerp(const Quaternion &a, const Quaternion &c, float t)
    {
        Quaternion result;
        Quaternion b = c;

        const float epsilon = 0.000001f;

        float cosHalfTheta = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;

        if (cosHalfTheta < 0)
        {
            b.x = -b.x;
            b.y = -b.y;
            b.z = -b.z;
            b.w = -b.w;
            cosHalfTheta = -cosHalfTheta;
        }

        if (fabsf(cosHalfTheta) >= 1.0f)
            result = a;
        else if (cosHalfTheta > 0.95f)
            result = Nlerp(a, b, t);
        else
        {
            float halfTheta = acosf(cosHalfTheta);
            float sinHalfTheta = sqrtf(1.0f - cosHalfTheta * cosHalfTheta);

            if (fabsf(sinHalfTheta) < epsilon)
            {
                result.x = (a.x * 0.5f + b.x * 0.5f);
                result.y = (a.y * 0.5f + b.y * 0.5f);
                result.z = (a.z * 0.5f + b.z * 0.5f);
                result.w = (a.w * 0.5f + b.w * 0.5f);
            }
            else
            {
                float ratioA = sinf((1 - t) * halfTheta) / sinHalfTheta;
                float ratioB = sinf(t * halfTheta) / sinHalfTheta;

                result.x = (a.x * ratioA + b.x * ratioB);
                result.y = (a.y * ratioA + b.y * ratioB);
                result.z = (a.z * ratioA + b.z * ratioB);
                result.w = (a.w * ratioA + b.w * ratioB);
            }
        }

        return result;
    }

    Vector3 Quaternion::ToEuler(const Quaternion &q)
    {
        Vector3 result;

        // Roll (x-axis rotation)
        float x0 = 2.0f * (q.w * q.x + q.y * q.z);
        float x1 = 1.0f - 2.0f * (q.x * q.x + q.y * q.y);
        result.x = atan2f(x0, x1);

        // Pitch (y-axis rotation)
        float y0 = 2.0f * (q.w * q.y - q.z * q.x);
        y0 = y0 > 1.0f ? 1.0f : y0;
        y0 = y0 < -1.0f ? -1.0f : y0;
        result.y = asinf(y0);

        // Yaw (z-axis rotation)
        float z0 = 2.0f * (q.w * q.z + q.x * q.y);
        float z1 = 1.0f - 2.0f * (q.y * q.y + q.z * q.z);
        result.z = atan2f(z0, z1);

        return result;
    }

    Matrix4x4 Quaternion::ToMatrix(const Quaternion &q)
    {
        Matrix4x4 result = Matrix4x4::Identity;

        float a2 = q.x * q.x;
        float b2 = q.y * q.y;
        float c2 = q.z * q.z;
        float ac = q.x * q.z;
        float ab = q.x * q.y;
        float bc = q.y * q.z;
        float ad = q.w * q.x;
        float bd = q.w * q.y;
        float cd = q.w * q.z;

        result.m[0] = 1 - 2 * (b2 + c2);
        result.m[1] = 2 * (ab + cd);
        result.m[2] = 2 * (ac - bd);

        result.m[4] = 2 * (ab - cd);
        result.m[5] = 1 - 2 * (a2 + c2);
        result.m[6] = 2 * (bc + ad);

        result.m[8] = 2 * (ac + bd);
        result.m[9] = 2 * (bc - ad);
        result.m[10] = 1 - 2 * (a2 + b2);

        return result;
    }

    const Quaternion Quaternion::Identity = Quaternion(0.0f, 0.0f, 0.0f, 1.0f);

    Quaternion Quaternion::operator*(const Quaternion &other) const
    {
        Quaternion result;

        float qax = x, qay = y, qaz = z, qaw = w;
        float qbx = other.x, qby = other.y, qbz = other.z, qbw = other.w;

        result.x = qax * qbw + qaw * qbx + qay * qbz - qaz * qby;
        result.y = qay * qbw + qaw * qby + qaz * qbx - qax * qbz;
        result.z = qaz * qbw + qaw * qbz + qax * qby - qay * qbx;
        result.w = qaw * qbw - qax * qbx - qay * qby - qaz * qbz;

        return result;
    }

    Quaternion Quaternion::operator*=(const Quaternion &other)
    {
        float qax = x, qay = y, qaz = z, qaw = w;
        float qbx = other.x, qby = other.y, qbz = other.z, qbw = other.w;

        x = qax * qbw + qaw * qbx + qay * qbz - qaz * qby;
        y = qay * qbw + qaw * qby + qaz * qbx - qax * qbz;
        z = qaz * qbw + qaw * qbz + qax * qby - qay * qbx;
        w = qaw * qbw - qax * qbx - qay * qby - qaz * qbz;

        return *this;
    }

    Vector3 Quaternion::operator*(const Vector3 &vector) const
    {
        Vector3 result;

        result.x = vector.x * (x * x + w * w - y * y - z * z) + vector.y * (2 * x * y - 2 * w * z) + vector.z * (2 * x * z + 2 * w * y);
        result.y = vector.x * (2 * w * z + 2 * x * y) + vector.y * (w * w - x * x + y * y - z * z) + vector.z * (-2 * w * x + 2 * y * z);
        result.z = vector.x * (-2 * w * y + 2 * x * z) + vector.y * (2 * w * x + 2 * y * z) + vector.z * (w * w - x * x - y * y + z * z);

        return result;
    }
}