#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


void SelectSort(vector <string>&A,vector <int>&indA)
{
    int k;
    for (int i=0; i<A.size()-1; i++)
    {
        k = i;
        for (int j=i+1; j<A.size(); j++)
        {
            if (A[indA[j]] < A[indA[k]]) {k = j;}
        }
        
        
        swap(indA[i],indA[k]);
        
    }
   
}
void SelectSortReverse(vector <string>&A,vector <int>&indA)
{
    int k;
    for (int i=0; i<A.size()-1; i++)
    {
        k = i;
        for (int j=i+1; j<A.size(); j++)
        {
            if (A[indA[j]] > A[indA[k]]) {k = j;}
        }
        
        
        swap(indA[i],indA[k]);
        
    }
   
}

void SelectSortSoglas(vector <string>&A,vector <int>&indA)
{
    int k;
    for (int i=0; i<indA.size()-1; i++)
    {
        k = i;
        for (int j=i+1; j<indA.size(); j++)
        {
           
            if (A[indA[j]] < A[indA[k]]) {k = j;}
            
            
        }
        
        
        swap(indA[i],indA[k]);
        
    }
   
}
void SelectSortGlas(vector <string>&A,vector <int>&indA)
{
    int k;
    for (int i=0; i<indA.size()-1; i++)
    {
        k = i;
        for (int j=i+1; j<indA.size(); j++)
        {
           
            if (A[indA[j]] < A[indA[k]]) {k = j;}
            
            
        }
        
        
        swap(indA[i],indA[k]);
        
    }
   
}

void onlysoglas(vector <string> &A, vector <int> &indC, vector<string> &soglas)
{
    for (int i=0;i<A.size();i++)
    {
        if (find(soglas.begin(),soglas.end(),A[i])!=soglas.end()) indC.push_back(i);
    }
}
void onlyglas(vector <string> &A, vector <int> &indD, vector<string> &glas)
{
    for (int i=0;i<A.size();i++)
    {
        if (find(glas.begin(),glas.end(),A[i])!=glas.end()) indD.push_back(i);
    }
}
int main()
{
    vector<string> soglas = {"б",  "в", "г", "д", "ж", "з", "й", "к", "л", "м", "н", "п", "р", "с", "т", "ф", "х", "ц", "ч", "ш", "щ"};
    vector<string> glas = {"а", "у", "о", "и", "э", "ы", "я", "ю", "е", "ё"};
    vector <string>A ={"п","р","о","з","о","р","е","н","к","о","к","о"};
    vector <int>indA;
    for (int i =0;i<A.size();i++)indA.push_back(i);
    for (auto i : A) cout << i << " ";
    cout << "\n";
    for (auto i : indA) cout << i << " ";
    
    cout << "\nПо возрастанию: ";
    SelectSort(A,indA);
    for (auto i : indA) cout << i << " ";
    
    cout << "\nПо убыванию: ";
    vector <int>indB;
    for (int i =0;i<A.size();i++)indB.push_back(i);
    SelectSortReverse(A,indB);
    for (auto i : indB) cout << i << " ";
    
    cout << "\nПо возрастанию согласные: ";
    vector <int>indC;
    onlysoglas(A,indC,soglas);
    SelectSortSoglas(A,indC);
    for (auto i : indC) cout << i << " ";
    
    cout << "\nПо убыванию гласные: ";
    vector <int>indD;
    onlysoglas(A,indD,glas);
    SelectSortGlas(A,indD);
    for (auto i : indD) cout << i << " ";
    return 0;
}