#ifndef LSMQSUARED_H
#define LSMQSUARED_H

#include "lsm.h"

class LSMQsuared : public LSM
{
public:
    LSMQsuared();
    LSMQsuared(class QVBoxLayout *layout, QVector<QPair<float, float>> data);
    virtual ~LSMQsuared() override;

protected:
    virtual float regressionFunction(float t) override;
    virtual QVector<float> findSollution() override;
    virtual void squaredError() override;
};

#endif // LSMQSUARED_H
