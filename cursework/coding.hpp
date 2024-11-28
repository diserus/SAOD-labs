#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "struct.hpp"
bool compareChances(const chanceSymbol &a, const chanceSymbol &b)
{
    return a.chance > b.chance;
}
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

void calculateProbSymbols(const std::string filename, chanceSymbol *&chanceSymbols, int &numsUnique)
{
    chanceSymbols = new chanceSymbol[256];
    int numsTotal = 0;
    numsUnique = 0;
    for (int i = 0; i < 256; i++)
    {
        chanceSymbols[i].ch = (char)(i - 128);
        chanceSymbols[i].chance = 0;
    }
    FILE *fp;
    fp = fopen("testBase4.dat", "rb");
    while (!feof(fp))
    {
        char c;
        fscanf(fp, "%c", &c);
        if (feof(fp))
            break;
        chanceSymbols[c + 128].chance += 1;
        numsTotal++;
    }
    printf("\n");
    fclose(fp);

    std::sort(chanceSymbols, chanceSymbols + 256, compareChances);
    for (int i = 0; i < 256 && chanceSymbols[i].chance != 0; i++)
    {
        chanceSymbols[i].chance /= numsTotal;
        numsUnique++;
    }
}

float calculationEntropy(chanceSymbol *&A, int nums)
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

float encodeDataBase(codeShannon *code)
{
    int fcompression = 0;
    int cfcompression = 0;
    FILE *fp, *fcoded;
    fp = fopen("testBase4.dat", "rb");
    fcoded = fopen("encoded.dat", "wb");

    char buffer;
    while (!feof(fp))
    {
        fscanf(fp, "%c", &buffer);
        fcompression++;
        for (int i = 0; i < 166; i++)
        {
            if (buffer == (char)(i - 128))
            {
                for (int j = 0; j < code[i].L; j++)
                {
                    putc(code[i].codeword[j], fcoded);
                    cfcompression++;
                }
            }
        }
    }

    fclose(fp);
    fclose(fcoded);
    return (float)fcompression / cfcompression;
}
