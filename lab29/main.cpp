#include <iostream>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <unordered_map>
#include <Windows.h>
#include <locale>

struct codeGilbert
{
    char ch = 0;
    float P = 0;  // вероятность символа
    float Q = 0;  // величина Q для кодирования
    int L = 0;    // длина кодового слова
    char *codeword = nullptr;  // кодовое слово
};

struct chanceSymbol
{
    char ch = 0;
    float chance = 0;
};

codeGilbert *GilbertCode(int numAlphabet, chanceSymbol *&chanceSymbols)
{
    codeGilbert *Gilbert = new codeGilbert[numAlphabet];
    float pr = 0; 

    for (int i = 0; i < numAlphabet; i++)
    {
        Gilbert[i].ch = chanceSymbols[i].ch;
        Gilbert[i].P = chanceSymbols[i].chance;
        Gilbert[i].L = -floor(log2(Gilbert[i].P)) + 1;
        Gilbert[i].Q = pr + Gilbert[i].P / 2;  
        pr = pr + Gilbert[i].P;  
    }

    for (int i = 0; i < numAlphabet; i++)
    {
        Gilbert[i].codeword = new char[Gilbert[i].L + 1];
        float q = Gilbert[i].Q;
        for (int j = 0; j < Gilbert[i].L; j++)
        {
            q = q * 2;  
            Gilbert[i].codeword[j] = (char)(floor(q) + '0'); 
            if (q >= 1)  
            {
                q = q - 1; 
            }
        }
        Gilbert[i].codeword[Gilbert[i].L] = '\0';
    }

    return Gilbert;
}

std::string encode(codeGilbert *Gilbert, const char *filename, int num)
{
    std::ifstream file(filename);
    std::string encodedText;
    char character;

    while (file.get(character))
    {
        for (int i = 0; i < num; i++)
        {
            if (Gilbert[i].ch == character)
            {
                encodedText += Gilbert[i].codeword;
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

float calculationAverageLength(codeGilbert *A, int nums)
{
    float answer = 0;
    for (int i = 0; i < nums; i++)
    {
        answer += A[i].L * A[i].P;
    }
    return answer;
}

bool craftInequality(codeGilbert *gilbert, int n)
{
    float sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += pow(2, -gilbert[i].L);
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
    codeGilbert *gilbert = GilbertCode(symbols.size(), chanceSymbols);
    std::cout << "Symbol" << std::setw(20) << "Chance symbol" << std::setw(20) << "Code word" << std::setw(30) << "Length code word" << "\n";
    for (size_t i = 0; i < symbols.size(); i++)
    {
        std::cout << gilbert[i].ch << std::setw(20) << gilbert[i].P << std::setw(20) << gilbert[i].codeword << std::setw(30) << gilbert[i].L << "\n";
    }
    std::cout << "\n\nCraft's inequality" << std::setw(20) << "Entropy" << std::setw(25) << "Average length" << std::setw(30) << "Redundancy of gilbert code\n";
    std::cout << craftInequality(gilbert, symbols.size()) << std::setw(37) << calculationEntropy(chanceSymbols, symbols.size()) << std::setw(20) << calculationAverageLength(gilbert, symbols.size())
              << std::setw(25) << calculationAverageLength(gilbert, symbols.size()) - calculationEntropy(chanceSymbols, symbols.size()) << "\n\n\n";

    std::string encodeStr = encode(gilbert, "for_encode", symbols.size());
    std::cout << encodeStr;
    std::cout << "\n\nData compression coefficient: " << encodeStr.size() / 8;
    delete[] gilbert;
    return 0;
}
