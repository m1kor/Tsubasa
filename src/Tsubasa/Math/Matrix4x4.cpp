#include <Tsubasa/Math/Matrix4x4.h>
#include <Tsubasa/Math/Vector3.h>
#include <Tsubasa/Math/Quaternion.h>
#include <math.h>

namespace Tsubasa
{
    Matrix4x4::Matrix4x4() {}

    Matrix4x4::Matrix4x4(float v[16])
    {
        for (int i = 0; i < 16; i++)
        {
            m[i] = v[i];
        }
    }

    Matrix4x4::~Matrix4x4() {}

    float Matrix4x4::Determinant() const
    {
        float result = 0.0f;

        // Cache the matrix values (speed optimization)
        float a00 = m[0], a01 = m[1], a02 = m[2], a03 = m[3];
        float a10 = m[4], a11 = m[5], a12 = m[6], a13 = m[7];
        float a20 = m[8], a21 = m[9], a22 = m[10], a23 = m[11];
        float a30 = m[12], a31 = m[13], a32 = m[14], a33 = m[15];

        result = a30 * a21 * a12 * a03 - a20 * a31 * a12 * a03 - a30 * a11 * a22 * a03 + a10 * a31 * a22 * a03 +
                 a20 * a11 * a32 * a03 - a10 * a21 * a32 * a03 - a30 * a21 * a02 * a13 + a20 * a31 * a02 * a13 +
                 a30 * a01 * a22 * a13 - a00 * a31 * a22 * a13 - a20 * a01 * a32 * a13 + a00 * a21 * a32 * a13 +
                 a30 * a11 * a02 * a23 - a10 * a31 * a02 * a23 - a30 * a01 * a12 * a23 + a00 * a31 * a12 * a23 +
                 a10 * a01 * a32 * a23 - a00 * a11 * a32 * a23 - a20 * a11 * a02 * a33 + a10 * a21 * a02 * a33 +
                 a20 * a01 * a12 * a33 - a00 * a21 * a12 * a33 - a10 * a01 * a22 * a33 + a00 * a11 * a22 * a33;

        return result;
    }

    Matrix4x4 Matrix4x4::Frustum(const float &left, const float &right, const float &bottom, const float &top, const float &near, const float &far)
    {
        Matrix4x4 result;

        float rl = right - left;
        float tb = top - bottom;
        float fn = far - near;

        result.m[0] = (near * 2.0f) / rl;
        result.m[1] = 0.0f;
        result.m[2] = 0.0f;
        result.m[3] = 0.0f;

        result.m[4] = 0.0f;
        result.m[5] = (near * 2.0f) / tb;
        result.m[6] = 0.0f;
        result.m[7] = 0.0f;

        result.m[8] = (right + left) / rl;
        result.m[9] = (top + bottom) / tb;
        result.m[10] = -(far + near) / fn;
        result.m[11] = -1.0f;

        result.m[12] = 0.0f;
        result.m[13] = 0.0f;
        result.m[14] = -(far * near * 2.0f) / fn;
        result.m[15] = 0.0f;

        return result;
    }

