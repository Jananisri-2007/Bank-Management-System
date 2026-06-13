#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

using namespace std;

// Create Account
void createAccount()
{
    int accNo;
    string name;
    double balance;

    cout << "\nEnter Account Number: ";
    cin >> accNo;

    cin.ignore();

    cout << "Enter Customer Name: ";
    getline(cin, name);

    cout << "Enter Initial Balance: ";
    cin >> balance;

    ofstream file("account.txt", ios::app);

    file << accNo << "|"
         << name << "|"
         << balance << endl;

    file.close();

    cout << "\nAccount Created Successfully!\n";
}

// Display All Accounts
void displayAccounts()
{
    ifstream file("account.txt");

    int accNo;
    string name;
    double balance;
    string line;

    cout << "\n========== ACCOUNT LIST ==========\n";

    while (getline(file, line))
    {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);

        accNo = stoi(line.substr(0, pos1));
        name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        balance = stod(line.substr(pos2 + 1));

        cout << "\nAccount No : " << accNo;
        cout << "\nName       : " << name;
        cout << "\nBalance    : " << balance;
        cout << "\n---------------------------";
    }

    file.close();
}

// Search Account
void searchAccount()
{
    int searchNo;
    bool found = false;

    cout << "\nEnter Account Number: ";
    cin >> searchNo;

    ifstream file("account.txt");
    string line;

    while (getline(file, line))
    {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);

        int accNo = stoi(line.substr(0, pos1));
        string name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        double balance = stod(line.substr(pos2 + 1));

        if (accNo == searchNo)
        {
            cout << "\nAccount Found!";
            cout << "\nAccount No : " << accNo;
            cout << "\nName       : " << name;
            cout << "\nBalance    : " << balance << endl;

            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "\nAccount Not Found!\n";
}

// Balance Inquiry
void checkBalance()
{
    int searchNo;
    bool found = false;

    cout << "\nEnter Account Number: ";
    cin >> searchNo;

    ifstream file("account.txt");
    string line;

    while (getline(file, line))
    {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);

        int accNo = stoi(line.substr(0, pos1));
        double balance = stod(line.substr(pos2 + 1));

        if (accNo == searchNo)
        {
            cout << "\nCurrent Balance: " << balance << endl;
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "\nAccount Not Found!\n";
}

// Deposit Money
void depositMoney()
{
    int searchNo;
    double amount;
    bool found = false;

    cout << "\nEnter Account Number: ";
    cin >> searchNo;

    cout << "Enter Amount to Deposit: ";
    cin >> amount;

    ifstream file("account.txt");
    ofstream temp("temp.txt");

    string line;

    while (getline(file, line))
    {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);

        int accNo = stoi(line.substr(0, pos1));
        string name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        double balance = stod(line.substr(pos2 + 1));

        if (accNo == searchNo)
        {
            balance += amount;
            found = true;
        }

        temp << accNo << "|"
             << name << "|"
             << balance << endl;
    }

    file.close();
    temp.close();

    remove("account.txt");
    rename("temp.txt", "account.txt");

    if (found)
        cout << "\nAmount Deposited Successfully!\n";
    else
        cout << "\nAccount Not Found!\n";
}

// Withdraw Money
void withdrawMoney()
{
    int searchNo;
    double amount;
    bool found = false;

    cout << "\nEnter Account Number: ";
    cin >> searchNo;

    cout << "Enter Amount to Withdraw: ";
    cin >> amount;

    ifstream file("account.txt");
    ofstream temp("temp.txt");

    string line;

    while (getline(file, line))
    {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);

        int accNo = stoi(line.substr(0, pos1));
        string name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        double balance = stod(line.substr(pos2 + 1));

        if (accNo == searchNo)
        {
            found = true;

            if (balance >= amount)
            {
                balance -= amount;
                cout << "\nWithdrawal Successful!\n";
            }
            else
            {
                cout << "\nInsufficient Balance!\n";
            }
        }

        temp << accNo << "|"
             << name << "|"
             << balance << endl;
    }

    file.close();
    temp.close();

    remove("account.txt");
    rename("temp.txt", "account.txt");

    if (!found)
        cout << "\nAccount Not Found!\n";
}

// Delete Account
void deleteAccount()
{
    int searchNo;
    bool found = false;

    cout << "\nEnter Account Number to Delete: ";
    cin >> searchNo;

    ifstream file("account.txt");
    ofstream temp("temp.txt");

    string line;

    while (getline(file, line))
    {
        size_t pos1 = line.find('|');

        int accNo = stoi(line.substr(0, pos1));

        if (accNo == searchNo)
        {
            found = true;
            continue;
        }

        temp << line << endl;
    }

    file.close();
    temp.close();

    remove("account.txt");
    rename("temp.txt", "account.txt");

    if (found)
        cout << "\nAccount Deleted Successfully!\n";
    else
        cout << "\nAccount Not Found!\n";
}

int main()
{
    int choice;

    do
    {
        cout << "\n\n================================";
        cout << "\n   BANK MANAGEMENT SYSTEM";
        cout << "\n================================";
        cout << "\n1. Create Account";
        cout << "\n2. Deposit Money";
        cout << "\n3. Withdraw Money";
        cout << "\n4. Balance Inquiry";
        cout << "\n5. Search Account";
        cout << "\n6. Display All Accounts";
        cout << "\n7. Delete Account";
        cout << "\n8. Exit";

        cout << "\n\nEnter Your Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            createAccount();
            break;

        case 2:
            depositMoney();
            break;

        case 3:
            withdrawMoney();
            break;

        case 4:
            checkBalance();
            break;

        case 5:
            searchAccount();
            break;

        case 6:
            displayAccounts();
            break;

        case 7:
            deleteAccount();
            break;

        case 8:
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 8);

    return 0;
}

