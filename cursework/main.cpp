#include "functions.hpp"
#include "struct.hpp"
using namespace std;
bool HR;
bool VR;

int main()
{
    FILE *fp = fopen("testBase4.dat", "rb");
    record mas3[4000] = {0};

    int readCount = fread((record *)mas3, sizeof(record), 4000, fp);
    record *indexArr[readCount];
    for (int i = 0; i < readCount; i++)
        indexArr[i] = &mas3[i];
    QuickSort(indexArr, 0, 3999);
    char keySearch[30];
    char choice;
    do
    {
        cout << "\n1. All records\n2. Search\n3. Exit\n";
        cin >> choice;
        if (choice == '1')
        {
            displayRecords(indexArr);
        }
        else if (choice == '2')
        {
            Queue *queue = displaySearch(indexArr, readCount);
            vertex *root = nullptr;
            std::cout << "\n-----------------------------------------------------------\n";
            List *temp = queue->head;
            while (temp != nullptr)
            {
                B2INSERT(root, temp->data, VR, HR);
                temp = temp->next;
            }
            work(root);
            queue->clear();
            cin >> keySearch;
            findAllVerticesWithKey(root, keySearch);
        }
        else if (choice != '1' && choice != '2' && choice != '3')
        {
            cout << "Incorrect input" << endl;
        }
    } while (choice != '3');

    return 0;
}
