#ifndef DELETEVERTEXDIALOG_H
#define DELETEVERTEXDIALOG_H

#include <QDialog>
#include "myopenglwidget.h"

namespace Ui {
class DeleteVertexDialog;
}

class DeleteVertexDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteVertexDialog(QWidget *parent = nullptr);
    ~DeleteVertexDialog();

    void SetIntermediary(Intermediary* intermedary) { _intermediary = intermedary; }
    void SetGLWidget(MyOpenGLWidget* widget) { _widget = widget; }

private slots:
    void on_ApplySettingsPushButton_clicked();
    void on_CancelPushButton_clicked();

private:
    Ui::DeleteVertexDialog *ui;

    Intermediary* _intermediary;
    QVector<QVector<int>> _adjMatrix;
    MyOpenGLWidget* _widget;
};

#endif // DELETEVERTEXDIALOG_H
