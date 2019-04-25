#include "lsmqsuared.h"
#include "QDebug"

LSMQsuared::LSMQsuared()
{

}

LSMQsuared::LSMQsuared(QVBoxLayout *layout, QVector<QPair<float, float> > data)
    : LSM(layout, data)
{
    k = findSollution();
    squaredError();
}

LSMQsuared::~LSMQsuared()
{
}

float LSMQsuared::regressionFunction(float t)
{
    return k[2] * powf(t, 2.f) + k[1] * t+ k[0];
}

QVector<float> LSMQsuared::findSollution()
{
    float a1 = 0.f;
    float a2 = 0.f;
    float a3 = 0.f;
    float b1 = 0.f;
    float b2 = 0.f;
    float b3 = 0.f;
    float c1 = 0.f;
    float c2 = 0.f;
    float c3 = 0.f;

    float e = 0.f;
    float f = 0.f;
    float g = 0.f;

    for (int i = 0; i < m_data.size(); i++)
    {
        a1 += 1.f;
        a2 += m_data[i].first;
        a3 += m_data[i].first * m_data[i].first;
        b3 += m_data[i].first * m_data[i].first * m_data[i].first;
        c3 += m_data[i].first * m_data[i].first * m_data[i].first * m_data[i].first;

        e += m_data[i].second;
        f += m_data[i].first * m_data[i].second;
        g += m_data[i].first * m_data[i].first * m_data[i].second;
    }

    b1 = a2;
    b2 = a3;
    c1 = a3;
    c2 = b3;

    Matrix C = Matrix(QVector<QVector<float>>{
                          {a1, a2, a3},
                          {b1, b2, b3},
                          {c1, c2, c3}
                      });
    Matrix D = Matrix(QVector<QVector<float>>{{e}, {f}, {g}});
    Matrix k = Matrix::inverse(C) * D;
    k.transp();

    auto res = Matrix::fromMatrix(k);

    return res[0];
}

void LSMQsuared::squaredError()
{
    float error = 0.f;

    for (int i = 0; i < m_data.size(); i++)
    {
        error += powf(k[2] * m_data[i].first * m_data[i].first + k[1] * m_data[i].first + k[0] - m_data[i].second, 2.f);
    }

    qDebug() << "Error: " << error << "\n";
}
