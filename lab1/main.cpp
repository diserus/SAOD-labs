#include <iostream>
using namespace std;

void FillInc(int A[],int n) 
{
    for(int i=0;i<n;i++)
    {
        A[i]=i;
    }
}

void FillDec(int A[],int n) 
{
    for(int i=0;i<n;i++)
    {
        A[i]=n-(i+1);
    }
}

void PrintMas(int A[],int n) 
{
    for(int i=0;i<n;i++)
    {
        cout<<A[i]<<" ";
    }
    cout<<"\n";
}

void FillRand(int A[],int n)
{
    for (int i=0;i<n;i++)
    {
        A[i]=rand()%10;
    }
}

int CheckSum(int A[],int n)
{
    int sum=0;
    for (int i=0;i<n;i++)
    {
        sum+=A[i];
    }
    return sum;
}
int RunNumber(int A[],int n)
{
    int k = 0;
    for (int i=0;i<=n;i++)
    {
        if (A[i] < A[i+1])
        {
            continue;
        } else k++;
    }
    return k;
}

int RunNumberSr(int A[],int n)
{
    int k = 0;
    int sm = 0;
    for (int i=0;i<=n;i++)
    {
        if (A[i] < A[i+1])
        {
            sm += A[i];
            continue;
        } else k++;
    }
    return sm/k;
}
int main() 
{
    int n=10;
    int A[n];
    FillInc(A,n);
    PrintMas(A,n);
    FillDec(A,n);
    PrintMas(A,n);
    FillRand(A,n);
    PrintMas(A,n);
    cout<<CheckSum(A,n)<<endl;
    cout<<RunNumber(A,n)<<endl;
    FillInc(A,n); 
    cout<<CheckSum(A,n)<<endl;
    cout<<RunNumber(A,n)<<endl;
    FillDec(A,n);
    cout<<CheckSum(A,n)<<endl;
    cout<<RunNumber(A,n)<<endl;
    FillRand(A,n);
    cout<<RunNumberSr(A,n)<<endl;
    return 0;
}
