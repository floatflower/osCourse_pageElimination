#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <QObject>
#include <QVector>
#include <QQueue>

class Algorithm : public QObject
{
    Q_OBJECT
public:
    explicit Algorithm(QObject *parent = 0);
    void setPageNum(int pageNum);
    void setProgramSerial(QQueue<char> *serial);
    virtual void simulate();
signals:
    void eliminate(bool needEliminate, int pageIndex, int programIndex, char programName);
public slots:
protected:
    QHash<char, int> *m_pageMap;
    QQueue<char> *m_programSerial;
    int m_pageNum;
};

#endif // ALGORITHM_H
