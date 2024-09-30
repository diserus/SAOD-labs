#include <iostream>
#include <iomanip>
struct vertex
{
    int Data;
    vertex *Left;
    vertex *Right;
};

bool addRecurse(vertex *&root, int data)
{
    bool boool = true;
    if (root == nullptr)
    {
        root = new vertex;
        root->Data = data;
        root->Left = nullptr;
        root->Right = nullptr;
    }
    else if (data < root->Data)
        boool = addRecurse(root->Left, data);
    else if (data > root->Data)
        boool = addRecurse(root->Right, data);
    else
    {
        std::cout << "Data this the key " << data << " already in vertex\n";
        boool = false;
    }
    return boool;
}
vertex *createRecurse(int n)
{
    vertex *root = nullptr;
    int i = 0;
    while (i < n)
    {
        int data = rand() % 500;
        if (addRecurse(root, data))
            i++;
    }
    return root;
}
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
bool deleteVertexWithKey(vertex *&root, int key)
{
    vertex **p = &root;
    while (*p != nullptr)
    {
        if ((*p)->Data < key)
            p = (&((*p)->Right));
        else if ((*p)->Data > key)
            p = (&((*p)->Left));
        else
            break;
    }
    if (*p != nullptr)
    {
        vertex *q = *p;
        if (q->Left == nullptr)
            *p = q->Right;
        else if (q->Right == nullptr)
            *p = q->Left;
        else
        {
            vertex *r = q->Left;
            vertex *s = q;
            if (r->Right == nullptr)
            {
                r->Right = q->Right;
                *p = r;
            }
            else
            {
                while (r->Right != nullptr)
                {
                    s = r;
                    r = r->Right;
                }
                s->Right = r->Left;
                r->Left = q->Left;
                r->Right = q->Right;
                *p = r;
            }
        }
        delete (q);
    }
    else
        return false;
    return true;
}
int main()
{
    srand(time(0));
    vertex *root = createRecurse(50);
    std::cout << "\n";
    int count = 10;
    char choice;
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
        if (deleteVertexWithKey(root, xx))
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

    return 0;
}
