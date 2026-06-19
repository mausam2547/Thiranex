#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class BankAccount
{
private:
    int accountNumber;
    string name;
    float balance;

public:
    void createAccount()
    {
        cout << "\nEnter Account Number: ";
        cin >> accountNumber;
        cin.ignore();

        cout << "Enter Customer Name: ";
        getline(cin, name);

        cout << "Enter Initial Deposit: ";
        cin >> balance;
    }

    void displayAccount() const
    {
        cout << "\nAccount Number : " << accountNumber;
        cout << "\nCustomer Name  : " << name;
        cout << "\nBalance        : Rs. " << balance << endl;
    }

    int getAccountNumber() const
    {
        return accountNumber;
    }

    float getBalance() const
    {
        return balance;
    }

    void deposit(float amount)
    {
        balance += amount;
        cout << "\nAmount Deposited Successfully!";
    }

    bool withdraw(float amount)
    {
        if (amount > balance)
        {
            cout << "\nInsufficient Balance!";
            return false;
        }

        balance -= amount;
        cout << "\nWithdrawal Successful!";
        return true;
    }

    void saveToFile(ofstream &file)
    {
        file << accountNumber << "|"
             << name << "|"
             << balance << endl;
    }

    void loadFromFile(string line)
    {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);

        accountNumber = stoi(line.substr(0, pos1));
        name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        balance = stof(line.substr(pos2 + 1));
    }
};

// Create Account
void createNewAccount()
{
    BankAccount acc;

    acc.createAccount();

    ofstream file("accounts.txt", ios::app);
    acc.saveToFile(file);
    file.close();

    cout << "\nAccount Created Successfully!\n";
}

// Balance Inquiry
void checkBalance()
{
    int accNo;
    bool found = false;

    cout << "\nEnter Account Number: ";
    cin >> accNo;

    ifstream file("accounts.txt");
    string line;

    while (getline(file, line))
    {
        BankAccount acc;
        acc.loadFromFile(line);

        if (acc.getAccountNumber() == accNo)
        {
            cout << "\nCurrent Balance: Rs. "
                 << acc.getBalance() << endl;
            found = true;
            break;
        }
    }

    if (!found)
        cout << "\nAccount Not Found!\n";

    file.close();
}

// Deposit Money
void depositMoney()
{
    int accNo;
    float amount;
    bool found = false;

    cout << "\nEnter Account Number: ";
    cin >> accNo;

    cout << "Enter Amount to Deposit: ";
    cin >> amount;

    ifstream file("accounts.txt");
    ofstream temp("temp.txt");

    string line;

    while (getline(file, line))
    {
        BankAccount acc;
        acc.loadFromFile(line);

        if (acc.getAccountNumber() == accNo)
        {
            acc.deposit(amount);
            found = true;
        }

        acc.saveToFile(temp);
    }

    file.close();
    temp.close();

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (!found)
        cout << "\nAccount Not Found!\n";
}

// Withdraw Money
void withdrawMoney()
{
    int accNo;
    float amount;
    bool found = false;

    cout << "\nEnter Account Number: ";
    cin >> accNo;

    cout << "Enter Amount to Withdraw: ";
    cin >> amount;

    ifstream file("accounts.txt");
    ofstream temp("temp.txt");

    string line;

    while (getline(file, line))
    {
        BankAccount acc;
        acc.loadFromFile(line);

        if (acc.getAccountNumber() == accNo)
        {
            acc.withdraw(amount);
            found = true;
        }

        acc.saveToFile(temp);
    }

    file.close();
    temp.close();

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (!found)
        cout << "\nAccount Not Found!\n";
}

// Display Account Details
void displayAccount()
{
    int accNo;
    bool found = false;

    cout << "\nEnter Account Number: ";
    cin >> accNo;

    ifstream file("accounts.txt");
    string line;

    while (getline(file, line))
    {
        BankAccount acc;
        acc.loadFromFile(line);

        if (acc.getAccountNumber() == accNo)
        {
            acc.displayAccount();
            found = true;
            break;
        }
    }

    if (!found)
        cout << "\nAccount Not Found!\n";

    file.close();
}

// Main Function
int main()
{
    int choice;

    do
    {
        cout << "\n========== BANK MANAGEMENT SYSTEM ==========\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Check Balance\n";
        cout << "5. Display Account Details\n";
        cout << "6. Exit\n";
        cout << "Enter Your Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            createNewAccount();
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
            displayAccount();
            break;

        case 6:
            cout << "\nThank You for Using Bank Management System!\n";
            break;

        default:
            cout << "\nInvalid Choice! Please Try Again.\n";
        }

    } while (choice != 6);

    return 0;
}