#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <polynomcalculator.h>

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
    Ui::MainWindow *ui;
    PolynomCalculator calculator;
    QString SpacedQString(QString target);

private slots:
    void equalExpressionClicked();
    void clearDataClicked();
    void inputPolynoms();
};
#endif // MAINWINDOW_H
