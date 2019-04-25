#include "visualios.h"
#include <QFileDialog>
#include <QMessageBox>
#include "sstream"

VisualIOS::VisualIOS()
{
}

QVector<QPair<float, float>> VisualIOS::readData()
{
    QFileDialog *fileDialog = new QFileDialog();
    QString filePath = fileDialog->getOpenFileName();

    return readData(filePath);
}

QVector<QPair<float, float>> VisualIOS::readData(QString path)
{
    std::ifstream ifs(path.toStdString());
    QVector<QPair<float, float>> data;

    if (ifs.is_open())
    {
        while (!ifs.eof())
        {
            float values[2];
            ifs >> values[0];
            ifs >> values[1];
            data.push_back(QPair<float, float>(values[0], values[1]));
        }
    }
    else
    {
        QMessageBox *message = new QMessageBox(
                        QMessageBox::Critical,
                        "Error!",
                        "Unable to open file!",
                        QMessageBox::Ok
                    );

        message->exec();
        delete message;
    }

    return data;
}


