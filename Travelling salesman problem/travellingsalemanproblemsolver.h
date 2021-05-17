#ifndef TRAVELLINGSALEMANPROBLEMSOLVER_H
#define TRAVELLINGSALEMANPROBLEMSOLVER_H

#include <QVector>

class TravellingSalemanProblemSolver
{
private:
    QVector<QVector<int>> _adjacencyMatrix;
    QVector<int> _route;
    int _routeLength = -1;

    void SetNullValueIntoInfinity(QVector<QVector<int>>& adjMatrix);
    QVector<int> InfinityFullVector(int length);

public:
    TravellingSalemanProblemSolver();
    TravellingSalemanProblemSolver(QVector<QVector<int>> adjMatrix);

    QVector<int> ComputeRoot();
    QVector<int> ComputeRoot(QVector<QVector<int>> adjMatrix);

    QVector<int> GetRouteVertexes() { return _route; }
    int GetRouteLength() { return _routeLength; }
};

#endif // TRAVELLINGSALEMANPROBLEMSOLVER_H
