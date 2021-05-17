#include "intermediary.h"

Intermediary::Intermediary()
{

}


void Intermediary::SetSalesmanRoot(QVector<int> route)
{
    if (route[0] == -1)
    {
        SalesmanRoute = "";
        SalesmanRootLength = -1;

        return;
    }

    QString strRoute = QString::number(route[0]);
    for (int i = 1; i < route.count(); i++)
        strRoute += ", " + QString::number(route[i]);

   SalesmanRoute = strRoute;
}
