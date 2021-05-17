#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <addvertexdialog.h>
#include <editvertexdialog.h>
#include <deletevertexdialog.h>

#include "myopenglwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow* ui;

    MyOpenGLWidget* _presentWidget;
    Intermediary*  _intermediary;

private slots:
    void AddVertexOnClick();
    void EditVertexOnClick();
    void DeleteVertexOnClick();
    void TimerOnTick();
};
#endif // MAINWINDOW_H
