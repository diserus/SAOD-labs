#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

struct List
{
    int key;
    List *next;
};

int hashFunction(int key, int tableSize)
{
    return key % tableSize;
}

int countCollisions(vector<List *> table)
{
    int collisions = -table.size();
    for (List *list : table)
    {
        if (list != nullptr)
        {
            collisions++;
            List *current = list;
            while (current->next != nullptr)
            {
                collisions++;
                current = current->next;
            }
        }
    }
    return collisions;
}

void printList(List *list)
{
    if (list == nullptr)
    {
        cout << "List is empty" << endl;
        return;
    }

    List *current = list;
    while (current != nullptr)
    {
        cout << current->key << " ";
        current = current->next;
    }
    cout << endl;
}

int main()
{

    // int tableSize = 5;

    // vector<List *> table(tableSize, nullptr);

    // int keys[] = {17, 18, 16, 9, 6, 15, 12, 19, 20, 1, 10, 3};
    // for (int key : keys)
    // {
    //     int index = hashFunction(key, tableSize);
    //     List *newList = new List;
    //     newList->key = key;

    //     newList->next = table[index];
    //     table[index] = newList;
    // }

    // int collisions = countCollisions(table);
    // cout << "Number of collisions: " << collisions << endl;

    // for (int i = 0; i < tableSize; i++)
    // {
    //     cout << "List " << i << ": ";
    //     List *current = table[i];
    //     while (current != nullptr)
    //     {
    //         cout << current->key << " ";
    //         current = current->next;
    //     }
    //     cout << endl;
    // }
    cout << setw(5) << "Size" << setw(10) << "N symb" << setw(10) << "N collisions" << "\n";

    for (int size = 11; size < 102; size += 10)
    {
        vector<List *> table(size, nullptr);

        cout << setw(5) << size;
    }
    return 0;
}
