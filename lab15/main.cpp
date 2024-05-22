#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

struct Element
{
    int key;
    Element *next;
};

int hashFunction(int key, int tableSize)
{
    return key % tableSize;
}

int countCollisions(vector<Element *> &hashTable)
{
    int collisions = 0;
    for (int i = 0; i < hashTable.size(); i++)
    {
        if (hashTable[i] != nullptr)
        {
            Element *current = hashTable[i];
            while (current->next != nullptr)
            {
                collisions++;
                current = current->next;
            }
        }
    }
    return collisions;
}

void printHashTable(vector<Element *> &hashTable)
{
    for (int i = 0; i < hashTable.size(); i++)
    {
        cout << "List " << i + 1 << ": ";
        Element *current = hashTable[i];
        while (current != nullptr)
        {
            cout << current->key << " ";
            current = current->next;
        }
        cout << endl;
    }
}

void insertElement(vector<Element *> &hashTable, int key)
{
    int index = hashFunction(key, hashTable.size());
    Element *newElement = new Element;
    newElement->key = key;
    newElement->next = hashTable[index];
    hashTable[index] = newElement;
}

void searchElement(vector<Element *> &hashTable, int key)
{
    int index = hashFunction(key, hashTable.size());
    Element *current = hashTable[index];
    int position = 0;

    while (current != nullptr)
    {
        if (current->key == key)
        {
            int listIndex = index;
            cout << "List: " << index + 1 << "\n";
            cout << "Position: " << position + 1 << "\n";
            return;
        }
        position++;
        current = current->next;
    }
    cout << "Element didn't found\n";
}

int main()
{
    srand(time(0));
    int table_sizes[] = {11, 13, 17, 19, 23, 29, 31, 37, 41, 43};
    cout << setw(5) << "Size" << setw(10) << "N symb" << setw(15) << "N collisions" << "\n";
    for (int table_size : table_sizes)
    {
        vector<Element *> hash_table(table_size, nullptr);

        for (int i = 0; i < 100; i++)
        {
            int elem = rand() % 10000;
            insertElement(hash_table, elem);
        }

        int collisions = countCollisions(hash_table);

        cout << setw(5) << table_size;
        cout << setw(10) << 100;
        cout << setw(15) << collisions;
        cout << endl;
    }
    vector<Element *> hash_table(5, nullptr);
    vector<int> keys = {15, 66, 16, 12, 1, 0, 5, 8478, 1, 3, 97, 4, 5654, 1, 51, 89};
    for (int key : keys)
        insertElement(hash_table, key);
    printHashTable(hash_table);
    searchElement(hash_table, 8478);
    return 0;
}
