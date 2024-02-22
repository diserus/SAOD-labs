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
    
    cout << "Size\tInc\tDec\tRnd\tInc theor.\tDec theor.\tRnd theor.\n";
    for (int size = 100; size <= 500; size += 100) {
        
        int A[size];
        FillInc(A,size);
        int ink_count_mc = BubbleSort(A,size);
        FillDec(A,size);
        int dec_count_mc = BubbleSort(A,size);
        FillRand(A,size);
        int rand_count_mc=BubbleSort(A,size);
        int bubble_count_inc_theoretical = (size*size-size)/2; 
        int bubble_count_dec_theoretical = (size*size-size)/2+((size*size-size)/2)*3; 
        int bubble_count_rand_theoretical = (size*size-size)/2+((3*(size*size-size))/4); 

        cout << size << "\t" << ink_count_mc << "\t" << dec_count_mc << "\t" << rand_count_mc << "\t" 
             << bubble_count_inc_theoretical << "\t\t" << bubble_count_dec_theoretical << "\t\t" << bubble_count_rand_theoretical << "\n";
    }


    return 0;
}
