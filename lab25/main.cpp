#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

const int N = 100;

struct vertex
{
    int data;
    int W;
    int h;
    vertex *left = nullptr;
    vertex *right = nullptr;
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

void work(vertex *p)
{
    if (p != NULL)
    {
        work(p->left);
        cout << p->data << "  ";
        work(p->right);
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
void addSDP(vertex *&p, int data, int weight)
{
    if (p == NULL)
    {
        p = new vertex;
        p->data = data;
        p->W = weight;
    }
    else if (data < p->data)
        addSDP(p->left, data, weight);
    else if (data > p->data)
        addSDP(p->right, data, weight);
}

vertex *createTree(int keys[], int weights[], int AR[][N + 1], int L, int R)
{
    if (L < R)
    {
        int k = AR[L][R];
        vertex *root = new vertex;
        root->data = keys[k - 1];
        root->W = weights[k - 1];
        root->left = createTree(keys, weights, AR, L, k - 1);
        root->right = createTree(keys, weights, AR, k, R);
        return root;
    }
    return NULL;
}
void A1(vertex *&root, int keys[], int weights[], int size)
{
    sort(weights, weights + size, greater<int>());
    for (int i = 0; i < size; i++)
    {
        addSDP(root, keys[i], weights[i]);
    }
}
void A2(vertex *&root, int keys[], int weights[], int L, int R)
{
    int wes = 0, sum = 0;
    if (L <= R)
    {
        int i = 0;
        for (i = L; i < R; i++)
            wes = wes + weights[i];

        for (i = L; i < R; i++)
        {
            if ((sum <= wes / 2) && (sum + weights[i] > wes / 2))
                break;
            sum = sum + weights[i];
        }

        addSDP(root, keys[i], weights[i]);
        A2(root, keys, weights, L, i - 1);
        A2(root, keys, weights, i + 1, R);
    }
}

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

    int *keys = new int[N + 1];
    int weights[N];
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
    sort(keys, keys + N);

    int AW[N + 1][N + 1]{};
    int AP[N + 1][N + 1]{};
    int AR[N + 1][N + 1]{};

    matrixAW(AW, weights, N);
    matrixAP_AR(AW, AP, AR, N);
    vertex *root = createTree(keys, weights, AR, 0, N);
    root->h = 1;
    int Wh = root->h * root->W;
    h_init(root, Wh);
    int Wf = 0;
    for (int i = 0; i < N; i++)
    {
        Wf += weights[i];
    }
    work(root);
    std::cout << "\n";
    vertex *root1 = nullptr;
    A1(root1, keys, weights, N);
    work(root1);
    vertex *root2 = nullptr;
    A2(root2, keys, weights, 0, N - 1);

    std::cout << "\n";
    work(root2);

    root1->h = 1;
    int Wh1 = root1->h * root1->W;
    h_init(root1, Wh1);

    root2->h = 1;
    int Wh2 = root2->h * root2->W;
    h_init(root2, Wh2);

    std::cout << "\n\nN = 100" << std::setw(10) << "Size" << std::setw(15) << "Checksum" << std::setw(15) << "Height" << std::setw(25) << "Average weight heigth\n";
    std::cout << "DOP" << std::setw(14) << Size(root) << std::setw(14) << Sum(root) << std::setw(12) << Height(root) << std::setw(19) << std::setprecision(2) << std::fixed << (float)Wh / Wf << "\n";
    std::cout << "A1" << std::setw(15) << Size(root1) << std::setw(14) << Sum(root1) << std::setw(13) << Height(root1) << std::setw(19) << std::setprecision(2) << std::fixed << (float)Wh1 / Wf << "\n";
    std::cout << "A2" << std::setw(15) << Size(root2) << std::setw(14) << Sum(root2) << std::setw(13) << Height(root2) << std::setw(18) << std::setprecision(2) << std::fixed << (float)Wh2 / Wf << "\n";
    delete[] keys;
    return 0;
}
