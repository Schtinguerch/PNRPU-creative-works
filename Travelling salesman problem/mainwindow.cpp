#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _intermediary = new Intermediary;

    _presentWidget = new MyOpenGLWidget(this);
    _presentWidget->ConnectIntermediary(_intermediary);

     ui->GraphicsLayout->addWidget(_presentWidget);

    _presentWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    _presentWidget->redraw();

    connect(ui->AddVertexPushButton, SIGNAL(clicked()), this, SLOT(AddVertexOnClick()));
    connect(ui->EditVertexPushButton, SIGNAL(clicked()), this, SLOT(EditVertexOnClick()));
    connect(ui->DeleteVertexPushButton, SIGNAL(clicked()), this, SLOT(DeleteVertexOnClick()));

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(TimerOnTick()));

    timer->setInterval(100);
    timer->start();
}

int ticks = 0;

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::AddVertexOnClick()
{
    AddVertexDialog* dialog = new AddVertexDialog;

    dialog->SetIntermediary(_intermediary);
    dialog->SetGLWidget(_presentWidget);

    dialog->show();
}

void MainWindow::EditVertexOnClick()
{
    EditVertexDialog* dialog = new EditVertexDialog;

    dialog->SetIntermediary(_intermediary);
    dialog->SetGLWidget(_presentWidget);

    dialog->show();
}

void MainWindow::DeleteVertexOnClick()
{
    DeleteVertexDialog* dialog = new DeleteVertexDialog;

    dialog->SetIntermediary(_intermediary);
    dialog->SetGLWidget(_presentWidget);

    dialog->show();
}

void MainWindow::TimerOnTick()
{
    ui->GotRouteLineEdit->setText(_intermediary->SalesmanRoute);

    int length = _intermediary->SalesmanRootLength;
    ui->GotRouteLengthLineEdit->setText((length > -1)? QString::number(length) : "");

    ticks++;
    if (ticks % 5 == 0)
    {
        try
        {
            _presentWidget->GetPresenter()->Tick();
            _presentWidget->redraw();
        }

        catch (...)
        {

        }
    }
}
