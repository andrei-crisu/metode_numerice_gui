#include "utilities.h"

//testeaza daca caracterul primit ca argumet
//este o cifra
bool isDigit(const QChar c)
{
 if(c>='0'&&c<='9')
        return true;
    else
        return false;
}

//testeaza daca caracterul primit ca argument este o litera
// nu este case sensitive
bool isLetter(const QChar c)
{
 if(c>='A'&&c<='Z')
        return true;
    else
         {
             if(c>='a'&&c<='z')
             return true;
         else
             return false;
         }
}
//determina daca un caracter este Spatiu alb( tab orizontal, tab vertical,enter sau spatiu)
bool isWhiteSpace(const QChar c)
{
    if(c=='\t'||c=='\v'||c=='\n'||c==' ')
        return true;
    else
        return false;

}

int countWhiteSpaces(QString str)
{
    int count=0;
    int len=str.length();
    for(int i=0;i<len;i++)
    {
        if(isWhiteSpace(str.at(i)))
            count++;
    }
    return count;
}

QString SolutionToString(double sol[MAX_LINE],int dim)
{
    int i=1;
    QString solution;
    solution="( ";
    for(i=1;i<=dim;i++)
    {
        solution+=QString::number(sol[i]);
        if(i<dim)
            solution+="; ";
    }
    solution+=" )";

    return solution;
}

void getTriangularMatrix(double triangularMatrix[MAX_LINE][MAX_COL],
                         double augmentedMatrix[MAX_LINE][MAX_COL],int dim,int triangularMatrixType)
{
    int i,j;

    if(triangularMatrixType==UPPER_TRIANGULAR)
    {
        for(i=1;i<=dim;i++)
            for(j=1;j<=dim;j++)
            {
                if(i<=j)
                    triangularMatrix[i][j]=augmentedMatrix[i][j];
                else
                    triangularMatrix[i][j]=0;
            }
    } else if(triangularMatrixType==LOWER_TRIANGULAR)
    {
        for(i=1;i<=dim;i++)
            for(j=1;j<=dim;j++)
            {
                if(i>=j)
                    triangularMatrix[i][j]=augmentedMatrix[i][j];
                else
                    triangularMatrix[i][j]=0;
            }
    } else
    {
        for(i=1;i<=dim;i++)
            for(j=1;j<=dim;j++)
                triangularMatrix[i][j]=0;
    }
}

//converteste o matrice de numere reale
//dubla precizie in sir de caractere
QString matrixToString(double matrix[MAX_LINE][MAX_COL],int ln,int col,int offset,int alignment)
{
    QString string;
    int i ,j,maxLength,spaceOfRepresentation;
    maxLength=getMaxStringLength(matrix,ln,col);
    spaceOfRepresentation=maxLength+offset;
    for(i=1;i<=ln;i++)
    {
        for(j=1;j<=col;j++)
        {
            string+=numberToString(matrix[i][j],RIGHT_ALIGNMENT,spaceOfRepresentation,' ');
        }
        string+="\n";
    }
    return string;
}

//converteste un numar real dubla precizie
// la sir de caractere
//la acest sir de caractere se adauga inainte sau dupa,in functie de tipul alinierii,
// un anumit numar de caractere de umplere
//caracterul de umplere este precizat prin parametrul ch
QString numberToString(double nr,int alignmentType,int spaceOfRepresentation,QChar ch)
{
    QString doubleAsString,fillString,stringRepresentation;
    int particularOffset;
    doubleAsString=QString::number(nr,'g',3);
    particularOffset=spaceOfRepresentation-doubleAsString.length();
    fillString=fillWith(ch,particularOffset);

    switch(alignmentType)
    {
    case LEFT_ALIGNMENT:
        stringRepresentation=doubleAsString+fillString;
        break;
    case RIGHT_ALIGNMENT:
        stringRepresentation=fillString+doubleAsString;
        break;
    default:
        break;
    }
    return stringRepresentation;
}

//returneaza un sir format din 'len' caractere 'ch'
QString fillWith(QChar ch,int len)
{
    QString string;
    while(len)
    {
        string+=ch;
        len--;
    }
    return string;
}

//returneaza lungimea celui mai lung sir
//acest sir este reprezetarea  sub forma de sir al
//unui element al matricei
//spre exemplificare
//pentru matricea
// 10 -10
// 10.25 -10.25
//cel mai lung element ca sir este -10.25
//functia apelata cu aceasta matrice
//ar returna valoarea 6 (adica numarul de caractere din reprezentarea ca
//sir a numarului)

