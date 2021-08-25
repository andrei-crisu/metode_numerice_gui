#include"particular_interpreter.h"

bool chio_interpreter(QString &str,QString &message,QString &result)
{

    if(str.length()<1)
    {
        message="Err -> Nu se poate prelucra o matrice vida!";
        return false;
    }
    if(countWhiteSpaces(str)==str.length())
    {
        QString msg="Err -> Nu se poate prelucra o matrice vida! ";
        msg=msg+HTML_ENTER;
        msg=msg+"Ati introdus doar caractere spatiu!";
        message=msg;
        return false;
    }
    str=removeWhiteCharacters(str);
    QVector<int> dimension=getDim_of_StringMatrix(str);

    if(!containValidCh(str," -.\n",DIGIT_ALLOWED,NO_LETTER_ALLOWED))
    {
        QString msg="Err -> Ati introdus caractere nepermise!";
        msg=msg+HTML_ENTER;
        msg=msg+"Puteti introduce doar numere reale (numere pozitive sau negative,"
        "cu virgula sau nu).";
        message=msg;
        return false;
    }

    if(exceeds_app_limitation(dimension))
    {
        QString msg="Err -> Ati introdus o matrice prea mare!";
        msg=msg+HTML_ENTER;
        msg=msg+"Dimensiunea maxima accepatata este: ("+QString::number(DIM_LIMIT)
                +","+QString::number(DIM_LIMIT)+")";
        message=msg;
        return false;
    }

   if(!isMatrixAsString(dimension,IS_SQUARE))
   {
       QString msg="Err -> Ati introdus o matrice nepatratica!";
       msg=msg+HTML_ENTER+"Nu se poate calcula determinantul unei matrice nepatratice!";
       message=msg;
       return false;
   }

   bool mistakesFound=false;
   QVector<int> pos= scanForMistakes(str,mistakesFound);
   if(mistakesFound)
   {
       QString msg="Err -> Punctul zecimal sau semnul nu se gasesc unde trebuie!";
       msg=msg+HTML_ENTER+"Greseala la elementul de pe linia: "+QString::number(pos.at(0))
               +", coloana: "+QString::number(pos.at(1));
       message=msg;
       return false;
   }
   double myMatrix[MAX_LINE][MAX_COL];
   bool extracted=false;
   extracted=getMatrix(myMatrix,dimension,str);
   if(!extracted)
   {
       QString msg="Err -> Matricea cupinde erori! Nu s-a putut efectua  prelucrarea!";
       message=msg;
       return false;
   }
   else

   {
       double determinant=0;
       determinant=chio_method(myMatrix,dimension.at(0));
       QString msg=" Good status >>> Matricea a fost procesata!";
       msg=msg+HTML_ENTER+"Dimensiune matrice: ("+QString::number(dimension.at(0))
               +","+QString::number(dimension.at(1))+"). ";
       msg+=" Valoarea determinantului este:";
       msg=msg+"<i><font color= #E8AB16 >  "+QString::number(determinant)+"</font></i>";
       message=msg;
       result="Valoarea determinantului este: ";
       result+=HTML_ENTER;
       result+=QString::number(determinant);
   }
    return true;
}

bool gauss_interpreter(QString &str,QString &message,QString &result)
{
    if(str.length()<1)
    {
        message="Err -> Nu se poate prelucra o matrice vida!";
        return false;
    }
    if(countWhiteSpaces(str)==str.length())
    {
        QString msg="Err -> Nu se poate prelucra o matrice vida!";
        msg=msg+HTML_ENTER;
        msg=msg+"Ati introdus doar caractere spatiu!";
        message=msg;
        return false;
    }
    str=removeWhiteCharacters(str);
    QVector<int> dimension=getDim_of_StringMatrix(str);

    if(!containValidCh(str," -.\n",DIGIT_ALLOWED,NO_LETTER_ALLOWED))
    {
        QString msg="Err -> Ati introdus caractere nepermise!";
        msg=msg+HTML_ENTER;
        msg=msg+"Puteti introduce doar numere reale (numere pozitive sau negative,"
        "cu virgula sau nu).";
        message=msg;
        return false;
    }

    if(exceeds_app_limitation(dimension))
    {
        QString msg="Err -> Ati introdus o matrice prea mare!";
        msg=msg+HTML_ENTER;
        msg=msg+"Dimensiunea maxima accepatata este: ("+QString::number(DIM_LIMIT)
                +","+QString::number(DIM_LIMIT)+")";
        message=msg;
        return false;
    }

   if(!isMatrixAsString(dimension,IS_NOT_SQUARE))
   {
       QString msg="Err -> Structura introdusa nu este o matrice!";
       message=msg;
       return false;
   }
   if(dimension.at(0)+1!=dimension.at(1))
   {
       QString msg="Err -> Dimensiune necorespunzatoare pentru matricea extinsa a sistemului!";
       message=msg;
       return false;
   }
   bool mistakesFound=false;
   QVector<int> pos= scanForMistakes(str,mistakesFound);
   if(mistakesFound)
   {
       QString msg="Err -> Punctul zecimal sau semnul nu se gasesc unde trebuie!";
       msg=msg+HTML_ENTER+"Greseala la elementul de pe linia: "+QString::number(pos.at(0))
               +", coloana: "+QString::number(pos.at(1));
       message=msg;
       return false;
   }
   double myMatrix[MAX_LINE][MAX_COL];
   bool extracted=false;
   extracted=getMatrix(myMatrix,dimension,str);
   if(!extracted)
   {
       QString msg="Err -> Matricea cupinde erori! Nu s-a putut efectua  prelucrarea!";
       message=msg;
       return false;
   }
   else

   {
       double sysSolution[MAX_LINE],triangularMatrix[MAX_LINE][MAX_COL];
       bool hasSolution=false;
       QString solutionAsString;
       hasSolution=gauss_method(myMatrix,dimension.at(0),sysSolution,triangularMatrix);
       if(!hasSolution)
       {
           QString msg="Good status >>> Matricea a fost procesata!";
           msg=msg+HTML_ENTER+"Dimensiunea matricei extinse: ("+QString::number(dimension.at(0))
                   +","+QString::number(dimension.at(1))+"). ";
           msg=msg+"<br><i><font color= #E8AB16 > Sistemul nu are solutie unica! </font></i>";
           message=msg;
           return false;
       }
       else
       {
           QString strTriangularMatrix=matrixToString(triangularMatrix,dimension.at(0),
                                                      dimension.at(1)-1,1,RIGHT_ALIGNMENT);
           solutionAsString=SolutionToString(sysSolution,dimension.at(0));
           QString msg=" Good status >>> Matricea a fost procesata!";
           msg=msg+HTML_ENTER+"Dimensiunea matricei extinse: ("+QString::number(dimension.at(0))
                   +","+QString::number(dimension.at(1))+"). ";
           msg+=" Solutia sistemului este: ";
           msg=msg+"<br><i><font color= #E8AB16 >  "+solutionAsString+"</font></i>";
           message=msg;

           QString entireText;
           entireText= "Matricea superior triunghiulara este: ";
           entireText+="<pre>";
           entireText+="\n";
           entireText+=strTriangularMatrix;
           entireText+="\n";
           entireText+="</pre>";
           entireText+="Iar solutia sistemului este:";
           entireText+="<pre>\n</pre>";
           entireText+=solutionAsString;
           result=entireText;

       }
   }
    return true;
}

bool lr_factorization_interpreter(QString &str,QString &message,QString &result)
{
    if(str.length()<1)
    {
        message="Err -> Nu se poate prelucra o matrice vida!";
        return false;
    }
    if(countWhiteSpaces(str)==str.length())
    {
        QString msg="Err -> Nu se poate prelucra o matrice vida!";
        msg=msg+HTML_ENTER;
        msg=msg+"Ati introdus doar caractere spatiu!";
        message=msg;
        return false;
    }
    str=removeWhiteCharacters(str);
    QVector<int> dimension=getDim_of_StringMatrix(str);

    if(!containValidCh(str," -.\n",DIGIT_ALLOWED,NO_LETTER_ALLOWED))
    {
        QString msg="Err -> Ati introdus caractere nepermise!";
        msg=msg+HTML_ENTER;
        msg=msg+"Puteti introduce doar numere reale (numere pozitive sau negative,"
        "cu virgula sau nu).";
        message=msg;
        return false;
    }

    if(exceeds_app_limitation(dimension))
    {
        QString msg="Err -> Ati introdus o matrice prea mare!";
        msg=msg+HTML_ENTER;
        msg=msg+"Dimensiunea maxima accepatata este: ("+QString::number(DIM_LIMIT)
                +","+QString::number(DIM_LIMIT)+")";
        message=msg;
        return false;
    }

   if(!isMatrixAsString(dimension,IS_NOT_SQUARE))
   {
       QString msg="Err -> Structura introdusa nu este o matrice!";
       message=msg;
       return false;
   }
   if(dimension.at(0)+1!=dimension.at(1))
   {
       QString msg="Err -> Dimensiune necorespunzatoare pentru matricea extinsa a sistemului!";
       message=msg;
       return false;
   }
   bool mistakesFound=false;
   QVector<int> pos= scanForMistakes(str,mistakesFound);
   if(mistakesFound)
   {
       QString msg="Err -> Punctul zecimal sau semnul nu se gasesc unde trebuie!";
       msg=msg+HTML_ENTER+"Greseala la elementul de pe linia: "+QString::number(pos.at(0))
               +", coloana: "+QString::number(pos.at(1));
       message=msg;
       return false;
   }
   double myMatrix[MAX_LINE][MAX_COL];
   bool extracted=false;
   extracted=getMatrix(myMatrix,dimension,str);
   if(!extracted)
   {
       QString msg="Err -> Matricea cupinde erori! Nu s-a putut efectua  prelucrarea!";
       message=msg;
       return false;
   }
   else

   {
       double sysSolution[MAX_LINE];
       double lowerTriangularMatrix[MAX_LINE][MAX_COL],upperTriangularMatrix[MAX_LINE][MAX_COL];
       bool hasSolution=false;
       QString solutionAsString;
       hasSolution=lr_factorization(myMatrix,dimension.at(0),sysSolution,
                                    lowerTriangularMatrix,upperTriangularMatrix);
       if(!hasSolution)
       {
           QString msg="Good status >>> Matricea a fost procesata!";
           msg=msg+HTML_ENTER+"Dimensiunea matricei extinse: ("+QString::number(dimension.at(0))
                   +","+QString::number(dimension.at(1))+"). ";
           msg=msg+"<br><i><font color= #E8AB16 > Sistemul nu are solutie unica! </font></i>";
           message=msg;
           return false;
       }
       else
       {
           QString strUpperTriangularMatrix,strLowerTriangularMatrix;
           strUpperTriangularMatrix=matrixToString(upperTriangularMatrix,dimension.at(0),
                                                   dimension.at(1)-1,1,RIGHT_ALIGNMENT);

           setPrincipalDiagonal(lowerTriangularMatrix,dimension.at(0),dimension.at(1)-1,1);
           strLowerTriangularMatrix=matrixToString(lowerTriangularMatrix,dimension.at(0),
                                                   dimension.at(1)-1,1,RIGHT_ALIGNMENT);
           solutionAsString=SolutionToString(sysSolution,dimension.at(0));
           QString msg=" Good status >>> Matricea a fost procesata!";
           msg=msg+HTML_ENTER+"Dimensiunea matricei extinse: ("+QString::number(dimension.at(0))
                   +","+QString::number(dimension.at(1))+"). ";
           msg+=" Solutia sistemului este: ";
           msg=msg+"<br><i><font color= #E8AB16 >  "+solutionAsString+"</font></i>";
           message=msg;

           QString entireText;
           entireText= "Matricea superior triunghiulara este: ";
           entireText+="<pre>";
           entireText+="\n";
           entireText+=strUpperTriangularMatrix;
           entireText+="\n";
           entireText+="</pre>";
           entireText+= "Matricea inferior triunghiulara este: ";
           entireText+="<pre>";
           entireText+="\n";
           entireText+=strLowerTriangularMatrix;
           entireText+="\n";
           entireText+="</pre>";
           entireText+="Iar solutia sistemului este:";
           entireText+="<pre>\n</pre>";
           entireText+=solutionAsString;
           result=entireText;

       }
   }
    return true;
}