    Matrix4x4 Matrix4x4::Inversed() const
    {
        Matrix4x4 result;

        // Cache the matrix values (speed optimization)
        float a00 = m[0], a01 = m[1], a02 = m[2], a03 = m[3];
        float a10 = m[4], a11 = m[5], a12 = m[6], a13 = m[7];
        float a20 = m[8], a21 = m[9], a22 = m[10], a23 = m[11];
        float a30 = m[12], a31 = m[13], a32 = m[14], a33 = m[15];

        float b00 = a00 * a11 - a01 * a10;
        float b01 = a00 * a12 - a02 * a10;
        float b02 = a00 * a13 - a03 * a10;
        float b03 = a01 * a12 - a02 * a11;
        float b04 = a01 * a13 - a03 * a11;
        float b05 = a02 * a13 - a03 * a12;
        float b06 = a20 * a31 - a21 * a30;
        float b07 = a20 * a32 - a22 * a30;
        float b08 = a20 * a33 - a23 * a30;
        float b09 = a21 * a32 - a22 * a31;
        float b10 = a21 * a33 - a23 * a31;
        float b11 = a22 * a33 - a23 * a32;

        // Calculate the invert determinant (inlined to avoid double-caching)
        float invDet = 1.0f / (b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06);

        result.m[0] = (a11 * b11 - a12 * b10 + a13 * b09) * invDet;
        result.m[1] = (-a01 * b11 + a02 * b10 - a03 * b09) * invDet;
        result.m[2] = (a31 * b05 - a32 * b04 + a33 * b03) * invDet;
        result.m[3] = (-a21 * b05 + a22 * b04 - a23 * b03) * invDet;
        result.m[4] = (-a10 * b11 + a12 * b08 - a13 * b07) * invDet;
        result.m[5] = (a00 * b11 - a02 * b08 + a03 * b07) * invDet;
        result.m[6] = (-a30 * b05 + a32 * b02 - a33 * b01) * invDet;
        result.m[7] = (a20 * b05 - a22 * b02 + a23 * b01) * invDet;
        result.m[8] = (a10 * b10 - a11 * b08 + a13 * b06) * invDet;
        result.m[9] = (-a00 * b10 + a01 * b08 - a03 * b06) * invDet;
        result.m[10] = (a30 * b04 - a31 * b02 + a33 * b00) * invDet;
        result.m[11] = (-a20 * b04 + a21 * b02 - a23 * b00) * invDet;
        result.m[12] = (-a10 * b09 + a11 * b07 - a12 * b06) * invDet;
        result.m[13] = (a00 * b09 - a01 * b07 + a02 * b06) * invDet;
        result.m[14] = (-a30 * b03 + a31 * b01 - a32 * b00) * invDet;
        result.m[15] = (a20 * b03 - a21 * b01 + a22 * b00) * invDet;

        return result;
    }

    Matrix4x4 Matrix4x4::Transposed() const
    {
        Matrix4x4 result;

        result.m[0] = m[0];
        result.m[1] = m[4];
        result.m[2] = m[8];
        result.m[3] = m[12];
        result.m[4] = m[1];
        result.m[5] = m[5];
        result.m[6] = m[9];
        result.m[7] = m[13];
        result.m[8] = m[2];
        result.m[9] = m[6];
        result.m[10] = m[10];
        result.m[11] = m[14];
        result.m[12] = m[3];
        result.m[13] = m[7];
        result.m[14] = m[11];
        result.m[15] = m[15];

        return result;
    }

    float Matrix4x4::Determinant(const Matrix4x4 &matrix)
    {
        float result = 0.0f;

        float a00 = matrix.m[0], a01 = matrix.m[1], a02 = matrix.m[2], a03 = matrix.m[3];
        float a10 = matrix.m[4], a11 = matrix.m[5], a12 = matrix.m[6], a13 = matrix.m[7];
        float a20 = matrix.m[8], a21 = matrix.m[9], a22 = matrix.m[10], a23 = matrix.m[11];
        float a30 = matrix.m[12], a31 = matrix.m[13], a32 = matrix.m[14], a33 = matrix.m[15];

        result = a30 * a21 * a12 * a03 - a20 * a31 * a12 * a03 - a30 * a11 * a22 * a03 + a10 * a31 * a22 * a03 +
                 a20 * a11 * a32 * a03 - a10 * a21 * a32 * a03 - a30 * a21 * a02 * a13 + a20 * a31 * a02 * a13 +
                 a30 * a01 * a22 * a13 - a00 * a31 * a22 * a13 - a20 * a01 * a32 * a13 + a00 * a21 * a32 * a13 +
                 a30 * a11 * a02 * a23 - a10 * a31 * a02 * a23 - a30 * a01 * a12 * a23 + a00 * a31 * a12 * a23 +
                 a10 * a01 * a32 * a23 - a00 * a11 * a32 * a23 - a20 * a11 * a02 * a33 + a10 * a21 * a02 * a33 +
                 a20 * a01 * a12 * a33 - a00 * a21 * a12 * a33 - a10 * a01 * a22 * a33 + a00 * a11 * a22 * a33;

        return result;
    }

