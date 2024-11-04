#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

const int N = 10;

struct vertex
{
    int data;
    int W;
    int h;
    vertex *left;
    vertex *right;
};

int Size(vertex *p)
{
    if (p == NULL)
        return 0;
    return 1 + Size(p->left) + Size(p->right);
}

int Sum(vertex *p)
{
    if (p == NULL)
        return 0;
    return p->data + Sum(p->left) + Sum(p->right);
}

int Height(vertex *p)
{
    if (p == NULL)
        return 0;
    return 1 + max(Height(p->left), Height(p->right));
}

float SumPaths(vertex *p, int L)
{
    if (p == NULL)
        return 0;
    return L + SumPaths(p->left, L + 1) + SumPaths(p->right, L + 1);
}

void ObhodLR(vertex *p)
{
    if (p != NULL)
    {
        ObhodLR(p->left);
        cout << p->data << "  ";
        ObhodLR(p->right);
    }
}

bool isUnique(int num, int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == num)
        {
            return false;
        }
    }
    return true;
}

// Функция для вычисления матрицы AW
void matrixAW(int AW[][N + 1], int weights[], int N)
{
    for (int i = 0; i <= N; ++i)
    {
        for (int j = i + 1; j <= N; ++j)
        {
            AW[i][j] = AW[i][j - 1] + weights[j - 1];
        }
    }
}

// Функция для вычисления матриц AP и AR
void matrixAP_AR(int AW[][N + 1], int AP[][N + 1], int AR[][N + 1], int N)
{
    for (int i = 0; i < N; ++i)
    {
        int j = i + 1;
        AP[i][j] = AW[i][j];
        AR[i][j] = j;
    }

    for (int h = 2; h <= N; ++h)
    {
        for (int i = 0; i <= N - h; ++i)
        {
            int j = i + h;
            int m = AR[i][j - 1];
            float minCost = AP[i][m - 1] + AP[m][j];

            for (int k = m + 1; k <= AR[i + 1][j]; ++k)
            {
                float cost = AP[i][k - 1] + AP[k][j];
                if (cost < minCost)
                {
                    m = k;
                    minCost = cost;
                }
            }

            AP[i][j] = minCost + AW[i][j];
            AR[i][j] = m;
        }
    }
}

// Функция для построения дерева на основе матрицы AR
vertex *createTree(int keys[], int weights[], int AR[][N + 1], int L, int R)
{
    if (L < R)
    {
        int k = AR[L][R];
        vertex *root = new vertex;
        root->data = keys[k - 1];
        root->W = weights[k - 1]; // Присваиваем вес
        root->left = createTree(keys, weights, AR, L, k - 1);
        root->right = createTree(keys, weights, AR, k, R);
        return root;
    }
    return NULL;
}

// Функция для вывода матриц
void printMatrix(int matrix[][N + 1], int N, const string &name)
{
    cout << "Matrix " << name << ":\n";
    for (int i = 0; i <= N; ++i)
    {
        for (int j = 0; j <= N; ++j)
        {
            if (matrix[i][j] == 0 && i != j)
                cout << setw(5) << " " << " ";
            else
                cout << setw(5) << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Рекурсивная функция для инициализации высоты узлов дерева
void h_init(vertex *p, int &Wh)
{
    if (p != NULL)
    {
        if (p->left != NULL)
        {
            p->left->h = p->h + 1;
            Wh += p->left->h * p->left->W;
        }
        if (p->right != NULL)
        {
            p->right->h = p->h + 1;
            Wh += p->right->h * p->right->W;
        }
        h_init(p->left, Wh);
        h_init(p->right, Wh);
    }
}

int main()
{
    srand(time(0));

    int min = 1;
    int max = 100;

    int *keys = new int[N];
    int weights[N + 1];
    int count = 0;

    while (count < N)
    {
        int num = rand() % (max - min + 1) + min;
        if (isUnique(num, keys, count))
        {
            keys[count] = num;
            weights[count] = rand() % 100 + 1;
            count++;
        }
    }

    // Сортировка ключей для корректной вставки в дерево
    sort(keys, keys + N);

    int AW[N + 1][N + 1]{};
    int AP[N + 1][N + 1]{};
    int AR[N + 1][N + 1]{};

    matrixAW(AW, weights, N);
    matrixAP_AR(AW, AP, AR, N);

    printMatrix(AW, N, "AW");
    printMatrix(AP, N, "AP");
    printMatrix(AR, N, "AR");

    // Создание дерева
    vertex *root = createTree(keys, weights, AR, 0, N);

    cout << "output(left to right)" << endl;
    ObhodLR(root);
    cout << endl
         << endl;

    // Инициализация переменных для расчета средней взвешенной высоты
    root->h = 1;
    int Wh = root->h * root->W; // начальная высота корня
    h_init(root, Wh);           // инициализация высот и вычисление суммы

    int Wf = 0; // сумма всех весов
    for (int i = 0; i < N; i++)
    {
        Wf += weights[i];
    }

    cout << setw(30) << "size" << setw(30) << "Check sum" << setw(20) << "Height" << setw(43) << "aver. weight. height" << endl;
    cout << "-------------------------------------------------------------------------------------" << endl;
    cout << setw(10) << "DOP" << setw(16) << Size(root) << setw(20) << Sum(root) << setw(15) << Height(root) << setw(20) << setprecision(4) << fixed << setw(25) << (float)Wh / Wf << endl;

    float prov = (float)AP[0][N] / AW[0][N];
    cout << endl;
    cout << "AP[0][N]/AW[0][N]: " << prov << endl;

    delete[] keys;
    return 0;
}
