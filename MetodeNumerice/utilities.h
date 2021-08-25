#ifndef UTILITIES_H
#define UTILITIES_H

#include <QChar>
#include <QString>
#include "constants.h"
#include"Lepton_parser/Lepton.h"
#include <math.h>

bool isDigit(const QChar c);

bool isLetter(const QChar c);

bool isWhiteSpace(const QChar c);

int countWhiteSpaces(QString str);

QString SolutionToString(double sol[MAX_LINE],int dim);

void getTriangularMatrix(double triangularMatrix[MAX_LINE][MAX_COL],
                         double augmentedMatrix[MAX_LINE][MAX_COL],int dim,int triangularMatrixType);

QString matrixToString(double matrix[MAX_LINE][MAX_COL],int ln,int col,int offset,int alignment);

QString numberToString(double nr,int alignmentType,int spaceOfRepresentation,QChar ch);

QString fillWith(QChar ch,int len);

int getMaxStringLength(double m[MAX_LINE][MAX_COL],int ln,int col);

void setPrincipalDiagonal(double m[MAX_LINE][MAX_COL],int ln,int col,double val);

void initializeMatrix(double m[MAX_LINE][MAX_COL],int ln,int col,double val=0);

bool is_diagonally_dominant(double m[MAX_LINE][MAX_COL],int dim,bool diagonal_dominance_type,bool orientation);

bool one_line_strict_dominance(double m[MAX_LINE][MAX_COL],int dim);

bool one_column_strict_dominance(double m[MAX_LINE][MAX_COL],int dim);

bool simetricMatrix(double m[MAX_LINE][MAX_COL],int dim);

void specialCopy(double dest[MAX_LINE][MAX_COL],double source[MAX_LINE][MAX_COL],int col1,int col2,int dim);

double user_fct(double &x,double val,Lepton::CompiledExpression &expression);

double user_fct2(double &x,double &y,double x_val,double y_val,Lepton::CompiledExpression &expression);


#endif
