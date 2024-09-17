#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

class HashTable
{
private:
  vector<int> linearTable;
  vector<int> quadraticTable;
  int size;
  int linearCollisions;
  int quadraticCollisions;

public:
  HashTable(int m)
  {
    size = m;
    linearTable.assign(size, -1);
    quadraticTable.assign(size, -1);
    linearCollisions = 0;
    quadraticCollisions = 0;
  }

  int hash(int key) { return key % size; }

  void linearProbeInsert(int key)
  {
    int index = hash(key);
    while (linearTable[index] != -1)
    {
      index = (index + 1) % size;
      linearCollisions++;
      if (linearCollisions >= size)
        return;
    }
    linearTable[index] = key;
  }

  void quadraticProbeInsert(int key)
  {
    int index = hash(key);
    int i = 1;
    while (quadraticTable[index] != -1)
    {
      index = (index + i * i) % size;
      quadraticCollisions++;
      if (quadraticCollisions >= size)
        return;
      i++;
    }
    quadraticTable[index] = key;
  }

  int getLinearCollisions() { return linearCollisions; }

  int getQuadraticCollisions() { return quadraticCollisions; }

  void displayTables()
  {
    cout << "Hash Table with Linear Probing:\n";
    for (int i = 0; i < size; i++)
    {
      cout << i << ": ";
      if (linearTable[i] != -1)
        cout << linearTable[i];
      cout << endl;
    }

    cout << "\nHash Table with Quadratic Probing:\n";
    for (int i = 0; i < size; i++)
    {
      cout << i << ": ";
      if (quadraticTable[i] != -1)
        cout << quadraticTable[i];
      cout << endl;
    }
  }
};

bool isPrime(int num)
{
  if (num <= 1)
    return false;
  if (num <= 3)
    return true;
  if (num % 2 == 0 || num % 3 == 0)
    return false;
  for (int i = 5; i * i <= num; i += 6)
  {
    if (num % i == 0 || num % (i + 2) == 0)
      return false;
  }
  return true;
}

int main()
{
  vector<int> keys = {12, 44, 13, 88, 23, 94, 11, 39, 20, 16};
  int m = 11;

  HashTable hashTable(m);

  for (int key : keys)
  {
    hashTable.linearProbeInsert(key);
  }

  for (int key : keys)
  {
    hashTable.quadraticProbeInsert(key);
  }

  hashTable.displayTables();
  int table_sizes[] = {11, 13, 17, 19, 23, 29, 31, 37, 41, 43};
  cout << "\nSize\tNumber\tLinear samples\tQuadratic tests" << endl;
  for (int size : table_sizes)
  {
    if (isPrime(size))
    {
      HashTable hashTable(size);
      vector<int> keys(size);
      for (int i = 0; i < size; ++i)
      {
        keys[i] = rand() % (size * 10);
      }

      for (int key : keys)
      {
        hashTable.linearProbeInsert(key);
      }
      int linearCollisions = hashTable.getLinearCollisions();

      hashTable = HashTable(size);
      for (int key : keys)
      {
        hashTable.quadraticProbeInsert(key);
      }
      int quadraticCollisions = hashTable.getQuadraticCollisions();

      cout << size << "\t" << size << "\t" << linearCollisions << "\t\t"
           << quadraticCollisions << endl;
    }
  }

  return 0;
}
