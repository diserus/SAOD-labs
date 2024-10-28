#include <iostream>
#include <iomanip>
bool HR;
bool VR;
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
bool insertDBD(vertex *&p, int data, bool &VR, bool &HR)
{
    if (p == nullptr)
    {
        p = new vertex;
        p->Data = data;
        p->Left = p->Right = nullptr;
        p->balance = false;
        VR = true;
    }
    else if (p->Data > data)
    {
        if (insertDBD(p->Left, data, VR, HR))
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
    else if (p->Data < data)
    {
        if (insertDBD(p->Right, data, VR, HR))
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

vertex *createDBD(int n, bool &VR, bool &HR)
{
    vertex *root = NULL;
    int i = 0;
    while (i < n)
    {
        int data = rand() % 1000;
        if (insertDBD(root, data, VR, HR))
            i++;
        // else
        //     std::cout << "Data with key " << data << " already in tree \n";
    }
    return root;
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
int main()
{
    srand(time(0));
    vertex *root = createDBD(100, VR, HR);
    vertex *root2 = createAVL(100);
    work(root);
    std::cout << "\n\nN = 100" << std::setw(10) << "Size" << std::setw(15) << "Checksum" << std::setw(15) << "Height" << std::setw(20) << "Average heigth\n";
    std::cout << "AVL" << std::setw(12) << size(root2) << std::setw(15) << checkSum(root2) << std::setw(13) << height(root2) << std::setw(16) << SDP(root2, 1) / size(root2) << "\n";
    std::cout << "DBD" << std::setw(12) << size(root) << std::setw(15) << checkSum(root) << std::setw(13) << height(root) << std::setw(16) << std::setprecision(2) << std::fixed << SDP(root, 1) / size(root) << "\n";
    return 0;
}
