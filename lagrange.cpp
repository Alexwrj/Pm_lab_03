#include "lagrange.h"

Lagrange::Lagrange(QVBoxLayout *layout, QVector<QPair<float, float>> data)
    : AbstractMethod (layout, data)
{
}

Lagrange::~Lagrange()
{
}

void Lagrange::calculate()
{
    QVector<QPair<float, float>> calculatedData;
    clearChart();

    auto findMin = [](QVector<QPair<float, float>> val) -> float{

        float min = val[0].first;
        for (int i = 1; i < val.size(); i++)
        {
            if (val[i].first < min){
                min = val[i].first;
            }
        }

        return min;
    };

    auto findMax = [](QVector<QPair<float, float>> val) -> float{

        float max = val[0].first;
        for (int i = 1; i < val.size(); i++)
        {
            if (val[i].first > max){
                max = val[i].first;
            }
        }

        return max;
    };

    float a = findMin(m_data);
    float b = findMax(m_data);

    const float n = 100.f;
    float h = (b - a) / n;

    auto f = [](float step, QVector<QPair<float, float>> data) -> float {
        float sum = 0.f;
        for (int i = 0; i < data.size(); i++)
        {
            float pr = data[i].second;
            for (int j = 0; j < data.size(); j++)
            {
                if (i != j)
                {
                    pr *= (step - data[j].first) / (data[i].first - data[j].first);
                }
            }
            sum += pr;
        }

        return sum;
    };

    for (int i = 0; i < n; i++)
    {
        calculatedData.push_back(QPair<float, float>(a + i * h, f(a + i * h, m_data)));
    }

    draw(calculatedData);
}
