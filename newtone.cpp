#include "newtone.h"

Newtone::Newtone()
{   
}

Newtone::Newtone(QVBoxLayout *layout, QVector<QPair<float, float> > data)
    : AbstractMethod (layout, data)
{
}

Newtone::~Newtone()
{
}

void Newtone::calculate()
{
    clearChart();
    int len = m_data.size();
    QVector<float> k(len);

    auto getCol = [](QVector<QPair<float, float>> data, bool flag = false) -> QVector<float> {
        QVector<float> retVal(data.size());

        for (int i = 0; i < data.size(); i++)
        {
            if (flag)
            {
                retVal[i] = data[i].second;
            }
            else
            {
                retVal[i] = data[i].first;
            }
        }

        return retVal;
    };

    QVector<float> x = getCol(m_data);
    QVector<float> y = getCol(m_data, true);

    k[0] = y[0];

    for (int i = 1; i < len; i++)
    {
        QVector<float> y1(len);
        for (int j = 0; j < len - i; j++)
        {
            y1[j] = (y[j + 1] - y[j]) / (x[j + i] - x[j]);
        }

        y = y1;
        k[i] = y[0];
    }

    auto f = [](QVector<float>k, float step, QVector<QPair<float, float>> data) -> float {
        float sum = 0.f;
        for (int i = 1; i < k.size(); i++)
        {
            float pr = 1.f;
            for (int j = 0; j < i; j++)
            {
                pr *= (step - data[j].first);
            }

            sum += k[i] * pr;
        }

        return k[0] + sum;
    };

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

    QVector<QPair<float, float>> calculatedValues;

    for (int i = 0; i < n; i++)
    {
        calculatedValues.push_back(QPair<float, float>(a + i * h, f(k, a + i * h, m_data)));
    }

    draw(calculatedValues);
}
