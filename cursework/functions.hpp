#pragma once
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <string>
#include <stdio.h>
#include "struct.hpp"
using namespace std;
void parseDate(char *date, int &day, int &month, int &year)
{
    std::sscanf(date, "%2d-%2d-%2d", &day, &month, &year);
}

bool compare(record &r1, record &r2)
{
    int day1, month1, year1;
    int day2, month2, year2;

    parseDate(r1.e, day1, month1, year1);
    parseDate(r2.e, day2, month2, year2);

    if (year1 != year2)
        return year1 < year2;
    else if (month1 != month2)
        return month1 < month2;
    else if (day1 != day2)
        return day1 < day2;
    else
        return strcmp(r1.b, r2.b) < 0;
}
int parseYear(char *date)
{
    int year;
    int day;
    int month;
    std::sscanf(date, "%2d-%2d-%2d", &day, &month, &year);
    return year;
}
int comparator(char *word1, char *word2)
{
    int i = 0;
    while (word1[i] != '\0' && word2[i] != '\0')
    {
        if ((word1[i] == ' ' && word2[i] != ' '))
            return -1;
        else if ((word2[i] == ' ' && word1[i] != ' '))
            return 1;
        else if ((word1[i] < word2[i]))
            return -1;
        else if ((word1[i] > word2[i]) || (word2[i] == ' ' && word1[i] != ' '))
            return 1;
        i++;
    }
    return 0;
}
void QuickSort(record *arr[], int L, int R)
{
    record *pivot = arr[L];
    int i = L, j = R;

    while (i <= j)
    {
        while (compare(*arr[i], *pivot))
            i++;
        while (compare(*pivot, *arr[j]))
            j--;
        if (i <= j)
        {
            std::swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    if (L < j)
        QuickSort(arr, L, j);
    if (i < R)
        QuickSort(arr, i, R);
}
int binarySearch(record *A[], int n, int elem, Queue *&queue)
{
    int l = 0;
    int r = n - 1;
    while (l <= r)
    {
        int i = (l + r) / 2;
        int year = parseYear(A[i]->e);

        if (year == elem)
        {
            queue->add(A[i]);

            int left = i - 1;
            while (left >= 0 && parseYear(A[left]->e) == elem)
            {
                queue->add(A[left]);
                left--;
            }
            int right = i + 1;
            while (right < n && parseYear(A[right]->e) == elem)
            {
                queue->add(A[right]);
                right++;
            }
            return 0;
        }

        if (year < elem)
            l = i + 1;
        else
            r = i - 1;
    }
    return 1;
}
bool B2INSERT(vertex *&p, record *data, bool &VR, bool &HR)
{
    if (p == nullptr)
    {
        p = new vertex;
        strcpy(p->data, data->a);
        p->Left = p->Right = p->simmilar = nullptr;
        p->record = data;
        p->balance = false;
        VR = true;
    }
    else if (comparator(p->data, data->a) == 1)
    {
        if (B2INSERT(p->Left, data, VR, HR))
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
    else if (comparator(p->data, data->a) == -1)
    {
        if (B2INSERT(p->Right, data, VR, HR))
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
    {
        if (B2INSERT(p->simmilar, data, VR, HR))
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
    return true;
}
void printRecord(record *rec)
{
    cout << rec->a << " " << rec->b << " " << rec->c << "\t"
         << rec->d << "\t" << rec->e << endl;
}
void displayRecords(record *indexArr[])
{
    int i = 0;
    while (i < 4000)
    {
        for (int j = 0; j < 20 && i < 4000; j++, i++)
        {
            printRecord(indexArr[i]);
        }
        char choice;
        do
        {
            cout << "\nDo you want to continue? (y/n): ";
            cin >> choice;
            system("cls");
            if (choice != 'y' && choice != 'n')
            {
                cout << "Incorrect input" << endl;
            }
        } while (choice != 'y' && choice != 'n');

        if (choice == 'n')
        {
            break;
        }
        i++;
    }
}
Queue *displaySearch(record *indexArr[], int readCount)
{
    int element;
    std::cout << "Input records what you want to find(key = year): ";
    std::cin >> element;
    Queue *queue = new Queue;
    if (binarySearch(indexArr, readCount, element, queue))
        std::cout << "Records didn't find\n";
    queue->print();
    return queue;
}
void work(vertex *p)
{
    if (p != nullptr)
    {
        work(p->Left);
        printRecord(p->record);
        work(p->simmilar);
        work(p->Right);
    }
}
void delTree(vertex *&p)
{
    if (p != nullptr)
    {
        delTree(p->Left);
        delTree(p->simmilar);
        delTree(p->Right);

        delete p;
        p = nullptr;
    }
}
int sizeTree(vertex *vertex)
{
    if (vertex == nullptr)
        return 0;
    else
        return 1 + sizeTree(vertex->Left) + sizeTree(vertex->Right) + sizeTree(vertex->simmilar);
}
void printAllRecords(vertex *node, char *key)
{
    if (node == nullptr)
        return;

    size_t lenPrefix = strlen(key);
    int cmp = strncmp(node->data, key, lenPrefix);

    // Обходим левое поддерево
    printAllRecords(node->Left, key);
    printAllRecords(node->simmilar, key);
    // Если текущий узел соответствует ключу или больше, выводим его
    if (cmp >= 0)
    {
        printRecord(node->record);
    }

    // Обходим правое поддерево
    printAllRecords(node->Right, key);
}
void treeSearch(vertex *root, char *key)
{
    vertex *p = root;
    size_t lenPrefix = strlen(key);
    while (p != nullptr)
    {

        int cmp = strncmp(p->data, key, lenPrefix);
        if (cmp < 0)
        {
            p = p->Right;
        }
        else if (cmp > 0)
        {
            p = p->Left;
        }
        else
        {
            printAllRecords(p, key);
            printAllRecords(p->Right, key);
            return;
        }
    }
}
