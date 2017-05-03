#ifndef ALGORITHMFIFO_H
#define ALGORITHMFIFO_H

#include <QObject>
#include <QQueue>

#include "algorithm.h"

class AlgorithmFIFO : public Algorithm
{
    Q_OBJECT
public:
    explicit AlgorithmFIFO(QObject *parent = 0);
    virtual void simulate();
signals:

public slots:
private:
    QQueue<char> *m_programRecord;
    QVector<char> *m_programInMem;
};

#endif // ALGORITHMFIFO_H
