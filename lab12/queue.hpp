#include <iostream>
#include "node.hpp"

template <typename T>
class Queue
{
private:
    Node<T> *head;
    Node<T> *tail;
    int sizeOfQueue;

public:
    Queue()
    {
        head = nullptr;
        tail = nullptr;
    }

    ~Queue()
    {
        while (size())
            pop();
    }

    bool isEmpty()
    {
        return head == nullptr;
    }

    void push(T data)
    {
        Node<T> *newNode = new Node<T>(data, nullptr);
        newNode->data = data;
        newNode->next = nullptr;
        sizeOfQueue++;
        if (isEmpty())
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

    void pop()
    {
        if (!isEmpty())
        {

            Node<T> *temp = head;
            head = head->next;
            sizeOfQueue--;
            delete temp;
        }
    }

    int peek()
    {
        if (!isEmpty())
        {
            return head->data;
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

            Node<T> *temp = head;
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
            Node<T> *temp = head;
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
            Node<T> *temp = head;
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

    Node<T> *getHeadNext()
    {
        if (!isEmpty() && head->next != nullptr)
        {
            return head->next;
        }
        return nullptr;
    }
    Node<T> *getHead()
    {
        if (head != nullptr)
        {
            return head;
        }
        return nullptr;
    }
    void setHead(Node<T> *node)
    {
        head = node;
    }
    Node<T> *getTail()
    {
        if (tail != nullptr)
        {
            return tail;
        }
        return nullptr;
    }
    void setTailNext(Node<T> *node)
    {
        tail->next = node;
    }

    void init()
    {
        head = nullptr;
        tail = nullptr;
    }
};
