#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDoubleValidator>

QString MainWindow::SpacedQString(QString target)
{
    QString value = target;
    int index = 0;

    while (index < value.length())
    {
        QChar ch = value[index];
        if ((ch == '+') || (ch == '-') || (ch == '*') || (ch == '/') || (ch == '^'))
        {
            value.insert(index, ' ');
            value.insert(index + 2, ' ');
            index++;
        }

        index++;
    }

    for (int i = 0; i < value.length(); i++)
        if (value[i] == '\n')
            value [i] = ' ';

    return value;
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->solveEquationPushButton,  SIGNAL (clicked()), this, SLOT (equalExpressionClicked()));
    connect(ui->clearPushButton, SIGNAL (clicked()), this, SLOT (clearDataClicked()));
    connect(ui->polynomsPlanTextEdit, SIGNAL (textChanged()), this, SLOT (inputPolynoms()));

    QDoubleValidator* val = new QDoubleValidator(this);
    val->setBottom(-10000.0);
    val->setTop(10000.00);
    val->setNotation(QDoubleValidator::StandardNotation);

    ui->exEqualsLineEdit->setValidator(val);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clearDataClicked()
{
    ui->polynomsPlanTextEdit->setPlainText("");
    ui->donePolynomsPlanTextEdit->setPlainText("");
    ui->inputExpressionTextEdit->setText("");
    ui->resultTextEdit->setPlainText("");
    ui->exEqualsLineEdit->setText("");
}

void MainWindow::inputPolynoms()
{
    QString inputtedPolynoms = calculator.ProcessInputText(ui->polynomsPlanTextEdit->toPlainText().replace(",", "."));
    ui->donePolynomsPlanTextEdit->setPlainText(inputtedPolynoms);
}

void MainWindow::equalExpressionClicked()
{
    QString input = ui->inputExpressionTextEdit->toPlainText();
    if (input.isEmpty()) return;

    QString inputExpression = SpacedQString(input);

    try
    {
        Polynom result = calculator.EvaluateExpression(inputExpression);
        QString output = result.ToStringWithoutName();

        QString exStrValue = ui->exEqualsLineEdit->text();

        int index = 0;
        while (index < exStrValue.length())
        {
            if (exStrValue[index] == ' ')
            {
                exStrValue.remove(index, 1);
                index--;
            }
            index++;
        }

        ui->exEqualsLineEdit->setText(exStrValue);

        for (int i = 0; i < exStrValue.length(); i++)
            if (isalpha(exStrValue[i].toLatin1()))
            {
                QString message = "ошибка: некорректное значение X";
                throw message;
            }

        if (!exStrValue.isEmpty())
        {
            output += "\n\nПри x = " + exStrValue + ": " + QString::number(result.GetValueFromX(exStrValue.toDouble()));
        }

        ui->resultTextEdit->setPlainText(output);
    }

    catch (QString message)
    {
        ui->resultTextEdit->setPlainText(message);
    }

    catch (...)
    {
        ui->resultTextEdit->setPlainText("ошибка: некорректное выражение");
    }
}
