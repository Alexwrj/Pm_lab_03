#ifndef NEWTONE_H
#define NEWTONE_H

#include "abstractmethod.h"

class Newtone : public AbstractMethod
{
public:
    Newtone();
    Newtone(class QVBoxLayout *layout, QVector<QPair<float, float>> data);
    virtual ~Newtone() override;
    virtual void calculate() override;
};

#endif // NEWTONE_H
