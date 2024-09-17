#include <iostream>
#include <iomanip>
struct vertex
{
    int Data;
    vertex *Left;
    vertex *Right;
};

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
void work(vertex *Root, int &sum)
{
    if (Root != nullptr)
    {
        sum += Root->Data;
        work(Root->Left, sum);
        std::cout << Root->Data << " ";
        work(Root->Right, sum);
    }
}
int main()
{
    srand(time(0));
    int N = 100;
    int A[N];
    for (int i = 0; i < N; i++)
        A[i] = rand() % 200;
    BubbleSort(A, N);
    vertex *root = ISDP(0, N - 1, A);
    int sum = 0;
    work(root, sum);
    std::cout << "\nSum: " << sum;
    std::cout << "\nSize: " << size(root);
    std::cout << "\nHeight: " << height(root);
    std::cout << "\nAverage height: " << std::setprecision(2) << std::fixed << SDP(root, 1) / size(root);
    return 0;
}
