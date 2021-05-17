#ifndef INTERMEDIARY_H
#define INTERMEDIARY_H

#include <QString>
#include <QBrush>
#include <QPen>

#include "graphprocessor.h"

class Intermediary
{
public:
    Intermediary();
    GraphProcessor* Processor = new GraphProcessor();

    int
        FontSize = 24,
        VertexRadius = 36,
        ArrowPeakLength = 18;

    QBrush
        VertexBackground = QBrush(QColor(186, 225, 255)),
        CanvasBackground = QBrush(QColor(250, 250, 250)),
        PanelBackground = QBrush(QColor(255, 255, 255)),
        VertexHighLightBackground = QBrush(QColor(255, 154, 162));

    QString FontFamily = "Bahnschrift";

    QPen Foreground = QPen(QColor(72, 72, 72)),
         PanelBorder = QPen(QColor(200, 200, 200)),
         ForegroundHighLight = QPen(QColor(255, 67, 8));

    int SalesmanRootLength = -1;
    QString SalesmanRoute;
    QVector<QVector<int>> AdjacencyMatrix =
    {
        {0, 0, 0, 26, 9, 0, 0},
        {0, 0, 0, 17, 0, 0, 23},
        {0, 0, 0, 0, 13, 5, 0},
        {26, 17, 0, 0, 0, 42, 0},
        {9, 0, 13, 0, 0, 0, 30},
        {0, 0, 5, 42, 0, 0, 19},
        {0, 23, 0, 0, 30, 19, 0},
    };

    void SetSalesmanRoot(QVector<int> route);
};

#endif // INTERMEDIARY_H
