#ifndef TRIGONOMETRICAL_H
#define TRIGONOMETRICAL_H

#include "abstractmethod.h"

class Trigonometrical : AbstractMethod
{
public:
    Trigonometrical();
    Trigonometrical(class QVBoxLayout *layout, QVector<QPair<float, float>> data);
    virtual ~Trigonometrical() override;
    virtual void calculate() override;
};

#endif // TRIGONOMETRICAL_H
