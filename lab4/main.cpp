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

int main() 
{
    
    cout << "\tBubble Sort\t\tShaker Sort" <<endl;
    cout << "Size\tInc\tDec\tRnd\tInc\tDec\tRnd\n";
    for (int size = 100; size <= 500; size += 100) {
        
        int A[size];
        FillInc(A,size);
        int ink_count_mc = BubbleSort(A,size);
        FillDec(A,size);
        int dec_count_mc = BubbleSort(A,size);
        FillRand(A,size);
        int rand_count_mc=BubbleSort(A,size);

        FillInc(A,size);
        int shaker_ink_count_mc = ShakerSort(A,size);
        FillDec(A,size);
        int shaker_dec_count_mc = ShakerSort(A,size);
        FillRand(A,size);
        int shaker_rand_count_mc=ShakerSort(A,size);

        cout << size << "\t" << ink_count_mc << "\t" << dec_count_mc << "\t" << rand_count_mc << "\t" 
             << shaker_ink_count_mc << "\t" << shaker_dec_count_mc << "\t" << shaker_rand_count_mc << "\n";
    }
    

    return 0;
}
