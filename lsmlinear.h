#ifndef LSMLINEAR_H
#define LSMLINEAR_H

#include "lsm.h"

class LSMLinear : public LSM
{
public:
    LSMLinear();
    LSMLinear(class QVBoxLayout *layout, QVector<QPair<float, float>> data);
    virtual ~LSMLinear() override;

protected:
    virtual float regressionFunction(float t) override;
    virtual QVector<float> findSollution() override;
    virtual void squaredError() override;
};

#endif // LSMLINEAR_H
