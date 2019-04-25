#ifndef SWEEP_H
#define SWEEP_H

#include "gluekitmath.h"
#include <QVector>

class Sweep
{
public:
    Sweep();

    static QVector<float> CalculateSolution(QVector<float> a, QVector<float> b, QVector<float> c, QVector<float> f);
};

#endif // SWEEP_H
