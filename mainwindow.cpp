#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStandardItemModel>
#include <QTableWidgetItem>
#include <cstdlib>
#include <ctime>
#include <QQueue>
#include <QDebug>
#include <QMessageBox>
#include <QTableWidget>

#include "algorithmfifo.h"
#include "algorithmlru.h"
#include "algorithmopt.h"

#define programAmount  32
#define pageAmount 5
#define programTypeAmount 8

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_count(0)
{
    ui->setupUi(this);

    m_pageTable = new QTableWidget(this);
    m_pageTable->setColumnCount(programAmount);
    m_pageTable->setRowCount(pageAmount + 1);


    m_programSerial = new QQueue<char>;
    srand(time(NULL));
    for (int i = 0; i < programAmount; i ++) {
        int randNum = rand() % programTypeAmount;
        char currentProgram = 'A' + randNum;
        QTableWidgetItem *item = new QTableWidgetItem(QString(currentProgram));
        m_pageTable->setHorizontalHeaderItem(i, item);
        m_programSerial->push_back(currentProgram);
    }

    ui->verticalLayout->addWidget(m_pageTable);
    m_pageTable->setVerticalHeaderItem(pageAmount, new QTableWidgetItem(QString("Eliminate?")));
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
    connect(m_algorithm, SIGNAL(simulateFinished()), this, SLOT(onSimulateEnd()));
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
            m_pageTable->setItem(i, serialIndex, new QTableWidgetItem(QString(programName)));
        }
        else if (serialIndex > 0){
            QTableWidgetItem *lastItem = m_pageTable->item(i, serialIndex - 1);
            if (lastItem != nullptr) {
                QString lastProgram = lastItem->text();
                m_pageTable->setItem(i, serialIndex, new QTableWidgetItem(QString(lastProgram)));
            }
        }
    }
    if (needEliminate) {
        m_pageTable->setItem(pageAmount, serialIndex, new QTableWidgetItem(QString("X")));
        m_count ++;
    }
    else {
        m_pageTable->setItem(pageAmount, serialIndex, new QTableWidgetItem(QString("O")));
    }
}

void MainWindow::onSimulateEnd()
{
    qDebug()<<"Finished!";
    QMessageBox messageBox(this);
    messageBox.setText(QString("Simulate finished! Page miss rate: %1").arg(((float)m_count/programAmount)));
    messageBox.exec();
}

void MainWindow::on_resetButton_clicked()
{
    QTableWidget *pageTable = new QTableWidget(this);
    pageTable->setColumnCount(programAmount);
    pageTable->setRowCount(pageAmount + 1);

    ui->verticalLayout->removeWidget(m_pageTable);
    m_pageTable = pageTable;

    int programSerialSize = m_programSerial->size();

    for (int i = 0; i < programSerialSize; i ++) {
        QTableWidgetItem *item = new QTableWidgetItem(QString(m_programSerial->at(i)));
        m_pageTable->setHorizontalHeaderItem(i, item);
    }

    ui->verticalLayout->addWidget(m_pageTable);
}
