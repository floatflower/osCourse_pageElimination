#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStandardItemModel>
#include <QTableWidgetItem>
#include <cstdlib>
#include <ctime>
#include <QQueue>
#include <QDebug>
#include <QMessageBox>

#include "algorithmfifo.h"
#include "algorithmlru.h"
#include "algorithmopt.h"

#define programAmount  40
#define pageAmount 5
#define programTypeAmount 8

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pageTable->setColumnCount(programAmount);
    ui->pageTable->setRowCount(pageAmount + 1);
    m_programSerial = new QQueue<char>;
    srand(time(NULL));
    for (int i = 0; i < programAmount; i ++) {
        int randNum = rand() % programTypeAmount;
        char currentProgram = 'A' + randNum;
        QTableWidgetItem *item = new QTableWidgetItem(QString(currentProgram));
        ui->pageTable->setHorizontalHeaderItem(i, item);
        m_programSerial->push_back(currentProgram);
    }
    ui->pageTable->setVerticalHeaderItem(pageAmount, new QTableWidgetItem(QString("Eliminate?")));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_programSerial;
    delete m_algorithm;
}

void MainWindow::on_startButton_clicked()
{
    if (!ui->optCheck->isChecked() && !ui->fifoCheck->isChecked() && !ui->lruCheck->isChecked()) {
        QMessageBox *messageBox = new QMessageBox;
        messageBox->setText(QString("You must select one of algorithm."));
        messageBox->setWindowTitle("Ooops!");
        messageBox->show();
        return;
    }

    if (ui->optCheck->isChecked()) {
        m_algorithm = new AlgorithmOPT(this);
        qDebug() << "Algorithm: OPT is selected";
    }
    else if (ui->fifoCheck->isChecked()) {
        m_algorithm = new AlgorithmFIFO(this);
        qDebug() << "Algorithm: FIFO is selected";
    }
    else if (ui->lruCheck->isChecked()){
        m_algorithm = new AlgorithmLRU(this);
        qDebug() << "Algorithm: LRU is selected";
    }
    m_algorithm->setPageNum(pageAmount);
    m_algorithm->setProgramSerial(m_programSerial);
    m_algorithm->simulate();
}

void MainWindow::on_optCheck_clicked()
{
    ui->fifoCheck->setChecked(false);
    ui->lruCheck->setChecked(false);
}

void MainWindow::on_fifoCheck_clicked()
{
    ui->optCheck->setChecked(false);
    ui->lruCheck->setChecked(false);
}

void MainWindow::on_lruCheck_clicked()
{
    ui->fifoCheck->setChecked(false);
    ui->optCheck->setChecked(false);
}

void MainWindow::onEliminate(bool needEliminate, int pageIndex, int serialIndex, char programName)
{
    for (int i = 0; i < pageAmount; i ++) {
        if (i == pageIndex) {
            ui->pageTable->setItem(i, serialIndex, new QTableWidgetItem(QString(programName)));
        }
        else if (serialIndex > 0){
            QTableWidgetItem *lastItem = ui->pageTable->item(i, serialIndex - 1);
            if (lastItem != nullptr) {
                QString lastProgram = lastItem->text();
                ui->pageTable->setItem(i, serialIndex, new QTableWidgetItem(QString(lastProgram)));
            }
        }
    }
    if (needEliminate) {
        ui->pageTable->setItem(pageAmount, serialIndex, new QTableWidgetItem(QString("X")));
    }
    else {
        ui->pageTable->setItem(pageAmount, serialIndex, new QTableWidgetItem(QString("O")));
    }
}
