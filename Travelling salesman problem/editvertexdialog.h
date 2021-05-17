#ifndef EDITVERTEXDIALOG_H
#define EDITVERTEXDIALOG_H

#include <QDialog>
#include "myopenglwidget.h"

namespace Ui {
class EditVertexDialog;
}

class EditVertexDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditVertexDialog(QWidget *parent = nullptr);
    ~EditVertexDialog();

    void SetIntermediary(Intermediary* intermedary) { _intermediary = intermedary; }
    void SetGLWidget(MyOpenGLWidget* widget) { _widget = widget; }
    void ShowConnections(int index);

private:
    Ui::EditVertexDialog *ui;

    Intermediary* _intermediary;
    QVector<QVector<int>> _adjMatrix;
    MyOpenGLWidget* _widget;
    int _index;

private slots:
    void ApplySettingsOnClick();
    void CancelOnClick();
    void on_EditedVertexIndexLineEdit_textEdited(const QString &arg1);
};

#endif // EDITVERTEXDIALOG_H