    Matrix4x4 Matrix4x4::Inverse(const Matrix4x4 &matrix)
    {
        Matrix4x4 result;

        // Cache the matrix values (speed optimization)
        float a00 = matrix.m[0], a01 = matrix.m[1], a02 = matrix.m[2], a03 = matrix.m[3];
        float a10 = matrix.m[4], a11 = matrix.m[5], a12 = matrix.m[6], a13 = matrix.m[7];
        float a20 = matrix.m[8], a21 = matrix.m[9], a22 = matrix.m[10], a23 = matrix.m[11];
        float a30 = matrix.m[12], a31 = matrix.m[13], a32 = matrix.m[14], a33 = matrix.m[15];

        float b00 = a00 * a11 - a01 * a10;
        float b01 = a00 * a12 - a02 * a10;
        float b02 = a00 * a13 - a03 * a10;
        float b03 = a01 * a12 - a02 * a11;
        float b04 = a01 * a13 - a03 * a11;
        float b05 = a02 * a13 - a03 * a12;
        float b06 = a20 * a31 - a21 * a30;
        float b07 = a20 * a32 - a22 * a30;
        float b08 = a20 * a33 - a23 * a30;
        float b09 = a21 * a32 - a22 * a31;
        float b10 = a21 * a33 - a23 * a31;
        float b11 = a22 * a33 - a23 * a32;

        // Calculate the invert determinant (inlined to avoid double-caching)
        float invDet = 1.0f / (b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06);

        result.m[0] = (a11 * b11 - a12 * b10 + a13 * b09) * invDet;
        result.m[1] = (-a01 * b11 + a02 * b10 - a03 * b09) * invDet;
        result.m[2] = (a31 * b05 - a32 * b04 + a33 * b03) * invDet;
        result.m[3] = (-a21 * b05 + a22 * b04 - a23 * b03) * invDet;
        result.m[4] = (-a10 * b11 + a12 * b08 - a13 * b07) * invDet;
        result.m[5] = (a00 * b11 - a02 * b08 + a03 * b07) * invDet;
        result.m[6] = (-a30 * b05 + a32 * b02 - a33 * b01) * invDet;
        result.m[7] = (a20 * b05 - a22 * b02 + a23 * b01) * invDet;
        result.m[8] = (a10 * b10 - a11 * b08 + a13 * b06) * invDet;
        result.m[9] = (-a00 * b10 + a01 * b08 - a03 * b06) * invDet;
        result.m[10] = (a30 * b04 - a31 * b02 + a33 * b00) * invDet;
        result.m[11] = (-a20 * b04 + a21 * b02 - a23 * b00) * invDet;
        result.m[12] = (-a10 * b09 + a11 * b07 - a12 * b06) * invDet;
        result.m[13] = (a00 * b09 - a01 * b07 + a02 * b06) * invDet;
        result.m[14] = (-a30 * b03 + a31 * b01 - a32 * b00) * invDet;
        result.m[15] = (a20 * b03 - a21 * b01 + a22 * b00) * invDet;

        return result;
    }

    Matrix4x4 Matrix4x4::LookAt(const Vector3 &eye, const Vector3 &target, const Vector3 &up)
    {
        Matrix4x4 result;

        float length = 0.0f;
        float ilength = 0.0f;

        // eye - target
        Vector3 vz(eye.x - target.x, eye.y - target.y, eye.z - target.z);

        // vz.Normalize()
        Vector3 v = vz;
        length = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
        if (length == 0.0f)
        {
            length = 1.0f;
        }
        ilength = 1.0f / length;
        vz.x *= ilength;
        vz.y *= ilength;
        vz.z *= ilength;

        // up.Cross(vz)
        Vector3 vx(up.y * vz.z - up.z * vz.y, up.z * vz.x - up.x * vz.z, up.x * vz.y - up.y * vz.x);

        // x.Normalize()
        v = vx;
        length = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
        if (length == 0.0f)
        {
            length = 1.0f;
        }
        ilength = 1.0f / length;
        vx.x *= ilength;
        vx.y *= ilength;
        vx.z *= ilength;

        // vz.Cross(vx)
        Vector3 vy(vz.y * vx.z - vz.z * vx.y, vz.z * vx.x - vz.x * vx.z, vz.x * vx.y - vz.y * vx.x);

        result.m[0] = vx.x;
        result.m[1] = vx.y;
        result.m[2] = vx.z;
        result.m[3] = -(vx.x * eye.x + vx.y * eye.y + vx.z * eye.z);  // vx.Dot(eye)
        result.m[4] = vy.x;
        result.m[5] = vy.y;
        result.m[6] = vy.z;
        result.m[7] = -(vy.x * eye.x + vy.y * eye.y + vy.z * eye.z);  // vy.Dot(eye)
        result.m[8] = vz.x;
        result.m[9] = vz.y;
        result.m[10] = vz.z;
        result.m[11] = -(vz.x * eye.x + vz.y * eye.y + vz.z * eye.z); // vz.Dot(eye)
        result.m[12] = 0.0f;
        result.m[13] = 0.0f;
        result.m[14] = 0.0f;
        result.m[15] = 1.0f;

        return result;
    }

