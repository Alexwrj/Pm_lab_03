#include "trigonometrical.h"
#include "gluekitmath.h"
#include "cmath"

Trigonometrical::Trigonometrical(QVBoxLayout *layout, QVector<QPair<float, float>> data)
    : AbstractMethod (layout, data)
{

}

Trigonometrical::Trigonometrical()
{
}

Trigonometrical::~Trigonometrical()
{
}

void Trigonometrical::calculate()
{
    clearChart();
    QVector<QPair<float, float>> calculatedValues;
    int n = m_data.size();
    QVector<ComplexNumber> X(n);
    QVector<float>a(n);
    QVector<float>b(n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            X[j] +=  ComplexNumber(m_data[i].first, 0.f)
                    * (ComplexNumber(cos((-2.f * static_cast<float>(M_PI) * i * j) / n), 0.f)
                    + ComplexNumber(0.f, 1.f)
                    * sin((-2.f * static_cast<float>(M_PI) * i * j) / n));

            a[j] = X[j].real;
            b[j] = X[j].imag;
        }
    }

    auto f = [](int n, QVector<float>a, QVector<float>b, float t) -> float{
        float PI = static_cast<float>(M_PI);
        float sum = 0.f;

        for (int i = 1; i < n / 2; i++)
        {
            sum += a[i] * cos((2.f * PI* t * i) / n) - b[i] * sin((2.f * PI* t * i) / n);
        }

        return (
                    (1.f / n)
                    * (a[0] + a[n / 2] * cos(PI * t) + 2.f * sum)
                );
    };

    for (float i = 0; i < m_data.size(); i += 0.01f)
    {
        calculatedValues.push_back(QPair<float, float>(i, f(n, a, b, i)));
    }

    draw(calculatedValues);
}
