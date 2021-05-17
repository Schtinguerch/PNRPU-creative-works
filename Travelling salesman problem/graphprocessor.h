#ifndef GRAPHPROCESSOR_H
#define GRAPHPROCESSOR_H

#include <QVector>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

class GraphProcessor
{
private:
    QVector<QVector<int>> _adjancencyMatrix;

public:
    GraphProcessor();
    GraphProcessor(QVector<QVector<int>> adjMatrix);

    QVector<QVector<int>> GetAdjancencyMatrix();
    void SetAdjancencyMatrix(QVector<QVector<int>> adjMatrix);

    QVector<QVector<int>> StringToMatrix(QString adjMatrixData);
    QString MatrixToString(QVector<QVector<int>> adjMatrix);

    QVector<QVector<int>> AddVertex(QVector<QVector<int>> adjMatrix);
    QVector<QVector<int>> AddConnection(QVector<QVector<int>> adjMatrix, int startVertex, int endVertex, int value);
    QVector<QVector<int>> DeleteVertex(QVector<QVector<int>> adjMatrix, int vertex);
};

#endif // GRAPHPROCESSOR_H
