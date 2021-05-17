#ifndef MYPAINTER_H
#define MYPAINTER_H

#include <QBrush>
#include <QFont>
#include <QPen>
#include <QWidget>

#include "intermediary.h"

class GraphPresenter
{
public:
    GraphPresenter();

public:
    void draw(QPainter *painter, QPaintEvent *event);
    void initializePresenter();
    void connectIntermediary(Intermediary* intermediary);

    void drawGraph(QPainter* painter, QPaintEvent* event);
    void drawRoot(QPainter* painter, QPaintEvent* event);
    void Tick();

private:
    Intermediary* _intermediary;

    QVector<QVector<int>> _adjancencyMatrix;
    QVector<int> _route;

    int _graphRadius,
        _vertexRadius,
        _arrowPeakLength,
        _fontSize,

        _ticks = 0,
        _prevVertex,
        _nextVertex;

    QString _fontFamily;
    QPen _foregroundPen;

    QBrush _vertexBackground,
           _canvasBackground;
};

#endif //MYPAINTER_H