bool jacobi_iterative_method(QString &matrixStr,QString &initialSol,QString &precisionStr,QString &strIterationNumber,
                             QString &message,QString &result)
{

    //variabile utilizate
    double systemMatrix[MAX_LINE][MAX_COL],initialVector[MAX_LINE][MAX_COL],precision=0.0001,iterationNr=200;
    //se extrage matricea sistemului
    if(matrixStr.isEmpty())
    {
        message="Err->Campul corespunzator matricei nu a fost completat!";
        message+=HTML_ENTER;
        message+="Indicati matricea extinsa a sistemului!";
        return false;
    }
    if(countWhiteSpaces(matrixStr)==matrixStr.length())
    {
        QString msg="Err -> Nu se poate face prelucrarea! ";
        msg=msg+HTML_ENTER;
        msg=msg+"Ati introdus doar spatii!";
        message=msg;
        return false;
    }

    matrixStr=removeWhiteCharacters(matrixStr);
    QVector<int> matrixDimension;
   if(!matrixValidator(matrixStr,message,IS_NOT_SQUARE,matrixDimension))
       return false;
   if(matrixDimension.at(0)+1!=matrixDimension.at(1))
   {
       QString msg="Err -> Dimensiune necorespunzatoare pentru matricea extinsa a sistemului!";
       msg+=HTML_ENTER;
       message=msg;
       return false;
   }
   bool extracted=false;
   extracted=getMatrix(systemMatrix,matrixDimension,matrixStr);
   if(!extracted)
   {
       QString msg="Err -> Matricea cupinde erori! Nu s-a putut efectua  prelucrarea!";
       message=msg;
       return false;
   }

   //se extrage precizia
   if(precisionStr.isEmpty())
   {
       message="Err->Campul corespunzator preciziei nu a fost completat!";
       message+=HTML_ENTER;
       message+="Indicati precizia de calcul!";
       return false;
   }


   bool isExtracted=false;
   precision=stringToNumber(precisionStr,isExtracted);
   if(!isExtracted)
   {
       message="Err->Campul corespunzator preciziei contine erori!";
       message+=HTML_ENTER;
       message+="Nu s-a putut citi precizia!";
       return false;
   }

   //se extrage numarul de iteratii
   if(strIterationNumber.isEmpty())
   {
       message="Err->Campul corespunzator numarului de iteratii nu a fost completat!";
       message+=HTML_ENTER;
       message+="Indicati numarul de iteratii!";
       return false;
   }
   bool iterationExtracted=false;
   iterationNr=stringToNumber(strIterationNumber,iterationExtracted);
   if(!iterationExtracted)
   {
       message="Err->Campul corespunzator numarului de iteratii contine erori!";
       message+=HTML_ENTER;
       message+="Nu s-a putut citi numarul de iteratii!";
       return false;
   }

   //se extrage vectorul solutie initial
   //se initializeaza mai intai vectorul care va stoca solutia initiala
   if(initialSol.isEmpty())
   {
       message="Err->Campul corespunzator vectorului intial de solutie nu a fost completat!";
       message+=HTML_ENTER;
       message+="Indicati vectorul initial al solutiei !";
       return false;
   }

    if(countWhiteSpaces(initialSol)==initialSol.length())
    {
        QString msg="Err -> Nu se poate face prelucrarea vectorului solutie initial! ";
        msg=msg+HTML_ENTER;
        msg=msg+"Ati introdus doar spatii in campul destinat acestuia!";
        message=msg;
        return false;
    }
   initialSol=removeWhiteCharacters(initialSol);
   initializeMatrix(initialVector,25,25);
   QVector<int> solVectorDimension;
   if(!matrixValidator(initialSol,message,IS_NOT_SQUARE,solVectorDimension))
       return false;
   if(solVectorDimension.at(0)!=matrixDimension.at(0)||solVectorDimension.at(1)!=1)
   {
       QString msg="Err -> Dimensiune necorespunzatoare pentru vectorul solutie initial !";
       msg+=HTML_ENTER;
       message=msg;
       return false;
   }
   bool solVectorExtracted=false;
   solVectorExtracted=getMatrix(initialVector,solVectorDimension,initialSol);
   if(!solVectorExtracted)
   {
       QString msg="Err -> Nu s-a putut extrage vectorul solutie initial. Exista erori in informatia introdusa!";
       message=msg;
       return false;
   }
   else
   {
       double solution[MAX_LINE];
       int iterationNumber=0;
       QString msg2="";
       int maxIterationNumber=iterationNr;

       //test method convergence
       if((is_diagonally_dominant(systemMatrix,matrixDimension.at(0),STRICT_DOMINANCE,ON_LINE)||
           is_diagonally_dominant(systemMatrix,matrixDimension.at(0),STRICT_DOMINANCE,ON_COLUMN))&&
               simetricMatrix(systemMatrix,matrixDimension.at(0)))
       {
           msg2+="Pentru aceasta matrice : metoda Jacobi este convergenta!";
           msg2+=HTML_ENTER;
           msg2+="Din testarea teoremei: ";
           msg2+=HTML_ENTER;
           msg2+="TEOREMA: Daca matricea este simetrica si diagonal strict dominanta";
           msg2+=" atunci metoda iterativa Jacobi converge!";


        }else if(is_diagonally_dominant(systemMatrix,matrixDimension.at(0),STRICT_DOMINANCE,ON_LINE)||
               is_diagonally_dominant(systemMatrix,matrixDimension.at(0),STRICT_DOMINANCE,ON_COLUMN))
       {
           msg2+="Pentru aceasta matrice : metoda Jacobi este convergenta!";
           msg2+=HTML_ENTER;
           msg2+="Din testarea teoremei: ";
           msg2+=HTML_ENTER;
           msg2+=" TEOREMA: Daca matricea este diagonal strict "
            "dominanta pe linii sau coloane atunci metodele iterative "
            "Seidel-Gauss si Jacobi sunt convergente.";
       }
       else if((is_diagonally_dominant(systemMatrix,matrixDimension.at(0),WEAK_DOMINANCE,ON_LINE)||
                is_diagonally_dominant(systemMatrix,matrixDimension.at(0),WEAK_DOMINANCE,ON_COLUMN))&&
               (one_column_strict_dominance(systemMatrix,matrixDimension.at(0))||
                one_line_strict_dominance(systemMatrix,matrixDimension.at(0))))
       {
           msg2+="Pentru aceasta matrice : metoda Jacobi este convergenta!";
           msg2+=HTML_ENTER;
           msg2+="Din testarea teoremei: ";
           msg2+=HTML_ENTER;
           msg2=" TEOREMA: Daca matricea este diagonal dominanta pe linii sau coloane"
                " si cel putin pe o linie sau pe o coloana este strict dominanta metodele "
                "Seidel-Gauss si Jacobi sunt convergente.";
       }
       else
       {
           msg2+="Din testarea teoremelor: ";
           msg2+=HTML_ENTER;
           msg2+=" TEOREMA: Daca matricea este diagonal strict "
            "dominanta pe linii sau coloane atunci metodele iterative "
            "Seidel-Gauss si Jacobi sunt convergente.";
           msg2+=HTML_ENTER;
           msg2+="TEOREMA: Daca matricea este simetrica si diagonal strict dominanta";
           msg2+=" atunci metoda iterativa Jacobi converge!";
           msg2+=HTML_ENTER;
           msg2+=" TEOREMA: Daca matricea este diagonal dominanta pe linii sau coloane"
                " si cel putin pe o linie sau pe o coloana este strict dominanta metodele "
                "Seidel-Gauss si Jacobi sunt convergente.";
           msg2+=HTML_ENTER;
           msg2+="Din verificarile anterioare: NU REZULTA CONVERGENTA metodei Jacobi pentru aceasta matrice!";

       }

       if(!jacobi_method(systemMatrix,matrixDimension.at(0),maxIterationNumber,precision,initialVector,solution,iterationNumber))
       {
            QString msg;
            msg+="Nu se poate obtine solutia in ";
            msg+=QString::number(maxIterationNumber);
            msg+=" iteratii cu precizia: ";
            msg+=QString::number(precision);
            msg+=" !";
            msg+=HTML_ENTER;
            msg+="In urma acestor calcule s-a obtinut ca solutie eronata (fara a se atinge precizia dorita) : ";
            msg+=HTML_ENTER;
            QString strSol=SolutionToString(solution,solVectorDimension.at(0));
            msg+=strSol;
            result=msg;
            message=msg2;
       }
       else
       {
           QString msg;
           msg="Solutia obtinuta  in ";
           msg+=QString::number(iterationNumber);
           msg+=" iteratii (numarul maxim de iteratii fiind: ";
           msg+=QString::number(maxIterationNumber);
           msg+=" ) ";
           msg+=", cu precizia: ";
           msg+=QString::number(precision);
           msg+=" este: ";
           msg+=HTML_ENTER;
           QString strSol=SolutionToString(solution,solVectorDimension.at(0));
           msg+=SolutionToString(solution,matrixDimension.at(0));
           result=msg;

           message="Good status: datele au fost prelucrate! ";
           message+=HTML_ENTER;
           message+=msg2;
           message+=HTML_ENTER;
           message+="Solutia sistemului obtinuta iterativ este: ";
           message+=HTML_ENTER;
           message+=strSol;
       }

   }

    return true;
}

