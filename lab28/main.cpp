#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <unordered_map>
#include <cmath>
#include <algorithm>
struct codeHuffman
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

int Up(float *&Pi, int n, float x)
{
    int j = 0;
    for (int i = n - 2; i > 0; i--)
    {
        if (Pi[i - 1] < x)
        {
            Pi[i] = Pi[i - 1];
        }
        else
        {
            j = i;
            break;
        }
    }
    Pi[j] = x;
    return j;
}

void Down(codeHuffman *&huffman, int n, int j)
{
    char *S = new char[huffman[j].L + 1];
    for (int i = 0; i < huffman[j].L; i++)
        S[i] = huffman[j].codeword[i];
    S[huffman[j].L] = '\0';

    int L = huffman[j].L;

    for (int i = j; i <= n - 2; i++)
    {
        delete[] huffman[i].codeword;
        huffman[i].codeword = new char[huffman[i + 1].L + 1];
        for (int t = 0; t < huffman[i + 1].L; t++)
            huffman[i].codeword[t] = huffman[i + 1].codeword[t];
        huffman[i].codeword[huffman[i + 1].L] = '\0';
        huffman[i].L = huffman[i + 1].L;
    }

    delete[] huffman[n - 1].codeword;
    delete[] huffman[n].codeword;

    huffman[n - 1].L = L + 1;
    huffman[n].L = L + 1;
    huffman[n - 1].codeword = new char[huffman[n - 1].L + 1];
    huffman[n].codeword = new char[huffman[n].L + 1];

    for (int i = 0; i < L; i++)
    {
        huffman[n - 1].codeword[i] = huffman[n].codeword[i] = S[i];
    }
    huffman[n - 1].codeword[L] = '0';
    huffman[n].codeword[L] = '1';
    huffman[n - 1].codeword[L + 1] = '\0';
    huffman[n].codeword[L + 1] = '\0';

    delete[] S;
}

void HuffmanCode(codeHuffman *&huffman, float *&Pi, int n)
{
    if (n == 2)
    {
        huffman[0].codeword = new char[1];
        huffman[0].codeword[0] = '0';
        huffman[0].L = 1;
        huffman[1].codeword = new char[1];
        huffman[1].codeword[0] = '1';
        huffman[1].L = 1;
    }
    else
    {
        float q = Pi[n - 2] + Pi[n - 1];
        int j = Up(Pi, n, q);
        HuffmanCode(huffman, Pi, n - 1);
        Down(huffman, n - 1, j);
    }
}
codeHuffman *Huffman(chanceSymbol *chanceSymbols, int numSymbols)
{
    codeHuffman *huffman = new codeHuffman[numSymbols];
    float *Pi = new float[numSymbols];

    for (int i = 0; i < numSymbols; i++)
    {
        huffman[i].ch = chanceSymbols[i].ch;
        huffman[i].P = Pi[i] = chanceSymbols[i].chance;
    }

    HuffmanCode(huffman, Pi, numSymbols);

    return huffman;
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
float calculationAverageLength(codeHuffman *A, int nums)
{
    float answer = 0;
    for (int i = 0; i < nums; i++)
    {
        answer += A[i].L * A[i].P;
    }
    return answer;
}
bool craftInequality(codeHuffman *huffman, int n)
{
    float sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += pow(2, -huffman[i].L);
    }
    if (sum <= 1)
        return true;
    else
        return false;
}
std::string encode(codeHuffman *huffman, const char *filename, int num)
{
    std::ifstream file(filename);
    std::string encodedText;
    char character;

    while (file.get(character))
    {
        for (int i = 0; i < num; i++)
        {
            if (huffman[i].ch == character)
            {
                encodedText += huffman[i].codeword;
                break;
            }
        }
    }

    file.close();
    return encodedText;
}
int main()
{
    std::vector<chanceSymbol> symbols;
    std::string filename = "text.txt";

    calculateSymbolChance(filename, symbols);
    std::sort(symbols.begin(), symbols.end(), compare);
    chanceSymbol *chanceSymbols = symbols.data();
    codeHuffman *codeHuffman = Huffman(chanceSymbols, symbols.size());

    std::cout << "Symbol" << std::setw(20) << "Chance symbol" << std::setw(20) << "Code word" << std::setw(30) << "Length code word" << "\n";
    for (size_t i = 0; i < symbols.size(); i++)
    {
        std::cout << codeHuffman[i].ch << std::setw(20) << codeHuffman[i].P << std::setw(20) << codeHuffman[i].codeword << std::setw(30) << codeHuffman[i].L << "\n";
    }

    std::cout << "\n\nCraft's inequality" << std::setw(20) << "Entropy" << std::setw(25) << "Average length" << std::setw(30) << "Redundancy of huffman code\n";
    std::cout << craftInequality(codeHuffman, symbols.size()) << std::setw(37) << calculationEntropy(chanceSymbols, symbols.size()) << std::setw(20) << calculationAverageLength(codeHuffman, symbols.size())
              << std::setw(25) << calculationAverageLength(codeHuffman, symbols.size()) - calculationEntropy(chanceSymbols, symbols.size()) << "\n\n\n";
    std::string encodeStr = encode(codeHuffman, "for_encode", symbols.size());
    std::cout << encodeStr;
    std::cout << "\n\nData compression coefficient: " << encodeStr.size() / 8;
    delete[] codeHuffman;
    return 0;
}
