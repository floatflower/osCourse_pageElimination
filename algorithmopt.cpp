#include "algorithmopt.h"

#include <QVector>
#include <QDebug>
#include <QHash>

AlgorithmOPT::AlgorithmOPT(QObject *parent)
    : Algorithm(parent)
{
    m_programInMem = new QVector<char>;
}
void AlgorithmOPT::simulate()
{
    int programIndex = 0;
    for (QQueue<char>::iterator it_programSerial = m_programSerial->begin();
         it_programSerial != m_programSerial->end();
         it_programSerial ++, programIndex ++) {
        char currentProgram = *it_programSerial;
        int programPosition = m_programInMem->indexOf(currentProgram);
        if (programPosition != -1) {
            // In memory
            qDebug() << "Current Program is"
                     << currentProgram
                     << "which in memory, no elimination.";
            emit eliminate(false, -1, programIndex, currentProgram);
        }
        else {
            // Not in memory
            if (m_programInMem->size() == m_pageNum) {
                QHash<char, int> futureTable;
                for (QVector<char>::iterator it_programInMem = m_programInMem->begin();
                     it_programInMem != m_programInMem->end();
                     it_programInMem ++) {
                    char program = *it_programInMem;
                    futureTable.insert(program, -1);
                }
                int count = 1;
                for (QQueue<char>::iterator it_futureProgram = it_programSerial + 1;
                     it_futureProgram != m_programSerial->end();
                     it_futureProgram ++, count ++) {
                    char futureProgram = *it_futureProgram;
                    if (futureTable.contains(futureProgram) && futureTable.value(futureProgram) == -1) {
                        futureTable.insert(futureProgram, count);
                    }
                }
                int max = 0;
                char eliminateProgram;
                for (QHash<char, int>::iterator it_futureTable = futureTable.begin();
                     it_futureTable != futureTable.end();
                     it_futureTable ++) {
                    //qDebug()<<it_futureTable.value()<<it_futureTable.key();
                    if (it_futureTable.value() == -1) {
                        eliminateProgram = it_futureTable.key();
                        break;
                    }
                    if (it_futureTable.value() > max) {
                        max = it_futureTable.value();
                        eliminateProgram = it_futureTable.key();
                    }
                }
                qDebug() << "CurrentProgram is"
                         << currentProgram
                         << "which is not in memory, eliminating program"
                         << eliminateProgram;
                int eliminateProgramPosition = m_programInMem->indexOf(eliminateProgram);
                m_programInMem->replace(eliminateProgramPosition, currentProgram);
                emit eliminate(true, eliminateProgramPosition, programIndex, currentProgram);
            }
            else if (m_programInMem->size() < m_pageNum) {
                m_programInMem->push_back(currentProgram);
                qDebug() << "CurrentProgram is"
                         << currentProgram
                         << "which is not in memory, but having available space.";
                emit eliminate(false, m_programInMem->size() - 1, programIndex, currentProgram);
            }
        }
    }
}
