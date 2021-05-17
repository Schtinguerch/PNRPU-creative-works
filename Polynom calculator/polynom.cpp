#include "polynom.h"
#include <math.h>

double plusu(double a, double b)
{
    return a + b;
}

double minusu(double a, double b)
{
    return a - b;
}

Polynom::Polynom(int adegree)
{
    degree = adegree;
    coef = new double[degree];

    for (int i = 0; i < degree; i++)
        coef[i] = 0.0;
}

Polynom::Polynom(int adegree, double acoef[])
{
    degree = adegree;
    coef = new double[degree];

    for (int i = 0; i < degree; i++)
        coef[i] = acoef[i];
}

Polynom::Polynom(double* coefs, int aDegree, QString vName)
{
    varName = vName;
    degree = aDegree;
    coef = new double[degree];

    for (int i = 0; i < degree; i++)
        coef[i] = coefs[i];

}

Polynom::Polynom(const Polynom& p)
{
    degree = p.degree;
    coef = new double[degree];

    for (int i = 0; i < degree; i++)
        coef[i] = p.coef[i];
}

Polynom::~Polynom()
{
    delete[] coef;
}

QString Polynom::ToString(void) const
{
    return varName + ": " + ToStringWithoutName();
}

QString Polynom::ToStringWithoutName() const
{
    QString str = "";
    bool isFirstCoef = true;

    for (int i = degree - 1; i >= 0; i--)
    {
        if (abs(coef[i] - 0) > pow(10, -6))
        {
            QString strCoef = (abs(coef[i]) == 1)? "" : QString::number(abs(coef[i]));
            QString strOper = (coef[i] > 0)? (isFirstCoef)? "" : "+" : "-";

            if (i == 1)
                str += strOper + strCoef + "x ";
            else if (i == 0)
                str += strOper + QString::number(abs(coef[i]));
            else
                str += strOper + strCoef + "x^" + QString::number(i) + " ";

            isFirstCoef = false;
        }
    }

    return str;
}

void Polynom::reduce(void)
{
    int tdeg = degree;
    for (int i = degree - 1; i >= 0; i--)
    {
        if (coef[i] != 0.0)
            break;
        else
            tdeg--;
    }

    degree = tdeg;
}

Polynom plus_minus(const Polynom& p1, const Polynom& p2, double op(double, double))
{
    Polynom
        *pmax,
        *pmin;

    if (p1.degree > p2.degree)
    {
        pmax = (Polynom*)&p1;
        pmin = (Polynom*)&p2;
    }

    else
    {
        pmax = (Polynom*)&p2;
        pmin = (Polynom*)&p1;
    }

    int min_degree = pmin->degree;
    int max_degree = pmax->degree;

    Polynom res(max_degree);

    for (int i = 0; i < max_degree; i++)
    {
        if (i < min_degree)
            res.coef[i] = op(pmax->coef[i], pmin->coef[i]);
        else
            res.coef[i] = pmax->coef[i];
    }

    return res;
}

Polynom& Polynom::operator=(const Polynom& p)
{
    if (this == &p)
        return *this;

    degree = p.degree;

    coef = new double[degree];
    for (int i = 0; i < degree; i++)
        coef[i] = p.coef[i];

    return *this;
}

Polynom operator + (const Polynom& p1, const Polynom& p2)
{
    return plus_minus(p1, p2, plusu);
}

Polynom operator - (const Polynom& p1, const Polynom& p2)
{
    return plus_minus(p1, p2, minusu);
}

Polynom operator * (const Polynom& p1, const Polynom& p2)
{
    Polynom res(p1.degree + p2.degree - 1);

    for (int i = 0; i < p1.degree; i++)
        for (int j = 0; j < p2.degree; j++)
            res.coef[i + j] += p1.coef[i] * p2.coef[j];

    return res;
}

Polynom operator / (const Polynom& p1, const Polynom& p2)
{
    Polynom temp = p1;
    int rdeg = temp.degree - p2.degree + 1;
    Polynom res(rdeg);

    for (int i = 0; i < rdeg; i++)
    {
        res.coef[rdeg - i - 1] = temp.coef[temp.degree - i - 1] / p2.coef[p2.degree - 1];
        for (int j = 0; j < p2.degree; j++)
            temp.coef[temp.degree - j - i - 1] -= p2.coef[p2.degree - j - 1] * res.coef[rdeg - i - 1];
    }

    temp.reduce();
    return res;
}

Polynom Polynom::Power(int grade)
{
    Polynom temp(*this);
    Polynom result(1, new double[1] { 1 });

    for (int i = 0; i < grade; i++)
        result = result * temp;

    return result;
}

Polynom Polynom::Power(const Polynom& grade)
{
    return Power(grade.coef[0]);
}

double Polynom::GetValueFromX(double x)
{
    double value = 0;
    for (int i = degree - 1; i >= 0; i--)
        value += pow(x, i) * coef[i];

    return value;
}