    Matrix4x4 Matrix4x4::Ortho(const float &left, const float &right, const float &bottom, const float &top, const float &near, const float &far)
    {
        Matrix4x4 result;

        float rl = (right - left);
        float tb = (top - bottom);
        float fn = (far - near);

        result.m[0] = 2.0f / rl;
        result.m[1] = 0.0f;
        result.m[2] = 0.0f;
        result.m[3] = 0.0f;
        result.m[4] = 0.0f;
        result.m[5] = 2.0f / tb;
        result.m[6] = 0.0f;
        result.m[7] = 0.0f;
        result.m[8] = 0.0f;
        result.m[9] = 0.0f;
        result.m[10] = -2.0f / fn;
        result.m[11] = 0.0f;
        result.m[12] = -(left + right) / rl;
        result.m[13] = -(top + bottom) / tb;
        result.m[14] = -(far + near) / fn;
        result.m[15] = 1.0f;

        return result;
    }

    Matrix4x4 Matrix4x4::Perspective(const float &fovY, const float &aspect, const float &near, const float &far)
    {
        Matrix4x4 result = Matrix4x4::Zero;

        double top = near * tan(fovY * 0.5);
        double bottom = -top;
        double right = top * aspect;
        double left = -right;

        // Matrix::Frustum(-right, right, -top, top, near, far);
        float rl = (right - left);
        float tb = (top - bottom);
        float fn = (far - near);

        result.m[0] = (near * 2.0f) / rl;
        result.m[5] = (near * 2.0f) / tb;
        result.m[8] = (right + left) / rl;
        result.m[9] = (top + bottom) / tb;
        result.m[10] = -(far + near) / fn;
        result.m[11] = -1.0f;
        result.m[14] = -(far * near * 2.0f) / fn;

        return result;
    }

    Matrix4x4 Matrix4x4::Rotate(const float &x, const float &y, const float &z)
    {
        Matrix4x4 result;

        float cz = cosf(z);
        float sz = sinf(z);
        float cy = cosf(y);
        float sy = sinf(y);
        float cx = cosf(x);
        float sx = sinf(x);

        result.m[0] = cz * cy;
        result.m[4] = cz * sy * sx - cx * sz;
        result.m[8] = sz * sx + cz * cx * sy;
        result.m[12] = 0;

        result.m[1] = cy * sz;
        result.m[5] = cz * cx + sz * sy * sx;
        result.m[9] = cx * sz * sy - cz * sx;
        result.m[13] = 0;

        result.m[2] = -sy;
        result.m[6] = cy * sx;
        result.m[10] = cy * cx;
        result.m[14] = 0;

        result.m[3] = 0;
        result.m[7] = 0;
        result.m[11] = 0;
        result.m[15] = 1;

        return result;
    }

    Matrix4x4 Matrix4x4::Rotate(const Vector3 &euler)
    {
        Matrix4x4 result;

        float cz = cosf(euler.z);
        float sz = sinf(euler.z);
        float cy = cosf(euler.y);
        float sy = sinf(euler.y);
        float cx = cosf(euler.x);
        float sx = sinf(euler.x);

        result.m[0] = cz * cy;
        result.m[4] = cz * sy * sx - cx * sz;
        result.m[8] = sz * sx + cz * cx * sy;
        result.m[12] = 0;

        result.m[1] = cy * sz;
        result.m[5] = cz * cx + sz * sy * sx;
        result.m[9] = cx * sz * sy - cz * sx;
        result.m[13] = 0;

        result.m[2] = -sy;
        result.m[6] = cy * sx;
        result.m[10] = cy * cx;
        result.m[14] = 0;

        result.m[3] = 0;
        result.m[7] = 0;
        result.m[11] = 0;
        result.m[15] = 1;

        return result;
    }

