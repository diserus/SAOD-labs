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

void FillRand(int A[],int n)
{
    for (int i=0;i<n;i++)
    {
        A[i]=rand()%10;
    }
}

int InsertSort(int A[], int n)
{
    int i, t, j,m=0,c=0;

    for (i = 1; i < n; i++) 
    { 
        t = A[i];
        j = i - 1;
        while (j >= 0 ) 
        {
            c++;
            if (A[j] > t)
            {
                A[j + 1] = A[j];
                m++;
                
            }
            else break;
            j--;
            
        }
        A[j + 1] = t;
        m+=2;
    }
    return m+c;
}

int ShellSort(int A[], int n) 
{
    
    int m=0,c=0;
    for (int interval = n / 2; interval > 0; interval /= 2) 
    {
        for (int i = interval; i < n; i += 1) 
        {
            int temp = A[i];
            int j;
            for (j = i; j >= interval && A[j - interval] > temp; j -= interval) 
            {
                A[j] = A[j - interval];
                m += 3;
                c++;
            }
            A[j] = temp;
            m+=2;
        }
    }
    return m+c;
}

int main()
{
    cout << "Size\th1...hm\tInsert\tShell\n";
    for (int size = 100; size <= 500; size += 100) {
        
        int A[size];
        FillRand(A,size);
        int mc_count_insert=InsertSort(A,size);
        int mc_count_shell=ShellSort(A,size);

        cout << size << "\t\t" << mc_count_insert << "\t" << mc_count_shell << "\n";
    }
    return 0;
}