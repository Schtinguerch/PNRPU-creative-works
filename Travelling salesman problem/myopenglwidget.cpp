#include "myopenglwidget.h"
#include "graphpresenter.h"
#include <QPainter>

MyOpenGLWidget::MyOpenGLWidget(QWidget* parent) : QOpenGLWidget(parent)
{
    _presenter = new GraphPresenter;

    QSurfaceFormat format = QSurfaceFormat::defaultFormat();
    format.setSamples(4);

    this->setFormat(format);
}

MyOpenGLWidget::~MyOpenGLWidget()
{
    if (_presenter != nullptr)
        delete _presenter;
}

void MyOpenGLWidget::redraw()
{
    this->update();
}

void MyOpenGLWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter;

    painter.begin(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    _presenter->draw(&painter,event);
    painter.end();
}

void MyOpenGLWidget::SetGraphPresenter(GraphPresenter *presenter)
{
    if (presenter != nullptr)
        _presenter = presenter;
}

void MyOpenGLWidget::ConnectIntermediary(Intermediary *intermediary)
{
    if (intermediary != nullptr)
    {
        _intermediary = intermediary;
      //  _intermediary->GlWidget = this;
        CopyIntermediry();
    }
}

void MyOpenGLWidget::CopyIntermediry()
{
    if (_intermediary != nullptr || _presenter != nullptr)
        _presenter->connectIntermediary(_intermediary);
}
