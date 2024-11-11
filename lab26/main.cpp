#include <iostream>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <unordered_map>
#include <Windows.h>
struct codeShannon
{
    char ch = 0;
    float P = 0;
    float Q = 0;
    int L = 0;
    char *codeword = nullptr;
};
struct chanceSymbol
{
    char ch = 0;
    float chance = 0;
};
codeShannon *ShannonCode(int numAlphabet, chanceSymbol *&chanceSymbols)
{
    codeShannon *shannon = new codeShannon[numAlphabet];
    float cumulativeProbability = 0;

    for (int i = 0; i < numAlphabet; i++)
    {
        shannon[i].ch = chanceSymbols[i].ch;
        shannon[i].P = chanceSymbols[i].chance;

        shannon[i].L = (int)ceil(log2(1 / shannon[i].P));

        shannon[i].Q = cumulativeProbability;
        cumulativeProbability += shannon[i].P;
    }

    for (int i = 0; i < numAlphabet; i++)
    {
        float temp = shannon[i].Q;
        shannon[i].codeword = new char[shannon[i].L + 1];

        for (int j = 0; j < shannon[i].L; j++)
        {
            temp = temp * 2;
            shannon[i].codeword[j] = (char)(floor(temp) + '0');

            if (temp >= 1)
            {
                temp -= 1;
            }
        }
        shannon[i].codeword[shannon[i].L] = '\0';
    }

    return shannon;
}
std::string encode(codeShannon *shannon, const char *filename, int num)
{
    std::ifstream file(filename);
    std::string encodedText;
    char character;

    while (file.get(character))
    {
        for (int i = 0; i < num; i++)
        {
            if (shannon[i].ch == character)
            {
                encodedText += shannon[i].codeword;
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
float calculationAverageLength(codeShannon *A, int nums)
{
    float answer = 0;
    for (int i = 0; i < nums; i++)
    {
        answer += A[i].L * A[i].P;
    }
    return answer;
}
bool craftInequality(codeShannon *shenon, int n)
{
    float sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += pow(2, -shenon[i].L);
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
    codeShannon *codeShanon = ShannonCode(symbols.size(), chanceSymbols);

    std::cout << "Symbol" << std::setw(20) << "Chance symbol" << std::setw(20) << "Code word" << std::setw(30) << "Length code word" << "\n";
    for (size_t i = 0; i < symbols.size(); i++)
    {
        std::cout << codeShanon[i].ch << std::setw(20) << codeShanon[i].P << std::setw(20) << codeShanon[i].codeword << std::setw(30) << codeShanon[i].L << "\n";
    }

    std::cout << "\n\nCraft's inequality" << std::setw(20) << "Entropy" << std::setw(25) << "Average length" << std::setw(30) << "Redundancy of Shenon code\n";
    std::cout << craftInequality(codeShanon, symbols.size()) << std::setw(37) << calculationEntropy(chanceSymbols, symbols.size()) << std::setw(20) << calculationAverageLength(codeShanon, symbols.size())
              << std::setw(25) << calculationAverageLength(codeShanon, symbols.size()) - calculationEntropy(chanceSymbols, symbols.size()) << "\n\n\n";

    std::string encodeStr = encode(codeShanon, "for_encode", symbols.size());
    std::cout << encodeStr;
    std::cout << "\n\nData compression coefficient: " << encodeStr.size() / 8;
    delete[] codeShanon;
    return 0;
}
