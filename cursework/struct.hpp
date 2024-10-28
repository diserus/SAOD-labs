#pragma once
#include <iostream>
using namespace std;
struct record
{
    char a[32];
    char b[18];
    short int c;
    short int d;
    char e[10];
};
struct List
{
    List *next = nullptr;
    record *data;
};

struct Queue
{
    List *head = nullptr;
    List *tail = nullptr;
    void add(record *rec)
    {
        List *newNode = new List;
        newNode->data = rec;
        newNode->next = nullptr;
        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }
    void print()
    {
        List *temp = head;
        while (temp != nullptr)
        {
            cout << temp->data->a << " " << temp->data->b << " " << temp->data->c << "\t"
                 << temp->data->d << "\t" << temp->data->e << endl;
            temp = temp->next;
        }
    }
    void clear()
    {
        while (head != nullptr)
        {
            List *temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    }
};

struct vertex
{
    char data[32]; // фио
    record *record;
    vertex *Left = nullptr;
    vertex *Right = nullptr;
    bool balance;
};
