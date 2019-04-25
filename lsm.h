#ifndef LSM_H
#define LSM_H

#include "abstractmethod.h"
#include "gluekitmath.h"
#include "cmath"

class LSM : public AbstractMethod
{
public:
    LSM();
    LSM(class QVBoxLayout *layout, QVector<QPair<float, float>> data);
    virtual ~LSM() override;
    virtual QVector<float> findSollution() = 0;
    virtual float regressionFunction(float t) = 0;
    virtual void squaredError() = 0;
    virtual void calculate() override;
protected:
    QVector<float> k;
};

#endif // LSM_H
