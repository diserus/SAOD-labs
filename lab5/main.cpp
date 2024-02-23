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

int SelectSort(int A[], int n)
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
    return m+c;
}

int ShakerSort(int A[], int n)
{
    int L = 0, R = n - 1, k,m=0,c=0;
    do {
        k = R;
        for (int j = R; j > L; j--) {
            c++;
            if (A[j] < A[j - 1]) {
                int temp = A[j];
                A[j] = A[j - 1];
                A[j - 1] = temp;
                k = j;
                m+=3;
            }
        }
        L = k;
        for (int j = L; j < R; j++) {
            c++;
            if (A[j] > A[j + 1]) {
                int temp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = temp;
                k = j;
                m+=3;
            }
        }
        R = k;
        
    } while (L < R);
    return m+c;
}

int BubbleSort(int A[], int n)
{
    int temp,m=0,c=0;
    for (int i = 0; i < n; i++)
    {
        for (int j = n-1; j > i; j--)
        {
            c++;
            if (A[j] < A[j-1])
            {
                temp = A[j];
                A[j] = A[j-1];
                A[j-1] = temp;
                m+=3;
            }
        }
    }
    return m+c;
}
int InsertSort(int A[], int n)
{
    int i, t, j,m=0,c=0;

    for (i = 1; i < n; i++) 
    { 
        t = A[i];
        j = i - 1;
        c++;
        while (j >= 0 && A[j] > t) 
        {
            c++;
            A[j + 1] = A[j];
            j--;
            m++;
            
        }
        A[j + 1] = t;
        m+=2;
    }
    return m+c;
}

int main() 
{
    cout << "\t\t\tInsert Sort\n";
    cout << "Size\tInc\tDec\tRnd\tInc t\tDec t\tRnd t\n";
    for (int size = 100; size <= 500; size += 100) {
        
        int A[size];
        FillInc(A,size);
        int ink_count_mc = InsertSort(A,size);
        FillDec(A,size);
        int dec_count_mc = InsertSort(A,size);
        FillRand(A,size);
        int rand_count_mc = InsertSort(A,size);

        int ink_count_mc_theor = size-1 + 2*(size-1) ;
        int dec_count_mc_theor = (size*size-size)/2 + (size*size-size)/2 +2*size - 2;
        int rand_count_mc_theor = ((size*size-size)/4+size-1)+((size*size-size)/4);

        cout << size << "\t" << ink_count_mc << "\t" << dec_count_mc << "\t" << rand_count_mc << "\t" 
             << ink_count_mc_theor << "\t" << dec_count_mc_theor << "\t" << rand_count_mc_theor << "\n";
    }
    
    cout << "\n\nSize\tSelect\tBubble\tShaker\tInsert\n";
    for (int size = 100; size <= 500; size += 100) {
        
        int A[size];
        FillRand(A,size);
        int select_count_mc = InsertSort(A,size);
        FillRand(A,size);
        int bubble_count_mc = BubbleSort(A,size);
        FillRand(A,size);
        int shaker_count_mc = ShakerSort(A,size);
        FillRand(A,size);
        int insert_count_mc = InsertSort(A,size);

    

        cout << size << "\t" << select_count_mc << "\t"<< bubble_count_mc << "\t"<<shaker_count_mc<< "\t"<<insert_count_mc <<"\n";
    }
    return 0;
}
