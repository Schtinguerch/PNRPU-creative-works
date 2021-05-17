#include "graphprocessor.h"
#include <QStringList>
#include <qmath.h>

GraphProcessor::GraphProcessor() {}

GraphProcessor::GraphProcessor(QVector<QVector<int>> adjMatrix)
{
    _adjancencyMatrix = adjMatrix;
}

QVector<QVector<int>> GraphProcessor::GetAdjancencyMatrix()
{
    return _adjancencyMatrix;
}

void GraphProcessor::SetAdjancencyMatrix(QVector<QVector<int>> adjMatrix)
{
    _adjancencyMatrix = adjMatrix;
}

QVector<QVector<int>> GraphProcessor::StringToMatrix(QString adjMatrixData)
{
    QVector<QVector<int>> adjMatrix;

    QString data = adjMatrixData;
    data = data.replace(", ", ";");
    data = data.replace(",\n", " ");
    data = data.replace(" ", ";");
    data = data.replace(" \n", " ");
    data = data.replace("\n\n", ";");
    data = data.replace("\n", ";");

    int index = -1;
    QStringList numbers = data.split(";");
    for (int i = 0; i < sqrt(numbers.count()); i++)
    {
        QVector<int> row;
        for (int j = 0; j < sqrt(numbers.count()); j++)
        {
            index++;
            row.push_back(numbers[i].toInt());
        }
        adjMatrix[i] = row;
    }

    return adjMatrix;
}

QString GraphProcessor::MatrixToString(QVector<QVector<int>> adjMatrix)
{
    QString data;
    for (int i = 0; i < adjMatrix[0].size(); i++)
    {
        data += QString::number(adjMatrix[i][0]);
        for (int j = 1; j < adjMatrix[0].size(); j++)
            data += ' ' + QString::number(adjMatrix[i][j]);
        data += '\n';
    }

    return data;
}


QVector<QVector<int>> GraphProcessor::AddVertex(QVector<QVector<int>> adjMatrix)
{
    QVector<int> newRow;
    newRow.push_back(0);

    for (int i = 0; i < adjMatrix.count(); i++)
    {
        adjMatrix[i].push_back(0);
        newRow.push_back(0);
    }

    adjMatrix.push_back(newRow);
    return adjMatrix;
}

QVector<QVector<int>> GraphProcessor::AddConnection(QVector<QVector<int>> adjMatrix, int startVertex, int endVertex, int value)
{
    adjMatrix[startVertex][endVertex] = value;
    return adjMatrix;
}

QVector<QVector<int>> GraphProcessor::DeleteVertex(QVector<QVector<int>> adjMatrix, int vertex)
{
    adjMatrix.removeAt(vertex);
    for (int i = 0; i < adjMatrix.count(); i++)
        adjMatrix[i].removeAt(vertex);

    return adjMatrix;
}
