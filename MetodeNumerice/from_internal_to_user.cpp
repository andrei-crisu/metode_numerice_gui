#include"from_internal_to_user.h"

QString printStatus(QTextEdit *userWindow,QString str,QString color)
{

    QString htmlEnd,htmlStart,entireString;
    QDateTime date = QDateTime::currentDateTime();
    QString formattedTime = date.toString("dd.MM.yyyy hh:mm:ss");
    entireString="<font color= #274472 size= \"5\" > "+formattedTime+": </font>";
    entireString=entireString+"<font color= "+color+" size= \"5\" > "+str+"</font><br>";
    userWindow->append((entireString));

    return str;
}


QString printOutput(QTextEdit *displayWindow,QString str,QString color)
{
    QString entireString="";
    entireString=entireString+"<font color= "+color+" size= \"5\" >";
    entireString=entireString+str+"</font><br>";
    displayWindow->append((entireString));
    return str;
}

