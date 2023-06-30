#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cmath>

using namespace std;

void wczytywanie(double** &A,double* &b, int &matrix_size)
{
    ifstream source_file("dane.csv");
    source_file >> matrix_size;
    A = new double*[matrix_size];
    A[0] = new double[matrix_size*matrix_size];
    for(int i = 1; i< matrix_size; i++)
        A[i] = A[i-1] + matrix_size;

    b = new double[matrix_size];

    char semicolumn;
    for (int i = 0; i < matrix_size+1; i++)
        source_file >> semicolumn;

    for (int i = 0; i < matrix_size; i++)
    {
        for (int j = 0; j < matrix_size; j++)
        {
            source_file >> A[i][j];
            source_file >> semicolumn;
        }
        source_file >> semicolumn;
        source_file >> b[i];
    }
    source_file.close();
}

void bezwyboru(double** &A, double* &b, int matrix_size)
{
    int i,j,k;
    double *p;
    p=new double[matrix_size];
    double *wyn;
    wyn=new double[matrix_size];
    if(A[0][0]!=0)
    {
        for(k=1;k<matrix_size;k++)
        {
            for(i=k;i<matrix_size;i++)
            {
                p[i] = A[i][k-1]/A[k-1][k-1];

            }
            for(i=k;i<matrix_size;i++)
            {
                for(j=k-1;j<matrix_size;j++)
                {
                    A[i][j]= (A[i][j] - p[i]*A[k-1][j]);

                }
                b[i]= b[i] - p[i]*b[k-1];
            }
        }
        double temp;
        wyn[0] = b[0];
        for (int i = 1; i < matrix_size; i++)
        {
            temp = 0;
            for (int j = 0; j < i; j++)
                temp += A[i][j] * wyn[j];
            wyn[i] = b[i] - temp;
        }
        wyn[matrix_size - 1] /= A[matrix_size - 1][matrix_size - 1];
        for (int i = matrix_size - 2; i >= 0; i--)
        {
            temp = 0;
            for (int j = i + 1; j < matrix_size; j++)
                temp += A[i][j] * wyn[j];
            wyn[i] = (wyn[i] - temp) / A[i][i];
        }
        for(i=0;i<matrix_size;i++)
        {
            cout<<"x"<<i+1<<"= "<<wyn[i]<<endl;
        }
    }
    else
        cout<<"element = 0"<<endl;
}

int main()
{
    double **A;
    double *b;
    int r;
    double *wyn;
    int matrix_size;
    wyn=new double[matrix_size];
    while (r!=5)
    {
        cout<<"1- wczytywanie, 2- bez wyboru, 5- wyjdz"<<endl;
        cin>>r;
        switch(r)
        {
        case 1:
            {
                wczytywanie(A,b,matrix_size);
            }
            break;
        case 2:
            {
                bezwyboru(A,b,matrix_size);

            }
            break;
        case 5:
            {
                return 0;
            }
        }
    }
    return 0;
}
