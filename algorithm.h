#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <QObject>

class Algorithm : public QObject
{
    Q_OBJECT
public:
    explicit Algorithm(QObject *parent = 0);

signals:

public slots:
};

#endif // ALGORITHM_H