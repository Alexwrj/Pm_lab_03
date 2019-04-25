#include "cubicspline.h"
#include "sweep.h"
#include <cmath>
#include <QDebug>

CubicSpline::CubicSpline()
{

}

CubicSpline::CubicSpline(QVBoxLayout *layout, QVector<QPair<float, float> > data)
    : AbstractMethod (layout, data)
{
}

CubicSpline::~CubicSpline()
{
}

void CubicSpline::calculate()
{
    clearChart();
    QVector<QPair<float, float>> calculatedData;
    int len = m_data.size();
    QVector<float> h;
    QVector<float> a;
    QVector<float> b;
    QVector<float> c;
    QVector<float> f;

    for (int i = 0; i < len - 1; i++)
    {
        h.push_back(m_data[i + 1].first - m_data[i].first);
    }

    for (int i = 0; i < len -3; i++)
    {
        a.push_back(h[i + 1]);
        b.push_back(h[i]);
    }

    for (int j = 0; j < len -2; j++)
    {
        c.push_back(2.f * (h[j] + h[j + 1]));
        f.push_back(3.f * (
                        ((m_data[j + 2].second - m_data[j + 1].second) / (h[j + 1]))
                        - ((m_data[j + 1].second - m_data[j].second) / (h[j])))
                );
    }

    auto sol = Sweep::CalculateSolution(a, b, c, f);

    sol.push_front(0.f);
    sol.push_back(0.f);
    int sLen = sol.size();

    QVector<float>bSol;
    QVector<float>dSol;

    for (int i = 0; i < sLen - 1; i++)
    {
        bSol.push_back(((m_data[i + 1].second - m_data[i].second) / (h[i]))
                - ((sol[i + 1] + 2.f * sol[i]) / (3.f)) * h[i]);
        dSol.push_back((sol[i + 1] - sol[i]) / (3.f * h[i]));
    }

    bSol.push_back((m_data[sLen - 1].second - m_data[sLen - 2].second) / (h[sLen - 2]));

    auto func = [](float step, QVector<QPair<float, float>>aSol, QVector<float>bSol, QVector<float>cSol, QVector<float>dSol) -> float{
        float f = 0.f;
        for (int i = 0; i < aSol.size() - 1; i++)
        {
            if (step >= aSol[i].first && step < aSol[i + 1].first)
            {
                float x = step - aSol[i].first;
                f = aSol[i].second + bSol[i] * x + cSol[i] * powf(x, 2.f) + dSol[i] * powf(x, 3.f);
            }
        }

        return f;
    };

    const float n = 1000.f;

    float aIntermediate = m_data[0].first;
    float bIntermediate = m_data[m_data.size() - 1].first;

    float step = (bIntermediate - aIntermediate) / n;

    for (int i = 0; i < n; i++)
    {
        calculatedData.push_back(QPair<float, float>(QPair<float, float>(aIntermediate + i * step,
                                                                         func(aIntermediate + i * step, m_data, bSol, sol, dSol))));
    }

    draw(calculatedData);
}
