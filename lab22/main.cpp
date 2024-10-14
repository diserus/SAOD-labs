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
void rotateLL1(vertex *&p, bool &decrease)
{
    vertex *q = p->Left;

    if (q->balance == 0)
    {
        p->balance = -1;
        q->balance = 1;
        decrease = false;
    }
    else
    {
        p->balance = 0;
        q->balance = 0;
    }
    p->Left = q->Right;
    q->Right = p;
    p = q;
}
void rotateRR1(vertex *&p, bool &decrease)
{
    vertex *q = p->Right;
    if (q->balance == 0)
    {
        p->balance = 1;
        q->balance = -1;
        decrease = false;
    }
    else
    {
        p->balance = 0;
        q->balance = 0;
    }
    p->Right = q->Left;
    q->Left = p;
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

void BL(vertex *&p, bool &decrease)
{
    if (p->balance == -1)
        p->balance = 0;
    else if (p->balance == 0)
    {
        p->balance = 1;
        decrease = false;
    }
    else if (p->balance == 1)
    {
        if (p->Right->balance >= 0)
            rotateRR1(p, decrease);
        else
            rotateRL(p);
    }
}
void BR(vertex *&p, bool &decrease)
{
    if (p->balance == 1)
        p->balance = 0;
    else if (p->balance == 0)
    {
        p->balance = -1;
        decrease = false;
    }
    else if (p->balance == -1)
    {
        if (p->Left->balance <= 0)
            rotateLL1(p, decrease);
        else
            rotateLR(p);
    }
}

void del(vertex *&r, vertex *&q, bool &decrease)
{
    if (r->Right != NULL)
    {
        del(r->Right, q, decrease);
        if (decrease)
            BR(r, decrease);
    }
    else
    {
        q->Data = r->Data;
        q = r;
        r = r->Left;
        decrease = true;
    }
}

bool deleteVertexWithKey(vertex *&p, int x, bool &decrease)
{
    vertex *q = NULL;
    if (p == NULL)
        return 1;
    else if (p->Data > x)
    {
        if (deleteVertexWithKey(p->Left, x, decrease))
            return 1;
        if (decrease)
            BL(p, decrease);
    }
    else if (p->Data < x)
    {
        if (deleteVertexWithKey(p->Right, x, decrease))
            return 1;
        if (decrease)
            BR(p, decrease);
    }
    else
    {
        q = p;
        if (q->Right == NULL)
        {
            p = q->Left;
            decrease = true;
        }
        else if (q->Left == NULL)
        {
            p = q->Right;
            decrease = true;
        }
        else
        {
            del(q->Left, q, decrease);
            if (decrease)
                BL(p, decrease);
        }
    }
    delete (q);
    return 0;
}

int main()
{
    vertex *root = createAVL(100);
    char choice;
    bool decrease;
    do
    {
        work(root);
        std::cout << "\n";
        std::string x;
        std::cout << "What do you want to delete?\n";
        std::cin >> x;
        while (!isdigit(x[0]))
        {
            std::cout << "Must be int\n";
            std::cin >> x;
        }
        int xx = std::stoi(x);
        if (!deleteVertexWithKey(root, xx, decrease))
        {

            std::cout << "Vertex with data \"" << x << "\" has been deleted\n";
            std::cout << "\n";
        }
        else
            std::cout << "Vertex doesn't exist in tree\n";
        std::cout << "Do you want to continue? (y/n)\n";
        std::cin >> choice;
        while (choice != 'y' && choice != 'n')
        {
            std::cout << "Incorrect input(y/n)\n";
            std::cin >> choice;
        }
    } while (choice != 'n');
}