bool seidel_gauss_iterative_method(QString &matrixStr,QString &initialSol,QString &precisionStr,QString &strIterationNumber,
                             QString &message,QString &result)
{

    //variabile utilizate
    double systemMatrix[MAX_LINE][MAX_COL],initialVector[MAX_LINE][MAX_COL],precision=0.0001,iterationNr=200;
    //se extrage matricea sistemului
    if(matrixStr.isEmpty())
    {
        message="Err->Campul corespunzator matricei nu a fost completat!";
        message+=HTML_ENTER;
        message+="Indicati matricea extinsa a sistemului!";
        return false;
    }
    if(countWhiteSpaces(matrixStr)==matrixStr.length())
    {
        QString msg="Err -> Nu se poate face prelucrarea! ";
        msg=msg+HTML_ENTER;
        msg=msg+"Ati introdus doar spatii!";
        message=msg;
        return false;
    }

    matrixStr=removeWhiteCharacters(matrixStr);

    QVector<int> matrixDimension;
   if(!matrixValidator(matrixStr,message,IS_NOT_SQUARE,matrixDimension))
       return false;
   if(matrixDimension.at(0)+1!=matrixDimension.at(1))
   {
       QString msg="Err -> Dimensiune necorespunzatoare pentru matricea extinsa a sistemului!";
       msg+=HTML_ENTER;
       message=msg;
       return false;
   }
   bool extracted=false;
   extracted=getMatrix(systemMatrix,matrixDimension,matrixStr);
   if(!extracted)
   {
       QString msg="Err -> Matricea cupinde erori! Nu s-a putut efectua  prelucrarea!";
       message=msg;
       return false;
   }

   //se extrage precizia
   if(precisionStr.isEmpty())
   {
       message="Err->Campul corespunzator preciziei nu a fost completat!";
       message+=HTML_ENTER;
       message+="Indicati precizia de calcul!";
       return false;
   }
   if(countWhiteSpaces(precisionStr)==precisionStr.length())
   {
       QString msg="Err -> Nu se poate face prelucrarea preciziei! ";
       msg=msg+HTML_ENTER;
       msg=msg+"Ati introdus doar spatii!";
       message=msg;
       return false;
   }

   precisionStr=removeWhiteCharacters(precisionStr);
   bool isExtracted=false;
   precision=stringToNumber(precisionStr,isExtracted);
   if(!isExtracted)
   {
       message="Err->Campul corespunzator preciziei contine erori!";
       message+=HTML_ENTER;
       message+="Nu s-a putut citi precizia!";
       return false;
   }

   //se extrage numarul de iteratii
   if(strIterationNumber.isEmpty())
   {
       message="Err->Campul corespunzator numarului de iteratii nu a fost completat!";
       message+=HTML_ENTER;
       message+="Indicati numarul de iteratii!";
       return false;
   }
   if(countWhiteSpaces(strIterationNumber)==strIterationNumber.length())
   {
       QString msg="Err -> Nu se poate face prelucrarea numarului de iteratii! ";
       msg=msg+HTML_ENTER;
       msg=msg+"Ati introdus doar spatii!";
       message=msg;
       return false;
   }

   strIterationNumber=removeWhiteCharacters(strIterationNumber);
   bool iterationExtracted=false;
   iterationNr=stringToNumber(strIterationNumber,iterationExtracted);
   if(!iterationExtracted)
   {
       message="Err->Campul corespunzator numarului de iteratii contine erori!";
       message+=HTML_ENTER;
       message+="Nu s-a putut citi numarul de iteratii!";
       return false;
   }

   //se extrage vectorul solutie initial
   //se initializeaza mai intai vectorul care va stoca solutia initiala
   if(initialSol.isEmpty())
   {
       message="Err->Campul corespunzator vectorului intial de solutie nu a fost completat!";
       message+=HTML_ENTER;
       message+="Indicati vectorul initial al solutiei !";
       return false;
   }

   if(countWhiteSpaces(initialSol)==initialSol.length())
   {
       QString msg="Err -> Nu se poate face prelucrarea! ";
       msg=msg+HTML_ENTER;
       msg=msg+"Ati introdus doar spatii!";
       message=msg;
       return false;
   }
   initializeMatrix(initialVector,25,25);
   QVector<int> solVectorDimension;
   if(!matrixValidator(initialSol,message,IS_NOT_SQUARE,solVectorDimension))
       return false;
   if(solVectorDimension.at(0)!=matrixDimension.at(0)||solVectorDimension.at(1)!=1)
   {
       QString msg="Err -> Dimensiune necorespunzatoare pentru vectorul solutie initial !";
       msg+=HTML_ENTER;
       message=msg;
       return false;
   }
   bool solVectorExtracted=false;
   solVectorExtracted=getMatrix(initialVector,solVectorDimension,initialSol);
   if(!solVectorExtracted)
   {
       QString msg="Err -> Nu s-a putut extrage vectorul solutie initial. Exista erori in informatia introdusa!";
       message=msg;
       return false;
   }
   else
   {
       double solution[MAX_LINE];
       int iterationNumber=0;
       QString msg2="";
       int maxIterationNumber=iterationNr;

       //test method convergence
       if(is_diagonally_dominant(systemMatrix,matrixDimension.at(0),STRICT_DOMINANCE,ON_LINE)||
               is_diagonally_dominant(systemMatrix,matrixDimension.at(0),STRICT_DOMINANCE,ON_COLUMN))
       {
           msg2+="Pentru aceasta matrice : metoda Seidel-Gauss este convergenta!";
           msg2+=HTML_ENTER;
           msg2+="Din testarea teoremei: ";
           msg2+=HTML_ENTER;
           msg2+=" TEOREMA: Daca matricea este diagonal strict "
            "dominanta pe linii sau coloane atunci metodele iterative "
            "Seidel-Gauss si Jacobi sunt convergente.";
       }
       else if((is_diagonally_dominant(systemMatrix,matrixDimension.at(0),WEAK_DOMINANCE,ON_LINE)||
                is_diagonally_dominant(systemMatrix,matrixDimension.at(0),WEAK_DOMINANCE,ON_COLUMN))&&
               (one_column_strict_dominance(systemMatrix,matrixDimension.at(0))||
                one_line_strict_dominance(systemMatrix,matrixDimension.at(0))))
       {
           msg2+="Pentru aceasta matrice : metoda Seidel-Gauss este convergenta!";
           msg2+=HTML_ENTER;
           msg2+="Din testarea teoremei: ";
           msg2+=HTML_ENTER;
           msg2=" TEOREMA: Daca matricea este diagonal dominanta pe linii sau coloane"
                " si cel putin pe o linie sau pe o coloana este strict dominanta metodele "
                "Seidel-Gauss si Jacobi sunt convergente.";
       }
       else
       {
           msg2+="Din testarea teoremelor: ";
           msg2+=HTML_ENTER;
           msg2+=" TEOREMA: Daca matricea este diagonal strict "
            "dominanta pe linii sau coloane atunci metodele iterative "
            "Seidel-Gauss si Jacobi sunt convergente.";
           msg2+=HTML_ENTER;
           msg2+=" TEOREMA: Daca matricea este diagonal dominanta pe linii sau coloane"
                " si cel putin pe o linie sau pe o coloana este strict dominanta metodele "
                "Seidel-Gauss si Jacobi sunt convergente.";
           msg2+=HTML_ENTER;
           msg2+="Din verificarile anterioare: "
                "NU REZULTA CONVERGENTA metodei Seidel-Gauss pentru aceasta matrice!";
           msg2+=HTML_ENTER;
           msg2+="Reprezinta un avertisment ... ";
           msg2+"Nu s-a verificat si teorema:";
           msg2+=HTML_ENTER;
           msg2+="TEOREMA: Daca matricea A este simetrica si pozitiv definita atunci metoda "
                "Seidel-Gauss converge!";


       }

       if(!seidel_gauss_method(systemMatrix,matrixDimension.at(0),maxIterationNumber,precision,initialVector,solution,iterationNumber))
       {
            QString msg;
            msg+="Nu se poate obtine solutia in ";
            msg+=QString::number(maxIterationNumber);
            msg+=" iteratii cu precizia: ";
            msg+=QString::number(precision);
            msg+=" !";
            msg+=HTML_ENTER;
            msg+="In urma acestor calcule s-a obtinut ca solutie eronata (fara a se atinge precizia dorita) : ";
            msg+=HTML_ENTER;
            QString strSol=SolutionToString(solution,solVectorDimension.at(0));
            msg+=strSol;
            result=msg;
            message=msg2;
       }
       else
       {
           QString msg;
           msg="Solutia obtinuta  in ";
           msg+=QString::number(iterationNumber);
           msg+=" iteratii (numarul maxim de iteratii fiind: ";
           msg+=QString::number(maxIterationNumber);
           msg+=" ) ";
           msg+=", cu precizia: ";
           msg+=QString::number(precision);
           msg+=" este: ";
           msg+=HTML_ENTER;
           QString strSol=SolutionToString(solution,solVectorDimension.at(0));
           msg+=SolutionToString(solution,matrixDimension.at(0));
           result=msg;

           message="Good status: datele au fost prelucrate! ";
           message+=HTML_ENTER;
           message+=msg2;
           message+=HTML_ENTER;
           message+="Solutia sistemului obtinuta iterativ este: ";
           message+=HTML_ENTER;
           message+=strSol;
       }

   }

    return true;
}

