#include "graphpresenter.h"
#include "travellingsalemanproblemsolver.h"

#include <QPaintEvent>
#include <QPainter>
#include <QWidget>
#include <QtCore/qmath.h>
#include <QObject>

double pi = 3.1415,
       peakAngleRadians = pi / 8;

int xPadding,
    yPadding;

GraphPresenter::GraphPresenter() {}

void GraphPresenter::initializePresenter()
{
    _adjancencyMatrix = _intermediary->AdjacencyMatrix;
    TravellingSalemanProblemSolver solver(_adjancencyMatrix);

    _ticks = 0;

    try
    {
        _route = solver.ComputeRoot();
    }

    catch (...)
    {
        _route = QVector<int> { -1 };
    }

    _intermediary->SetSalesmanRoot(_route);
    _intermediary->SalesmanRootLength = solver.GetRouteLength();

    _vertexRadius = _intermediary->VertexRadius;
    _fontSize = _intermediary->FontSize;
    _fontFamily = _intermediary->FontFamily;
    _arrowPeakLength = _intermediary->ArrowPeakLength;

    _vertexBackground = _intermediary->VertexBackground;
    _canvasBackground = _intermediary->CanvasBackground;
    _foregroundPen = _intermediary->Foreground;
}

void GraphPresenter::draw(QPainter *painter, QPaintEvent *event)
{
    drawGraph(painter, event);
    drawRoot(painter, event);
}

void GraphPresenter::drawGraph(QPainter *painter, QPaintEvent* event)
{
    int vertexCount = _adjancencyMatrix[0].size();
    _graphRadius = qMax(painter->window().width() / 5, 100);

    yPadding = painter->window().height() / 2;
    xPadding = painter->window().width() / 2;

    painter->fillRect(event->rect(), _canvasBackground);
    painter->setBrush(_vertexBackground);

    painter->setPen(_foregroundPen);
    painter->setFont(QFont(_fontFamily, _fontSize * 0.8));

    _foregroundPen.setWidth(3);

    for (int i = 0; i < vertexCount; i++)
    {
        //угол (полярная система координат)
        double polarAngle = pi * 3 / 2 + pi * 2 / vertexCount * i;

        //координаты узла графа (декартова система координат)
        int xc = cos(polarAngle) * _graphRadius + xPadding;
        int yc = sin(polarAngle) * _graphRadius + yPadding;

        //координаты текста (номер вершины)
        int c1 = xc - 20,
            c2 = yc - _fontSize / 2,
            c3 = 40,
            c4 = _fontSize;

        QString text; text.setNum(i + 1);
        painter->drawEllipse(QRectF(xc - _vertexRadius, yc - _vertexRadius, 2 * _vertexRadius, 2 * _vertexRadius));
        painter->drawText(QRect(c1, c2, c3, c4), Qt::AlignCenter, text);

        for (int k = 0; k < vertexCount; k++)
        {
            if (_adjancencyMatrix[i][k] != 0)
            {
                if ((i == _prevVertex - 1 && k == _nextVertex - 1) || (i == _nextVertex - 1 && k == _prevVertex - 1) && _route[0] != -1)
                {
                    painter->setBrush(_intermediary->VertexHighLightBackground);
                    painter->setPen(_intermediary->ForegroundHighLight);
                    _intermediary->ForegroundHighLight.setWidth(5);

                    painter->drawEllipse(QRectF(xc - _vertexRadius, yc - _vertexRadius, 2 * _vertexRadius, 2 * _vertexRadius));
                    painter->drawText(QRect(c1, c2, c3, c4), Qt::AlignCenter, text);
                }

                //линия
                double a2 = pi * 3 / 2 + pi * 2 / vertexCount * k,
                       xc2 = cos(a2) * _graphRadius + xPadding,
                       yc2 = sin(a2) * _graphRadius + yPadding;

                double l = sqrt((xc2 - xc) * (xc2 - xc) + (yc2 - yc) * (yc2 - yc));

                int xl1 = (xc2 - xc) / l * _vertexRadius + xc,
                    yl1 = (yc2 - yc) / l * _vertexRadius + yc,

                    xl2 = xc2 - (xc2 - xc) / l * _vertexRadius,
                    yl2 = yc2 - (yc2 - yc) / l * _vertexRadius;

                painter->drawLine(xl1, yl1, xl2, yl2);

                //стрелка
                double peakBaseAngleRadians;

                if (xc2 == xl2 && yl2 < yc2)
                    peakBaseAngleRadians = pi * 3 / 2;

                else if (yc2 == yl2 && xl2 < xc2)
                    peakBaseAngleRadians = pi;

                else if (xc2 == xl2 && yl2 > yc2)
                    peakBaseAngleRadians = pi / 2;

                else if (yc2 == yl2 && xl2 > xc2)
                    peakBaseAngleRadians = 0;

                else if (xl2 > xc2 && yl2 < yc2)
                    peakBaseAngleRadians = atan((yc2 - yl2) / (xc2 - xl2)) + pi * 2;

                else if (xl2 < xc2 && yl2 < yc2)
                    peakBaseAngleRadians = atan((yc2 - yl2) / (xc2 - xl2)) + pi;

                else if (xl2 < xc2 && yl2 > yc2)
                    peakBaseAngleRadians = atan((yc2 - yl2) / (xc2 - xl2)) + pi;

                else if (xl2 > xc2 && yl2 > yc2)
                    peakBaseAngleRadians = atan((yc2 - yl2) / (xc2 - xl2));

                int xs1 = cos(peakBaseAngleRadians + peakAngleRadians) * _arrowPeakLength + xl2,
                    ys1 = sin(peakBaseAngleRadians + peakAngleRadians) * _arrowPeakLength + yl2,
                    xs2 = cos(peakBaseAngleRadians - peakAngleRadians) * _arrowPeakLength + xl2,
                    ys2 = sin(peakBaseAngleRadians - peakAngleRadians) * _arrowPeakLength + yl2;

                painter->drawLine(xl2, yl2, xs1, ys1);
                painter->drawLine(xl2, yl2, xs2, ys2);

                //текст
                int textWidth = 40,
                    textHeight = _fontSize + 5,

                    lineCenterX = (xl2 + xl1) / 2,
                    lineCenterY = (yl2 + yl1) / 2;

                QString lengthText = QString::number(_adjancencyMatrix[i][k]);

                if (_adjancencyMatrix[i][k] != _adjancencyMatrix[k][i] && _adjancencyMatrix[i][k] != 0 && i != k
                        && _adjancencyMatrix[k][i] != 0)
                {
                    textWidth += 24;
                    lengthText += "; " + QString::number(_adjancencyMatrix[k][i]);
                }

                painter->setBrush(_intermediary->PanelBackground);
                painter->setPen(_intermediary->PanelBorder);
                painter->drawRect(lineCenterX - textWidth / 2, lineCenterY - textHeight / 2, textWidth, textHeight);

                painter->setBrush(_vertexBackground);
                painter->setPen(_foregroundPen);
                painter->drawText(QRect(lineCenterX - textWidth / 2, lineCenterY - textHeight / 2, textWidth, textHeight), Qt::AlignCenter, lengthText);
            }
        }

        painter->setBrush(_vertexBackground);
        painter->setPen(_foregroundPen);
    }
}