int getMaxStringLength(double m[MAX_LINE][MAX_COL],int ln,int col)
{
    int maxLen=0;
    QString str;
    int i,j;
    for(i=1;i<=ln;i++)
        for(j=1;j<=col;j++)
        {
            str=QString::number(m[i][j],'g',3);
            if(maxLen<str.length())
                maxLen=str.length();
        }
    return maxLen;
}

// set all the elements on the main diagonal to the value stored in the variable val
void setPrincipalDiagonal(double m[MAX_LINE][MAX_COL],int ln,int col,double val)
{
    int i,n;
    if(ln<col)
        n=ln;
    else
        n=col;
    for(i=1;i<=n;i++)
        m[i][i]=val;
}

//set all the elements of a 2D arry to the value stored in the variable val
void initializeMatrix(double m[MAX_LINE][MAX_COL],int ln,int col,double val)
{
    int i,j;
    for(i=1;i<=ln;i++)
        for(j=1;j<=ln;j++)
            m[i][j]=val;
}

//test if a matrix is diagonally dominant
//the argument: diagonal_dominance_type can have 2 values
// STRICT_DOMINANCE  (comparison will be  " > "
// WEAK_DOMINANCE (comparsion  will be  " >= "
//the argument: orientation argument  can have 2 values
// ON_LINE diagonal dominance is tested on lines
// ON_COLUMN diagonal dominance is tested on columns
bool is_diagonally_dominant(double m[MAX_LINE][MAX_COL],int dim,bool diagonal_dominance_type,bool orientation)
{
  bool diagonal_dominance=false;
  int i,j;
  double sum;
  for(i=1;i<=dim;i++)
  {
      sum=0;
      for(j=1;j<=dim;j++)
      {
          if(orientation==ON_LINE)
              sum+=fabs(m[i][j]);
          else
              sum+=fabs(m[j][i]);
      }
//we have this condition : fabs(2*m[i][i])>sum because we make
// sum with all elements from line/column
      if(diagonal_dominance_type==STRICT_DOMINANCE)
      {
          if(fabs(2*m[i][i])>sum)
              diagonal_dominance=true;
          else
          {
              diagonal_dominance=false;
              return diagonal_dominance;
          }
      }
      else
      {
          if(fabs(2*m[i][j])>=sum)
              diagonal_dominance=true;
          else
          {
              diagonal_dominance=false;
              return diagonal_dominance;
          }
      }
  }
  return diagonal_dominance;
}

//test if exist any line with strict dominance
bool one_line_strict_dominance(double m[MAX_LINE][MAX_COL],int dim)
{
    bool strict_dominance=false;
    int i,j;
    double sum;
    for(i=1;i<=dim;i++)
    {
        sum=0;
        for(j=1;j<=dim;j++)
        {
            sum+=fabs(m[i][j]);
        }
        if(fabs(2*m[i][i])>sum)
        {
            strict_dominance=true;
            return strict_dominance;
        }
        else
        {
            strict_dominance=false;
        }
    }
    return strict_dominance;
}

//test if exist any column with strict dominance
bool one_column_strict_dominance(double m[MAX_LINE][MAX_COL],int dim)
{
    bool strict_dominance=false;
    int i,j;
    double sum;
    for(i=1;i<=dim;i++)
    {
        sum=0;
        for(j=1;j<=dim;j++)
        {
            sum+=fabs(m[j][i]);
        }
        if(fabs(2*m[i][i])>sum)
        {
            strict_dominance=true;
            return strict_dominance;
        }
        else
        {
            strict_dominance=false;
        }
    }
    return strict_dominance;
}

bool simetricMatrix(double m[MAX_LINE][MAX_COL],int dim)
{
    int i,j;
    for(i=1;i<=dim;i++)
        for(j=i;j<=dim;j++)
            if(m[i][j]!=m[j][i])
                return  false;
    return true;
}

//copy column  col2 from matrix source to matrix dest at column col1
//both matrices must have the same number of columns
void specialCopy(double dest[MAX_LINE][MAX_COL],double source[MAX_LINE][MAX_COL],
                 int col1,int col2,int dim)
{
    int i;
    for(i=1;i<=dim;i++)
        dest[i][col1]=source[i][col2];

}

double user_fct(double &x,double val,Lepton::CompiledExpression &expression)
{
    double result;
    x=val;
    result=expression.evaluate();
    return result;
}

double user_fct2(double &x,double &y,double x_val,double y_val,Lepton::CompiledExpression &expression)
{
    double result;
    x=x_val;
    y=y_val;
    result=expression.evaluate();
    return result;
}

