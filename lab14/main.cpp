#include <math.h>
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct List
{
    List *next;
    union
    {
        int data;
        unsigned char Digit[sizeof(data)];
    };
};

struct Queue
{
    List *head;
    List *tail;
};

void QueueFillInc(int n, List *(&head), List *(&tail))
{
    int i = 1;
    List *p;
    head = tail = new List;
    head->next = tail->next = 0;
    tail->data = i;
    i++;
    do
    {
        p = new List;
        p->data = i;
        tail->next = p;
        tail = p;
        i++;

    } while (i <= n);
    tail->next = 0;
}

void QueueFillDec(int n, List *(&head), List *(&tail))
{
    int i = n;
    List *p;
    head = tail = new List;
    head->next = tail->next = 0;
    tail->data = i;
    i--;
    do
    {
        p = new List;
        p->data = i;
        tail->next = p;
        tail = p;
        i--;

    } while (i > 0);
    tail->next = 0;
}

void QueueFillRand(int n, List *(&head), List *(&tail))
{
    srand(time(NULL));
    int i = 1;
    List *p;
    head = tail = new List;
    head->next = tail->next = 0;
    tail->data = rand() % (n * 2);
    i++;
    do
    {
        p = new List;
        p->data = rand() % (n * 2);
        tail->next = p;
        tail = p;
        i++;

    } while (i <= n);
    tail->next = 0;
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

int DigitalSort(List *(&S), List *(&tail))
{
    int M = 0;
    int KDI[4] = {3, 2, 1, 0};
    int L = 4;
    List *temp;
    Queue q[256];
    List *p;
    unsigned char d;
    int k;

    for (int j = L - 1; j >= 0; j--)
    {
        for (int i = 0; i <= 255; i++)
        {
            q[i].tail = (List *)&(q[i].head);
        }
        p = S;
        k = KDI[j];
        while (p != NULL)
        {
            M++;
            d = p->Digit[k];
            q[d].tail->next = p;
            q[d].tail = p;
            p = p->next;
        }
        temp = p = (List *)&S;

        int i = 0;
        int sign = 1;

        while ((i > -1) && (i < 256))
        {
            if (q[i].tail != (List *)&(q[i].head))
            {
                M++;
                p->next = q[i].head;
                p = q[i].tail;
            }
            i += sign;
        }

        p->next = NULL;
        S = temp->next;
    }
    return M;
}
void DeleteList(List *(&head), List *(&tail))
{

    List *p, *t;
    for (p = head; p; p = t)
    {
        t = p->next;
        delete p;
    }
    head = tail = NULL;
}

int main()
{
    List *head = NULL, *tail = NULL;
    int inc, dec, rand, teor;

    cout << endl
         << " " << setw(22) << "Digital Sort" << endl;
    cout << " N" << setw(8) << "M teor" << setw(9) << "Inc" << setw(10) << "Dec" << setw(10) << "Rand" << endl;
    for (int n = 100; n < 600; n += 100)
    {
        QueueFillInc(n, head, tail);
        inc = DigitalSort(head, tail);
        QueueFillDec(n, head, tail);
        dec = DigitalSort(head, tail);
        QueueFillRand(n, head, tail);
        rand = DigitalSort(head, tail);
        teor = 4 * (n + 256);
        cout << n << setw(6) << teor << setw(10) << inc << setw(10) << dec << setw(9) << rand << endl;
        DeleteList(head, tail);
    }
    return 0;
}
