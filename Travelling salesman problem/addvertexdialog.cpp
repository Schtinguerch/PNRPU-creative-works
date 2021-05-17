#include "addvertexdialog.h"
#include "ui_addvertexdialog.h"

#include <QMessageBox>

AddVertexDialog::AddVertexDialog(QWidget *parent) : QDialog(parent), ui(new Ui::AddVertexDialog)
{
    ui->setupUi(this);
    connect(ui->ApplyPushButton, SIGNAL(clicked()), this, SLOT(ApplySettingsOnClick()));
    connect(ui->CancelPushButton, SIGNAL(clicked()), this, SLOT(CancelOnClick()));
}

AddVertexDialog::~AddVertexDialog()
{
    delete ui;
}

void AddVertexDialog::ApplySettingsOnClick()
{
    _intermediary->AdjacencyMatrix = _intermediary->Processor->AddVertex(_intermediary->AdjacencyMatrix);
    QStringList connections = ui->VertexRefsPlainTextEdit->toPlainText().split("\n");

    for (QString connection : connections)
    {
        if (connection.contains(": "))
        {
            connection = connection.replace(", ", ";");
            QStringList data = connection.split(": ");

            int startVertex = _intermediary->AdjacencyMatrix.count() - 1,
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

void AddVertexDialog::CancelOnClick()
{
    hide();
}
