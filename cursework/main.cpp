#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;
struct record
{
    char a[32];
    char b[18];
    short int c;
    short int d;
    char e[10];
};
struct List
{
    List *next;
    record data;
};

struct Queue
{
    List *head;
    List *tail;
    void add(record *rec)
    {
        List *newNode = new List;
        newNode->data = *rec;
        newNode->next = nullptr;
        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }
    void print()
    {
        while (head != nullptr)
        {
            cout << head->data.a << " " << head->data.b << " " << head->data.c << "\t"
                 << head->data.d << "\t" << head->data.e << endl;
        }
    }
};

void parseDate(char *date, int &day, int &month, int &year)
{
    std::sscanf(date, "%2d-%2d-%2d", &day, &month, &year);
}

bool compare(record &r1, record &r2)
{
    int day1, month1, year1;
    int day2, month2, year2;

    parseDate(r1.e, day1, month1, year1);
    parseDate(r2.e, day2, month2, year2);

    if (year1 != year2)
        return year1 < year2;
    else if (month1 != month2)
        return month1 < month2;
    else if (day1 != day2)
        return day1 < day2;
    else
        return strcmp(r1.b, r2.b) < 0;
}

void QuickSort(record *arr[], int L, int R)
{
    record *pivot = arr[L];
    int i = L, j = R;

    while (i <= j)
    {
        while (compare(*arr[i], *pivot))
            i++;
        while (compare(*pivot, *arr[j]))
            j--;
        if (i <= j)
        {
            std::swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    if (L < j)
        QuickSort(arr, L, j);
    if (i < R)
        QuickSort(arr, i, R);
}
int binarySearch(int A[], int n, int elem)
{
    int l = 0;
    int r = n - 1;
    int i = 0;
    while (l < r)
    {
        i = (l + r) / 2;
        if (A[i] < elem)
            l = i + 1;
        else
            r = i;
    }
    if (A[r] == elem)
        return r;
    else
        return -1;
}
int main()
{
    FILE *fp = fopen("testBase4.dat", "rb");
    record mas3[4000] = {0};

    int readCount = fread((record *)mas3, sizeof(record), 4000, fp);
    record *indexArr[readCount];
    for (int i = 0; i < readCount; i++)
        indexArr[i] = &mas3[i];
    QuickSort(indexArr, 0, 3999);
    int i = 0;
    while (i < 4000)
    {
        for (int j = 0; j < 20 && i < 4000; j++, i++)
        {
            cout << indexArr[i]->a << " " << indexArr[i]->b << " " << indexArr[i]->c << "\t"
                 << indexArr[i]->d << "\t" << indexArr[i]->e << endl;
        }
        char choice;
        do
        {
            cout << "\nDo you want to continue? (y/n): ";
            cin >> choice;

            if (choice != 'y' && choice != 'n')
            {
                cout << "Incorrect input" << endl;
            }
        } while (choice != 'y' && choice != 'n');

        if (choice == 'n')
        {
            break;
        }
        i++;
    }
    return 0;
}
