#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

void FillInc(vector<int> &arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        arr[i] = i;
    }
}

void FillDec(vector<int> &arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        arr[i] = n - (i + 1);
    }
}

void FillRand(vector<int> &arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        arr[i] = (rand() % 100);
    }
}

void QuickSort(vector<int> &arr, int L, int R, int &c, int &m)
{
    int x = arr[L], i = L, j = R;
    while (i <= j)
    {
        while (arr[i] < x)
        {
            i++;
            c++;
        }
        while (arr[j] > x)
        {
            j--;
            c++;
        }
        if (i <= j)
        {
            swap(arr[i], arr[j]);
            m += 3;
            i++;
            j--;
        }
    }
    if (L < j)
        QuickSort(arr, L, j, c, m);
    if (i < R)
        QuickSort(arr, i, R, c, m);
}

void printArray(vector<int> &arr)
{
    for (int i = 0; i < arr.size(); ++i)
        cout << arr[i] << " ";
    cout << "\n";
}

int main()
{
    cout << setw(5) << "N" << setw(10) << "Dec" << setw(10) << "Inc" << setw(10) << "Rand"
         << setw(10) << "theor\n";
    for (int size = 100; size <= 500; size += 100)
    {
        int C = (size * size + 5 * size + 4) / 2;
        int M = 3 * (size - 1);
        // int C = (int)(size * log2(size));
        // int M = (int)(size * log2(size));
        int mDec = 0, cDec = 0;
        int mInc = 0, cInc = 0;
        int mRand = 0, cRand = 0;
        vector<int> arr(size);
        cout << setw(5) << size;
        FillDec(arr, size);
        QuickSort(arr, 0, arr.size() - 1, cDec, mDec);
        cout << setw(10) << cDec + mDec;
        FillInc(arr, size);
        QuickSort(arr, 0, arr.size() - 1, cInc, mInc);
        cout << setw(10) << cInc + mInc;
        FillRand(arr, size);
        QuickSort(arr, 0, arr.size() - 1, cRand, mRand);
        cout << setw(10) << cRand + mRand;
        cout << setw(10) << C + M << "\n";
    }

    int m = 0;
    int c = 0;
    vector<int> arr(100);
    FillRand(arr, 100);
    QuickSort(arr, 0, arr.size() - 1, m, c);
    printArray(arr);
}
