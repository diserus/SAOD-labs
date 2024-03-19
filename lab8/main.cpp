#include <vector>
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;

typedef struct
{
    string firstname,lastname,otchestvo,phoneNumber;
} phoneInfo;

bool comprassion(phoneInfo x, phoneInfo y,int &fKey,int &sKey,bool &reverse)
{
    string fKeyPole1 ,fKeyPole2, sKeyPole1,sKeyPole2 ;
    switch(fKey)
    {
        case 1: {fKeyPole1 = x.firstname;fKeyPole2 = y.firstname; break;}
        case 2: {fKeyPole1 = x.lastname;fKeyPole2 = y.lastname; break;}
        case 3: {fKeyPole1 = x.otchestvo;fKeyPole2 = y.otchestvo; break;}
        case 4: {fKeyPole1 = x.phoneNumber;fKeyPole2 = y.phoneNumber; break;}
    }
    switch(sKey)
    { 
        case 1: {sKeyPole1 = x.firstname; sKeyPole2 = y.firstname; break;}
        case 2: {sKeyPole1 = x.lastname; sKeyPole2 = y.lastname; break;}
        case 3: {sKeyPole1 = x.otchestvo; sKeyPole2 = y.otchestvo; break;}
        case 4: {sKeyPole1 = x.phoneNumber; sKeyPole2 = y.phoneNumber; break;}
    }
    if (reverse)
    {
        if (fKeyPole1 > fKeyPole2) 
            return true;
        else if (fKeyPole1 < fKeyPole2)
            return false;
        else 
            return sKeyPole1 > sKeyPole2;
    }
    else
    {
        if (fKeyPole1 < fKeyPole2) 
            return true;
        else if (fKeyPole1 > fKeyPole2)
            return false;
        else 
            return sKeyPole1 < sKeyPole2;
    }
}

void SelectSort(vector <phoneInfo> &phoneBook,int &fKey,int &sKey,bool &reverse)
{
    int k;
    int n=phoneBook.size();
    for (int i=0; i<n-1; i++)
    {
        k = i;
        for (int j=i+1; j<n; j++)
        {
            if (comprassion(phoneBook[j],phoneBook[k],fKey,sKey,reverse)) k = j;
        }
        
        
        swap(phoneBook[i],phoneBook[k]);
    }
}
void printTable(vector<phoneInfo> &phoneBook)
{
    cout << left << setw(15) << "First name" 
         << setw(15) << "Last name" 
         << setw(15) << "Otchestvo" 
         << setw(15) << "Phone number" << "\n\n";

    for (auto phoneInfo : phoneBook) 
    {
        cout << left << setw(15) << phoneInfo.firstname 
             << setw(15) << phoneInfo.lastname 
             << setw(15) << phoneInfo.otchestvo 
             << setw(15) << phoneInfo.phoneNumber << "\n";
    }
    cout << "\n";
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
    printTable(phoneBook);
    cout << "Default sort key: last name and phone number\n\n";
    cout << "Do you want to change a key(1 or 0)?";
    int ans,fKey=2,sKey=4;
    
    cin >> ans;
    if (ans==1)
    {
        ans=0;
        cout << "Choose first key:\n" << "1. First name\n2. Last name\n3. Otchestvo\n4. Phone number\n";
        cin >> ans;
        switch(ans)
        {
            case 1: {fKey=1; break;}
            case 2: {fKey=2; break;}
            case 3: {fKey=3; break;}
            case 4: {fKey=4; break;}
        }
        cout << "Choose second key:\n" << "1. First name\n2. Last name\n3. Otchestvo\n4. Phone number\n";
        cin >> ans;
        switch(ans)
        {
            case 1: {sKey=1; break;}
            case 2: {sKey=2; break;}
            case 3: {sKey=3; break;}
            case 4: {sKey=4; break;}
        }
    }
    bool reverse = true;
    SelectSort(phoneBook,fKey,sKey,reverse);
    printTable(phoneBook);
    return 0;
}