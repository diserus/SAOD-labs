#include <iostream>
#include <iomanip>
struct vertex
{
    int Data;
    vertex *Left = nullptr;
    vertex *Right = nullptr;
    short int balance = 0;
};
void work(vertex *p)
{
    if (p != nullptr)
    {
        work(p->Left);
        std::cout << p->Data << " ";
        work(p->Right);
    }
}
int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

int size(vertex *vertex)
{
    if (vertex == nullptr)
        return 0;
    else
        return 1 + size(vertex->Left) + size(vertex->Right);
}

int height(vertex *vertex)
{
    if (vertex == nullptr)
        return 0;
    else
        return 1 + max(height(vertex->Left), height(vertex->Right));
}
double SDP(vertex *vertex, int L)
{
    if (vertex == nullptr)
        return 0;
    else
        return L + SDP(vertex->Left, L + 1) + SDP(vertex->Right, L + 1);
}
int checkSum(vertex *p)
{
    if (p == nullptr)
        return 0;
    else
        return (p->Data + checkSum(p->Left) + checkSum(p->Right));
}
void rotateRR(vertex *&p)
{
    vertex *q = p->Right;
    p->balance = 0;
    q->balance = 0;
    p->Right = q->Left;
    q->Left = p;
    p = q;
}
void rotateRL(vertex *&p)
{
    vertex *q = p->Right;
    vertex *r = q->Left;
    if (r->balance > 0)
        p->balance = -1;
    else
        p->balance = 0;

    if (r->balance < 0)
        q->balance = 1;
    else
        q->balance = 0;

    r->balance = 0;
    p->Right = r->Left;
    q->Left = r->Right;
    r->Left = p;
    r->Right = q;
    p = r;
}

void rotateLR(vertex *&p)
{
    vertex *q = p->Left;
    vertex *r = q->Right;
    if (r->balance < 0)
        p->balance = 1;
    else
        p->balance = 0;

    if (r->balance > 0)
        q->balance = -1;
    else
        q->balance = 0;

    r->balance = 0;
    p->Left = r->Right;
    q->Right = r->Left;
    r->Left = q;
    r->Right = p;
    p = r;
}
void rotateLL(vertex *&p)
{
    vertex *q = p->Left;
    p->balance = 0;
    q->balance = 0;
    p->Left = q->Right;
    q->Right = p;
    p = q;
}

bool addAVL(vertex *&p, int data, bool &rost)
{
    if (p == nullptr)
    {
        p = new vertex;
        p->Data = data;
        rost = true;
    }
    else if (p->Data > data)
    {
        if (addAVL(p->Left, data, rost))
        {
            if (rost)
            {
                if (p->balance > 0)
                {
                    p->balance = 0;
                    rost = false;
                }
                else if (p->balance == 0)
                {
                    p->balance = -1;
                    rost = true;
                }
                else if ((p->Left)->balance < 0)
                {
                    rotateLL(p);
                    rost = false;
                }
                else
                {
                    rotateLR(p);
                    rost = false;
                }
            }
        }
        else
        {
            return false;
        }
    }

    else if (p->Data < data)
    {
        if (addAVL(p->Right, data, rost))
        {
            if (rost)
            {
                if (p->balance < 0)
                {
                    p->balance = 0;
                    rost = false;
                }
                else if (p->balance == 0)
                {
                    p->balance = 1;
                    rost = true;
                }
                else if ((p->Right)->balance > 0)
                {
                    rotateRR(p);
                    rost = false;
                }
                else
                {
                    rotateRL(p);
                    rost = false;
                }
            }
        }
        else
        {
            return false;
        }
    }
    else
        return false;
    return true;
}

vertex *createAVL(int n)
{
    vertex *root = NULL;
    int i = 0;
    bool rost;
    while (i < n)
    {
        int data = rand() % 1000;

        if (addAVL(root, data, rost))
            i++;
        // else
        //     std::cout << "Data with key " << data << " already in vertex"<< std::endl;
    }
    return root;
}
vertex *ISDP(int L, int R, int A[])
{
    if (L > R)
        return 0;
    else
    {
        int m = (L + R) / 2;
        vertex *p = new vertex;
        p->Data = A[m];
        p->Left = ISDP(L, m - 1, A);
        p->Right = ISDP(m + 1, R, A);
        return p;
    }
}
void BubbleSort(int A[], int n)
{
    int temp;
    for (int i = 0; i < n; i++)
    {
        for (int j = n - 1; j > i; j--)
        {
            if (A[j] < A[j - 1])
            {
                temp = A[j];
                A[j] = A[j - 1];
                A[j - 1] = temp;
            }
        }
    }
}
vertex *createISDP(int size)
{
    int A[size];
    for (int i = 0; i < size; i++)
    {
        A[i] = rand() % 1000;
    }
    BubbleSort(A, size);
    return ISDP(0, size - 1, A);
}
int main()
{
    srand(time(0));
    vertex *root = createAVL(100);
    vertex *root2 = createISDP(100);
    work(root);
    std::cout << "\n\nN = 100" << std::setw(10) << "Size" << std::setw(15) << "Checksum" << std::setw(15) << "Height" << std::setw(20) << "Average heigth\n";
    std::cout << "ISDP" << std::setw(12) << size(root2) << std::setw(15) << checkSum(root2) << std::setw(13) << height(root2) << std::setw(16) << SDP(root2, 1) / size(root2) << "\n";
    std::cout << "AVL" << std::setw(13) << size(root) << std::setw(15) << checkSum(root) << std::setw(13) << height(root) << std::setw(17) << std::setprecision(2) << std::fixed << SDP(root, 1) / size(root) << "\n";
    return 0;
}
