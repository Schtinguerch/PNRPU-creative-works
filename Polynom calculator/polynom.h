#pragma once
#include <QString>

#ifndef POLYNOM_H
#define POLYNOM_H

class Polynom
{
private:
    int degree;
    double* coef;
    QString varName;

    Polynom (int adegree);
    void reduce(void);

    friend Polynom plus_minus(const Polynom& p1, const Polynom& p2, double op(double, double));

public:
    Polynom(int aDegree, double acoef[]);
    Polynom(double* coefs, int aDegree, QString vName);
    Polynom(const Polynom& copied);
    ~Polynom();

    QString ToString() const;
    QString ToStringWithoutName() const;
    void SetVariableName(QString variableName) { varName = variableName; }
    QString GetVariableName() { return varName; }

    friend Polynom operator + (const Polynom& p1, const Polynom& p2);
    friend Polynom operator - (const Polynom& p1, const Polynom& p2);
    friend Polynom operator * (const Polynom& p1, const Polynom& p2);
    friend Polynom operator / (const Polynom& p1, const Polynom& p2);

    Polynom& operator = (const Polynom& p);
    Polynom Power(int grade);
    Polynom Power(const Polynom& grade);

    double GetValueFromX(double x);
};

#endif // POLYNOM_H
