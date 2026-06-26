#include <iostream>
#include <cmath>

class Vector3
{
public:
    float x;
    float y;
    float z;

    Vector3(float x = 0.0f,
            float y = 0.0f,
            float z = 0.0f)
        : x(x), y(y), z(z)
    {
    }

    void print() const
    {
        std::cout << "("
                  << x << ", "
                  << y << ", "
                  << z << ")\n";
    }
};

class Matrix4
{
private:
    float m[4][4];

public:

    Matrix4()
    {
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            {
                m[i][j] = 0.0f;
            }
        }
    }

    static Matrix4 Identity()
    {
        Matrix4 result;

        for(int i=0;i<4;i++)
        {
            result.m[i][i] = 1.0f;
        }

        return result;
    }

    static Matrix4 Translation(
        float tx,
        float ty,
        float tz)
    {
        Matrix4 result = Identity();

        result.m[0][3] = tx;
        result.m[1][3] = ty;
        result.m[2][3] = tz;

        return result;
    }

    static Matrix4 Scale(
        float sx,
        float sy,
        float sz)
    {
        Matrix4 result = Identity();

        result.m[0][0] = sx;
        result.m[1][1] = sy;
        result.m[2][2] = sz;

        return result;
    }

    static Matrix4 RotationX(float angle)
    {
        Matrix4 result = Identity();

        float c = std::cos(angle);
        float s = std::sin(angle);

        result.m[1][1] = c;
        result.m[1][2] = -s;
        result.m[2][1] = s;
        result.m[2][2] = c;

        return result;
    }

    static Matrix4 RotationY(float angle)
    {
        Matrix4 result = Identity();

        float c = std::cos(angle);
        float s = std::sin(angle);

        result.m[0][0] = c;
        result.m[0][2] = s;
        result.m[2][0] = -s;
        result.m[2][2] = c;

        return result;
    }

    static Matrix4 RotationZ(float angle)
    {
        Matrix4 result = Identity();

        float c = std::cos(angle);
        float s = std::sin(angle);

        result.m[0][0] = c;
        result.m[0][1] = -s;
        result.m[1][0] = s;
        result.m[1][1] = c;

        return result;
    }

    Matrix4 operator*(const Matrix4& other) const
    {
        Matrix4 result;

        for(int row=0; row<4; row++)
        {
            for(int col=0; col<4; col++)
            {
                float sum = 0.0f;

                for(int k=0; k<4; k++)
                {
                    sum +=
                        m[row][k] *
                        other.m[k][col];
                }

                result.m[row][col] = sum;
            }
        }

        return result;
    }

    Vector3 transformPoint(
        const Vector3& v) const
    {
        float x =
            m[0][0] * v.x +
            m[0][1] * v.y +
            m[0][2] * v.z +
            m[0][3];

        float y =
            m[1][0] * v.x +
            m[1][1] * v.y +
            m[1][2] * v.z +
            m[1][3];

        float z =
            m[2][0] * v.x +
            m[2][1] * v.y +
            m[2][2] * v.z +
            m[2][3];

        return Vector3(x,y,z);
    }

    void print() const
    {
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            {
                std::cout
                    << m[i][j]
                    << "\t";
            }

            std::cout << "\n";
        }
    }
};

int main()
{
    Vector3 spaceship(1,0,0);

    Matrix4 translation =
        Matrix4::Translation(
            10,
            5,
            3);

    Matrix4 rotation =
        Matrix4::RotationY(
            3.14159f / 2.0f);

    Matrix4 scale =
        Matrix4::Scale(
            2,
            2,
            2);

    Matrix4 worldTransform =
        translation *
        rotation *
        scale;

    Vector3 finalPosition =
        worldTransform.transformPoint(
            spaceship);

    std::cout
        << "Final Position:\n";

    finalPosition.print();

    return 0;
}