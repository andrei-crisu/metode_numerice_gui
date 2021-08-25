#ifndef ERROR_H
#define ERROR_H
#include<QString>

class Error
{
public:
    Error();
    Error(QString str);
    QString what();
private:
    QString error;
};

#endif // ERROR_H