    Matrix4x4 Matrix4x4::Rotate(const Vector3 &axis, const float &angle)
    {
        Matrix4x4 result;

        float x = axis.x, y = axis.y, z = axis.z;

        float lengthSquared = x * x + y * y + z * z;

        if ((lengthSquared != 1.0f) && (lengthSquared != 0.0f))
        {
            float ilength = 1.0f / sqrtf(lengthSquared);
            x *= ilength;
            y *= ilength;
            z *= ilength;
        }

        float sinres = sinf(angle);
        float cosres = cosf(angle);
        float t = 1.0f - cosres;

        result.m[0] = x * x * t + cosres;
        result.m[1] = y * x * t + z * sinres;
        result.m[2] = z * x * t - y * sinres;
        result.m[3] = 0.0f;

        result.m[4] = x * y * t - z * sinres;
        result.m[5] = y * y * t + cosres;
        result.m[6] = z * y * t + x * sinres;
        result.m[7] = 0.0f;

        result.m[8] = x * z * t + y * sinres;
        result.m[9] = y * z * t - x * sinres;
        result.m[10] = z * z * t + cosres;
        result.m[11] = 0.0f;

        result.m[12] = 0.0f;
        result.m[13] = 0.0f;
        result.m[14] = 0.0f;
        result.m[15] = 1.0f;

        return result;
    }

