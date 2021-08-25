#include "basic_text_interpreter.h"

bool getMatrix(double matrix[MAX_LINE][MAX_COL],QVector<int> dim,QString str)
{
    int k=0;
    QString aux;
    QString string=str;
    QStringList elemente;
    elemente=string.split(QRegularExpression("\\s+"));
    for(int i=1;i<=dim.at(0);i++)
        for(int j=1;j<=dim.at(1);j++)
        {
            aux=elemente.at(k);
            matrix[i][j]=aux.toDouble();
            k++;
        }
    return true;
}
bool isMatrixAsString(QVector<int> dim,bool isSquareMatrix)
{
 QVector<int> dimension= dim;
 if(dimension.at(0)==-1||dimension.at(1)==-1)
     return false;
 else if(isSquareMatrix)
     if(dimension.at(0)!=dimension.at(1))
         return false;
    return true;
}
QVector<int> getDim_of_StringMatrix(QString string)
{
    //Se presupune initial ca sirul nu reprezinta o matrice
    //motiv pentru care
    //dim va retine valori ce nu pot reprezenta
    //dimeniunea unei matrici
    QVector<int> dim;
    dim.append(-1);
    dim.append(-1);
    //retine numarul aparitiilor caracterului SPATIU
    //aflate inaintea caracterului ENTER anterior
    int oldSpaceOccurrence=0;
    //retine toate aparitiile caracterului SPATIU
    //aflate inaintea caracterului ENTER curent
    //sau ,in cazul in care s-a ajuns la finalul sirului
    //retine toate aparitiile ale caracterului SPATIU
    //de la utlimul ENTER pana la final
    int newSpaceOccurrence=0;
    //numara toate aparitiile caracterului ENTER
    int EnterOccurrence=0;
    //Scopul:elimina toate aparitiile succesive ale caracterului SPACE ' ';
    //de fapt fiecare subir "  " (format din 2 caractere spatiu)
    //este inlocuit cu un subsir format dintr-un singur caracter spatiu " "

    for(int i=0;i<string.length();i++)
    {
       if(string.at(i)==' ')
           newSpaceOccurrence++;
       else if(string.at(i)=='\n')
       {
           newSpaceOccurrence++;
           //numarul de elemente ale liniilor se compara incepand cu
           //a 2 a
           // comparatia facandu-se cu precedenta
           if(EnterOccurrence>0)
           {
               //incepand cu linia a doua
               //daca numarul de elemente de pe aceasta
               //difera de cel de pe anterioara
               //inseaman ca nu se poate discuta despre o matrice
               //prin urmare: se va returna o dimensiune invalida
               if(oldSpaceOccurrence!=newSpaceOccurrence)
               {
                   return dim;
               }
           }
           oldSpaceOccurrence=newSpaceOccurrence;
           newSpaceOccurrence=0;
           EnterOccurrence++;

       }
    }
    newSpaceOccurrence++;
    if(oldSpaceOccurrence!=newSpaceOccurrence &&EnterOccurrence>0)
    {
        return dim;
    }
    EnterOccurrence++;

    //in acest punct al programului (in cazul in care nu se va indeplini
    //niciuna din conditiile anterioare de return ,pentru ca altfel nu s-ar mai ajunge aici):
    //EnterOccurrence are stocat numarul de aparitii ale caracterului ENTER
    //adica numarul de linii ale matricei
    //atat oldSpaceOccurrence cat si newSpaceOccurence vor stoca numarul de coloane ale matricei
    dim.replace(0,EnterOccurrence);
    dim.replace(1,newSpaceOccurrence);
    return dim;
}

QString replaceAll(QString entire_string,QString str1,QString str2)
{
    while(entire_string.count(str1)!=0)
    {
    entire_string.replace(str1,str2);
    }
    return entire_string;
}

QString removeWhiteCharacters(QString string)
{
    string=replaceAll(string,"\t"," ");
    string=replaceAll(string,"\v"," ");
    string=replaceAll(string,"  "," ");
    string=replaceAll(string," \n","\n");
    string=replaceAll(string,"\n ","\n");
    string=replaceAll(string,"\n\n","\n");
    if(string.at(0)==' '||string.at(0)=='\n')
        string=string.right(string.length()-1);
    if(string.at(string.length()-1)==' '||string.at(string.length()-1)=='\n')
        string=string.left(string.length()-1);
    return string;
}

//scaneaza sirul string si returneaza
//adevarat daca nu contine alte caractere
//decat cele specificate prin sirului allowedSymbols
//mai mult daca cei doi indicatori Digit,Letter ( sunt setati la true/ implicit sunt setati)
// functia va omite si literele si cifrele
//daca va gasi un caracter diferit de cele enumerate mai sus
//atunci functia va returna valoarea false
bool containValidCh(QString string,QString allowedSymbols,bool Digit,bool Letter)
{
    bool valid=false;
    string=string.toUpper();
    for(int i=0;i<string.length();i++)
       {
        valid=false;
        if(Letter)
            if(string.at(i)>='A'&&string.at(i)<='Z')
            {
                valid=true;
                continue;
            }
        if(Digit)
            if(string.at(i)>='0'&&string.at(i)<='9')
            {
                valid=true;
                continue;
            }
        int j;
        for(j=0;j<allowedSymbols.length();j++)
            if(allowedSymbols.at(j)!=string.at(i))
                continue;
        else
            {
                valid=true;
                break;
            }
        if(valid==false)
            return valid;
       }
    return valid;
}
//testeaza daca matricea introdusa depaseste dimeniuniele impuse
//adica aplicatia poate prelucra cel mult matrici de dimeniunile impuse
// de constan DIM_LIMIT
//functia returneaza adevarat daca s-a depasit limita
//altfel returneaza fals

