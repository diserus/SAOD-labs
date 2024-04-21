#include <iostream>
#include "node.hpp"

template <typename T>
class Stack
{
private:
    int sizeOfStack;
    Node<T> *currentTop;

public:
    Stack()
    {
        sizeOfStack = 0;
        currentTop = NULL;
    }

    ~Stack()
    {
        while (size())
            pop();
    }

    void push(T element)
    {
        Node<T> *node = new Node<T>(element, currentTop);
        currentTop = node;
        sizeOfStack++;
    }

    void pop()
    {
        Node<T> *node = currentTop;
        currentTop = currentTop->next;
        sizeOfStack--;
        delete node;
    }

    T top()
    {
        return currentTop->data;
    }

    int size()
    {
        return sizeOfStack;
    }

    void fill_rand(int size)
    {
        srand(time(0));
        for (int i = 0; i < size; i++)
        {
            push(rand() % 100);
        }
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

    void printStack()
    {
        Node<T> *currentNode = currentTop;
        while (currentNode != NULL)
        {
            std::cout << currentNode->data << " ";
            currentNode = currentNode->next;
        }
        std::cout << std::endl;
    }

    T check_sum()
    {
        Node<T> *currentNode = currentTop;
        T sum = 0;
        while (currentNode != NULL)
        {
            sum += currentNode->data;
            currentNode = currentNode->next;
        }
        return sum;
    }

    T check_series()
    {
        T k = 1;
        Node<T> *currentNode = currentTop;
        while (currentNode != NULL && currentNode->next != NULL)
        {
            if (currentNode->data < currentNode->next->data)
            {
                k++;
                currentNode = currentNode->next;
            }
            else
            {
                currentNode = currentNode->next;
            }
        }

        return k;
    }
    void clear()
    {
        while (size())
            pop();
    }
};
