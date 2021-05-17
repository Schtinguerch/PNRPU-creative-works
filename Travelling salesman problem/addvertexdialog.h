#ifndef ADDVERTEXDIALOG_H
#define ADDVERTEXDIALOG_H

#include <QDialog>
#include "myopenglwidget.h"

namespace Ui {
class AddVertexDialog;
}

class AddVertexDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddVertexDialog(QWidget *parent = nullptr);
    ~AddVertexDialog();

    void SetIntermediary(Intermediary* intermedary) { _intermediary = intermedary; }
    void SetGLWidget(MyOpenGLWidget* widget) { _widget = widget; }

private:
    Ui::AddVertexDialog *ui;

    Intermediary* _intermediary;
    QVector<QVector<int>> _adjMatrix;
    MyOpenGLWidget* _widget;

private slots:
    void ApplySettingsOnClick();
    void CancelOnClick();
};

#endif // ADDVERTEXDIALOG_H