bool krylov_interpreter(QString &matrixStr,QString &initVect,QString &message,QString &result)
{
    //variabile utilizate
    double systemMatrix[MAX_LINE][MAX_COL],initialVector[MAX_LINE][MAX_COL];

    //se extrage matricea
    if(matrixStr.isEmpty())
    {
        message="Err->Campul corespunzator matricei nu a fost completat!";
        message+=HTML_ENTER;
        message+="Introduceti matricea!";
        return false;
    }
    if(countWhiteSpaces(matrixStr)==matrixStr.length())
    {
        QString msg="Err -> Nu se poate face prelucrarea matricei! ";
        msg=msg+HTML_ENTER;
        msg=msg+"Ati introdus doar spatii!";
        message=msg;
        return false;
    }

    matrixStr=removeWhiteCharacters(matrixStr);

    QVector<int> matrixDimension;
   if(!matrixValidator(matrixStr,message,IS_NOT_SQUARE,matrixDimension))
       return false;
   if(matrixDimension.at(0)!=matrixDimension.at(1))
   {
       QString msg="Err -> Dimensiune necorespunzatoare! Matricea trebuie sa fie patratica";
       msg+=HTML_ENTER;
       message=msg;
       return false;
   }
   if(matrixDimension.at(0)+1>=DIM_LIMIT)
   {
       QString msg="Err -> Dimensiune prea mare!Aplicatia nu permite calculul valorilor proprii ";
       msg+="pentru o matrice de dimensiune mai mare decat: ";
       msg+=QString::number(DIM_LIMIT-1);
       msg+=HTML_ENTER;
       message=msg;
       return false;
   }

   bool extracted=false;
   extracted=getMatrix(systemMatrix,matrixDimension,matrixStr);
   if(!extracted)
   {
       QString msg="Err -> Matricea cupinde erori! Nu s-a putut efectua  prelucrarea!";
       message=msg;
       return false;
   }

   //se extrage vectorul initial
   //se initializeaza mai intai vectorul care va stoca solutia initiala
   if(initVect.isEmpty())
   {
       message="Err->Campul corespunzator vectorului intial nu a fost completat!";
       message+=HTML_ENTER;
       message+="Introduceti  vectorul:!";
       return false;
   }

   if(countWhiteSpaces(initVect)==initVect.length())
   {
       QString msg="Err -> Nu se poate face prelucrarea vectorului initial! ";
       msg=msg+HTML_ENTER;
       msg=msg+"Ati introdus doar spatii!";
       message=msg;
       return false;
   }
   initVect=removeWhiteCharacters(initVect);
   initializeMatrix(initialVector,MAX_LINE,MAX_COL);
   QVector<int> solVectorDimension;
   if(!matrixValidator(initVect,message,IS_NOT_SQUARE,solVectorDimension))
       return false;
   if(solVectorDimension.at(0)!=matrixDimension.at(0)||solVectorDimension.at(1)!=1)
   {
       QString msg="Err -> Dimensiune necorespunzatoare pentru vectorul initial !";
       msg+=HTML_ENTER;
       message=msg;
       return false;
   }
   bool solVectorExtracted=false;
   solVectorExtracted=getMatrix(initialVector,solVectorDimension,initVect);
   if(!solVectorExtracted)
   {
       QString msg="Err -> Nu s-a putut extrage vectorul initial. Exista erori in informatia introdusa!";
       message=msg;
       return false;
   }
   else
   {
       double solution[MAX_LINE],y[MAX_LINE][MAX_COL];
       initializeMatrix(y,MAX_LINE,MAX_COL);
       specialCopy(y,initialVector,matrixDimension.at(1),1,matrixDimension.at(0));

       if(!krylov(systemMatrix,y,matrixDimension.at(0),solution))
       {
            QString msg;
            msg+="Nu se pot extrage valorile proprii! ";
            msg+=HTML_ENTER;
            message=msg;
            return false;
       }
       else
       {
           QString msg="";
           QString strSol=SolutionToString(solution,solVectorDimension.at(0));
           msg+="In urma aplicarii metodei Krylov s-au obtinut coeficientii: ";
           msg+=HTML_ENTER;
           msg+=strSol;
           msg+=HTML_ENTER;
           solution[0]=1;
           msg+=polynomialString(solution,solVectorDimension.at(0));
           result=msg;

           message="Good status: datele au fost prelucrate! ";
           message+=HTML_ENTER;
           message+="Rezulatat: ";
           message+=strSol;
       }

   }
    return true;
}

bool fadeev_interpreter(QString &matrixStr,QString &message,QString &result)
{
    //variabile utilizate
    double matrix[MAX_LINE][MAX_COL];

    //se extrage matricea
    if(matrixStr.isEmpty())
    {
        message="Err->Campul corespunzator matricei nu a fost completat!";
        message+=HTML_ENTER;
        message+="Introduceti matricea!";
        return false;
    }

    if(countWhiteSpaces(matrixStr)==matrixStr.length())
    {
        QString msg="Err -> Nu se poate face prelucrarea! ";
        msg=msg+HTML_ENTER;
        msg=msg+"Ati introdus doar spatii!";
        message=msg;
        return false;
    }

    matrixStr=removeWhiteCharacters(matrixStr);

    QVector<int> matrixDimension;
   if(!matrixValidator(matrixStr,message,IS_NOT_SQUARE,matrixDimension))
       return false;
   if(matrixDimension.at(0)!=matrixDimension.at(1))
   {
       QString msg="Err -> Dimensiune necorespunzatoare! Matricea trebuie sa fie patratica";
       msg+=HTML_ENTER;
       message=msg;
       return false;
   }
   if(matrixDimension.at(0)+1>=DIM_LIMIT)
   {
       QString msg="Err -> Dimensiune prea mare!Aplicatia nu permite calculul valorilor proprii ";
       msg+="pentru o matrice de dimensiune mai mare decat: ";
       msg+=QString::number(DIM_LIMIT-1);
       msg+=HTML_ENTER;
       message=msg;
       return false;
   }

   bool extracted=false;
   extracted=getMatrix(matrix,matrixDimension,matrixStr);
   if(!extracted)
   {
       QString msg="Err -> Matricea cupinde erori! Nu s-a putut efectua  prelucrarea!";
       message=msg;
       return false;
   }
   else
   {
       double coeff[MAX_LINE],invMatrix[MAX_LINE][MAX_COL];
       if(!fadeev(matrix,invMatrix,coeff,matrixDimension.at(0)))
       {
            QString msg;
            msg+="Nu se pot extrage valorile proprii! ";
            msg+=HTML_ENTER;
            message=msg;
            return false;
       }
       else
       {
           QString msg="";
           QString strSol=SolutionToString(coeff,matrixDimension.at(0));
           msg+="In urma aplicarii metodei Fadeev s-au obtinut coeficientii: ";
           msg+=HTML_ENTER;
           msg+=strSol;
           msg+=HTML_ENTER;
           coeff[0]=1;
           msg+=polynomialString(coeff,matrixDimension.at(0));
           msg+=HTML_ENTER;
           msg+="Inversa matricei date este: ";
           msg+=HTML_ENTER;
           msg+="<pre>";
           msg+=matrixToString(invMatrix,matrixDimension.at(0),matrixDimension.at(1),2,RIGHT_ALIGNMENT);
           msg+="</pre>";
           result=msg;
           message="Good status: datele au fost prelucrate! ";
           message+=HTML_ENTER;
           message+="Rezulatat: ";
           message+=strSol;
       }

   }
    return true;
}

bool lagrange_interpolation_interpreter(QString &pointsString,QString &xValueAsString,
                                        QString &message,QString &result)
{
    //variabile utilizate
    double pointsMatrix[MAX_LINE][MAX_COL],x_coord;
    message="";
    result="";

    //se extrage matricea ce reprezinta punctele in care se cunoaste valoare functiei
    if(pointsString.isEmpty())
    {
        message="Err->Campul corespunzator punctelor cunoscute nu a fost completat!";
        message+=HTML_ENTER;
        message+="Specificati punctele!";
        return false;
    }
    if(countWhiteSpaces(pointsString)==pointsString.length())
    {
        QString msg="Err -> Nu se poate face prelucrarea! ";
        msg=msg+HTML_ENTER;
        msg=msg+"Ati introdus doar spatii!";
        message=msg;
        return false;
    }
    pointsString=removeWhiteCharacters(pointsString);

    QVector<int> matrixDimension;
    if(!matrixValidator(pointsString,message,IS_NOT_SQUARE,matrixDimension))
       return false;
    if(matrixDimension.at(1)!=2)
    {
       QString msg="Err -> Dimensiune necorespunzatoare! Matricea trebuie sa aiba 2 coloane";
       msg+=HTML_ENTER;
       message=msg;
       return false;
    }
    if(matrixDimension.at(0)+1>=DIM_LIMIT)
    {
       QString msg="Err -> Dimensiune prea mare!Aplicatia nu permite  ";
       msg+="aproximarea intr-un numar de puncte mai mare decat: ";
       msg+=QString::number(DIM_LIMIT-1);
       msg+=HTML_ENTER;
       message=msg;
       return false;
    }

    bool extracted=false;
    extracted=getMatrix(pointsMatrix,matrixDimension,pointsString);
    if(!extracted)
    {
       QString msg="Err -> Matricea cuprinde erori! Nu s-a putut efectua  prelucrarea!";
       message=msg;
       return false;
    }

    //se extrage valoarea lui x in care se doreste aproximarea functiei
    if(xValueAsString.isEmpty())
    {
        message="Err->Campul corespunzator punctului nu a fost completat!";
        message+=HTML_ENTER;
        message+="Indicati punctul in care se doreste aproximarea valorii functiei!";
        return false;
    }

    bool isExtracted=false;
    x_coord=stringToNumber(xValueAsString,isExtracted);
    if(!isExtracted)
    {
        message="Err->Campul corespunzator punctului in care se doreste aproximarea valorii"
" functiei contine erori!";
        message+=HTML_ENTER;
        message+="Nu s-a putut citi punctul!";
        return false;
    }
    else
    {
        QString msg="",strVal="";
        double val;
        val=lagrange_interpolation(pointsMatrix,matrixDimension.at(0),x_coord);
        strVal=QString::number(val);
        msg="Interpolare Lagrange: valoarea aproximativa a functie in punctul ";
        msg+=QString::number(x_coord);
        msg+=" este ";
        msg+=strVal;
        result=msg;
        message="Good status: datele au fost prelucrate! ";
        message+=HTML_ENTER;
        message+="Rezulatat: ";
        message+=strVal;
    }
    return true;
}

bool newton_interpolation_interpreter(QString &pointsString,QString &xValueAsString,
                                        QString &message,QString &result)
{
    //variabile utilizate
    double pointsMatrix[MAX_LINE][MAX_COL],x_coord;
    message="";
    result="";

    //se extrage matricea ce reprezinta punctele in care se cunoaste valoare functiei
    if(pointsString.isEmpty())
    {
        message="Err->Campul corespunzator punctelor cunoscute nu a fost completat!";
        message+=HTML_ENTER;
        message+="Specificati punctele!";
        return false;
    }
    if(countWhiteSpaces(pointsString)==pointsString.length())
    {
        QString msg="Err -> Nu se poate face prelucrarea! ";
        msg=msg+HTML_ENTER;
        msg=msg+"Ati introdus doar spatii!";
        message=msg;
        return false;
    }
    pointsString=removeWhiteCharacters(pointsString);

    QVector<int> matrixDimension;
    if(!matrixValidator(pointsString,message,IS_NOT_SQUARE,matrixDimension))
       return false;
    if(matrixDimension.at(1)!=2)
    {
       QString msg="Err -> Dimensiune necorespunzatoare! Matricea trebuie sa aiba 2 coloane";
       msg+=HTML_ENTER;
       message=msg;
       return false;
    }
    if(matrixDimension.at(0)+1>=DIM_LIMIT)
    {
       QString msg="Err -> Dimensiune prea mare!Aplicatia nu permite  ";
       msg+="aproximarea intr-un numar de puncte mai mare decat: ";
       msg+=QString::number(DIM_LIMIT-1);
       msg+=HTML_ENTER;
       message=msg;
       return false;
    }

    bool extracted=false;
    extracted=getMatrix(pointsMatrix,matrixDimension,pointsString);
    if(!extracted)
    {
       QString msg="Err -> Matricea cuprinde erori! Nu s-a putut efectua  prelucrarea!";
       message=msg;
       return false;
    }

    //se extrage valoarea lui x in care se doreste aproximarea functiei
    if(xValueAsString.isEmpty())
    {
        message="Err->Campul corespunzator punctului nu a fost completat!";
        message+=HTML_ENTER;
        message+="Indicati punctul in care se doreste aproximarea valorii functiei!";
        return false;
    }

    bool isExtracted=false;
    x_coord=stringToNumber(xValueAsString,isExtracted);
    if(!isExtracted)
    {
        message="Err->Campul corespunzator punctului in care se doreste aproximarea valorii"
" functiei contine erori!";
        message+=HTML_ENTER;
        message+="Nu s-a putut citi punctul!";
        return false;
    }
    else
    {
        QString msg="",strVal="";
        double val=0;
        val=newton_interpolation(pointsMatrix,matrixDimension.at(0),x_coord);
        strVal=QString::number(val);
        msg+="Interpolare Newton: valoarea aproximativa a functie in punctul ";
        msg+=QString::number(x_coord);
        msg+=" este ";
        msg+=strVal;
        result=msg;
        message="Good status: datele au fost prelucrate! ";
        message+=HTML_ENTER;
        message+="Rezulatat: ";
        message+=strVal;
    }
    return true;
}

