#include <iostream>
#include <ctime>
#include <math.h>
#include <iomanip>
#include <cmath>
#include <algorithm>
using namespace std;

int cnt = 0;

struct List
{
    List *next;
    int data;
};

struct Queue
{
    List *head;
    List *tail;
};

void FillInk(int n, List *(&head))
{
    int i = n;
    List *p;
    p = NULL;
    do
    {
        head = new List;
        head->next = p;
        p = head;
        head->data = i;
        i--;
    } while (i > 0);
}

void FillDec(int n, List *(&head))
{
    int i = 1;
    List *p;
    p = NULL;
    do
    {
        head = new List;
        head->next = p;
        p = head;
        head->data = i;
        i++;
    } while (i <= n);
}

void FillRand(int n, List *(&head))
{
    srand(time(NULL));
    int i = 1;
    List *p;
    p = NULL;
    do
    {
        head = new List;
        head->next = p;
        p = head;
        head->data = rand() % (n * 2);
        i++;
    } while (i <= n);
}

void PrintList(List *p)
{
    while (p != NULL)
    {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

void merge(List **a, int q, List **b, int r, Queue *c, int &C, int &M)
{
    while (q != 0 && r != 0)
    {
        C++;
        if ((*a)->data <= (*b)->data)
        {
            M++;
            c->tail->next = *a;
            c->tail = *a;
            *a = (*a)->next;
            q--;
        }
        else
        {
            M++;
            c->tail->next = *b;
            c->tail = *b;
            *b = (*b)->next;
            r--;
        }
    }
    while (q > 0)
    {
        M++;
        c->tail->next = *a;
        c->tail = *a;
        *a = (*a)->next;
        q--;
    }
    while (r > 0)
    {
        M++;
        c->tail->next = *b;
        c->tail = *b;
        *b = (*b)->next;
        r--;
    }
}

int Split(List *S, List **a, List **b, int &M)
{
    List *k, *p;
    *a = S;
    *b = S->next;
    int n = 1;
    k = *a;
    p = *b;
    while (p != NULL)
    {
        n++;
        k->next = p->next;
        k = p;
        p = p->next;
    }
    M += n;
    return n;
}

int MergeSort(List *(&S), List *(&tail))
{
    int C = 0, M = 0;
    List *a;
    List *b;
    int n = Split(S, &a, &b, M);
    int p = 1;
    int q, r;
    Queue c[2];
    while (p < n)
    {
        c[0].tail = (List *)&(c[0].head);
        c[1].tail = (List *)&(c[1].head);

        int i = 0;
        int m = n; // текущее кол-во элементов в a и b
        while (m > 0)
        {
            if (m >= p)
            {
                q = p;
            }
            else
            {
                q = m;
            }
            m = m - q;

            if (m >= p)
            {
                r = p;
            }
            else
            {
                r = m;
            }
            m = m - r;
            merge(&a, q, &b, r, &c[i], C, M);
            i = 1 - i;
        }
        a = c[0].head;
        b = c[1].head;
        p = 2 * p;
    }
    c[0].tail->next = NULL;
    S = c[0].head;
    tail = c[0].tail;
    return M + C;
}

int main()
{
    List *head = NULL, *tail = NULL;
    int inc, dec, rand, teor;

    cout << endl
         << " " << setw(22) << "MergeSort" << endl;
    cout << " n" << setw(8) << "teor" << setw(9) << "inc" << setw(10) << "dec" << setw(10) << "rand" << endl;

    for (int n = 100; n < 600; n += 100)
    {
        FillInk(n, head);
        inc = MergeSort(head, tail);
        FillDec(n, head);
        dec = MergeSort(head, tail);
        FillRand(n, head);
        rand = MergeSort(head, tail);
        teor = n * ceil(log2(n)) + n * ceil(log2(n)) + n;
        cout << n << setw(6) << teor << setw(10) << inc << setw(10) << dec << setw(9) << rand << endl;
    }
    return 0;
}
