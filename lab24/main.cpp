#include <iostream>
#include <algorithm>
struct vertex
{
    int data;
    int weight;
    vertex *left = nullptr;
    vertex *right = nullptr;
};

void calculation_AW(int **AW, int **VW, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = (i + 1); j < size; j++)
        {
            AW[i][j] = AW[i][j - 1] + VW[1][j];
        }
    }
}

void calculation_APandAR(int **AP, int **AR, int **AW, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int j = i + 1;
        AP[i][j] = AW[i][j];
        AR[i][j] = j;
    }
    for (int h = 2; h < size; h++)
    {
        for (int i = 0; i < size - h; i++)
        {
            int j = i + h;
            int m = AR[i][j - 1];
            int min = AP[i][m - 1] + AP[m][j];
            for (int k = m + 1; k <= AR[i + 1][j]; k++)
            {
                int x = AP[i][k - 1] + AP[k][j];
                if (x < min)
                {
                    m = k;
                    min = x;
                }
            }
            AP[i][j] = min + AW[i][j];
            AR[i][j] = m;
        }
    }
}
void addRST_R(vertex *&p, int data, int weight)
{
    if (p == NULL)
    {
        p = new vertex;
        p->data = data;
        p->weight = weight;
    }
    else if (data < p->data)
        addRST_R(p->left, data, weight);
    else if (data > p->data)
        addRST_R(p->right, data, weight);
}
void createvertex(vertex *&root, int lBorder, int rBorder, int **AR, int **VW)
{
    if (lBorder < rBorder)
    {
        int k = AR[lBorder][rBorder];
        addRST_R(root, VW[0][k], VW[1][k]);
        createvertex(root, lBorder, k - 1, AR, VW);
        createvertex(root, k, rBorder, AR, VW);
    }
}

void printSquareMatrix(int **arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            std::cout.width(5);
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
void work(vertex *p)
{
    if (p != nullptr)
    {
        work(p->left);
        std::cout << p->data << " ";
        work(p->right);
    }
}
int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

int sizeTree(vertex *vertex)
{
    if (vertex == nullptr)
        return 0;
    else
        return 1 + sizeTree(vertex->left) + sizeTree(vertex->right);
}

int height(vertex *vertex)
{
    if (vertex == nullptr)
        return 0;
    else
        return 1 + max(height(vertex->left), height(vertex->right));
}
double SDP(vertex *vertex, int L)
{
    if (vertex == nullptr)
        return 0;
    else
        return L + SDP(vertex->left, L + 1) + SDP(vertex->right, L + 1);
}
int checkSum(vertex *p)
{
    if (p == nullptr)
        return 0;
    else
        return (p->data + checkSum(p->left) + checkSum(p->right));
}
int sumLengthWaysTreeDOP(vertex *root, int L)
{
    int S;
    if (root == nullptr)
    {
        S = 0;
    }
    else
    {
        S = root->weight * L + sumLengthWaysTreeDOP(root->left, L + 1) + sumLengthWaysTreeDOP(root->right, L + 1);
    }
    return S;
}
int weightTree(vertex *root)
{
    int n;
    if (root == nullptr)
    {
        n = 0;
    }
    else
    {
        n = root->weight + weightTree(root->left) + weightTree(root->right);
    }
    return n;
}
float weightedAverageHeightTree(vertex *p)
{
    float h;
    h = (float)sumLengthWaysTreeDOP(p, 1) / weightTree(p);
    return h;
}

void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    int size = 25;
    int **VandW = new int *[2]; // Данные и их веса

    for (int i = 0; i < 2; i++)
    {
        VandW[i] = new int[size + 1];
        VandW[i][0] = 0;
    }

    // Заполение вершин неповторяющимися числами
    bool table[2 * size] = {false};
    int x;
    for (int i = 1; i < size + 1; i++)
    {
        while (table[x = rand() % (2 * size)])
            ;
        table[x] = true;
        VandW[0][i] = x;
    }
    // Сортировка вершин
    for (int i = 1; i < size + 1; i++)
    {
        for (int j = size - 1 + 1; j > i; j--)
        {
            if (VandW[0][j] < VandW[0][j - 1])
            {
                swap(&VandW[0][j], &VandW[0][j - 1]);
            }
        }
    }
    // Случайные веса для вершин
    for (int i = 1; i < size + 1; i++)
    {
        VandW[1][i] = rand() % size + 1;
    }

    // Вывод начальных данных и весов
    short int tmp = 0;
    for (int i = 1; i < size + 1; i++)
    {
        std::cout.width(3);
        std::cout << VandW[0][i];
        std::cout << "[";
        std::cout.width(2);
        std::cout << VandW[1][i];
        std::cout << "]" << "  ";
        tmp++;
        if (tmp == 10)
        {
            std::cout << std::endl;
            tmp = 0;
        }
    }
    std::cout << std::endl;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

    int **AW = new int *[size + 1]; // матрица весов
    int **AP = new int *[size + 1]; // матрица взвешенных высот
    int **AR = new int *[size + 1]; // матрица индексов

    for (int i = 0; i < size + 1; i++)
    {
        AW[i] = new int[size + 1];
        AP[i] = new int[size + 1];
        AR[i] = new int[size + 1];
        for (int j = 0; j < size + 1; j++)
            AW[i][j] = AP[i][j] = AR[i][j] = 0;
    }
    calculation_AW(AW, VandW, size + 1);
    calculation_APandAR(AP, AR, AW, size + 1);
    if (size < 26)
    {
        std::cout << "Matrix AW:" << std::endl;
        printSquareMatrix(AW, size + 1);
        std::cout << "Matrix AP:" << std::endl;
        printSquareMatrix(AP, size + 1);
        std::cout << "Matrix AR:" << std::endl;
        printSquareMatrix(AR, size + 1);
    }
    vertex *root = nullptr;
    createvertex(root, 0, size, AR, VandW);
    work(root);

    std::cout << "\n_____________________\n";
    std::cout << "Size " << sizeTree(root) << "\n";
    std::cout << "Checksum " << checkSum(root) << "\n";
    std::cout << "Height " << height(root) << "\n";
    std::cout << "Weighted Average Height " << weightedAverageHeightTree(root) << "\n";
    std::cout << "AP[0,size] / AW[0,size] = " << (double)AP[0][size] / AW[0][size] << "\n";
    std::cout << "\n\n";
    return 0;
}
