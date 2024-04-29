#include "../lab12/queue.hpp"
#include "../lab12/stack.hpp"
#include <iostream>
#include <vector>
#include <array>

void splitting(Node<int> *S, Node<int> *&a, Node<int> *&b, int n)
{
    a = S;
    b = S->next;
    n = 1;
    Node<int> *k = a;
    Node<int> *p = b;

    while (p)
    {
        n++;
        k->next = p->next;
        k = p;
        p = p->next;
    }
}

void merge(Node<int> *&a, int &q, Node<int> *&b, int &r, Queue<int> &c)
{
    while (q != 0 && r != 0)
    {
        if (a->data <= b->data)
        {
            c.push(a->data);
            a = a->next;
            q--;
        }
        else
        {
            c.push(b->data);
            b = b->next;
            r--;
        }
    }
    while (q > 0)
    {
        c.push(a->data);
        a = a->next;
        q--;
    }
    while (r > 0)
    {
        c.push(b->data);
        b = b->next;
        r--;
    }
}

void mergesort(Node<int> *S, int n)
{

    Node<int> *a;
    Node<int> *b;
    Queue<int> c0;
    Queue<int> c1;
    std::array c = {c0, c1};
    int p = 1;
    int q = 0;
    int r = 0;
    int m = 0;
    int i = 0;

    splitting(S, a, b, n);
    while (p < n)
    {
        c[0].init();
        c[1].init();
        i = 0;
        m = n;
        while (m > 0)
        {
            if (m >= p)
                q = p;
            else
                q = m;
            m = m - q;
            if (m >= p)
                r = p;
            else
                r = m;
            m = m - r;
            merge(a, q, b, r, c[i]);
            i = 1 - i;
        }
        a = c[0].getHead();
        b = c[1].getHead();
        p = 2 * p;
    }
    c[0].setTailNext(nullptr);
    S = c[0].getHead();
}

int main()
{
    Queue<int> S;
    S.fill_rand(10);
    mergesort(S.getHead(), 10);
    S.printQueue();
    return 0;
}
