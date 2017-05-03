#include "algorithmlru.h"

#include <QVector>
#include <QDebug>

AlgorithmLRU::AlgorithmLRU(QObject *parent)
    : Algorithm(parent)
{
    m_programInMem = new QVector<char>;
    m_usedRecord = new QVector<char>;
}
void AlgorithmLRU::simulate()
{
    int programIndex = 0;
    for (QQueue<char>::iterator it_programSerial = m_programSerial->begin();
         it_programSerial != m_programSerial->end();
         it_programSerial ++, programIndex ++) {
        char currentProgram = *it_programSerial;
        int programPosition = m_programInMem->indexOf(currentProgram);
        if (programPosition != -1){
            // In memory
            qDebug() << "Current Program is"
                     << currentProgram
                     << "which in memory, no elimination.";
            int newUsing = m_usedRecord->indexOf(currentProgram);
            m_usedRecord->remove(newUsing);
            m_usedRecord->push_back(currentProgram);
            emit eliminate(false, -1, programIndex, currentProgram);
        }
        else {
            // Not in memory
            if (m_programInMem->size() == m_pageNum) {
                char leastRecentlyUsed = m_usedRecord->front();
                m_usedRecord->pop_front();
                int eliminateProgramPosition = m_programInMem->indexOf(leastRecentlyUsed);
                m_programInMem->replace(eliminateProgramPosition, currentProgram);
                m_usedRecord->push_back(currentProgram);
                qDebug() << "CurrentProgram is"
                         << currentProgram
                         << "which is not in memory, eliminating program"
                         << leastRecentlyUsed;
                emit eliminate(true, eliminateProgramPosition, programIndex, currentProgram);
            }
            else if (m_programInMem->size() < m_pageNum){
                m_programInMem->push_back(currentProgram);
                m_usedRecord->push_back(currentProgram);
                qDebug() << "CurrentProgram is"
                         << currentProgram
                         << "which is not in memory, but having available space.";
                emit eliminate(false, m_programInMem->size() - 1, programIndex, currentProgram);
            }
        }
    }
}
