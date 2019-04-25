#include "lsm.h"

LSM::LSM()
{   
}

LSM::LSM(QVBoxLayout *layout, QVector<QPair<float, float>> data)
    : AbstractMethod(layout, data)
{
}

LSM::~LSM()
{
}

void LSM::calculate()
{
    clearChart();

    int n = m_data.size();
    QVector<QPair<float, float>> calculatedValues(n);

    for (int i = 0; i < n; i++)
    {
        calculatedValues[i] = QPair<float, float>(i, regressionFunction(i));
    }

    draw(calculatedValues);
}