bool exceeds_app_limitation(QVector<int> dim)
{
    int ln,col;
    ln=dim.at(0);
    col=dim.at(1);
    if(ln>DIM_LIMIT||col>DIM_LIMIT)
        return true;
    else
        return false;
}

QVector<int> scanForMistakes(QString str,bool &existMistake)
{
    QVector<int> position;
    position.append(-1);
    position.append(-1);
    int ln,col,i,len=0;
    ln=col=1;
    len=str.length();
    if(str.at(0)=='-')
    {
        if(len<=1)
        {
            existMistake=true;
            position.replace(0,ln);
            position.replace(1,col);
            return position;
        }
        else if (!isDigit(str.at(1)))
        {
            existMistake=true;
            return position;
        }
    }
    for(i=1;i<len-1;i++)
    {
        if(str.at(i)==' ')
        {
            col++;
        } else if(str.at(i)=='\n')
            {
                ln++;
                col=1;
            }
            else if(str.at(i)=='-')
            {
                if (isDigit(str.at(i-1))||!isDigit(str.at(i+1)))
                {
                    existMistake=true;
                    position.replace(0,ln);
                    position.replace(1,col);
                    return position;
                }
            } else if(str.at(i)=='.')
            {
                if (!isDigit(str.at(i-1))||!isDigit(str.at(i+1)))
                {
                    existMistake=true;
                    position.replace(0,ln);
                    position.replace(1,col);
                    return position;
                }
            }
    }
    return position;
}

//testeaza daca sirul matrixStr
//intruneste  o parte din conditiile pentru a fi o matrice
bool matrixValidator(QString &matrixStr,QString &message,int matrixType,QVector<int> &dimension)
{
    if((matrixStr.length()<1))
    {
        message="Err -> Introduceti mai intai matricea !";
        message+=HTML_ENTER;
        message+="Nu ati introdus matricea !!!";
        return false;
    }

    matrixStr=removeWhiteCharacters(matrixStr);
    dimension =getDim_of_StringMatrix(matrixStr);

    if(!containValidCh(matrixStr," -.\n",DIGIT_ALLOWED,NO_LETTER_ALLOWED))
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

   if(!isMatrixAsString(dimension,matrixType))
   {
       QString msg="Err -> Structura introdusa nu este o matrice!";
       message=msg;
       return false;
   }
   bool mistakesFound=false;
   QVector<int> pos= scanForMistakes(matrixStr,mistakesFound);
   if(mistakesFound)
   {
       QString msg="Err -> Punctul zecimal sau semnul nu se gasesc unde trebuie!";
       msg=msg+HTML_ENTER+"Greseala la elementul de pe linia: "+QString::number(pos.at(0))
               +", coloana: "+QString::number(pos.at(1));
       message=msg;
       return false;
   }
   return true;
}

double stringToNumber(QString &string,bool &isExtracted)
{
    isExtracted=false;
    bool isNumber=false;

    if(countWhiteSpaces(string)==string.length())
        return (isExtracted=false);
    string=removeWhiteCharacters(string);

    double nr=string.toDouble(&isNumber);
    if(!isNumber)
    {
        return 0;
    }

    isExtracted=true;
    return nr;
}

QString polynomialString(double krylov_coefficient[MAX_LINE],int dim)
{
    QString polynomial_string="Polinomul caracteristic: ";
    QString aux="";
    QChar lambda;
    lambda=QChar(LAMBDA_SYMBOL);

    QString str="";
    int count_zero=0;
    polynomial_string+=HTML_ENTER;
    polynomial_string+="p(";
    polynomial_string+=lambda;
    polynomial_string+=")= ";

    for(int k=0;k<=dim;k++)
    {

        if(krylov_coefficient[k]!=0)
        {
            if((k!=0)&&krylov_coefficient[k]>0)
                str+="+";
            if(krylov_coefficient[k]==-1&&(k!=dim))
                str+="-";
            if(fabs(krylov_coefficient[k])!=1||(fabs(krylov_coefficient[k])==1&&(dim==k)))
            {
                str+=QString::number(krylov_coefficient[k]);
                //if(dim!=k)
                    //polynomial_string+="*";
            }
            if(dim-k!=0)
            {
                str+=lambda;
                if((dim-k)!=1)
                {
                    aux="<sup>"+QString::number(dim-k)+"</sup>";
                    str+=aux;
                }

            }
        }
        else
            count_zero++;
    }
    if(count_zero==dim+1)
        str+="0";
    if(str.at(0)=='+')
    {
        str=str.mid(1);
    }
    polynomial_string=polynomial_string+str;
    return polynomial_string;
}
