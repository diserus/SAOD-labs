#include <iostream>
#include "node.hpp"

template <typename T>
class Queue
{
private:
    Node<T> *front;
    Node<T> *rear;
    int sizeOfQueue;

public:
    Queue()
    {
        front = nullptr;
        rear = nullptr;
    }

    ~Queue()
    {
        while (size())
            pop();
    }

    bool isEmpty()
    {
        return front == nullptr;
    }

    void push(T data)
    {
        Node<T> *newNode = new Node<T>(data, nullptr);
        newNode->data = data;
        newNode->next = nullptr;
        sizeOfQueue++;
        if (isEmpty())
        {
            front = newNode;
            rear = newNode;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
        }
    }

    void pop()
    {
        if (!isEmpty())
        {

            Node<T> *temp = front;
            front = front->next;
            sizeOfQueue--;
            delete temp;
        }
    }

    int peek()
    {
        if (!isEmpty())
        {
            return front->data;
        }
    }

    int size()
    {
        return sizeOfQueue;
    }

    void printQueue()
    {
        if (!isEmpty())
        {

            Node<T> *temp = front;
            while (temp != nullptr)
            {
                std::cout << temp->data << " ";
                temp = temp->next;
            }
            std::cout << "\n";
        }
        return;
    }

    void fill_inc(int size)
    {
        for (int i = 0; i < size; i++)
        {
            push(i);
        }
    }

    void fill_dec(int size)
    {
        for (int i = size - 1; i >= 0; i--)
        {
            push(i);
        }
    }

    void fill_rand(int size)
    {
        srand(time(0));
        for (int i = 0; i < size; i++)
        {
            push(rand() % 100);
        }
    }

    T check_sum()
    {
        T sum = 0;
        if (!isEmpty())
        {
            Node<T> *temp = front;
            while (temp != nullptr)
            {
                sum += temp->data;
                temp = temp->next;
            }
        }
        return sum;
    }

    T check_series()
    {
        T k = 1;
        if (!isEmpty())
        {
            Node<T> *temp = front;
            while (temp->next != nullptr)
            {
                if (temp->data <= temp->next->data)
                {
                    temp = temp->next;
                }
                else
                {
                    k++;
                    temp = temp->next;
                }
            }
        }
        return k;
    }

    void clear()
    {
        while (!isEmpty())
            pop();
    }
};
