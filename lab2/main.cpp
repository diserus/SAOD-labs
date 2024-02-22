#include <iostream>
using namespace std;
int i, j;

// Сумма элементов массива

int CheckSum(int A[],int n)
{
    int sum=0;
    for (int i=0;i<n;i++)
    {
        sum+=A[i];
    }
    return sum;
}

// Заполинть по возрастанию

void FillInc(int A[],int n) 
{
    for(int i=0;i<n;i++)
    {
        A[i]=i;
    }
}

// Заполнить по убыванию

void FillDec(int A[],int n) 
{
    for(int i=0;i<n;i++)
    {
        A[i]=n-(i+1);
    }
}

// Заполнить случайными числами

void FillRand(int A[],int n)
{
    for (int i=0;i<n;i++)
    {
        A[i]=rand()%10;
    }
}

// Кол-во серий

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

// Средний размер серии

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

// Вывод массива

void PrintMas(int A[],int n) 
{
    for(int i=0;i<n;i++)
    {
        cout<<A[i]<<" ";
    }
    cout<<"\n";
}

// Сортировка выбором

void SelectSort(int A[], int n)
{
    int k, temp, m=0, c=0;
    for (int i=0; i<n-1; i++)
    {
        k = i;
        for (int j=i+1; j<n; j++)
        {
            c++;
            if (A[j] < A[k]) {k = j;}
        }
        
        
        temp = A[i];
        A[i] = A[k];
        A[k] = temp;
        m+=3;
        
    }
    cout<<"M = " << m<<endl;
    cout<<"C = " << c<<endl;
}


int main()
{
    int n;
    cout<<"Input N: "; cin>>n;
    
    cout << "\nInk array: ";
    int A[n];
    FillInc(A,n);
    PrintMas(A,n);
    cout << "Summa: "<< CheckSum(A,n) << endl;
    cout << "Run number: " <<RunNumber(A,n)<< "\n" << endl;
    
    SelectSort(A, n);
    cout << "Sorted ink array: ";
    PrintMas(A,n);
    cout << "Summa: "<< CheckSum(A,n) << endl;
    cout << "Run number: " <<RunNumber(A,n)<< "\n" << endl;
    
    cout << "Dec array: ";
    FillDec(A,n);
    PrintMas(A,n);
    cout << "Summa: "<< CheckSum(A,n) << endl;
    cout << "Run number: " <<RunNumber(A,n)<< "\n" << endl;
    
    SelectSort(A, n);
    cout << "Sorted dec array: ";
    PrintMas(A,n);
    cout << "Summa: "<< CheckSum(A,n) << endl;
    cout << "Run number: " <<RunNumber(A,n)<< "\n" << endl;
    
    cout << "Random array: ";
    FillRand(A,n);
    PrintMas(A,n);
    cout << "Summa: "<< CheckSum(A,n) << endl;
    cout << "Run number: " <<RunNumber(A,n)<< "\n" << endl;
    
    SelectSort(A, n);
    cout << "Sorted random array: ";
    PrintMas(A,n);
    cout << "Summa: "<< CheckSum(A,n) << endl;
    cout << "Run number: " <<RunNumber(A,n)<< "\n" << endl;
    cout << "Average length of series random array: ";
    cout << RunNumberSr(A,n)<<endl;
    return 0;
}