bool spline_interpolation_interpreter(QString &pointsString,QString &xValueAsString,
                                        QString &message,QString &result)
{
    //variabile utilizate
    double pointsMatrix[MAX_LINE][MAX_COL],x_coord=0,y_coord=0;
    message="";
    result="";

    //se extrage matricea ce reprezinta punctele in care se cunoaste valoare functiei
    if(pointsString.isEmpty())
    {
        message="Err->Campul corespunzator punctelor cunoscute nu a fost completat!";
        message+=HTML_ENTER;
        message+="Specificati punctele!";
        return false;
    }
    if(countWhiteSpaces(pointsString)==pointsString.length())
    {
        QString msg="Err -> Nu se poate face prelucrarea! ";
        msg=msg+HTML_ENTER;
        msg=msg+"Ati introdus doar spatii!";
        message=msg;
        return false;
    }
    pointsString=removeWhiteCharacters(pointsString);

    QVector<int> matrixDimension;
    if(!matrixValidator(pointsString,message,IS_NOT_SQUARE,matrixDimension))
       return false;
    if(matrixDimension.at(1)!=2)
    {
       QString msg="Err -> Dimensiune necorespunzatoare! Matricea trebuie sa aiba 2 coloane";
       msg+=HTML_ENTER;
       message=msg;
       return false;
    }
    if(matrixDimension.at(0)+1>=DIM_LIMIT)
    {
       QString msg="Err -> Dimensiune prea mare!Aplicatia nu permite  ";
       msg+="aproximarea intr-un numar de puncte mai mare decat: ";
       msg+=QString::number(DIM_LIMIT-1);
       msg+=HTML_ENTER;
       message=msg;
       return false;
    }

    bool extracted=false;
    extracted=getMatrix(pointsMatrix,matrixDimension,pointsString);
    if(!extracted)
    {
       QString msg="Err -> Matricea cuprinde erori! Nu s-a putut efectua  prelucrarea!";
       message=msg;
       return false;
    }

    //se extrage valoarea lui x in care se doreste aproximarea functiei
    if(xValueAsString.isEmpty())
    {
        message="Err->Campul corespunzator punctului nu a fost completat!";
        message+=HTML_ENTER;
        message+="Indicati punctul in care se doreste aproximarea valorii functiei!";
        return false;
    }

    bool isExtracted=false;
    x_coord=stringToNumber(xValueAsString,isExtracted);
    if(!isExtracted)
    {
        message="Err->Campul corespunzator punctului in care se doreste aproximarea valorii"
" functiei contine erori!";
        message+=HTML_ENTER;
        message+="Nu s-a putut citi punctul!";
        return false;
    }
    else
    {
        bool interpolationDone=false;
        QString msg="",strVal="";

        interpolationDone=spline_interpolation(pointsMatrix,matrixDimension.at(0),x_coord,y_coord);
        if(!interpolationDone)
        {
            message="Nu s-a putut realiza interpolarea!";
            return false;
        }
        else
        {
        strVal=QString::number(y_coord);
        msg+="Interpolare prin functii spline cubice: valoarea aproximativa a functie in punctul ";
        msg+=QString::number(x_coord);
        msg+=" este ";
        msg+=strVal;
        result=msg;
        message="Good status: datele au fost prelucrate! ";
        message+=HTML_ENTER;
        message+="Rezulatat: ";
        message+=strVal;
        return true;
        }
    }
    return true;
}

bool mas_method_interpreter(QString functionStr,QString precisionStr,
                            QString initialValueStr,QString itMaxStr,QString &message,QString &result )
{
    //variabile utilizate
    double precision=0.0001,it_max=100,initial_value=0;
    bool status=false;

    //se extrage functia
    if(functionStr.isEmpty())
    {
        message="Err->Campul corespunzator functiei nu a fost completat!";
        message+=HTML_ENTER;
        message+="Indicati functia careia trebuie sa i se determine o solutie!";
        return false;
    }
    if(countWhiteSpaces(functionStr)==functionStr.length())
    {
        QString msg="Err -> Nu se poate face prelucrarea functiei! ";
        msg=msg+HTML_ENTER;
        msg=msg+"In campul functiei ati introdus doar spatii!";
        message=msg;
        return false;
    }

    //se extrage precizia
    if(precisionStr.isEmpty())
    {
        message="Err->Campul corespunzator preciziei nu a fost completat!";
        message+=HTML_ENTER;
        message+="Indicati precizia de calcul!";
        return false;
    }
    if(countWhiteSpaces(precisionStr)==precisionStr.length())
    {
        QString msg="Err -> Nu se poate face prelucrarea preciziei! ";
        msg=msg+HTML_ENTER;
        msg=msg+"Ati introdus doar spatii!";
        message=msg;
        return false;
    }

    precisionStr=removeWhiteCharacters(precisionStr);
    if(precisionStr.length()>7)
    {
        QString msg="Err -> Campul preciziei este prea lung! ";
        msg=msg+HTML_ENTER;
        msg=msg+"Introduceti maxim 7 caractere!";
        msg+=HTML_ENTER;
        msg+="Numarul de caractere introdus la preciezie este: ";
        msg+=QString::number(precisionStr.length());
        message=msg;
        return false;
    }

    bool isExtracted=false;
    precision=stringToNumber(precisionStr,isExtracted);
    if(!isExtracted)
    {
        message="Err->Campul corespunzator preciziei contine erori!";
        message+=HTML_ENTER;
        message+="Nu s-a putut extrage precizia!";
        return false;
    }

    //se extrage numarul maxim de iteratii
    if(itMaxStr.isEmpty())
    {
        message="Err->Campul corespunzator numarului maxim de iteratii nu este completat!";
        return false;
    }
    if(countWhiteSpaces(itMaxStr)==itMaxStr.length())
    {
        QString msg="Err -> Nu se poate face prelucrarea numarului maxim de iteratii! ";
        msg=msg+HTML_ENTER;
        msg=msg+"Ati introdus doar spatii!";
        message=msg;
        return false;
    }
    itMaxStr=removeWhiteCharacters(itMaxStr);
    bool extracted1=false;
    it_max=stringToNumber(itMaxStr,extracted1);
    if(!extracted1)
    {
        message="Err->Campul corespunzator numarului maxim de iteratii contine erori!";
        message+=HTML_ENTER;
        message+="Nu s-a putut extrage numarul maxim de iteraii!";
        return false;
    }

    //se extrage valoarea initiala
    if(initialValueStr.isEmpty())
    {
        message="Err->Campul corespunzator valorii initiale nu a fost completat!";
        return false;
    }

    if(countWhiteSpaces(initialValueStr)==initialValueStr.length())
    {
        QString msg="Err -> Nu se poate extrage valoarea intiala! ";
        msg=msg+HTML_ENTER;
        msg=msg+"Campul contine doar spatii!";
        message=msg;
        return false;
    }

    initialValueStr=removeWhiteCharacters(initialValueStr);
    bool extracted2=false;
    initial_value=stringToNumber(initialValueStr,extracted2);
    if(!extracted2)
    {
        message="Err->Campul corespunzator valorii initiale contine erori!";
        message+=HTML_ENTER;
        message+="Nu s-a putut extrage valoarea intiala!";
        return false;
    }

    std::string fct = functionStr.toLocal8Bit().constData();
    try
    {
        double final_value=0;
        bool evaluated=false;
        evaluated=mas_method(fct,initial_value,it_max,precision,final_value);
        if(evaluated)
        {
            result="O solutie a ecuatiei:";
            result+=HTML_ENTER;
            result+=removeWhiteCharacters(functionStr);
            result+=" este: ";
            QString solStr=QString::number(final_value);
            result+=solStr;
            result+=HTML_ENTER;
            message=("Rezulatat calcul: "+solStr);
            status=true;
        }
        else
        {
            message="Nu s-a putut obtine solutia in ";
            message+=itMaxStr;
            message+=" iteratii cu precizia";
            message+="cu precizia ";
            message+=precisionStr;
        }
    }
    catch(Lepton::Exception &e)
    {
        message="Err: Campul functiei cuprinde erori!";
        message+=HTML_ENTER;
        std::string err=e.what();
        QString qerr = QString::fromStdString(err);
        message+=qerr;
    }
    catch(Error &e)
    {
        message=e.what();
    }

    return status;
}

