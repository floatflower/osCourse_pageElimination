#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QQueue>
#include "algorithm.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_startButton_clicked();
    void on_optCheck_clicked();
    void on_fifoCheck_clicked();
    void on_lruCheck_clicked();
    void onEliminate(bool needEliminate, int pageIndex, int serialIndex, char programName);
private:
    Ui::MainWindow *ui;
    Algorithm *m_algorithm;
    QQueue<char> *m_programSerial;
};

#endif // MAINWINDOW_H
