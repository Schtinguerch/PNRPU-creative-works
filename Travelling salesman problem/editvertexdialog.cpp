#include "editvertexdialog.h"
#include "ui_editvertexdialog.h"

EditVertexDialog::EditVertexDialog(QWidget *parent) : QDialog(parent), ui(new Ui::EditVertexDialog)
{
    ui->setupUi(this);

    connect(ui->ApplyPushButton, SIGNAL(clicked()), this, SLOT(ApplySettingsOnClick()));
    connect(ui->CancelPushButton, SIGNAL(clicked()), this, SLOT(CancelOnClick()));
}

EditVertexDialog::~EditVertexDialog()
{
    delete ui;
}

void EditVertexDialog::ApplySettingsOnClick()
{
    QStringList connections = ui->VertexRefsPlainTextEdit->toPlainText().split("\n");

    for (QString connection : connections)
    {
        if (connection.contains(": "))
        {
            connection = connection.replace(", ", ";");
            QStringList data = connection.split(": ");

            int startVertex = _index - 1,
                endVertex = data[0].toInt() - 1,
                outValue = 0, inValue = 0;

            QStringList vertexes = data[1].split(";");

            if (vertexes.length() == 1)
            {
                outValue = vertexes[0].toInt();
                inValue = outValue;
            }

            else if (vertexes.length() == 2)
            {
                outValue = vertexes[0].toInt();
                inValue = vertexes[1].toInt();
            }

            _intermediary->AdjacencyMatrix = _intermediary->Processor->AddConnection(_intermediary->AdjacencyMatrix, startVertex, endVertex, outValue);
            _intermediary->AdjacencyMatrix = _intermediary->Processor->AddConnection(_intermediary->AdjacencyMatrix, endVertex, startVertex, inValue);
        }
    }

    QString data = _intermediary->Processor->MatrixToString(_intermediary->AdjacencyMatrix);
    _widget->GetPresenter()->initializePresenter();

    hide();
}

void EditVertexDialog::CancelOnClick()
{
    hide();
}

void EditVertexDialog::ShowConnections(int index)
{
    int startIndex = index;
    if (index >= 0 && index < _intermediary->AdjacencyMatrix.count())
    {
        QString connectionRow = "";

        for (int i = 0; i < _intermediary->AdjacencyMatrix.count(); i++)
        {
            if (i == startIndex) continue;

            int value = _intermediary->AdjacencyMatrix[startIndex][i];
            bool isFirstConnect = true;

            connectionRow += QString::number(i + 1) + ": " + QString::number(value);

            value = _intermediary->AdjacencyMatrix[i][startIndex];
            connectionRow += ", " + QString::number(value) + '\n';

        }

        ui->VertexRefsPlainTextEdit->setPlainText(connectionRow);
    }


}

void EditVertexDialog::on_EditedVertexIndexLineEdit_textEdited(const QString &arg1)
{
    _index = ui->EditedVertexIndexLineEdit->text().toInt();
    ShowConnections(_index - 1);
}

