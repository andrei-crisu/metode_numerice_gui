#ifndef FROM_INTERNAL_TO_USER_H
#define FROM_INTERNAL_TO_USER_H

#include<QDateTime>
#include<QTextEdit>
#include <QString>


QString printStatus(QTextEdit *statusWindow,QString str,QString color);

QString printOutput(QTextEdit *displayWindow,QString str,QString color);


#endif // FROM_INTERNAL_TO_USER_H
