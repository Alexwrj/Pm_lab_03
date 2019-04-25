#include "lsmcubic.h"
#include "QDebug"

LSMCubic::LSMCubic()
{   
}

LSMCubic::LSMCubic(QVBoxLayout *layout, QVector<QPair<float, float> > data)
    : LSM(layout, data)
{
    k = findSollution();
    squaredError();
}

LSMCubic::~LSMCubic()
{
}

QVector<float> LSMCubic::findSollution()
{
    float a[] = {0.f, 0.f, 0.f, 0.f};
    float b[] = {0.f, 0.f, 0.f, 0.f};
    float c[] = {0.f, 0.f, 0.f, 0.f};
    float d[] = {0.f, 0.f, 0.f, 0.f};

    float e[] = {0.f, 0.f, 0.f, 0.f};

    for (int i = 0; i < m_data.size(); i++)
    {
        float x = m_data[i].first;
        float y = m_data[i].second;

        a[0] += 1.f;
        a[1] += x;
        a[2] += powf(x, 2.f);
        a[3] += powf(x, 3.f);
        b[3] += powf(x, 4.f);
        c[3] += powf(x, 5.f);
        d[3] += powf(x, 6.f);

        e[0] += y;
        e[1] += y * x;
        e[2] += y * powf(x, 2.f);
        e[3] += y * powf(x, 3.f);
    }

    b[0] = a[1];
    b[1] = a[2];
    b[2] = a[3];

    c[0] = b[1];
    c[1] = b[2];
    c[2] = b[3];

    d[0] = c[1];
    d[1] = c[2];
    d[2] = c[3];

    Matrix C = Matrix(QVector<QVector<float>>{
                          {a[0], a[1], a[2], a[3]},
                          {b[0], b[1], b[2], b[3]},
                          {c[0], c[1], c[2], c[3]},
                          {d[0], d[1], d[2], d[3]}
                      });
    Matrix D = Matrix(QVector<QVector<float>>{{e[0]}, {e[1]}, {e[2]}, {e[3]}});
    Matrix k = Matrix::inverse(C) * D;

    k.transp();

    auto res = Matrix::fromMatrix(k);

    return res[0];
}

float LSMCubic::regressionFunction(float t)
{
    return k[3] * powf(t, 3.f) + k[2] * powf(t, 2.f) + k[1] * t + k[0];
}

void LSMCubic::squaredError()
{
    float error = 0.f;

    for (int i = 0; i < m_data.size(); i++)
    {
        float x = m_data[i].first;
        float y = m_data[i].second;

        error += powf(k[3] * powf(x, 3.f) + k[2] * powf(x, 2.f) + k[1] * x + k[0] - y, 2.f);
    }

    qDebug() << "Error: " << error << "\n";
}