bool newton_approximation_interpreter(QString functionStr,QString precisionStr,
                            QString initialValueStr,QString itMaxStr,QString &message,QString &result )
{
    //variabile utilizate
    double precision=0.0001,it_max=100,initial_value=0;
    bool status=false;

    //se extrage functia
    if(functionStr.isEmpty())
    {
        message="Err->Campul corespunzator functiei nu a fost completat!";
        message+=HTML_ENTER;
        message+="Indicati functia careia trebuie sa i se determine o solutie!";
        return false;
    }
    if(countWhiteSpaces(functionStr)==functionStr.length())
    {
        QString msg="Err -> Nu se poate face prelucrarea functiei! ";
        msg=msg+HTML_ENTER;
        msg=msg+"In campul functiei ati introdus doar spatii!";
        message=msg;
        return false;
    }
    functionStr=functionStr+"+x-x";

    //se extrage precizia
    if(precisionStr.isEmpty())
    {
        message="Err->Campul corespunzator preciziei nu a fost completat!";
        message+=HTML_ENTER;
        message+="Indicati precizia de calcul!";
        return false;
    }
    if(countWhiteSpaces(precisionStr)==precisionStr.length())
    {
        QString msg="Err -> Nu se poate face prelucrarea preciziei! ";
        msg=msg+HTML_ENTER;
        msg=msg+"Ati introdus doar spatii!";
        message=msg;
        return false;
    }

    precisionStr=removeWhiteCharacters(precisionStr);
    if(precisionStr.length()>7)
    {
        QString msg="Err -> Campul preciziei este prea lung! ";
        msg=msg+HTML_ENTER;
        msg=msg+"Introduceti maxim 7 caractere!";
        msg+=HTML_ENTER;
        msg+="Numarul de caractere introdus la preciezie este: ";
        msg+=QString::number(precisionStr.length());
        message=msg;
        return false;
    }

    bool isExtracted=false;
    precision=stringToNumber(precisionStr,isExtracted);
    if(!isExtracted)
    {
        message="Err->Campul corespunzator preciziei contine erori!";
        message+=HTML_ENTER;
        message+="Nu s-a putut extrage precizia!";
        return false;
    }

    //se extrage numarul maxim de iteratii
    if(itMaxStr.isEmpty())
    {
        message="Err->Campul corespunzator numarului maxim de iteratii nu este completat!";
        return false;
    }
    if(countWhiteSpaces(itMaxStr)==itMaxStr.length())
    {
        QString msg="Err -> Nu se poate face prelucrarea numarului maxim de iteratii! ";
        msg=msg+HTML_ENTER;
        msg=msg+"Ati introdus doar spatii!";
        message=msg;
        return false;
    }
    itMaxStr=removeWhiteCharacters(itMaxStr);
    bool extracted1=false;
    it_max=stringToNumber(itMaxStr,extracted1);
    if(!extracted1)
    {
        message="Err->Campul corespunzator numarului maxim de iteratii contine erori!";
        message+=HTML_ENTER;
        message+="Nu s-a putut extrage numarul maxim de iteraii!";
        return false;
    }

    //se extrage valoarea initiala
    if(initialValueStr.isEmpty())
    {
        message="Err->Campul corespunzator valorii initiale nu a fost completat!";
        return false;
    }

    if(countWhiteSpaces(initialValueStr)==initialValueStr.length())
    {
        QString msg="Err -> Nu se poate extrage valoarea intiala! ";
        msg=msg+HTML_ENTER;
        msg=msg+"Campul contine doar spatii!";
        message=msg;
        return false;
    }

    initialValueStr=removeWhiteCharacters(initialValueStr);
    bool extracted2=false;
    initial_value=stringToNumber(initialValueStr,extracted2);
    if(!extracted2)
    {
        message="Err->Campul corespunzator valorii initiale contine erori!";
        message+=HTML_ENTER;
        message+="Nu s-a putut extrage valoarea intiala!";
        return false;
    }

    std::string fct = functionStr.toLocal8Bit().constData();
    try
    {
        double final_value=0;
        bool evaluated=false;
        evaluated=newton_approximation_method(fct,fct,initial_value,it_max,precision,final_value);
        if(evaluated)
        {
            result="Aproximare Newton: o solutie a ecuatiei este: ";
            QString solStr=QString::number(final_value);
            result+=solStr;
            result+=HTML_ENTER;
            message=("Rezulatat calcul: "+solStr);
            status=true;
        }
        else
        {
            message="Nu s-a putut obtine solutia in ";
            message+=itMaxStr;
            message+=" iteratii cu precizia";
            message+="cu precizia ";
            message+=precisionStr;
        }
    }
    catch(Lepton::Exception &e)
    {
        message="Err: Campul functiei cuprinde erori!";
        message+=HTML_ENTER;
        std::string err=e.what();
        QString qerr = QString::fromStdString(err);
        message+=qerr;
    }
    catch(Error &e)
    {
        message=e.what();
    }

    return status;
}


bool integral_trapezoidal_rule_interpreter(QString &functionStr,QString &precisionStr,QString &down_limit,
                                           QString &up_limit,QString &message,QString &result)
{
    //variabile utilizate
    double precision=0.001,top_limit,bottom_limit;
    bool status=false;
    //se extrage functia
    if(functionStr.isEmpty())
    {
        message="Err->Campul corespunzator functiei nu a fost completat!";
        message+=HTML_ENTER;
        message+="Indicati functia careia trebuie sa i se calculeze integrala!";
        return false;
    }
    if(countWhiteSpaces(functionStr)==functionStr.length())
    {
        QString msg="Err -> Nu se poate face prelucrarea functiei! ";
        msg=msg+HTML_ENTER;
        msg=msg+"In campul functiei ati introdus doar spatii!";
        message=msg;
        return false;
    }
    functionStr=removeWhiteCharacters(functionStr);

   //se extrage precizia
   if(precisionStr.isEmpty())
   {
       message="Err->Campul corespunzator preciziei nu a fost completat!";
       message+=HTML_ENTER;
       message+="Indicati precizia de calcul!";
       return false;
   }
   if(countWhiteSpaces(precisionStr)==precisionStr.length())
   {
       QString msg="Err -> Nu se poate face prelucrarea preciziei! ";
       msg=msg+HTML_ENTER;
       msg=msg+"Ati introdus doar spatii!";
       message=msg;
       return false;
   }

   precisionStr=removeWhiteCharacters(precisionStr);
   if(precisionStr.length()>7)
   {
       QString msg="Err -> Campul preciziei este prea lung! ";
       msg=msg+HTML_ENTER;
       msg=msg+"Introduceti maxim 7 caractere!";
       msg+=HTML_ENTER;
       msg+="Numarul de caractere introdus la preciezie este: ";
       msg+=QString::number(precisionStr.length());
       message=msg;
       return false;
   }

   bool isExtracted=false;
   precision=stringToNumber(precisionStr,isExtracted);
   if(!isExtracted)
   {
       message="Err->Campul corespunzator preciziei contine erori!";
       message+=HTML_ENTER;
       message+="Nu s-a putut citi precizia!";
       return false;
   }

   //se extrage limita de jos a integralei ( capatul din stanga al intervalului)
   if(down_limit.isEmpty())
   {
       message="Err->Campul corespunzator limitei de jos (capatului inferior al intervalului) nu a fost completat!";
       message+=HTML_ENTER;
       message+="Indicati valoarea!";
       return false;
   }
   if(countWhiteSpaces(down_limit)==down_limit.length())
   {
       QString msg="Err -> Nu se poate face prelucrarea limitei de jos! ";
       msg=msg+HTML_ENTER;
       msg=msg+"Ati introdus doar spatii!";
       message=msg;
       return false;
   }

   down_limit=removeWhiteCharacters(down_limit);
   bool limit1_extracted=false;
   bottom_limit=stringToNumber(down_limit,limit1_extracted);
   if(!limit1_extracted)
   {
       message="Err->Campul corespunzator limitei de jos contine erori!";
       message+=HTML_ENTER;
       message+="Nu s-a putut extrage limita de jos!";
       return false;
   }

   //se extrage limita de sus a integralei(capatul din dreapta al intervalului
   if(up_limit.isEmpty())
   {
       message="Err->Campul corespunzator limitei de sus a integralei este gol!";
       message+=HTML_ENTER;
       message+="Indicati limita de sus a integralei !";
       return false;
   }

   if(countWhiteSpaces(up_limit)==up_limit.length())
   {
       QString msg="Err -> Nu se poate face prelucrarea limitei de sus a integralei! ";
       msg=msg+HTML_ENTER;
       msg=msg+"Campul contine doar spatii!";
       message=msg;
       return false;
   }

   up_limit=removeWhiteCharacters(up_limit);
   bool limit2_extracted=false;
   top_limit=stringToNumber(up_limit,limit2_extracted);
   if(!limit2_extracted)
   {
       message="Err->Campul corespunzator limitei de sus contine erori!";
       message+=HTML_ENTER;
       message+="Nu s-a putut extrage limita de sus!";
       return false;
   }

   std::string fct = functionStr.toLocal8Bit().constData();
   try
   {
   double val=integral_trapezoidal_rule(bottom_limit,top_limit,precision,fct);

   result="Rezultatul calculului integralei cu metoda trapezului: ";
   result+=HTML_ENTER;
   result+="<font size=  45 px >";
   result+=(QChar(INTEGRAL_SYMBOL));
   result+=" </font> ";
   result+=("<sub>"+down_limit+"</sub>");
   result+=("<sup>"+up_limit+"</sup> ");
   result+=removeWhiteCharacters(functionStr);
   result+="dx= ";
   QString integralValue=QString::number(val);
   result+=integralValue;
   message=("Rezulatat calcul: "+integralValue);
   status=true;
   }
   catch(Lepton::Exception &e)
   {
       message="Err: Campul functiei cuprinde erori!";
       message+=HTML_ENTER;
       std::string err=e.what();
       QString qerr = QString::fromStdString(err);
       message+=qerr;
   }
   catch(Error &e)
   {
       message=e.what();
   }

    return status;
}

