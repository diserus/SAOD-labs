#include <iostream>
#include <iomanip>
struct vertex
{
    int Data;
    vertex *Left;
    vertex *Right;
};
bool addDoubleKos(vertex *&root, int data)
{
    vertex **p = &root;
    while (*p != nullptr)
    {
        if (data < (*p)->Data)
            p = &((*p)->Left);
        else if (data > (*p)->Data)
            p = &((*p)->Right);
        else
        {
            std::cout << "Data this the key " << data << " already in tree\n";
            return false;
        }
    }
    if (*p == nullptr)
    {
        *p = new vertex;
        (*p)->Data = data;
        (*p)->Right = nullptr;
        (*p)->Left = nullptr;
    }
    return true;
}
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
        std::cout << "Data this the key " << data << " already in tree\n";
        boool = false;
    }
    return boool;
}
vertex *createDoubleKos(int n)
{
    vertex *root = nullptr;
    int i = 0;
    while (i < n)
    {
        int data = rand() % 500;
        if (addDoubleKos(root, data))
            i++;
    }
    return root;
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
        A[i] = rand() % 500;
    }
    BubbleSort(A, size);
    return ISDP(0, size - 1, A);
}
void work(vertex *p)
{
    if (p != NULL)
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
    if (p == NULL)
        return 0;
    else
        return (p->Data + checkSum(p->Left) + checkSum(p->Right));
}
int main()
{
    srand(time(0));
    int N = 100;
    vertex *root1 = createDoubleKos(N);
    vertex *root2 = createRecurse(N);
    vertex *root3 = createISDP(N);
    system("cls");
    std::cout << "\nDouble indirection: ";
    work(root1);
    std::cout << "\n\nRecursion: ";
    work(root2);
    std::cout << "\n\nN = 100" << std::setw(10) << "Size" << std::setw(15) << "Checksum" << std::setw(15) << "Height" << std::setw(20) << "Average heigth\n";
    std::cout << "ISDP" << std::setw(12) << size(root3) << std::setw(15) << checkSum(root3) << std::setw(13) << height(root3) << std::setw(16) << SDP(root3, 1) / size(root3) << "\n";
    std::cout << "SDP1" << std::setw(12) << size(root1) << std::setw(15) << checkSum(root1) << std::setw(13) << height(root1) << std::setw(16) << std::setprecision(2) << std::fixed << SDP(root1, 1) / size(root1) << "\n";
    std::cout << "SDP2" << std::setw(12) << size(root2) << std::setw(15) << checkSum(root2) << std::setw(13) << height(root2) << std::setw(16) << std::setprecision(2) << std::fixed << SDP(root2, 1) / size(root2) << "\n";
    return 0;
}
