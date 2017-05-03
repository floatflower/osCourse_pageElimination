#ifndef ALGORITHMOPT_H
#define ALGORITHMOPT_H

#include <QVector>
#include <QObject>
#include "algorithm.h"

class AlgorithmOPT : public Algorithm
{
    Q_OBJECT
public:
    explicit AlgorithmOPT(QObject *parent = 0);
    virtual void simulate();
signals:

public slots:
private:
    QVector<char> *m_programInMem;
};

#endif // ALGORITHMOPT_H
