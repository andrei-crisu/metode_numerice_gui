#include <numerical_methods.h>
#include<QDebug>

double chio_method(double a[MAX_LINE][MAX_COL],int n)
{
    double det,aux;
    int i,j;
    if(n==1)
    {
        det=a[1][1];
        return det;
    }
    det=1;
        do
        {
            if(a[1][1]==0)
            {
                i=2;
                while(i<=n&&a[i][1]==0)
                    i++;
                if(i>n)
                {
                    det=0;
                    return det;
                }
                for(j=1;j<=n;j++)
                {
                    aux=a[1][j];
                    a[1][j]=a[i][j];
                    a[i][j]=aux;
                }
                det=-det;
            }
            for(i=1;i<=n-2;i++)
                det=det*a[1][1];
            for(i=2;i<=n;i++)
                for(j=2;j<=n;j++)
                a[i][j]=a[i][j]*a[1][1]-a[i][1]*a[1][j];
            n--;
            for(i=1;i<=n;i++)
                for(j=1;j<=n;j++)
                a[i][j]=a[i+1][j+1];
        }
        while(n!=1);
        det=a[1][1]/det;
    return det;
}

bool gauss_method(double matrix[MAX_LINE][MAX_COL],int n,
                      double sol[MAX_LINE],double triangularMatrix[MAX_LINE][MAX_COL])
{
    double s,piv,aux;
    int i,j,k,lin;
    double a[MAX_LINE][MAX_COL];
    for(i=1;i<=n;i++)
        for(j=1;j<=n+1;j++)
            a[i][j]=matrix[i][j];

    for(k=1;k<=n-1;k++)
    {
        piv=fabs(a[k][k]);
        lin=k;
        for(i=k+1;i<=n;i++)
        {
            if(piv<fabs(a[i][k]))
            {
                piv=fabs(a[i][k]);
                lin=i;
            }
        }

        //sistemul nu are solutie unica
        if(piv==0)
            return false;

        if(lin!=k)
            for(j=k;j<=n+1;j++)
            {
                aux=a[k][j];
                a[k][j]=a[lin][j];
                a[lin][j]=aux;
            }
        for(i=k+1;i<=n;i++)
        {
            a[i][k]=a[i][k]/a[k][k];
            for(j=k+1;j<=n+1;j++)
                a[i][j]=a[i][j]-a[i][k]*a[k][j];
        }
    }
    //extragerea solutiilor sistemului

    //sistemul nu are solutie unica
    if(a[n][n]==0)
        return false;

    a[n][n+1]=a[n][n+1]/a[n][n];
    for(i=n-1;i>=1;i--)
    {
        s=0;
        for(j=i+1;j<=n;j++)
            s=s+a[i][j]*a[j][n+1];
        a[i][n+1]=(a[i][n+1]-s)/a[i][i];
    }
    //extrage din matricea extinsa matricea triunghiulara (superior triunghiulara)
    //matricea triunghiulara este triangularMatrix,
    //iar extragerea se face din matricea extinsa a
    getTriangularMatrix(triangularMatrix,a,n,UPPER_TRIANGULAR);

    //incarcarea solutiilor in vectorul de solutii
    for(i=1;i<=n;i++)
        sol[i]=a[i][n+1];
    return true;
}