bool simpson_rule_interpreter(QString &functionStr,QString &precisionStr,QString &down_limit,
                                           QString &up_limit,QString &message,QString &result)
{
    //variabile utilizate
    double precision=0.001,top_limit,bottom_limit;
    bool status=false;
    //se extrage functia
    if(functionStr.isEmpty())
    {
        message="Err->Campul corespunzator functiei nu a fost completat!";
        message+=HTML_ENTER;
        message+="Indicati functia careia trebuie sa i se calculeze integrala!";
        return false;
    }
    if(countWhiteSpaces(functionStr)==functionStr.length())
    {
        QString msg="Err -> Nu se poate face prelucrarea functiei! ";
        msg=msg+HTML_ENTER;
        msg=msg+"In campul functiei ati introdus doar spatii!";
        message=msg;
        return false;
    }
    functionStr=removeWhiteCharacters(functionStr);

   //se extrage precizia
   if(precisionStr.isEmpty())
   {
       message="Err->Campul corespunzator preciziei nu a fost completat!";
       message+=HTML_ENTER;
       message+="Indicati precizia de calcul!";
       return false;
   }
   if(countWhiteSpaces(precisionStr)==precisionStr.length())
   {
       QString msg="Err -> Nu se poate face prelucrarea preciziei! ";
       msg=msg+HTML_ENTER;
       msg=msg+"Ati introdus doar spatii!";
       message=msg;
       return false;
   }

   precisionStr=removeWhiteCharacters(precisionStr);
   if(precisionStr.length()>7)
   {
       QString msg="Err -> Campul preciziei este prea lung! ";
       msg=msg+HTML_ENTER;
       msg=msg+"Introduceti maxim 7 caractere!";
       msg+=HTML_ENTER;
       msg+="Numarul de caractere introdus la preciezie este: ";
       msg+=QString::number(precisionStr.length());
       message=msg;
       return false;
   }

   bool isExtracted=false;
   precision=stringToNumber(precisionStr,isExtracted);
   if(!isExtracted)
   {
       message="Err->Campul corespunzator preciziei contine erori!";
       message+=HTML_ENTER;
       message+="Nu s-a putut citi precizia!";
       return false;
   }

   //se extrage limita de jos a integralei ( capatul din stanga al intervalului)
   if(down_limit.isEmpty())
   {
       message="Err->Campul corespunzator limitei de jos (capatului inferior al intervalului) nu a fost completat!";
       message+=HTML_ENTER;
       message+="Indicati valoarea!";
       return false;
   }
   if(countWhiteSpaces(down_limit)==down_limit.length())
   {
       QString msg="Err -> Nu se poate face prelucrarea limitei de jos! ";
       msg=msg+HTML_ENTER;
       msg=msg+"Ati introdus doar spatii!";
       message=msg;
       return false;
   }

   down_limit=removeWhiteCharacters(down_limit);
   bool limit1_extracted=false;
   bottom_limit=stringToNumber(down_limit,limit1_extracted);
   if(!limit1_extracted)
   {
       message="Err->Campul corespunzator limitei de jos contine erori!";
       message+=HTML_ENTER;
       message+="Nu s-a putut extrage limita de jos!";
       return false;
   }

   //se extrage limita de sus a integralei(capatul din dreapta al intervalului
   if(up_limit.isEmpty())
   {
       message="Err->Campul corespunzator limitei de sus a integralei este gol!";
       message+=HTML_ENTER;
       message+="Indicati limita de sus a integralei !";
       return false;
   }

   if(countWhiteSpaces(up_limit)==up_limit.length())
   {
       QString msg="Err -> Nu se poate face prelucrarea limitei de sus a integralei! ";
       msg=msg+HTML_ENTER;
       msg=msg+"Campul contine doar spatii!";
       message=msg;
       return false;
   }

   up_limit=removeWhiteCharacters(up_limit);
   bool limit2_extracted=false;
   top_limit=stringToNumber(up_limit,limit2_extracted);
   if(!limit2_extracted)
   {
       message="Err->Campul corespunzator limitei de sus contine erori!";
       message+=HTML_ENTER;
       message+="Nu s-a putut extrage limita de sus!";
       return false;
   }

   std::string fct = functionStr.toLocal8Bit().constData();
   try
   {
   double val=simpson_rule(bottom_limit,top_limit,precision,fct);

   result="Rezultatul calculului integralei cu metoda Simpson: ";
   result+=HTML_ENTER;
   result+="<font size=  45 px >";
   result+=(QChar(INTEGRAL_SYMBOL));
   result+=" </font> ";
   result+=("<sub>"+down_limit+"</sub>");
   result+=("<sup>"+up_limit+"</sup> ");
   result+=removeWhiteCharacters(functionStr);
   result+="dx= ";
   QString integralValue=QString::number(val);
   result+=integralValue;
   message=("Rezulatat calcul: "+integralValue);
   status=true;
   }
   catch(Lepton::Exception &e)
   {
       message="Err: Campul functiei cuprinde erori!";
       message+=HTML_ENTER;
       std::string err=e.what();
       QString qerr = QString::fromStdString(err);
       message+=qerr;
   }
   catch(Error &e)
   {
       message=e.what();
   }

    return status;
}

bool double_integration_interpreter(QString & functionStr,QString &verticiesStr,QString &message,QString &result)
{
    bool interpreter_status=false;
    //variabile utilizate
    double verticiesMatrix[MAX_LINE][MAX_COL];
    message="";
    result="";

    //se extrage matricea ce reprezinta cele trei varfuri ale triunghiului
    if(verticiesStr.isEmpty())
    {
        message="Err->Nu ati precizat varfurile triunghiului!";
        message+=HTML_ENTER;
        message+="Specificati varfurile triunghiului!";
        return false;
    }
    if(countWhiteSpaces(verticiesStr)==verticiesStr.length())
    {
        QString msg="Err -> Nu se poate face prelucrarea! ";
        msg=msg+HTML_ENTER;
        msg=msg+"Ati introdus doar spatii!";
        message=msg;
        return false;
    }
    verticiesStr=removeWhiteCharacters(verticiesStr);

    QVector<int> matrixDimension;
    if(!matrixValidator(verticiesStr,message,IS_NOT_SQUARE,matrixDimension))
       return false;
    if(matrixDimension.at(0)!=3||matrixDimension.at(1)!=2)
    {
       QString msg="Err -> Dimensiune necorespunzatoare! Matricea trebuie sa aiba 3 linii si 2 coloane";
       msg+=HTML_ENTER;
       message=msg;
       return false;
    }

    bool extracted=false;
    extracted=getMatrix(verticiesMatrix,matrixDimension,verticiesStr);
    if(!extracted)
    {
       QString msg="Err -> Matricea cuprinde erori! Nu s-a putut efectua  prelucrarea!";
       message=msg;
       return false;
    }

    //se extrage functia
    if(functionStr.isEmpty())
    {
        message="Err->Campul corespunzator functiei nu a fost completat!";
        message+=HTML_ENTER;
        message+="Indicati functia careia trebuie sa i se calculeze integrala!";
        return false;
    }
    if(countWhiteSpaces(functionStr)==functionStr.length())
    {
        QString msg="Err -> Nu se poate face prelucrarea functiei! ";
        msg=msg+HTML_ENTER;
        msg=msg+"In campul functiei ati introdus doar spatii!";
        message=msg;
        return false;
    }
    functionStr=removeWhiteCharacters(functionStr);

    std::string fct = functionStr.toLocal8Bit().constData();
    try
    {
    double val=double_integration(verticiesMatrix,fct);

    result="Rezultatul calculului integralei duble pe un domeniu triunghi est: ";
    result+=HTML_ENTER;
    result+="< font size= 45 px >";
    result+=(QChar(DINTEGRAL_SYMBOL));
    result+="< /font >";
    result+="<sub>";
    result+=QChar(DELTA_SYMBOL);
    result+=+"</sub >  ";
    result+=removeWhiteCharacters(functionStr);
    result+=" dxdy= ";
    QString integralValue=QString::number(val);
    result+=integralValue;
    message=("Rezulatat calcul: "+integralValue);
    interpreter_status=true;
    }
    catch(Lepton::Exception &e)
    {
        message="Err: Campul functiei cuprinde erori!";
        message+=HTML_ENTER;
        std::string err=e.what();
        QString qerr = QString::fromStdString(err);
        message+=qerr;
    }
    catch(Error &e)
    {
        message=e.what();
    }
    return interpreter_status;
}

bool euler_cauchy_interpreter(QString &pointsStr,QString &iterationStr,QString &initValStr, QString &functionStr,
                              QString &epsilonStr  ,QString &message, QString &result)
{
    bool interpreterStatus=false;
    double matrix_points[MAX_LINE][MAX_COL],max_iteration=200,eps=0.001,init_value=0;
    //se extrage matricea
    if(pointsStr.isEmpty())
    {
        message="Err->Campul corespunzator punctelor Xi in care se doreste aproximarea "
"solutiei problemei Cauchy!";
        message+=HTML_ENTER;
        message+="Introduceti punctele!";
        return false;
    }
    if(countWhiteSpaces(pointsStr)==pointsStr.length())
    {
        QString msg="Err -> Nu se poate face prelucrarea punctelor! ";
        msg=msg+HTML_ENTER;
        msg=msg+"Ati introdus doar spatii!";
        message=msg;
        return false;
    }

    pointsStr=removeWhiteCharacters(pointsStr);

    QVector<int> matrixDimension;
   if(!matrixValidator(pointsStr,message,IS_NOT_SQUARE,matrixDimension))
       return false;
   if(matrixDimension.at(1)!=1)
   {
       QString msg="Err -> Dimensiune necorespunzatoare! Matricea trebuie sa aiba o singura coloana";
       msg+=HTML_ENTER;
       message=msg;
       return false;
   }
   if(matrixDimension.at(0)<2)
   {
       QString msg="Err -> Dimensiune necorespunzatoare! Matricea trebuie sa aiba cel putin 2 linii";
       msg+=HTML_ENTER;
       message=msg;
       return false;
   }
   if(matrixDimension.at(0)+1>=DIM_LIMIT)
   {
       QString msg="Err -> Dimensiune prea mare!Aplicatia nu permite calculul valorilor proprii ";
       msg+="pentru o matrice de dimensiune mai mare decat: ";
       msg+=QString::number(DIM_LIMIT-1);
       msg+=HTML_ENTER;
       message=msg;
       return false;
   }

   bool extracted=false;
   extracted=getMatrix(matrix_points,matrixDimension,pointsStr);
   if(!extracted)
   {
       QString msg="Err ->Campul pentru introducerea punctelor cuprinde erori! Nu s-a putut efectua  prelucrarea!";
       message=msg;
       return false;
   }
   //se extrage functia
   if(functionStr.isEmpty())
   {
       message="Err->Campul corespunzator functiei nu a fost completat!";
       message+=HTML_ENTER;
       message+="Indicati functia careia trebuie sa i se determine o solutie!";
       return false;
   }
   if(countWhiteSpaces(functionStr)==functionStr.length())
   {
       QString msg="Err -> Nu se poate face prelucrarea functiei! ";
       msg=msg+HTML_ENTER;
       msg=msg+"In campul functiei ati introdus doar spatii!";
       message=msg;
       return false;
   }

   //se extrage precizia
   if(epsilonStr.isEmpty())
   {
       message="Err->Campul corespunzator preciziei nu a fost completat!";
       message+=HTML_ENTER;
       message+="Indicati precizia de calcul!";
       return false;
   }
   if(countWhiteSpaces(epsilonStr)==epsilonStr.length())
   {
       QString msg="Err -> Nu se poate face prelucrarea preciziei! ";
       msg=msg+HTML_ENTER;
       msg=msg+"Ati introdus doar spatii!";
       message=msg;
       return false;
   }

   epsilonStr=removeWhiteCharacters(epsilonStr);
   if(epsilonStr.length()>7)
   {
       QString msg="Err -> Campul preciziei este prea lung! ";
       msg=msg+HTML_ENTER;
       msg=msg+"Introduceti maxim 7 caractere!";
       msg+=HTML_ENTER;
       msg+="Numarul de caractere introdus la preciezie este: ";
       msg+=QString::number(epsilonStr.length());
       message=msg;
       return false;
   }

   bool isExtracted=false;
   eps=stringToNumber(epsilonStr,isExtracted);
   if(!isExtracted)
   {
       message="Err->Campul corespunzator preciziei contine erori!";
       message+=HTML_ENTER;
       message+="Nu s-a putut extrage precizia!";
       return false;
   }

   //se extrage numarul maxim de iteratii
   if(iterationStr.isEmpty())
   {
       message="Err->Campul corespunzator numarului maxim de iteratii nu este completat!";
       return false;
   }
   if(countWhiteSpaces(iterationStr)==iterationStr.length())
   {
       QString msg="Err -> Nu se poate face prelucrarea numarului maxim de iteratii! ";
       msg=msg+HTML_ENTER;
       msg=msg+"Ati introdus doar spatii!";
       message=msg;
       return false;
   }
   iterationStr=removeWhiteCharacters(iterationStr);
   bool extracted1=false;
   max_iteration=stringToNumber(iterationStr,extracted1);
   if(!extracted1)
   {
       message="Err->Campul corespunzator numarului maxim de iteratii contine erori!";
       message+=HTML_ENTER;
       message+="Nu s-a putut extrage numarul maxim de iteraii!";
       return false;
   }

   //se extrage valoarea initiala
   if(initValStr.isEmpty())
   {
       message="Err->Campul corespunzator valorii initiale nu a fost completat!";
       return false;
   }

   if(countWhiteSpaces(initValStr)==initValStr.length())
   {
       QString msg="Err -> Nu se poate extrage valoarea intiala! ";
       msg=msg+HTML_ENTER;
       msg=msg+"Campul contine doar spatii!";
       message=msg;
       return false;
   }

   initValStr=removeWhiteCharacters(initValStr);
   bool extracted2=false;
   init_value=stringToNumber(initValStr,extracted2);
   if(!extracted2)
   {
       message="Err->Campul corespunzator valorii initiale contine erori!";
       message+=HTML_ENTER;
       message+="Nu s-a putut extrage valoarea intiala!";
       return false;
   }

   std::string fct = functionStr.toLocal8Bit().constData();
   try
   {
       double result_matrix[MAX_LINE][2];
       bool evaluated=false;
       evaluated=euler_chauchy(matrix_points,matrixDimension.at(0),fct,
                               max_iteration,eps,init_value,result_matrix);
       if(evaluated)
       {
           result="Valorile aproximative ale solutiei problemei Cauchy obtinute "
           "cu metoda Euler in punctele date sunt: ";
           QString solStr=HTML_ENTER;
           for(int i=0;i<matrixDimension.at(0)-1;i++)
           {
               solStr+=("(x<sub>("+QString::number(i+1)+ ")</sub>= ");
               solStr+=QString::number(result_matrix[i][0]);
               solStr+=("  ,  y<sub>("+QString::number(i+1)+ ")</sub>= ");
               solStr+=QString::number(result_matrix[i][1]);
               solStr+=")";
               solStr+=HTML_ENTER;
           }
           result+=solStr;
           message=("Rezulatat calcul =>Metoda Euler: "+solStr);
           interpreterStatus=true;
       }
       else
       {
           message="Nu s-a putut obtine solutia in ";
           message+=iterationStr;
           message+=" iteratii cu precizia";
           message+="cu precizia ";
           message+=epsilonStr;
       }
   }
   catch(Lepton::Exception &e)
   {
       message="Err: Campul functiei cuprinde erori!";
       message+=HTML_ENTER;
       std::string err=e.what();
       QString qerr = QString::fromStdString(err);
       message+=qerr;
   }
   catch(Error &e)
   {
       message=e.what();
   }

    return interpreterStatus;
}

