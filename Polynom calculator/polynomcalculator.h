#pragma once

#ifndef POLYNOMCALCULATOR_H
#define POLYNOMCALCULATOR_H

#include <string>
#include <QString>
#include <QVector>
#include <QStack>
#include <QStringList>
#include <polynom.h>
#include <stack>

class PolynomCalculator
{
private:
    QVector<Polynom> _polynoms;

    std::string ConvertToPostfix(std::string infix);
    std::string ConvertToPrefix(std::string infix);

    Polynom EvaluatePrefix(std::string expression);
    bool IsValid(std::string expression);

public:
    PolynomCalculator() {}
    Polynom GetPolynomByName(QString name);

    QString ProcessInputText(QString text);
    Polynom EvaluateExpression(QString expression);
};

#endif // POLYNOMCALCULATOR_H
