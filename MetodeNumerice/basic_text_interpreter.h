#ifndef BASIC_TEXT_INTERPRETER_H
#define BASIC_TEXT_INTERPRETER_H

#include "constants.h"
#include "utilities.h"
#include <QString>
#include <QRegularExpression>
#include<QDateTime>

bool getMatrix(double matrix[MAX_LINE][MAX_COL],QVector<int> dim,QString str);

bool try_extract_matrix(bool &extraction);

bool isMatrixAsString(QVector<int> dim,bool isSquareMatrix=IS_NOT_SQUARE);

QVector<int> getDim_of_StringMatrix(QString string);

QString replaceAll(QString entire_string,QString str1,QString str2);

QString removeWhiteCharacters(QString string);

bool containValidCh(QString string,QString allowedSymbols,
                    bool allowedDigit=DIGIT_ALLOWED,bool allowedLetter=LETTER_ALLOWED);

bool exceeds_app_limitation(QVector<int> dim);

QVector<int> scanForMistakes(QString str,bool &existMistake);

bool matrixValidator(QString &matrixStr,QString &message,int matrixType,QVector<int> &dim);

double stringToNumber(QString &string,bool &isExtracted);

QString polynomialString(double krylov_coefficient[MAX_LINE],int dim);

#endif // BASIC_TEXT_INTERPRETER_H
