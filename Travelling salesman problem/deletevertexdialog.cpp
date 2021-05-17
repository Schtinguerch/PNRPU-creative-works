#include "deletevertexdialog.h"
#include "ui_deletevertexdialog.h"

DeleteVertexDialog::DeleteVertexDialog(QWidget *parent) : QDialog(parent), ui(new Ui::DeleteVertexDialog)
{
    ui->setupUi(this);
    ui->DelitableVertexIndexLineEdit->setText("1");
}

DeleteVertexDialog::~DeleteVertexDialog()
{
    delete ui;
}

void DeleteVertexDialog::on_ApplySettingsPushButton_clicked()
{
    int deletedVertex = ui->DelitableVertexIndexLineEdit->text().toInt() - 1;

    if (deletedVertex >= 0 && deletedVertex < _intermediary->AdjacencyMatrix.count())
        _intermediary->AdjacencyMatrix = _intermediary->Processor->DeleteVertex(_intermediary->AdjacencyMatrix, deletedVertex);
    _widget->GetPresenter()->initializePresenter();

    hide();
}


void DeleteVertexDialog::on_CancelPushButton_clicked()
{
    hide();
}