bool lr_factorization(double matrix[MAX_LINE][MAX_COL],int n,double sol[MAX_LINE],
                  double lowerTriangularMatrix[MAX_LINE][MAX_COL],
                  double upperTriangularMatrix[MAX_LINE][MAX_COL])
{
    double aux,s=0,piv;
    int i,j,k,h;
    double a[MAX_LINE][MAX_COL];
    for(i=1;i<=n;i++)
            for(j=1;j<=n+1;j++)
                a[i][j]=matrix[i][j];

    if(a[1][1]==0)
    {
        i=1;
        do
        {
            i++;
        }
        while(a[i][1]==0&&i<=n);
        //sistemul nu are solutie unica
        //se returneaza fals
        if(i>n)
            return false;

        for(j=1;j<=n+1;j++)
        {
            aux=a[1][j];
            a[1][j]=a[i][j];
            a[i][j]=aux;
        }
    }
    for(i=2;i<=n;i++)
        a[i][1]=a[i][1]/a[1][1];
    for(k=2;k<=n;k++)
    {
        i=k;
        do
        {
            s=0;
            piv=0;
            for(h=1;h<=k-1;h++)
                s=s+a[i][h]*a[h][k];
            piv=a[i][k]-s;
            i++;
        }
        while(piv==0&&i<=n);

        //sistemul nu are solutie unica
        //se returneaza fals
        if(piv==0)
            return false;

        if(i!=k+1)
            for(j=1;j<=n+1;j++)
            {
                aux=a[k][j];
                a[k][j]=a[i-1][j];
                a[i-1][j]=aux;
            }
        for(j=k;j<=n;j++)
        {
            s=0;
            for(h=1;h<=k-1;h++)
                s=s+a[k][h]*a[h][j];
            a[k][j]=a[k][j]-s;
        }
        for(i=k+1;i<=n;i++)
        {
            s=0;
            for(h=1;h<=k-1;h++)
                s=s+a[i][h]*a[h][k];
            a[i][k]=(a[i][k]-s)/a[k][k];
        }
    }
    for(i=2;i<=n;i++)
    {
        s=0;
        for(k=1;k<=i-1;k++)
            s=s+a[i][k]*a[k][n+1];
        a[i][n+1]=a[i][n+1]-s;
    }
    a[n][n+1]=a[n][n+1]/a[n][n];
    for(i=n-1;i>=1;i--)
    {
        s=0;
        for(j=i+1;j<=n;j++)
            s=s+a[i][j]*a[j][n+1];
        a[i][n+1]=(a[i][n+1]-s)/a[i][i];
    }

    //extragerea celor doua matrici
    //superior respeciv inferior triunghiulare
    if(!(upperTriangularMatrix==nullptr)||!(lowerTriangularMatrix==nullptr))
    {
        getTriangularMatrix(upperTriangularMatrix,a,n,UPPER_TRIANGULAR);
        getTriangularMatrix(lowerTriangularMatrix,a,n,LOWER_TRIANGULAR);
    }
    //stocarea solutie in vectorul de solutii sol
    for(i=1;i<=n;i++)
    {
        sol[i]=a[i][n+1];
    }

    return true;
}

bool jacobi_method(double m[MAX_LINE][MAX_COL],int n,int maxIterationNumber,
                   double precision,double initialSolution[MAX_LINE][MAX_COL],double solution[MAX_LINE],
                   int &iterationNumber)
{
    int it,itmax=0,i,j;
    double a[MAX_LINE][MAX_COL],b[MAX_LINE],eps,x[MAX_LINE],y[MAX_LINE],max,s;
    itmax=maxIterationNumber;
    eps=precision;

    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
        {
            a[i][j]=m[i][j];
        }
    //coloana termenilor liberi reprezinta ultima coloana in matricea extinsa m a sistemului
    //primita ca parametru
    for(i=1;i<=n;i++)
    {
        b[i]=m[i][n+1];
    }


    //se copiaza in vectorul x
    //solutia de inceput
    for(i=1;i<=n;i++)
    {
        x[i]=initialSolution[i][1];
    }
    it=0;
    do
    {
        max=0;
        for(i=1;i<=n;i++)
        {
            s=0;
            for(j=1;j<=n;j++)
                if(j!=i)
                    s=s+a[i][j]*x[j];
            y[i]=(b[i]-s)/a[i][i];
            if(max<fabs(y[i]-x[i]))
                max=fabs(y[i]-x[i]);
        }
        for(i=1;i<=n;i++)
            x[i]=y[i];
        it++;
    }
    while(max>eps&&it<=itmax);
    if(it>itmax)
    {
        return false;
    }
    for(i=1;i<=n;i++)
    {
        solution[i]=x[i];
    }
    iterationNumber=it;
    return true;
}