void GraphPresenter::drawRoot(QPainter *painter, QPaintEvent* event)
{
    int ticks = 1;
    if (_route.count() > 1)
        ticks = _ticks % (_route.count() - 1);

    if (_route[0] != -1)
    {
        int
            vertexCount = _adjancencyMatrix[0].size(),

            rectHeight = _vertexRadius * 2 + 32,
            rectWidth = (_vertexRadius * 2 + 40) * _route.count(),

            rectX = (painter->window().width() - rectWidth) / 2,
            rectY = painter->window().height() - rectHeight + 4;

        painter->setBrush(_intermediary->PanelBackground);
        painter->setPen(_intermediary->PanelBorder);

        painter->drawRect(rectX, rectY, rectWidth, rectHeight);

        painter->setBrush(_vertexBackground);
        painter->setPen(_foregroundPen);

        painter->drawLine
        (
            rectX + _vertexRadius / 2 + 10,
            rectY + rectHeight / 2,
            rectX + rectWidth - _vertexRadius / 2 - 10,
            rectY + rectHeight / 2
        );

        painter->setBrush(_intermediary->VertexHighLightBackground);
        painter->setPen(_intermediary->ForegroundHighLight);
        _intermediary->ForegroundHighLight.setWidth(5);

        painter->drawLine
        (
            rectX + _vertexRadius / 2,
            rectY + rectHeight / 2,
            rectX + _vertexRadius / 2 + rectWidth * ticks / _route.count(),
            rectY + rectHeight / 2
        );

        painter->setBrush(_vertexBackground);
        painter->setPen(_foregroundPen);
        _foregroundPen.setWidth(3);

        for (int i = 0; i < _route.count(); i++)
        {
            int pointX = rectX + _vertexRadius / 2 + rectWidth * i / _route.count(),
                pointY = rectY + (rectHeight - _vertexRadius * 2) / 2,
                diameter = 2 * _vertexRadius;

            QString text = QString::number(_route[i]);

            if (i == ticks)
            {
                painter->setBrush(_intermediary->VertexHighLightBackground);
                painter->setPen(_intermediary->ForegroundHighLight);
                _intermediary->ForegroundHighLight.setWidth(5);
            }

            painter->drawEllipse(QRectF(pointX, pointY, diameter, diameter));
            painter->drawText(QRect(pointX, pointY, diameter, diameter), Qt::AlignCenter, text);

            painter->setBrush(_vertexBackground);
            painter->setPen(_foregroundPen);
            _foregroundPen.setWidth(3);
        }
    }
}

void GraphPresenter::connectIntermediary(Intermediary *intermediary)
{
    if (intermediary != nullptr)
    {
        _intermediary = intermediary;
        initializePresenter();
    }
}

void GraphPresenter::Tick()
{
    _ticks++;
    try
    {
        int iterations = _route.count() - 1;
        if (iterations != 0)
        {
            _prevVertex = _route[(_ticks - 1) % iterations];
            _nextVertex = _route[_ticks % iterations];
        }
    }
    catch (...)
    {

    }

}
