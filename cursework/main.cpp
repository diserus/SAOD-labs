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
    Queue *queue = nullptr;
    vertex *root = nullptr;
    bool bSearched = false;
    bool treeCreated = false;
    do
    {
        cout << "\n1. All records\n2. Search\n3. Tree\n4. Search in tree\n5. Exit\n";
        cin >> choice;
        if (choice == '1')
        {
            system("cls");
            displayRecords(indexArr);
        }
        else if (choice == '2')
        {
            system("cls");
            queue = displaySearch(indexArr, readCount);
            bSearched = true;
        }
        else if (choice == '3')
        {
            system("cls");
            if (bSearched == false)
            {
                delTree(root);
                queue = displaySearch(indexArr, readCount);
            }
            List *temp = queue->head;
            while (temp != nullptr)
            {
                B2INSERT(root, temp->data, VR, HR);
                temp = temp->next;
            }
            work(root);
            treeCreated = true;
        }
        else if (choice == '4')
        {
            system("cls");
            if (treeCreated == false)
            {
                delTree(root);
                queue = displaySearch(indexArr, readCount);
                List *temp = queue->head;
                while (temp != nullptr)
                {
                    B2INSERT(root, temp->data, VR, HR);
                    temp = temp->next;
                }
                work(root);
            }
            std::cout << "Input a search key: ";
            cin >> keySearch;
            treeSearch(root, keySearch);
        }
        else if (choice == '1' && choice == '2' && choice == '3' && choice == '4' && choice == '5')
        {
            system("cls");
            cout << "Incorrect input" << endl;
        }
    } while (choice != '5');
    std::cout << "Queue: " << queue->size << "\n";
    std::cout << "Tree: " << sizeTree(root) << "\n";
    queue->clear();
    return 0;
}
