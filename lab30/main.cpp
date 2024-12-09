#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
const int t = 256;
const int w = 1283;
std::vector<int> rabinKarpSearch(std::string &text, std::string &substr, int &comparisons)
{
    std::vector<int> indexes;
    int tlen = text.length();

    int plen = substr.length();

    int flag;
    int c = 1, i = 0;

    int hash_p = 0, hash = 0;
    while (i < plen)
    {
        hash_p = (hash_p * t + substr[i]) % w;
        hash = (hash * t + text[i]) % w;
        i++;
    }

    for (int i = 1; i <= plen - 1; i++)
        c = (c * t) % w;

    i = 0;
    while (i <= tlen - plen)
    {
        if (hash_p == hash)
        {
            flag = 1;
            for (int j = 0; j < plen; j++)
            {
                comparisons++;
                if (substr[j] == text[i + j])
                {
                    continue;
                }
                else
                {
                    flag = 0;
                    break;
                }
            }
            if (flag == 1)
                indexes.push_back(i);
        }

        if (i < tlen - plen)
        {
            hash = ((t * (hash - text[i] * c)) + text[i + plen]) % w;
            if (hash < 0)
            {
                hash = hash + w;
            }
        }
        i++;
    }
    return indexes;
}
std::vector<int> bruteForceSearch(const std::string &text, const std::string &substr, int &comparisons)
{
    std::vector<int> occurrences;
    comparisons = 0;

    for (size_t i = 0; i <= text.length() - substr.length(); ++i)
    {
        bool match = true;
        for (size_t j = 0; j < substr.length(); ++j)
        {
            comparisons++;
            if (text[i + j] != substr[j])
            {
                match = false;
                break;
            }
        }

        if (match)
        {
            occurrences.push_back(i);
        }
    }

    return occurrences;
}
int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    std::string text = "Theme of the day is the theme of the day is the theme of the day";
    std::string substr = "is";
    int comparisons = 0;
    std::vector<int> indexes = bruteForceSearch(text, substr, comparisons);
    std::cout << "Текст: " << text << std::endl;
    std::cout << "Подстрока: " << substr << std::endl;
    std::cout << "Индексы: ";
    for (int index : indexes)
        std::cout << index << " ";
    std::cout << "\nКоличество сравнений: " << comparisons << std::endl;
    comparisons = 0;
    indexes = rabinKarpSearch(text, substr, comparisons);
    std::cout << "\n\nТекст: " << text << std::endl;
    std::cout << "Подстрока: " << substr << std::endl;
    std::cout << "Индексы: ";
    for (int index : indexes)
        std::cout << index << " ";
    std::cout << "\nКоличество сравнений: " << comparisons << std::endl;
    return 0;
}
