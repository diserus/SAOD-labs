#include <iostream>
#include <iomanip>
#define R() rand() % 20 + 1

struct vertex
{
    int Data;
    vertex *Left;
    vertex *Right;
};

vertex *init(int Data)
{
    vertex *Root = new vertex;
    Root->Left = nullptr;
    Root->Right = nullptr;
    Root->Data = Data;
    return Root;
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
// 0: top to down; 1: Left to Right; 2:Down to top
void work(vertex *Root, int mode, int &sum)
{
    if (mode == 0 && Root != nullptr)
    {
        sum += Root->Data;
        std::cout << Root->Data << " ";
        work(Root->Left, 0, sum);
        work(Root->Right, 0, sum);
    }
    if (mode == 1 && Root != nullptr)
    {
        sum += Root->Data;
        work(Root->Left, 1, sum);
        std::cout << Root->Data << " ";
        work(Root->Right, 1, sum);
    }
    if (mode == 2 && Root != nullptr)
    {
        sum += Root->Data;
        work(Root->Left, 2, sum);
        work(Root->Right, 2, sum);
        std::cout << Root->Data << " ";
    }
}

int main()
{
    srand(time(0));
    vertex *Root = init(R());
    Root->Right = init(R());
    Root->Right->Right = init(R());
    Root->Right->Right->Left = init(R());
    Root->Left = init(R());
    Root->Left->Right = init(R());
    Root->Left->Right->Left = init(R());
    int sum = 0;

    std::cout << "Top to down: ";
    work(Root, 0, sum);
    std::cout << "\nSum: " << sum << "\n";
    sum = 0;

    std::cout << "Left to right: ";
    work(Root, 1, sum);
    std::cout << "\nSum: " << sum << "\n";
    sum = 0;

    std::cout << "Down to top: ";
    work(Root, 2, sum);
    std::cout << "\nSum: " << sum << "\n";
    std::cout << "Size: " << size(Root);
    std::cout << "\nHeight: " << height(Root);
    std::cout << "\nAverage height: " << std::setprecision(2) << std::fixed << SDP(Root, 1) / size(Root);
}
