#ifndef PARTICULAR_INTERPRETER_H
#define PARTICULAR_INTERPRETER_H

#include<QString>
#include<QTextEdit>
#include"constants.h"
#include "utilities.h"
#include "numerical_methods.h"
#include "basic_text_interpreter.h"

bool chio_interpreter(QString &str,QString &message,QString &result);

bool gauss_interpreter(QString &str,QString &message,QString &result);

bool lr_factorization_interpreter(QString &str,QString &message,QString &result);

bool jacobi_iterative_method(QString &matrixStr,QString &initialSol,QString &precisionStr,QString &strIterationNumber,
                             QString &message,QString &result);

bool seidel_gauss_iterative_method(QString &matrixStr,QString &initialSol,QString &precisionStr,QString &strIterationNumber,
                             QString &message,QString &result);

bool krylov_interpreter(QString &matrixStr,QString &initVect,QString &message,QString &result);

bool fadeev_interpreter(QString &matrixStr,QString &message,QString &result);

bool lagrange_interpolation_interpreter(QString &pointsString,QString &xValueAsString,
                                        QString &message,QString &result);

bool newton_interpolation_interpreter(QString &pointsString,QString &xValueAsString,
                                        QString &message,QString &result);

bool spline_interpolation_interpreter(QString &pointsString,QString &xValueAsString,
                                        QString &message,QString &result);

bool mas_method_interpreter(QString functionStr,QString precisionStr,
                            QString initialValueStr,QString itMaxStr,QString &message,QString &result );

bool newton_approximation_interpreter(QString functionStr,QString precisionStr,
                            QString initialValueStr,QString itMaxStr,QString &message,QString &result );

bool integral_trapezoidal_rule_interpreter(QString &functionStr,QString &precisionStr,QString &down_limit,
                                           QString &up_limit,QString &message,QString &result);

bool simpson_rule_interpreter(QString &functionStr,QString &precisionStr,QString &down_limit,
                                           QString &up_limit,QString &message,QString &result);

bool double_integration_interpreter(QString & functionStr,
                                    QString &verticiesStr,QString &message,QString &result);

bool euler_cauchy_interpreter(QString &pointsStr,QString &iterationStr,QString &initValStr, QString &functionStr,
                              QString &epsilonStr  ,QString &message, QString &result);

bool runge_kutta_interpreter(QString &pointsStr,QString &iterationStr,QString &initValStr, QString &functionStr,
                              QString &epsilonStr  ,QString &message, QString &result);

#endif // PARTICULAR_INTERPRETER_H
