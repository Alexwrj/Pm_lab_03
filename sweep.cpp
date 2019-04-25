#include "sweep.h"

Sweep::Sweep()
{

}

QVector<float> Sweep::CalculateSolution(QVector<float> a, QVector<float> b, QVector<float> c, QVector<float> f)
{
    QVector<float> alpha(a.size());
    QVector<float> beta(c.size());
    QVector<float> gamma(c.size());

    alpha[0] = -b[0] / c[0];
    beta[0] = f[0] / c[0];

    int size = c.size();

    for (int i = 1; i < size; i++)
    {
        gamma[i] = c[i] + a[i - 1] * alpha[i - 1];

        if (i != size - 1)
        {
            alpha[i] = -b[i] / gamma[i];
        }

        beta[i] = (-a[i - 1] * beta[i - 1] + f[i]) / gamma[i];
    }

    QVector<float> solution(size);

    solution[size - 1] = beta[size - 1];

    for (int i = size - 2; i >= 0; i--)
    {
        solution[i] = alpha[i] * solution[ i + 1] + beta[i];
    }

    return solution;
}