bool runge_kutta_interpreter(QString &pointsStr,QString &iterationStr,QString &initValStr, QString &functionStr,
                              QString &epsilonStr  ,QString &message, QString &result)
{
    bool interpreterStatus=false;
    double matrix_points[MAX_LINE][MAX_COL],max_iteration=200,eps=0.001,init_value=0;
    //se extrage matricea
    if(pointsStr.isEmpty())
    {
        message="Err->Campul corespunzator punctelor Xi in care se doreste aproximarea "
"solutiei problemei Cauchy!";
        message+=HTML_ENTER;
        message+="Introduceti punctele!";
        return false;
    }
    if(countWhiteSpaces(pointsStr)==pointsStr.length())
    {
        QString msg="Err -> Nu se poate face prelucrarea punctelor! ";
        msg=msg+HTML_ENTER;
        msg=msg+"Ati introdus doar spatii!";
        message=msg;
        return false;
    }

    pointsStr=removeWhiteCharacters(pointsStr);

    QVector<int> matrixDimension;
   if(!matrixValidator(pointsStr,message,IS_NOT_SQUARE,matrixDimension))
       return false;
   if(matrixDimension.at(1)!=1)
   {
       QString msg="Err -> Dimensiune necorespunzatoare! Matricea trebuie sa aiba o singura coloana";
       msg+=HTML_ENTER;
       message=msg;
       return false;
   }
   if(matrixDimension.at(0)<2)
   {
       QString msg="Err -> Dimensiune necorespunzatoare! Matricea trebuie sa aiba cel putin 2 linii";
       msg+=HTML_ENTER;
       message=msg;
       return false;
   }
   if(matrixDimension.at(0)+1>=DIM_LIMIT)
   {
       QString msg="Err -> Dimensiune prea mare!Aplicatia nu permite calculul valorilor proprii ";
       msg+="pentru o matrice de dimensiune mai mare decat: ";
       msg+=QString::number(DIM_LIMIT-1);
       msg+=HTML_ENTER;
       message=msg;
       return false;
   }

   bool extracted=false;
   extracted=getMatrix(matrix_points,matrixDimension,pointsStr);
   if(!extracted)
   {
       QString msg="Err ->Campul pentru introducerea punctelor cuprinde erori! Nu s-a putut efectua  prelucrarea!";
       message=msg;
       return false;
   }
   //se extrage functia
   if(functionStr.isEmpty())
   {
       message="Err->Campul corespunzator functiei nu a fost completat!";
       message+=HTML_ENTER;
       message+="Indicati functia careia trebuie sa i se determine o solutie!";
       return false;
   }
   if(countWhiteSpaces(functionStr)==functionStr.length())
   {
       QString msg="Err -> Nu se poate face prelucrarea functiei! ";
       msg=msg+HTML_ENTER;
       msg=msg+"In campul functiei ati introdus doar spatii!";
       message=msg;
       return false;
   }

   //se extrage precizia
   if(epsilonStr.isEmpty())
   {
       message="Err->Campul corespunzator preciziei nu a fost completat!";
       message+=HTML_ENTER;
       message+="Indicati precizia de calcul!";
       return false;
   }
   if(countWhiteSpaces(epsilonStr)==epsilonStr.length())
   {
       QString msg="Err -> Nu se poate face prelucrarea preciziei! ";
       msg=msg+HTML_ENTER;
       msg=msg+"Ati introdus doar spatii!";
       message=msg;
       return false;
   }

   epsilonStr=removeWhiteCharacters(epsilonStr);
   if(epsilonStr.length()>7)
   {
       QString msg="Err -> Campul preciziei este prea lung! ";
       msg=msg+HTML_ENTER;
       msg=msg+"Introduceti maxim 7 caractere!";
       msg+=HTML_ENTER;
       msg+="Numarul de caractere introdus la preciezie este: ";
       msg+=QString::number(epsilonStr.length());
       message=msg;
       return false;
   }

   bool isExtracted=false;
   eps=stringToNumber(epsilonStr,isExtracted);
   if(!isExtracted)
   {
       message="Err->Campul corespunzator preciziei contine erori!";
       message+=HTML_ENTER;
       message+="Nu s-a putut extrage precizia!";
       return false;
   }

   //se extrage numarul maxim de iteratii
   if(iterationStr.isEmpty())
   {
       message="Err->Campul corespunzator numarului maxim de iteratii nu este completat!";
       return false;
   }
   if(countWhiteSpaces(iterationStr)==iterationStr.length())
   {
       QString msg="Err -> Nu se poate face prelucrarea numarului maxim de iteratii! ";
       msg=msg+HTML_ENTER;
       msg=msg+"Ati introdus doar spatii!";
       message=msg;
       return false;
   }
   iterationStr=removeWhiteCharacters(iterationStr);
   bool extracted1=false;
   max_iteration=stringToNumber(iterationStr,extracted1);
   if(!extracted1)
   {
       message="Err->Campul corespunzator numarului maxim de iteratii contine erori!";
       message+=HTML_ENTER;
       message+="Nu s-a putut extrage numarul maxim de iteraii!";
       return false;
   }

   //se extrage valoarea initiala
   if(initValStr.isEmpty())
   {
       message="Err->Campul corespunzator valorii initiale nu a fost completat!";
       return false;
   }

   if(countWhiteSpaces(initValStr)==initValStr.length())
   {
       QString msg="Err -> Nu se poate extrage valoarea intiala! ";
       msg=msg+HTML_ENTER;
       msg=msg+"Campul contine doar spatii!";
       message=msg;
       return false;
   }

   initValStr=removeWhiteCharacters(initValStr);
   bool extracted2=false;
   init_value=stringToNumber(initValStr,extracted2);
   if(!extracted2)
   {
       message="Err->Campul corespunzator valorii initiale contine erori!";
       message+=HTML_ENTER;
       message+="Nu s-a putut extrage valoarea intiala!";
       return false;
   }

   std::string fct = functionStr.toLocal8Bit().constData();
   try
   {
       double result_matrix[MAX_LINE][2];
       bool evaluated=false;
       evaluated=runge_kutta(matrix_points,matrixDimension.at(0),fct,
                               max_iteration,eps,init_value,result_matrix);
       if(evaluated)
       {
           result="Valorile aproximative ale solutiei problemei Cauchy obtinute "
           "cu metoda Runge-Kutta in punctele date sunt: ";
           QString solStr=HTML_ENTER;
           for(int i=0;i<matrixDimension.at(0)-1;i++)
           {
               solStr+=("(x<sub>("+QString::number(i+1)+ ")</sub>= ");
               solStr+=QString::number(result_matrix[i][0]);
               solStr+=("  ,  y<sub>("+QString::number(i+1)+ ")</sub>= ");
               solStr+=QString::number(result_matrix[i][1]);
               solStr+=")";
               solStr+=HTML_ENTER;
           }
           result+=solStr;
           message=("Rezulatat calcul =>Metoda Runge-Kutta: "+solStr);
           interpreterStatus=true;
       }
       else
       {
           message="Nu s-a putut obtine solutia in ";
           message+=iterationStr;
           message+=" iteratii cu precizia";
           message+="cu precizia ";
           message+=epsilonStr;
       }
   }
   catch(Lepton::Exception &e)
   {
       message="Err: Campul functiei cuprinde erori!";
       message+=HTML_ENTER;
       std::string err=e.what();
       QString qerr = QString::fromStdString(err);
       message+=qerr;
   }
   catch(Error &e)
   {
       message=e.what();
   }

    return interpreterStatus;
}
