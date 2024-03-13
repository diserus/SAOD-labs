#include <iostream>
using namespace std;
void PrintMas(int A[],int n) 
{
    for(int i=0;i<n;i++)
    {
        cout<<A[i]<<" ";
    }
    cout<<"\n";
}

void FillInc(int A[],int n) 
{
    for(int i=0;i<n;i++)
    {
        A[i]=i;
    }
}

int binarySearch1(int A[],int n,int elem,int &c)
{
    int l = 0;
    int r = n-1;
    c = 0;
    while (l <= r) 
    {
        int i =  (l+r) / 2;
        c+=2;
        if (A[i] == elem) 
            return i;  
        if (A[i] < elem) 
            l = i + 1;
        else 
            r = i - 1;
    }
    return -1;  
}

int binarySearch2(int A[],int n,int elem,int &c)
{
    int l = 0;
    int r = n-1;
    c = 0;
    int i = 0;
    while (l<r)
    {
        c++;
        i=(l+r)/2;
        if (A[i]<elem)
            l=i+1;
        else 
            r=i;
    }
    c++;
    if (A[r]==elem) 
        return r;
    else
        return -1;
}

int main()
{
    int c1;
    int c2;
    cout << "Size" << "\t" << "Binary Search 1" << "\t" << "Binary Search 2\n"; 
    for (int size = 100; size<=1000; size+=100)
    {
        int A[size];
        FillInc(A,size);

        binarySearch1(A,size,5,c1);
        binarySearch2(A,size,5,c2);

        cout << size << "\t\t" << c1 << "\t\t" << c2 << "\n";
    }
    int target;
    cout << "Input the element that you want to find: ";
    cin >> target;
    int B[1000];
    FillInc(B,1000);
    cout << "\nElement: " << target << "\n" << "Index: " << binarySearch2(B,1000,target,c1);
}