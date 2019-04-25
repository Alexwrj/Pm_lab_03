#ifndef VISUALIOS_H
#define VISUALIOS_H

#include "fstream"
#include <QPair>
#include <QVector>

class VisualIOS
{
public:
    VisualIOS();
    static QVector<QPair<float, float>> readData();
    static void writeData();
    static QVector<QPair<float, float>> readData(QString path);

private:
    static void writeData(QVector<QPair<float, float>> data, QString path);
};

#endif // VISUALIOS_H