bool seidel_gauss_method(double m[MAX_LINE][MAX_COL],int n,int maxIterationNumber,
                   double precision,double initialSolution[MAX_LINE][MAX_COL],double solution[MAX_LINE],
                   int &iterationNumber)
{
    int it,itmax=0,i,j;
    double a[MAX_LINE][MAX_COL],b[MAX_LINE],eps,x[MAX_LINE],y,max,s;
    itmax=maxIterationNumber;
    eps=precision;

    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
        {
            a[i][j]=m[i][j];
        }
    //coloana termenilor liberi reprezinta ultima coloana in matricea extinsa m a sistemului
    //primita ca parametru
    for(i=1;i<=n;i++)
    {
        b[i]=m[i][n+1];
    }


    //se copiaza in vectorul x
    //solutia de inceput
    for(i=1;i<=n;i++)
    {
        x[i]=initialSolution[i][1];
    }
    it=0;
    do
    {
        max=0;
        for(i=1;i<=n;i++)
        {
            s=0;
            for(j=1;j<=n;j++)
                if(j!=i)
                    s=s+a[i][j]*x[j];
            y=(b[i]-s)/a[i][i];
            if(max<abs(y-x[i]))
                max=abs(y-x[i]);
            x[i]=y;
        }
        it++;
    }
    while(max>eps&&it<=itmax);
    if(it>itmax)
    {
        return false;
    }
    for(i=1;i<=n;i++)
    {
        solution[i]=x[i];
    }
    iterationNumber=it;
    return true;
}

bool krylov(double a[MAX_LINE][MAX_COL],double y[MAX_LINE][MAX_COL],int dim,double sol[MAX_LINE])
{
    bool eigenvalues_found=false;
    int n,i,j,k;
    n=dim;
    /*
       for(i=1;i<=n;i++)
    {
        printf("(0)y[%d]= ",i);
        scanf("%f",&y[i][n]);
    }
    */
    for(j=n-1;j>=1;j--)
        for(i=1;i<=n;i++)
        {
            y[i][j]=0;
            for(k=1;k<=n;k++)
                y[i][j]=y[i][j]+a[i][k]*y[k][j+1];
        }
    for(i=1;i<=n;i++)
    {
        y[i][n+1]=0;
        for(k=1;k<=n;k++)
            y[i][n+1]=y[i][n+1]+a[i][k]*y[k][1];
        y[i][n+1]=(-1)*y[i][n+1];
    }
    eigenvalues_found=lr_factorization(y,n,sol);
    return eigenvalues_found;
}

bool fadeev(double m[MAX_LINE][MAX_COL],double invMatrix[MAX_LINE][MAX_COL],double coeff[MAX_LINE],int dim)
{
    int n,i,j,h,k;
    double a[MAX_LINE][MAX_COL],b[MAX_LINE][MAX_COL],d[MAX_LINE][MAX_COL],c[MAX_LINE];
    n=dim;
    //se copiaza elementele matricei m in matricea a
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
        {
            a[i][j]=m[i][j];
        }

    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            if(i==j)
                b[i][j]=1;
            else
                b[i][j]=0;
    for(k=1;k<=n-1;k++)
    {
        for(i=1;i<=n;i++)
            for(j=1;j<=n;j++)
            {
                d[i][j]=0;
                for(h=1;h<=n;h++)
                    d[i][j]=d[i][j]+a[i][h]*b[h][j];
            }
        c[k]=0;
        for(i=1;i<=n;i++)
            c[k]=c[k]+d[i][i];
        c[k]=-c[k]/k;
        for(i=1;i<=n;i++)
            for(j=1;j<=n;j++)
                if(i==j)
                    b[i][j]=d[i][j]+c[k];
                else
                    b[i][j]=d[i][j];
    }
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
        {
            d[i][j]=0;
            for(h=1;h<=n;h++)
                d[i][j]=d[i][j]+a[i][h]*b[h][j];
        }
    c[n]=0;
    for(i=1;i<=n;i++)
        c[n]=c[n]+d[i][i];
    c[n]=-c[n]/n;
    if(c[n]==0)
    {
        return false;
    }
    else
    {
        //inversa matricei este stocata in matricea invMatrix:
        for(i=1;i<=n;i++)
        {
            for(j=1;j<=n;j++)
                invMatrix[i][j]=-b[i][j]/c[n];
        }
    }
   //se incarca in vector coeff coeficientii polinomului caracteristic
    for(i=1;i<=n;i++)
        coeff[i]=c[i];
    return true;
}

double lagrange_interpolation(double points[MAX_LINE][MAX_COL],int dim,double x_coord)
{

    int n,i,k;
    double x[MAX_LINE],f[MAX_LINE],z,P,L;
    n=dim-1;
    //punctul in care se doreste valoarea functiei
    z=x_coord;
    //se copiaza punctele care se cunosc
    for(i=0;i<=n;i++)
    {
        x[i]=points[i+1][1];
        f[i]=points[i+1][2];
    }

    //De aici incepe metoda
    L=0;
    for(k=0;k<=n;k++)
    {
        P=1;
        for(i=0;i<=n;i++)
            if(i!=k)
            P=P*(z-x[i])/(x[k]-x[i]);
        L=L+f[k]*P;
    }
    //"Valoarea aproximativa a functiei in punctul x_coord este reprezentat de L
    return L;
}

