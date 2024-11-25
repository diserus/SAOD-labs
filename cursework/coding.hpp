#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "struct.hpp"

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

void calculateProbSymbols(const std::string filename, std::vector<chanceSymbol> &chanceSymbols, int &numsUnique)
{
    int windows866[256] = {0};
    int totalNums = 0;
    char ch;

    std::fstream file(filename, std::ios::in | std::ios::binary);
    if (!file.is_open())
    {
        std::cout << "Error opening file";
        exit(1);
    }

    while (file.read((char *)&ch, sizeof(ch)))
    {
        totalNums++;
        if (int(ch) < 0)
            windows866[int(ch) + 256]++;
        else
            windows866[int(ch)]++;
    }
    file.close();

    numsUnique = 0;
    for (int i = 0; i < 256; i++)
    {
        if (windows866[i] != 0)
        {
            numsUnique++;
            chanceSymbol symbol;
            symbol.ch = char(i);
            symbol.chance = (float)windows866[i] / (float)totalNums;
            chanceSymbols.push_back(symbol);
        }
    }
}

bool compareChances(const chanceSymbol &a, const chanceSymbol &b)
{
    return a.chance > b.chance;
}
