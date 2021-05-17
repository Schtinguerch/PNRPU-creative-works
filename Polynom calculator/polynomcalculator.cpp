#include "polynomcalculator.h"

QString PolynomCalculator::ProcessInputText(QString text)
{
    QStringList expressions = text.split("\n");

    QVector<Polynom> polynoms;
    QVector<QString> names;

    QString donePolynoms = "";
    int index = -1;

    for (QString expression : expressions)
    {
        bool isSuitForProcessing = false;
        for (int i = 0; i < expression.length() - 1; i++)
            if ((expression[i] == ':') && (expression[i + 1] == ' '))
            {
                isSuitForProcessing = true;
                break;
            }

        if (isSuitForProcessing)
        {
            index++;

            QStringList declaration = expression.split(": ");
            QStringList coefsStr = declaration[1].split(" ");
            double* coefs = new double[coefsStr.count()];

            try
            {
                for (int i = 0; i < coefsStr.count(); i++)
                    coefs[i] = coefsStr.value(coefsStr.count() - i - 1).toDouble();
            }

            catch (...)
            {
                 QString message = "ошибка: введено не число";
                 throw message;
            }


            polynoms.push_back(Polynom(coefs, coefsStr.count(), declaration[0]));
            names.push_back(declaration[0]);

            delete[] coefs;
        }
    }

    for (int i = 0; i < polynoms.count(); i++)
    {
        polynoms[i].SetVariableName(names[i]);
        donePolynoms += polynoms[i].ToString() + '\n';
    }


    _polynoms = polynoms;
    return donePolynoms;
}

bool isOperator(char c)
{
    return (!isalpha(c) && !isdigit(c));
}

int getPriority(char C)
{
    if (C == '-' || C == '+')
        return 1;
    else if (C == '*' || C == '/')
        return 2;
    else if (C == '^')
        return 3;
    return 0;
}

bool areEquals(QString first, QString second)
{
    if (first.length() != second.length())
        return false;

    for (int i = 0; i < first.length(); i++)
    {
        char ch1 = first[i].toLatin1();
        char ch2 = second[i].toLatin1();

        if (ch1 != ch2)
        {
            return false;
        }
    }

    return true;
}

bool areBracketsBalanced(std::string expression)
{
    int leftBracketsCount = 0,
        rightBracketsCount = 0;

    for (int i = 0; i < expression.length(); i++)
        if (expression[i] == '(')
            leftBracketsCount++;
        else if (expression[i] == ')')
            rightBracketsCount++;

    return leftBracketsCount == rightBracketsCount;
}

bool PolynomCalculator::IsValid(std::string expression)
{
    for (int i = 0; i < expression.length(); i++)
    {
        char c = expression[i];
        bool isSuitSpecial = false;

        switch (c)
        {
            case '(':
            case ')':
            case ',':
            case '.':
            case ' ':
            case '+':
            case '-':
            case '*':
            case '/':
            case '^':
                isSuitSpecial = true;
                break;
        }

        if (!(isalpha(c) || isdigit(c) || isSuitSpecial))
            return false;
    }

    return true;
}

Polynom PolynomCalculator::GetPolynomByName(QString name)
{
    for (int i = 0; i < _polynoms.size(); i++)
    {
        QString inputName = name;
        QString compareName = _polynoms[i].GetVariableName();

        bool comparison = areEquals(inputName, compareName);

        if (comparison)
            return _polynoms[i];
    }

    QString message = "ошибка: переменная с именем \"" + name + "\" не найдена";
    throw message;
}

