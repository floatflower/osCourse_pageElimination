#include "algorithm.h"

#include <QHash>

Algorithm::Algorithm(QObject *parent) : QObject(parent)
{
    this->m_pageMap = new QHash<char, int>;
    connect(this, SIGNAL(eliminate(bool,int,int,char)), parent, SLOT(onEliminate(bool,int,int,char)));
}

void Algorithm::setPageNum(int pageNum)
{
    m_pageNum = pageNum;
}

void Algorithm::setProgramSerial(QQueue<char> *serial)
{
    m_programSerial = serial;
}

void Algorithm::simulate()
{

}
