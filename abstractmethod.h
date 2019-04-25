#ifndef ABSTRACTMETHOD_H
#define ABSTRACTMETHOD_H

#include <QVector>
#include <QPair>

class AbstractMethod
{
public:
    AbstractMethod();
    AbstractMethod(class QVBoxLayout *layout, QVector<QPair<float, float>> data);
    virtual ~AbstractMethod();
    virtual void calculate() = 0;

protected:
    void draw(QVector<QPair<float, float>> calculatedData);
    void clearChart();

    class QVBoxLayout *m_layout;
    QVector<QPair<float, float>> m_data;
};

#endif // ABSTRACTMETHOD_H
