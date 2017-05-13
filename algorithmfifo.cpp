#include "algorithmfifo.h"
#include <QQueue>
#include <QHash>
#include <QDebug>

AlgorithmFIFO::AlgorithmFIFO(QObject *parent)
    : Algorithm(parent)
{
    m_programRecord = new QQueue<char>;
    m_programInMem = new QVector<char>;
}

void AlgorithmFIFO::simulate()
{
    int programIndex = 0;
    for (QQueue<char>::iterator it_programSerial = m_programSerial->begin();
         it_programSerial != m_programSerial->end();
         it_programSerial ++, programIndex ++) {
        char currentProgram = (*it_programSerial);
        int programPosition = m_programInMem->indexOf(currentProgram);
        if (programPosition != -1) {
            // In memory
            qDebug() << "Current Program is"
                     << currentProgram
                     << "which in memory, no elimination.";
            emit eliminate(false, -1, programIndex, '@');
        }
        else {
            // Not in memory
            if (m_programInMem->size() == m_pageNum) {
                char firstIn = m_programRecord->front();
                m_programRecord->pop_front();
                m_programRecord->push_back(currentProgram);
                int eliminateProgramPosition = m_programInMem->indexOf(firstIn);
                m_programInMem->replace(eliminateProgramPosition, currentProgram);
                qDebug() << "CurrentProgram is"
                         << currentProgram
                         << "which is not in memory, eliminating program"
                         << firstIn;
                emit eliminate(true, eliminateProgramPosition, programIndex, currentProgram);
            }
            else if (m_programInMem->size() < m_pageNum){
                m_programInMem->push_back(currentProgram);
                m_programRecord->push_back(currentProgram);
                qDebug() << "CurrentProgram is"
                         << currentProgram
                         << "which is not in memory, but having available space.";
                emit eliminate(false, m_programInMem->size() - 1, programIndex, currentProgram);
            }
        }
    }
    emit simulateFinished();
}
