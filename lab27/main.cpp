#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <unordered_map>
#include <cmath>
#include <algorithm>
struct codeFano
{
    char ch = 0;
    float P = 0;
    int L = 0;
    char *codeword = nullptr;
};
struct chanceSymbol
{
    char ch = 0;
    float chance = 0;
};
int med(int L, int R, codeFano *fano)
{
    float SumL = 0;
    for (int i = L; i < R; i++)
    {
        SumL = SumL + fano[i].P;
    }
    float SumR = fano[R].P;
    int m = R;
    while (SumL >= SumR)
    {
        m = m - 1;
        SumL = SumL - fano[m].P;
        SumR = SumR + fano[m].P;
    }
    return m;
}

void Fano(int L, int R, int k, codeFano *&fano)
{

    if (L < R)
    {
        k = k + 1;
        int m = med(L, R, fano);

        for (int i = L; i <= R; i++)
        {
            if (fano[i].codeword != nullptr)
            {
                char *temp = new char[k];
                for (int j = 0; j < k - 1; j++)
                    temp[j] = fano[i].codeword[j];
                delete[] fano[i].codeword;
                fano[i].codeword = temp;
            }
            else
                fano[i].codeword = new char[k];
            if (i <= m)
            {
                fano[i].codeword[k - 1] = '0';
                fano[i].L = fano[i].L + 1;
            }
            else
            {
                fano[i].codeword[k - 1] = '1';
                fano[i].L = fano[i].L + 1;
            }
            fano[i].codeword[fano[i].L] = '\0';
        }
        Fano(L, m, k, fano);
        Fano(m + 1, R, k, fano);
    }
}
codeFano *FanoCode(chanceSymbol *&chanceSymbols, int numSymbols)
{
    codeFano *fano = new codeFano[numSymbols];
    for (int i = 0; i < numSymbols; i++)
    {
        fano[i].ch = chanceSymbols[i].ch;
        fano[i].P = chanceSymbols[i].chance;
    }
    Fano(0, numSymbols - 1, 0, fano);
    return fano;
}
std::string encode(codeFano *fano, const char *filename, int num)
{
    std::ifstream file(filename);
    std::string encodedText;
    char character;

    while (file.get(character))
    {
        for (int i = 0; i < num; i++)
        {
            if (fano[i].ch == character)
            {
                encodedText += fano[i].codeword;
                break;
            }
        }
    }

    file.close();
    return encodedText;
}
void calculateSymbolChance(const std::string &filename, std::vector<chanceSymbol> &symbols)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return;
    }

    std::unordered_map<char, float> frequency;
    int totalCharacters = 0;
    char ch;
    while (file.get(ch))
    {
        frequency[ch]++;
        totalCharacters++;
    }

    for (const auto &pair : frequency)
    {
        chanceSymbol symbol;
        symbol.ch = pair.first;
        symbol.chance = static_cast<float>(pair.second) / totalCharacters;
        symbols.push_back(symbol);
    }

    file.close();
}
bool compare(const chanceSymbol &a, const chanceSymbol &b)
{
    return a.chance > b.chance;
}
float calculationEntropy(chanceSymbol *A, int nums)
{
    float answer = 0;
    for (int i = 0; i < nums; i++)
    {
        answer += (A[i].chance * log2(A[i].chance));
    }
    return -answer;
}
float calculationAverageLength(codeFano *A, int nums)
{
    float answer = 0;
    for (int i = 0; i < nums; i++)
    {
        answer += A[i].L * A[i].P;
    }
    return answer;
}
bool craftInequality(codeFano *fano, int n)
{
    float sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += pow(2, -fano[i].L);
    }
    if (sum <= 1)
        return true;
    else
        return false;
}
int main()
{
    std::vector<chanceSymbol> symbols;
    std::string filename = "text.txt";

    calculateSymbolChance(filename, symbols);
    std::sort(symbols.begin(), symbols.end(), compare);
    chanceSymbol *chanceSymbols = symbols.data();
    codeFano *codeFano = FanoCode(chanceSymbols, symbols.size());
    std::cout << "Symbol" << std::setw(20) << "Chance symbol" << std::setw(20) << "Code word" << std::setw(30) << "Length code word" << "\n";
    for (size_t i = 0; i < symbols.size(); i++)
    {
        std::cout << codeFano[i].ch << std::setw(20) << codeFano[i].P << std::setw(20) << codeFano[i].codeword << std::setw(30) << codeFano[i].L << "\n";
    }

    std::cout << "\n\nCraft's inequality" << std::setw(20) << "Entropy" << std::setw(25) << "Average length" << std::setw(30) << "Redundancy of Fano code\n";
    std::cout << craftInequality(codeFano, symbols.size()) << std::setw(37) << calculationEntropy(chanceSymbols, symbols.size()) << std::setw(20) << calculationAverageLength(codeFano, symbols.size())
              << std::setw(25) << calculationAverageLength(codeFano, symbols.size()) - calculationEntropy(chanceSymbols, symbols.size()) << "\n\n\n";
    delete[] codeFano;
    return 0;
}
