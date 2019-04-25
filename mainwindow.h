#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QVector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_chooseData_triggered();
    void on_exit_triggered();
    void on_exitBtn_clicked();

    void on_inDataValidationBtn_clicked();

    void on_calculateBtn_clicked();

private:
    Ui::MainWindow *ui;
    QString filePath;
    bool bIsFileExist;
    QSettings m_settings;
    QVector<float> values;
    bool bIsFileOk;

    bool checkFile(QString path);
    void checkFile();
};

#endif // MAINWINDOW_H
