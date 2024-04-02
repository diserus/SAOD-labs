#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

void FillInc(vector<int> &arr,int n) 
{
    for(int i=0;i<n;i++)
    {
        arr[i]=i;
    }
}

void FillDec(vector<int> &arr,int n) 
{
    for(int i=0;i<n;i++)
    {
        arr[i]=n-(i+1);
    }
}

void FillRand(vector<int> &arr,int n)
{
    for (int i=0;i<n;i++)
    {
        arr[i]=(rand()%10);
    }
}

int build_heap(vector<int> &arr, int i, int R)
{
    
    int m=0;
    int c=0;
    
    int x=arr[i];
    while (true)
    {
        
        m++;
        int j=2*i;
        if (j>R) {c++; break;}
        if (j<R && arr[j+1]<=arr[j]) {j++; c++;}
        if(x<=arr[j]) {c++; break;}
        arr[i]=arr[j];
        i=j;
    }
    m++;
    arr[i]=x;
    return m+c;
}

void build_heap(vector<int> &arr, int n, int i,int &m, int &c)
{
    
    int x = arr[i];
    while (true)
    {
        m++;
        int j = 2 * i + 1;
        if (j >= n) {c++; break;}
        if (j + 1 < n && arr[j + 1] <= arr[j]) {c++; j++;}
        if (x <= arr[j]) {c++; break;}
        arr[i] = arr[j];
        i = j;
    }
    m++;
    arr[i] = x;
}

int heapSort(vector<int> &arr, int n)
{
    int m = 0;
    int c = 0;

    for (int i = n / 2 - 1; i >= 0; i--)
    {
        build_heap(arr, n, i, m, c);
    }

    for (int i = n - 1; i >= 0; i--)
    {
        m+=2;
        swap(arr[0], arr[i]);
        build_heap(arr, i, 0, m, c);
    }
    return m + c;
}


void printArray(vector<int> &arr)
{
    for (int i=0; i<arr.size(); ++i)
        cout << arr[i] << " ";
    cout << "\n";
}

int main()
{
    
    cout << setw(5) << "N" << setw(11) << "M+C theor" << setw(11) << "Dec" << setw(8) <<"Rand" << setw(10) << "Inc\n";
    for (int size = 100;size<=500;size+=100)
    {
        vector<int> arr(size);
        cout << setw(5) << size;
        cout << setw(11)<<(int)(log2(size) + 2)+(int)(2*log2(size));
        FillDec(arr,size);
        cout <<  setw(11) << build_heap(arr,1,arr.size()-1);
        FillRand(arr,size);
        cout <<  setw(8) << build_heap(arr,1,arr.size()-1);
        FillInc(arr,size);
        cout <<  setw(10) << build_heap(arr,1,arr.size()-1) << "\n";
    }
    cout << "\n\n";
    cout << setw(5) << "N"  << setw(11) << "Dec" << setw(8) <<"Rand" << setw(10) << "Inc\n";
    for (int size = 100;size<=500;size+=100)
    {
        vector<int> arr(size);
        cout << setw(5) << size;
        FillDec(arr,size);
        cout <<  setw(11) << heapSort(arr,size);
        FillRand(arr,size);
        cout <<  setw(8) << heapSort(arr,size);
        FillInc(arr,size);
        cout <<  setw(10) << heapSort(arr,size);
        // cout << setw(10) << (int)(2 * size * std::log2(size) +size+ 2 + size * std::log2(size) + 6.5 * size - 4) <<"\n";
    }
    
}