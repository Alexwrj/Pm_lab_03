#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "visualios.h"
#include "lagrange.h"
#include "newtone.h"
#include "cubicspline.h"
#include "lsmlinear.h"
#include "lsmqsuared.h"
#include "lsmcubic.h"
#include "trigonometrical.h"
#include "QMessageBox"
#include "fstream"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QCoreApplication::setOrganizationName("GlueKit");
    QCoreApplication::setApplicationName("Interpolation");

    filePath = m_settings.value(
                "/Settings/StringKey",
                QCoreApplication::applicationDirPath() + "/values.txt"
                ).toString();
    checkFile();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_chooseData_triggered()
{
    QFileDialog *fileDialog = new QFileDialog();
    filePath = fileDialog->getOpenFileName();

    checkFile();
    if (checkFile(filePath))
    {
        m_settings.setValue("/Settings/StringKey", filePath);
    }
}

void MainWindow::on_exit_triggered()
{
    close();
}

void MainWindow::on_exitBtn_clicked()
{
    close();
}

bool MainWindow::checkFile(QString path)
{
    std::ifstream ifs(path.toStdString(), std::ios::in);
    bool isOpen = ifs.is_open();

    ifs.close();

    return isOpen;
}

void MainWindow::checkFile()
{
    bIsFileOk = checkFile(filePath);

    if(bIsFileOk)
    {
        ui->idDataValidationLbl->setText("Файл найден по пути: \n" + filePath);
        ui->idDataValidationLbl->setStyleSheet("QLabel {color: green;}");
    }
    else
    {
        ui->idDataValidationLbl->setText("Невозможно открыть файл по следующему пути: \n" + filePath);
        ui->idDataValidationLbl->setStyleSheet("QLabel {color: red;}");

    }
}

void MainWindow::on_inDataValidationBtn_clicked()
{
    checkFile();
}

void MainWindow::on_calculateBtn_clicked()
{
    if (bIsFileOk)
    {
        auto data = VisualIOS::readData(filePath);

        if (ui->comboMethod->currentIndex() == 0)
        {
            auto *method = new Lagrange(ui->chartLayout, data);
            method->calculate();
            delete method;
        }
        else if (ui->comboMethod->currentIndex() == 1)
        {
            auto *method = new Newtone(ui->chartLayout, data);
            method->calculate();
            delete method;
        }
        else if (ui->comboMethod->currentIndex() == 2)
        {
            auto *method = new CubicSpline(ui->chartLayout, data);
            method->calculate();
            delete method;
        }
        else if (ui->comboMethod->currentIndex() == 3)
        {
            auto *method = new LSMLinear(ui->chartLayout, data);
            method->calculate();
            delete method;
        }
        else if (ui->comboMethod->currentIndex() == 4)
        {
            auto *method = new LSMQsuared(ui->chartLayout, data);
            method->calculate();
            delete method;
        }
        else if (ui->comboMethod->currentIndex() == 5)
        {
            auto *method = new LSMCubic(ui->chartLayout, data);
            method->calculate();
            delete method;
        }
        else if (ui->comboMethod->currentIndex() == 6)
        {
            auto *method = new Trigonometrical(ui->chartLayout, data);
            method->calculate();
            delete method;
        }
    }
    else
    {
        QMessageBox *message = new QMessageBox(
                        QMessageBox::Critical,
                        "Error!",
                        "Unable to read data!",
                        QMessageBox::Retry | QMessageBox::Abort
                    );
        int ch = message->exec();
        delete message;

        if (ch == QMessageBox::Retry)
        {
            on_chooseData_triggered();
            on_calculateBtn_clicked();
        }
    }
}