double newton_interpolation(double points[MAX_LINE][MAX_COL],int dim,double x_coord)
{

    int n,i,j,k;
    double x[MAX_LINE],f[MAX_LINE],z,p,N,s;
    n=dim-1;
    //punctul in care se doreste valoarea functiei
    z=x_coord;
    //se copiaza punctele care se cunosc
    for(i=0;i<=n;i++)
    {
        x[i]=points[i+1][1];
        f[i]=points[i+1][2];
    }

    //De aici incepe metoda
    N=f[0];
    for(k=1;k<=n;k++)
    {
        s=0;
        for(j=0;j<=k;j++)
        {
            p=1;
            for(i=0;i<=k;i++)
                if(i!=j)
                    p=p*(x[j]-x[i]);
            s=s+f[j]/p;
        }
        p=1;
        for(i=0;i<k;i++)
            p=p*(z-x[i]);
        N=N+s*p;
    }
    //"Valoarea aproximativa a functiei in punctul x_coord este reprezentata de N
    return N;
}

bool  spline_interpolation(double points[MAX_LINE][MAX_COL],int dim,double x_coord,double &y_coord)
{
    int n,i;
    double x[MAX_LINE],f[MAX_LINE],z;
    double a[MAX_LINE],t[MAX_LINE],u[MAX_LINE],h[MAX_LINE],b[MAX_LINE],c[MAX_LINE],Siz;
    n=dim-1;
    //punctul in care se doreste valoarea functiei
    z=x_coord;
    //se copiaza punctele care se cunosc
    for(i=0;i<=n;i++)
    {
        x[i]=points[i+1][1];
        f[i]=points[i+1][2];
    }

    //De aici incepe metoda
    for(i=1;i<=n;i++)
        h[i]=x[i]-x[i-1];
    for(i=1;i<=n-1;i++)
        a[i]=2*(h[i]+h[i+1]);
    for(i=1;i<=n-2;i++)
    {
        b[i]=h[i+1];
        c[i]=b[i];
    }
    for(i=1;i<=n-1;i++)
        t[i]=6*(f[i+1]-f[i])/h[i+1]-6*(f[i]-f[i-1])/h[i];
    for(i=1;i<=n-2;i++)
    {
        if(a[i]==0)
        {
            //"Sistemul nu are solutie unica!";
            return false;
        }
        c[i]=c[i]/a[i];
        a[i+1]=a[i+1]-b[i]*c[i];
    }
    for(i=2;i<=n-1;i++)
        t[i]=t[i]-c[i-1]*t[i-1];
    if(a[n-1]==0)
    {
       // "Sistemul nu are solutie unica!"
        return false;
    }
    t[n-1]=t[n-1]/a[n-1];
    for(i=n-2;i>=1;i--)
        t[i]=(t[i]-b[i]*t[i+1])/a[i];
    for(i=1;i<=n-1;i++)
        u[i]=t[i];
    u[0]=0;
    u[n]=0;
    for(i=1;i<=n;i++)
        if((z>=x[i-1])&&z<=x[i])
        {
            float p1,p2;
            p1=(z-x[i-1])*(z-x[i-1])*(z-x[i-1]);
            p2=(x[i]-z)*(x[i]-z)*(x[i]-z);
            Siz=(u[i]*p1+u[i-1]*p2)/(6*h[i])+(f[i]-(u[i]*(h[i]*h[i]))/6)*(z-x[i-1])/h[i]+(f[i-1]-(u[i-1]*(h[i]*h[i]))/6)*(x[i]-z)/h[i];
            //Valoarea aproximativa a functiei in punctul z este Siz;
            y_coord=Siz;
            return true;
        }
    return false;
}