std::string PolynomCalculator::ConvertToPostfix(std::string infix)
{
    infix = '(' + infix + ')';
    int l = infix.size();
    std::stack<char> char_stack;
    std::string output;

    for (int i = 0; i < l; i++) {

        // If the scanned character is an
        // operand, add it to output.
        if (isalpha(infix[i]) || isdigit(infix[i]) || (infix[i] == ' '))
            output += infix[i];

        // If the scanned character is an
        // ‘(‘, push it to the stack.
        else if (infix[i] == '(')
            char_stack.push('(');

        // If the scanned character is an
        // ‘)’, pop and output from the stack
        // until an ‘(‘ is encountered.
        else if (infix[i] == ')')
        {
            while (char_stack.top() != '(')
            {
                output += char_stack.top();
                char_stack.pop();
            }

            // Remove '(' from the stack
            char_stack.pop();
        }

        // Operator found
        else {
            if (isOperator(char_stack.top()))
            {
                while ((getPriority(infix[i])
                    < getPriority(char_stack.top()))
                    || (getPriority(infix[i])
                        <= getPriority(char_stack.top()) && infix[i] == '^'))
                {
                    output += char_stack.top();
                    char_stack.pop();
                }

                // Push current Operator on stack
                char_stack.push(infix[i]);
            }
        }
    }
    return output;
}

std::string PolynomCalculator::ConvertToPrefix(std::string infix)
{
    if (!areBracketsBalanced(infix))
    {
        QString message = "Ошибка: скобки не сбалансированы";
        throw message;
    }

    if (!IsValid(infix))
    {
        QString message = "Ошибка: некорректное выражение";
        throw message;
    }

    int l = infix.size();
    reverse(infix.begin(), infix.end());

    for (int i = 0; i < l; i++) {

        if (infix[i] == '(') {
            infix[i] = ')';
            i++;
        }
        else if (infix[i] == ')') {
            infix[i] = '(';
            i++;
        }
    }

    std::string prefix = ConvertToPostfix(infix);
    reverse(prefix.begin(), prefix.end());

    return prefix;
}

Polynom PolynomCalculator::EvaluatePrefix(std::string expression)
{
    std::stack<Polynom> Stack;

    for (int j = expression.size() - 1; j >= 0; j--) {

        // if jth character is the delimiter ( which is
        // space in this case) then skip it
        if (expression[j] == ' ')
            continue;

        // Push operand to Stack
        // To convert expression[j] to digit subtract
        // '0' from expression[j].
        if (isdigit(expression[j])) {
            // there may be more than
            // one digits in a number

            double num = 0, i = j;
            while (j < expression.size() && isdigit(expression[j]))
                j--;
            j++;

            // from [j, i] exprsn contains a number
            for (int k = j; k <= i; k++)
                num = num * 10 + double(expression[k] - '0');

            double* numbers = new double[1];
            numbers[0] = num;

            Polynom zeroDegree(1, numbers);

            Stack.push(zeroDegree);
        }

        else if (isalpha(expression[j])) {
            double i = j;
            std::string variable;

            while (j < expression.size() && isalpha(expression[j]))
                j--;
            j++;

            // from [j, i] expression contains a number
            for (int k = j; k <= i; k++)
                variable += expression[k];

            Polynom a = GetPolynomByName(QString::fromStdString(variable));
            Stack.push(a);
        }
        else {

            // Operator encountered
            // Pop two elements from Stack
            Polynom o1 = Stack.top();
            Stack.pop();

            Polynom o2 = Stack.top();
            Stack.pop();

            // Use switch case to operate on o1
            // and o2 and perform o1 O o2.
            switch (expression[j]) {
            case '+':
                Stack.push(o1 + o2);
                break;
            case '-':
                Stack.push(o1 - o2);
                break;
            case '*':
                Stack.push(o1 * o2);
                break;
            case '/':
                Stack.push(o1 / o2);
                break;
            case '^':
                Stack.push(o1.Power(o2));
                break;
            }
        }
    }

    return Stack.top();
}

Polynom PolynomCalculator::EvaluateExpression(QString expression)
{
    std::string prefixExpression = ConvertToPrefix(expression.toStdString());
    Polynom result = EvaluatePrefix(prefixExpression);

    return result;
}
