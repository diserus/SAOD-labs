#include "functions.hpp"
#include "coding.hpp"
#include "struct.hpp"
#include <iomanip>
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
    char keySearch[32];
    char choice;
    Queue *queue = nullptr;
    vertex *root = nullptr;
    bool bSearched = false;
    bool treeCreated = false;
    int numsUnique;
    std::vector<chanceSymbol> symbols;
    calculateProbSymbols("testBase4.dat", symbols, numsUnique);
    std::sort(symbols.begin(), symbols.end(), compareChances);
    chanceSymbol *chanceSymbols = symbols.data();
    codeShannon *codeShanon = ShannonCode(numsUnique, chanceSymbols);
    do
    {
        cout << "\n1. All records\n2. Search\n3. Tree\n4. Search in tree\n5. Encode\n6. Exit\n";
        std::cin >> choice;
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

            std::cin.ignore();
            std::cin.getline(keySearch, sizeof(keySearch));
            treeSearch(root, keySearch);
        }
        else if (choice == '5')
        {
            std::cout << "Symbol" << std::setw(20) << "Chance symbol" << std::setw(20) << "Code word" << std::setw(30) << "Length code word" << "\n";
            for (int i = 0; i < numsUnique; i++)
            {
                std::cout << codeShanon[i].ch << std::setw(20) << codeShanon[i].P << std::setw(20) << codeShanon[i].codeword << std::setw(30) << codeShanon[i].L << "\n";
            }
        }
        else if (choice == '1' && choice == '2' && choice == '3' && choice == '4' && choice == '5' && choice == '6')
        {
            system("cls");
            cout << "Incorrect input" << endl;
        }
    } while (choice != '6');
    std::cout << "Queue: " << queue->size << "\n";
    std::cout << "Tree: " << sizeTree(root) << "\n";
    queue->clear();
    delete codeShanon;
    return 0;
}
