#ifndef _NODE
#define _NODE
template <typename T>
struct Node
{
    T data;
    Node<T> *next;

    Node(T newData, Node<T> *nextNode)
    {
        data = newData;
        next = nextNode;
    }
};
#endif
