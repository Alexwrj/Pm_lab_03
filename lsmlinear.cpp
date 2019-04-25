#include "lsmlinear.h"
#include "QDebug"

LSMLinear::LSMLinear()
{

}

LSMLinear::LSMLinear(QVBoxLayout *layout, QVector<QPair<float, float> > data)
    : LSM(layout, data)
{
    k = findSollution();
    squaredError();
}

LSMLinear::~LSMLinear()
{
}

QVector<float> LSMLinear::findSollution()
{
    float a = 0.f;
    float b = 0.f;
    float c = 0.f;
    float d = 0.f;
    float e = 0.f;
    float f = 0.f;

    for (int i = 0; i < m_data.size(); i++)
    {
        a += 1.f;
        b += m_data[i].first;
        d += m_data[i].first * m_data[i].first;
        e += m_data[i].second;
        f += m_data[i].first * m_data[i].second;
    }

    c = b;

    Matrix C = Matrix(QVector<QVector<float>>{{a, b}, {c, d}});
    Matrix D = Matrix(QVector<QVector<float>>{{e}, {f}});

    Matrix k = Matrix::inverse(C) * D;
    k.transp();

    auto res = Matrix::fromMatrix(k);

    return res[0];
}

float LSMLinear::regressionFunction(float t)
{
    return k[1] * t + k[0];
}

void LSMLinear::squaredError()
{
    float error = 0.f;

    for (int i = 0; i < m_data.size(); i++)
    {
        error += powf(k[1]* m_data[i].first + k[0] - m_data[i].second, 2.f);
    }

    qDebug() << "Error: " << error << "\n";
}