bool mas_method(std::string function,double initial_value,int it_max,double precison,double &final_value)
{
    Lepton::CompiledExpression expression =
            Lepton::Parser::parse(function).createCompiledExpression();
    double& x = expression.getVariableReference("x");
    double x0,eps,x1,dif;
    int itmax,it;
    x0=initial_value;
    eps=precison;
    itmax=it_max;
    it=0;
    do
    {
        x1=user_fct(x,x0,expression);
        dif=fabs(x1-x0);
        x0=x1;
        it++;
    }
    while(dif>eps&&it<=itmax);
    if(it>itmax)
    {
        return false;
    }

    final_value=x1;
    return true;

}

bool newton_approximation_method(std::string fct,std::string fct_der,double initial_value,
                                 int it_max,double precison,double &final_value)
{
    Lepton::CompiledExpression function =
            Lepton::Parser::parse(fct).createCompiledExpression();
    double& x = function.getVariableReference("x");
    std::string der_fct=fct+"x^2-x^2";
    Lepton::CompiledExpression der_function=Lepton::Parser::parse(der_fct).differentiate("x").optimize().createCompiledExpression();
    double& x_der=der_function.getVariableReference("x");
    double x0,eps,x1,dif;
    double denominator;
    int itmax,it;
    x0=initial_value;
    eps=precison;
    itmax=it_max;
    it=0;
    do
        {
            denominator=user_fct(x_der,x0,der_function);
            if(denominator==0)
                throw Error("Operatie ilegala.Impartirea prin 0 este interzisa! "
                 "Derivata functie se anuleaza in: "+QString::number(x0));
            x1=x0-user_fct(x,x0,function)/denominator;
            dif=fabs(x1-x0);
            x0=x1;
            it++;
        }
        while(dif>eps&&it<=itmax);
        if(it>itmax)
        {
            throw Error("Nu se poate obtine solutia in "+QString::number(itmax)+
                    " cu precizia dorita: "+QString::number(eps));
        }

    final_value=x1;
    return true;
}
double integral_trapezoidal_rule(double a,double b,double precison,std::string function)
{

    Lepton::CompiledExpression expression =
            Lepton::Parser::parse(function).createCompiledExpression();
    double& x = expression.getVariableReference("x");
    double eps,value;
    eps=precison;
    double Integr,Integr0,S,h;
    int n,i;
    n=1;
    Integr=(user_fct(x,a,expression)+user_fct(x,b,expression))*(b-a)/2;
    int it=0;
    do
    {
        it++;
        n=n*2;
        h=(b-a)/n;
        Integr0=Integr;
        S=0;
        for(i=1;i<=n-1;i++)
        {
            value=a+i*h;
            S=S+user_fct(x,value,expression);
        }
        Integr=(user_fct(x,a,expression)+2*S+user_fct(x,b,expression))*h/2;
        if(it>=1000)
        {
            throw Error("S-au realizat deja "+QString::number(it)+" iteratii! Nu"
" se poate aproxima integrala cu o precizie atat de mica");
        }
    }
    while(fabs(Integr-Integr0)>eps);
    return Integr;
}

double simpson_rule(double a,double b,double precison,std::string function)
{

    Lepton::CompiledExpression expression =
            Lepton::Parser::parse(function).createCompiledExpression();
    double& x = expression.getVariableReference("x");
    double eps,value;
    eps=precison;
    double Integr,Integr0,s1,s2,h;
    int n,i,it=0;
    n=1;
    Integr=(user_fct(x,a,expression)+4*user_fct(x,(a+b)/2,expression)+user_fct(x,b,expression))*(b-a)/6;
    do
    {
        it++;
        n=n*2;
        h=(b-a)/n;
        Integr0=Integr;
        s1=0;
        for(i=1;i<=n-1;i++)
            s1=s1+user_fct(x,a+i*h,expression);
        s2=0;
        for(i=1;i<=n-1;i++)
            s2=s2+user_fct(x,a+i*h+h/2,expression);
        Integr=(user_fct(x,a,expression)+2*s1+4*s2+user_fct(x,b,expression))*h/6;
        if(it>=1000)
        {
            throw Error("S-au realizat deja "+QString::number(it)+" iteratii! Nu"
" se poate aproxima integrala cu o precizie atat de mica");
        }
    }
    while(fabs(Integr-Integr0)>eps);
    value=Integr;
    return value;
}

