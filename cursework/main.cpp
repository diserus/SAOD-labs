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
    List *next = nullptr;
    record data;
};

struct Queue
{
    List *head = nullptr;
    List *tail = nullptr;
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
            head = head->next;
        }
    }
    void clear()
    {
        while (head != nullptr)
        {
            List *temp = head;
            head = head->next;
            delete temp;
        }
    }
};

struct vertex
{
    int data;
    vertex *Left = nullptr;
    vertex *Right = nullptr;
    int balance;
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
int parseYear(char *date)
{
    int year;
    int day;
    int month;
    std::sscanf(date, "%2d-%2d-%2d", &day, &month, &year);
    return year;
}
int binarySearch(record *A[], int n, int elem, Queue *queue)
{
    int l = 0;
    int r = n - 1;
    while (l <= r)
    {
        int i = (l + r) / 2;
        int year = parseYear(A[i]->e);

        if (year == elem)
        {
            queue->add(A[i]);

            int left = i - 1;
            while (left >= 0 && parseYear(A[left]->e) == elem)
            {
                queue->add(A[left]);
                left--;
            }
            int right = i + 1;
            while (right < n && parseYear(A[right]->e) == elem)
            {
                queue->add(A[right]);
                right++;
            }
            return 0;
        }

        if (year < elem)
            l = i + 1;
        else
            r = i - 1;
    }
    return 1;
}

bool B2INSERT(vertex *&p, int data, bool &VR, bool &HR)
{
    if (p == nullptr)
    {
        p = new vertex;
        p->data = data;
        p->Left = p->Right = nullptr;
        p->balance = false;
        VR = true;
    }
    else if (p->data > data)
    {
        if (B2INSERT(p->Left, data, VR, HR))
        {
            if (VR)
            {
                if (!p->balance)
                {
                    vertex *q = p->Left;
                    p->Left = q->Right;
                    q->Right = p;
                    p = q;
                    q->balance = true;
                    VR = false;
                    HR = true;
                }
                else
                {
                    p->balance = false;
                    VR = true;
                    HR = false;
                }
            }
            else
                HR = false;
        }
        else
            return false;
    }
    else if (p->data < data)
    {
        if (B2INSERT(p->Right, data, VR, HR))
        {
            if (VR)
            {
                p->balance = true;
                HR = true;
                VR = false;
            }
            else if (HR)
            {
                if (p->balance)
                {
                    vertex *q = p->Right;
                    p->balance = false;
                    q->balance = false;
                    p->Right = q->Left;
                    q->Left = p;
                    p = q;
                    VR = true;
                    HR = false;
                }
                else
                    HR = false;
            }
        }
        else
            return false;
    }
    else
        return false;
    return true;
}

vertex *createDBD(int n, bool &VR, bool &HR, bool log)
{
    vertex *root = NULL;
    int i = 0;
    while (i < n)
    {
        int data = rand() % 1000;
        if (B2INSERT(root, data, VR, HR))
            i++;
        else
            std::cout << "Data with key " << data << " already in tree\n";
    }
    return root;
}

void displayRecords(record *indexArr[])
{
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
}
void displaySearch(record *indexArr[], int readCount)
{
    int element;
    std::cout << "Input records what you want to find(key = year): ";
    std::cin >> element;
    Queue *queue = new Queue;
    if (binarySearch(indexArr, readCount, element, queue))
        std::cout << "Records didn't find\n";
    queue->print();
    queue->clear();
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
    char choice;
    do
    {
        cout << "\n1. All records\n2. Search\n3. Exit\n";
        cin >> choice;
        if (choice == '1')
        {
            displayRecords(indexArr);
        }
        else if (choice == '2')
        {
            displaySearch(indexArr, readCount);
        }
        else if (choice != '1' && choice != '2' && choice != '3')
        {
            cout << "Incorrect input" << endl;
        }
    } while (choice != '3');

    return 0;
}
