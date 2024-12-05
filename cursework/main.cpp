#include "functions.hpp"
#include "coding.hpp"
#include "struct.hpp"
#include <iomanip>
using namespace std;
bool HR;
bool VR;

int main()
{
    record mas3[4000] = {0};
    int readCount;  
    record **indexArr = readDataBase(mas3, readCount); 
    QuickSort(indexArr, 0, 3999);
    char keySearch[32];
    char choice;
    Queue *queue = nullptr;
    vertex *root = nullptr;
    bool bSearched = false;
    bool treeCreated = false;
    int numsUnique = 0;
    float compression = 0;
    chanceSymbol *chanceSymbols = nullptr;
    calculateProbSymbols("testBase4.dat", chanceSymbols, numsUnique);

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
            std::cout << "N" << setw(20) << "Symbol" << setw(20) << "Propability" << setw(20) << "Codeword" << setw(20) << "Length\n";

            for (int i = 0; i < numsUnique; i++)
            {
                std::cout << i << setw(20) << codeShanon[i].ch << setw(20) << std::fixed << std::setprecision(10) << codeShanon[i].P << setw(20) << codeShanon[i].codeword << setw(20) << codeShanon[i].L << std::endl;
            }
            std::cout << "\nEntrophy:" << std::fixed << std::setprecision(4) << calculationEntropy(chanceSymbols, numsUnique) << "\n";
            std::cout << "\nRedundancy: " << std::fixed << std::setprecision(4) << calculationAverageLength(codeShanon, numsUnique) - calculationEntropy(chanceSymbols, numsUnique) << "\n";
            compression = encodeDataBase(codeShanon);
            std::cout << "Compression: " << compression;
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

    for (int i = 0; i < numsUnique; i++)
    {
        delete[] codeShanon[i].codeword; // Освобождаем память для кодовых слов
    }
    delete[] codeShanon;
    delete[] indexArr;
    delete[] chanceSymbols;
    return 0;
}