    Matrix4x4 Matrix4x4::Rotate(const Quaternion &quaternion)
    {
        Matrix4x4 result = Matrix4x4::Identity;

        float a2 = quaternion.x * quaternion.x;
        float b2 = quaternion.y * quaternion.y;
        float c2 = quaternion.z * quaternion.z;
        float ac = quaternion.x * quaternion.z;
        float ab = quaternion.x * quaternion.y;
        float bc = quaternion.y * quaternion.z;
        float ad = quaternion.w * quaternion.x;
        float bd = quaternion.w * quaternion.y;
        float cd = quaternion.w * quaternion.z;

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

    Matrix4x4 Matrix4x4::Scale(const float &x, const float &y, const float &z)
    {
        Matrix4x4 result = Matrix4x4::Identity;

        result.m[0] = x;
        result.m[5] = y;
        result.m[10] = z;

        return result;
    }

    Matrix4x4 Matrix4x4::Scale(const Vector3 &scale)
    {
        Matrix4x4 result = Matrix4x4::Identity;

        result.m[0] = scale.x;
        result.m[5] = scale.y;
        result.m[10] = scale.z;

        return result;
    }

    Matrix4x4 Matrix4x4::Translate(const float &x, const float &y, const float &z)
    {
        Matrix4x4 result = Matrix4x4::Identity;

        result.m[12] = x;
        result.m[13] = y;
        result.m[14] = z;

        return result;
    }

    Matrix4x4 Matrix4x4::Translate(const Vector3 &translation)
    {
        Matrix4x4 result = Matrix4x4::Identity;

        result.m[12] = translation.x;
        result.m[13] = translation.y;
        result.m[14] = translation.z;

        return result;
    }

    Matrix4x4 Matrix4x4::Transpose(const Matrix4x4 &matrix)
    {
        Matrix4x4 result;

        result.m[0] = matrix[0];
        result.m[1] = matrix[4];
        result.m[2] = matrix[8];
        result.m[3] = matrix[12];
        result.m[4] = matrix[1];
        result.m[5] = matrix[5];
        result.m[6] = matrix[9];
        result.m[7] = matrix[13];
        result.m[8] = matrix[2];
        result.m[9] = matrix[6];
        result.m[10] = matrix[10];
        result.m[11] = matrix[14];
        result.m[12] = matrix[3];
        result.m[13] = matrix[7];
        result.m[14] = matrix[11];
        result.m[15] = matrix[15];

        return result;
    }

    Matrix4x4 Matrix4x4::TRS(const Vector3 &position, const Quaternion &rotation, const Vector3 &scale)
    {
        Matrix4x4 result;

        result.m[0] = (1.0f - 2.0f * (rotation.y * rotation.y + rotation.z * rotation.z)) * scale.x;
        result.m[1] = (rotation.x * rotation.y + rotation.z * rotation.w) * scale.x * 2.0f;
        result.m[2] = (rotation.x * rotation.z - rotation.y * rotation.w) * scale.x * 2.0f;
        result.m[3] = 0.0f;
        result.m[4] = (rotation.x * rotation.y - rotation.z * rotation.w) * scale.y * 2.0f;
        result.m[5] = (1.0f - 2.0f * (rotation.x * rotation.x + rotation.z * rotation.z)) * scale.y;
        result.m[6] = (rotation.y * rotation.z + rotation.x * rotation.w) * scale.y * 2.0f;
        result.m[7] = 0.0f;
        result.m[8] = (rotation.x * rotation.z + rotation.y * rotation.w) * scale.z * 2.0f;
        result.m[9] = (rotation.y * rotation.z - rotation.x * rotation.w) * scale.z * 2.0f;
        result.m[10] = (1.0f - 2.0f * (rotation.x * rotation.x + rotation.y * rotation.y)) * scale.z;
        result.m[11] = 0.0f;
        result.m[12] = position.x;
        result.m[13] = position.y;
        result.m[14] = position.z;
        result.m[15] = 1.0f;

        return result;
    }

    const Matrix4x4 Matrix4x4::Identity = Matrix4x4((float[]){1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f});
    const Matrix4x4 Matrix4x4::Zero = Matrix4x4();

    float &Matrix4x4::operator[](const int index)
    {
        return m[index];
    }

    float Matrix4x4::operator[](const int index) const
    {
        return m[index];
    }

    Matrix4x4 Matrix4x4::operator*(const Matrix4x4 &other) const
    {
        Matrix4x4 result;
        result[0] = m[0] * other.m[0] + m[1] * other.m[4] + m[2] * other.m[8] + m[3] * other.m[12];
        result[1] = m[0] * other.m[1] + m[1] * other.m[5] + m[2] * other.m[9] + m[3] * other.m[13];
        result[2] = m[0] * other.m[2] + m[1] * other.m[6] + m[2] * other.m[10] + m[3] * other.m[14];
        result[3] = m[0] * other.m[3] + m[1] * other.m[7] + m[2] * other.m[11] + m[3] * other.m[15];
        result[4] = m[4] * other.m[0] + m[5] * other.m[4] + m[6] * other.m[8] + m[7] * other.m[12];
        result[5] = m[4] * other.m[1] + m[5] * other.m[5] + m[6] * other.m[9] + m[7] * other.m[13];
        result[6] = m[4] * other.m[2] + m[5] * other.m[6] + m[6] * other.m[10] + m[7] * other.m[14];
        result[7] = m[4] * other.m[3] + m[5] * other.m[7] + m[6] * other.m[11] + m[7] * other.m[15];
        result[8] = m[8] * other.m[0] + m[9] * other.m[4] + m[10] * other.m[8] + m[11] * other.m[12];
        result[9] = m[8] * other.m[1] + m[9] * other.m[5] + m[10] * other.m[9] + m[11] * other.m[13];
        result[10] = m[8] * other.m[2] + m[9] * other.m[6] + m[10] * other.m[10] + m[11] * other.m[14];
        result[11] = m[8] * other.m[3] + m[9] * other.m[7] + m[10] * other.m[11] + m[11] * other.m[15];
        result[12] = m[12] * other.m[0] + m[13] * other.m[4] + m[14] * other.m[8] + m[15] * other.m[12];
        result[13] = m[12] * other.m[1] + m[13] * other.m[5] + m[14] * other.m[9] + m[15] * other.m[13];
        result[14] = m[12] * other.m[2] + m[13] * other.m[6] + m[14] * other.m[10] + m[15] * other.m[14];
        result[15] = m[12] * other.m[3] + m[13] * other.m[7] + m[14] * other.m[11] + m[15] * other.m[15];
        return result;
    }

    Matrix4x4 Matrix4x4::operator*=(const Matrix4x4 &other)
    {
        *this = *this * other;
        return *this;
    }

    Vector3 Matrix4x4::operator*(const Vector3 &vector) const
    {
        return Vector3(m[0] * vector.x + m[4] * vector.y + m[8] * vector.z + m[12], m[1] * vector.x + m[5] * vector.y + m[9] * vector.z + m[13], m[2] * vector.x + m[6] * vector.y + m[10] * vector.z + m[14]);
    }

    Quaternion Matrix4x4::operator*(const Quaternion &quaternion) const
    {
        Quaternion result;

        result.x = m[0] * quaternion.x + m[4] * quaternion.y + m[8] * quaternion.z + m[12] * quaternion.w;
        result.y = m[1] * quaternion.x + m[5] * quaternion.y + m[9] * quaternion.z + m[13] * quaternion.w;
        result.z = m[2] * quaternion.x + m[6] * quaternion.y + m[10] * quaternion.z + m[14] * quaternion.w;
        result.w = m[3] * quaternion.x + m[7] * quaternion.y + m[11] * quaternion.z + m[15] * quaternion.w;

        return result;
    }
}