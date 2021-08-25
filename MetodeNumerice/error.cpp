#include "error.h"

Error::Error()
{
    error="Error: Unknown error!";
}

Error::Error(QString err)
{
    error="Error: ";
    error+=err;
}

QString Error::what()
{
    return error;
}
