#include "travellingsalemanproblemsolver.h"
#include <algorithm>

TravellingSalemanProblemSolver::TravellingSalemanProblemSolver()
{

}

TravellingSalemanProblemSolver::TravellingSalemanProblemSolver(QVector<QVector<int>> adjMatrix)
{
    _adjacencyMatrix = adjMatrix;
    SetNullValueIntoInfinity(_adjacencyMatrix);
}

void TravellingSalemanProblemSolver::SetNullValueIntoInfinity(QVector<QVector<int>> &adjMatrix)
{
    for (int i = 0; i < adjMatrix.size(); i++)
    {
        for (int k = 0; k < adjMatrix.size(); k++)
        {
            if (i == k || adjMatrix[i][k] == 0)
                adjMatrix[i][k] = INT_MAX;
        }
    }
}

QVector<int> TravellingSalemanProblemSolver::InfinityFullVector(int length)
{
    QVector<int> infinityFill(length);
    std::fill(infinityFill.begin(), infinityFill.end(), INT_MAX);

    return infinityFill;
}

QVector<int> TravellingSalemanProblemSolver::ComputeRoot(QVector<QVector<int>> adjMatrix)
{
    _adjacencyMatrix = adjMatrix;
    SetNullValueIntoInfinity(_adjacencyMatrix);

    return ComputeRoot();
}

QVector<int> TravellingSalemanProblemSolver::ComputeRoot()
{
    QVector<int> result_arr_1;
    QVector<int> result_arr_2;
    QVector<int> valueRoutes;

    int sum = 0,
        steps = 0;
    bool flag = true;
    QVector<QVector<int>> data = _adjacencyMatrix;

    int len = data[0].size();

    while (flag)
    {
        steps++;
        if (steps > 1000)
        {
            _route = QVector<int> { -1 };
            _routeLength = -1;
            throw 1;
        }

        QVector<int> row = InfinityFullVector(len);
        QVector<int> column = InfinityFullVector(len);

        for (int i = 0; i < len; i++)
            for (int k = 0; k < len; k++)
                row[i] = qMin(row[i], data[i][k]);

        for (int i = 0; i < len; i++)
            for (int k = 0; k < len; k++)
                if (row[i] != INT_MAX && data[i][k] != INT_MAX)
                    data[i][k] -= row[i];

        for (int i = 0; i < len; i++)
            for (int k = 0; k < len; k++)
                column[k] = qMin(column[k], data[i][k]);

        for (int i = 0; i < len; i++)
            for (int k = 0; k < len; k++)
                if (column[k] != INT_MAX && data[i][k] != INT_MAX)
                    data[i][k] -= column[k];

        int max_mark_x,
            max_mark_y,
            max_mark = -1;

        for (int i = 0; i < len; i++)
        {
            for (int k = 0; k < len; k++)
            {
                if (data[i][k] == 0)
                {
                    int min1 = INT_MAX;
                    int min2 = INT_MAX;

                    for (int j = 0; j < len; j++)
                        if (j != k)
                            min1 = qMin(min1, data[i][j]);

                    for (int j = 0; j < len; j++)
                        if (j != i)
                            min2 = qMin(min2, data[j][k]);

                    if (min1 == INT_MAX || min2 == INT_MAX || min1 + min2 > max_mark)
                    {
                        max_mark = min1 + min2;
                        max_mark_x = i;
                        max_mark_y = k;
                    }
                }
            }
        }

        sum += _adjacencyMatrix[max_mark_x][max_mark_y];
        data[max_mark_y][max_mark_x] = INT_MAX;

        for (int i = 0; i < len; i++)
        {
            data[max_mark_x][i] = INT_MAX;
            data[i][max_mark_y] = INT_MAX;
        }

        result_arr_1.push_back(max_mark_x + 1);
        result_arr_2.push_back(max_mark_y + 1);

        flag = false;
        int counter = 0;

        for (int i = 0; i < len; i++)
            for (int k = 0; k < len; k++)
                if (data[i][k] != INT_MAX)
                    flag = true;
    }

    valueRoutes.push_back(result_arr_1[0]);
    valueRoutes.push_back(result_arr_2[0]);

    int x = result_arr_2[0];

    result_arr_1.erase(result_arr_1.begin());
    result_arr_2.erase(result_arr_2.begin());

    while (result_arr_1.size() != 0)
    {
        steps++;
        if (steps > 1000)
        {
            _route = QVector<int> { -1 };
            _routeLength = -1;
            throw 1;
        }

        for (int i = 0; i < result_arr_1.size(); i++)
        {
            if (result_arr_1[i] == x)
            {
                valueRoutes.push_back(result_arr_2[i]);
                x = result_arr_2[i];

                result_arr_1.erase(result_arr_1.begin() + i);
                result_arr_2.erase(result_arr_2.begin() + i);
                break;
            }
        }
    }

    _route = valueRoutes;
    _routeLength = sum;
    return valueRoutes;
}
