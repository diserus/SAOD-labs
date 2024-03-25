#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

typedef struct
{
    string firstname,lastname,otchestvo,phoneNumber;
} phoneInfo;

bool comprassion(phoneInfo x, phoneInfo y)
{
    if (x.lastname < y.lastname) 
        return true;
    else if (x.lastname > y.lastname)
        return false;
    else 
        return x.phoneNumber < y.phoneNumber;
    
}

void SelectSort(vector <phoneInfo> &phoneBook,vector <int> &indexArray)
{
    int k;
    int n=phoneBook.size();
    for (int i=0; i<n-1; i++)
    {
        k = i;
        for (int j=i+1; j<n; j++)
        {
            if (comprassion(phoneBook[indexArray[j]],phoneBook[indexArray[k]])) k = j;
        }
        
        
        swap(indexArray[i],indexArray[k]);
    }
}

void printTable(vector<phoneInfo> &phoneBook,vector <int> &indexArray)
{
    cout << left << setw(15) << "First name" 
         << setw(15) << "Last name" 
         << setw(15) << "Otchestvo" 
         << setw(15) << "Phone number" << "\n\n";

    for (int i = 0; i < phoneBook.size();i++) 
    {
        cout << left << setw(15) << phoneBook[indexArray[i]].firstname 
             << setw(15) << phoneBook[indexArray[i]].lastname 
             << setw(15) << phoneBook[indexArray[i]].otchestvo 
             << setw(15) << phoneBook[indexArray[i]].phoneNumber << "\n";
    }
    cout << "\n\n";
}

int main()
{
    vector<phoneInfo> phoneBook
    {
        {"Alex","Vaschuk","Alexeevich","88005553535"},
        {"Konstantin","Prozorenko","Vladislavovich","89513929080"},
        {"Voldemarius","Yanenko","Vladimirovich","12345678900"},
        {"Andrey","Prozorenko","Alexeevich","98765432100"}
    }; 
    vector<int> indexArray{0,1,2,3};
    vector<int> indexArray1{0,1,2,3};
    printTable(phoneBook,indexArray);
    SelectSort(phoneBook,indexArray);
    printTable(phoneBook,indexArray);
    return 0;
}