double double_integration(double vertices[MAX_LINE][MAX_COL],std::string function)
{
    std::string fct;
    fct=function+"+x-x+y-y";
    Lepton::CompiledExpression expression = Lepton::Parser::parse(fct).createCompiledExpression();
    double& x = expression.getVariableReference("x");
    double & y=expression.getVariableReference("y");
    double x1,x2,x3,y1,y2,y3;
    double l1,l2,l3,S,p,I;
    //
    x1=vertices[1][1];
    y1=vertices[1][2];
    x2=vertices[2][1];
    y2=vertices[2][2];
    x3=vertices[3][1];
    y3=vertices[3][2];
    //

    l1=sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
    l2=sqrt((x2-x3)*(x2-x3)+(y2-y3)*(y2-y3));
    l3=sqrt((x3-x1)*(x3-x1)+(y3-y1)*(y3-y1));
    p=(l1+l2+l3)/2;
    S=sqrt(p*(p-l1)*(p-l2)*(p-l3));
    I=S/12*(user_fct2(x,y,x1,y1,expression)+user_fct2(x,y,x2,y2,expression)+
            user_fct2(x,y,x3,y3,expression)+9*user_fct2(x,y,((x1+x2+x3)/3),((y1+y2+y3)/3),expression));
    return I;
}

bool euler_chauchy(double points[MAX_LINE][MAX_COL],int dim,std::string function,
                   double iteration,double precision,double initial_value,double calculus[MAX_LINE][2])
{
    bool is_ok=false;
    int n,it=0,itmax;
    double X[MAX_LINE],Y[MAX_COL],x,y,xx,yy,h,aux,eps;
    n=dim-1;
    std::string fct;
    fct=function+"+x-x+y-y";
    Lepton::CompiledExpression expression = Lepton::Parser::parse(fct).createCompiledExpression();
    double& x_var = expression.getVariableReference("x");
    double & y_var =expression.getVariableReference("y");

    for(int i=0;i<=n;i++)
    {
        X[i]=points[i+1][1];
    }
    Y[0]=initial_value;
    eps=precision;
    itmax=iteration;
    int i=0;
    do
    {
        it=0;
        x=X[i];
        xx=X[i+1];
        y=Y[i];
        h=xx-x;
        yy=y+h*user_fct2(x_var,y_var,x,y,expression);
        do
        {
            it++;
            h=h/2;
            aux=yy;
            while(x<xx)
            {
                y=y+h*user_fct2(x_var,y_var,x,y,expression);
                x=x+h;
            }
            yy=y;
            x=X[i];
            y=Y[i];
        }while(fabs(yy-aux)>eps&&(it<itmax));
        Y[i+1]=yy;
        calculus[i][0]=xx;
        calculus[i][1]=yy;
        i++;
    }while(i<n);

    is_ok=true;
    return is_ok;
}

bool runge_kutta(double points[MAX_LINE][MAX_COL],int dim,std::string function,
                   double iteration,double precision,double initial_value,double calculus[MAX_LINE][2])
{
    bool is_ok=false;
    int n,it=0,itmax;
    double X[MAX_LINE],Y[MAX_COL],x,y,xx,yy,h,aux,eps,k1,k2;
    n=dim-1;
    std::string fct;
    fct=function+"+x-x+y-y";
    Lepton::CompiledExpression expression = Lepton::Parser::parse(fct).createCompiledExpression();
    double& x_var = expression.getVariableReference("x");
    double & y_var =expression.getVariableReference("y");
    for(int i=0;i<=n;i++)
    {
        X[i]=points[i+1][1];
    }
    Y[0]=initial_value;
    eps=precision;
    itmax=iteration;
    int i=0;
    do{
        x=X[i];
        xx=X[i+1];
        y=Y[i];
        h=xx-x;
        k1=h*user_fct2(x_var,y_var,x,y,expression);
        k2=h*user_fct2(x_var,y_var,x+2*h/3,y+2*k1/3,expression);
        yy=y+(k1+3*k2)/4;
        do{
            h=h/2;
            aux=yy;
            while(x<xx){
                k1=h*user_fct2(x_var,y_var,x,y,expression);
                k2=h*user_fct2(x_var,y_var,x+2*h/3,y+2*k1/3,expression);
                y=y+(k1+3*k2)/4;
                x=x+h;
            }
        }while(fabs(yy-aux)>eps&&(it<itmax));
        Y[i+1]=yy;
        calculus[i][0]=xx;
        calculus[i][1]=yy;
        i++;
    }while(i<n);
    is_ok=true;
    return is_ok;
}

