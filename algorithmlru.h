#ifndef ALGORITHMLRU_H
#define ALGORITHMLRU_H

#include <QVector>
#include <QObject>
#include "algorithm.h"

class AlgorithmLRU : public Algorithm
{
    Q_OBJECT
public:
    explicit AlgorithmLRU(QObject *parent = 0);
    virtual void simulate();
signals:

public slots:
private:
    QVector<char> *m_programInMem;
    QVector<char> *m_usedRecord;
};

#endif // ALGORITHMLRU_H
