#ifndef CUBICSPLINE_H
#define CUBICSPLINE_H

#include "abstractmethod.h"

class CubicSpline : public AbstractMethod
{
public:
    CubicSpline();
    CubicSpline(class QVBoxLayout *layout, QVector<QPair<float, float>> data);
    virtual ~CubicSpline() override;
    virtual void calculate() override;
};

#endif // CUBICSPLINE_H
