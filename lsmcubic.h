#ifndef LSMCUBIC_H
#define LSMCUBIC_H

#include "lsm.h"

class LSMCubic : public LSM
{
public:
    LSMCubic();
    LSMCubic(class QVBoxLayout *layout, QVector<QPair<float, float>> data);
    virtual ~LSMCubic() override;

protected:
    virtual QVector<float> findSollution() override;
    virtual float regressionFunction(float t) override;
    virtual void squaredError() override;
};

#endif // LSMCUBIC_H
