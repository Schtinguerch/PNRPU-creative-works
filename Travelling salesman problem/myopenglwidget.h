#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H
#include "graphpresenter.h"
#include <QOpenGLWidget>

class MyOpenGLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    MyOpenGLWidget(QWidget *parent);
    ~MyOpenGLWidget();

    void SetGraphPresenter(GraphPresenter* presenter);
    void ConnectIntermediary(Intermediary* intermediary);
    GraphPresenter* GetPresenter() { return _presenter; };

public slots:
    void redraw();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    GraphPresenter* _presenter;
    Intermediary*   _intermediary;

    void CopyIntermediry();
};

#endif // MYOPENGLWIDGET_H
