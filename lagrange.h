#ifndef LAGRANGE_H
#define LAGRANGE_H

#include "abstractmethod.h"

class Lagrange : public AbstractMethod
{
public:
    Lagrange();
    Lagrange(class QVBoxLayout *layout, QVector<QPair<float, float>> data);
    virtual ~Lagrange() override;
    virtual void calculate() override;

};

#endif // LAGRANGE_H
