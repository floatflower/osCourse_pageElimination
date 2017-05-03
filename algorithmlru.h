#ifndef ALGORITHMLRU_H
#define ALGORITHMLRU_H

#include <QObject>

class AlgorithmLRU : public QObject
{
    Q_OBJECT
public:
    explicit AlgorithmLRU(QObject *parent = 0);

signals:

public slots:
};

#endif // ALGORITHMLRU_H