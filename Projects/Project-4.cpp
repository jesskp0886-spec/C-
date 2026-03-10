#include <iostream>
using namespace std;

void copyString(char* dest, const char* src, int maxSize) {
    int i = 0;
    while (src[i] != '\0' && i < maxSize - 1) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

class BankAccount {
protected:
    char accountNumber[30];
    char accountHolderName[50];
    double balance;

public:
    BankAccount() {
        accountNumber[0] = '\0';
        accountHolderName[0] = '\0';
        balance = 0.0;
    }

    BankAccount(const char* num, const char* name, double bal) {
        copyString(accountNumber, num, 30);
        copyString(accountHolderName, name, 50);
        balance = bal;
    }

    virtual ~BankAccount() {}

    void deposit(double amount) {
        if (amount > 0) balance += amount;
    }

    virtual void withdraw(double amount) {
        if (amount > 0 && amount <= balance) balance -= amount;
        else cout << "Insufficient balance.\n";
    }

    double getBalance() const { return balance; }

    virtual void displayAccountInfo() const {
        cout << "Account Number : " << accountNumber << endl;
        cout << "Holder Name    : " << accountHolderName << endl;
        cout << "Balance        : " << balance << endl;
    }

    virtual void calculateInterest() const {
        cout << "No interest for base account.\n";
    }
};

class SavingsAccount : public BankAccount {
private:
    double interestRate;

public:
    SavingsAccount() : BankAccount() { interestRate = 0.0; }

    SavingsAccount(const char* num, const char* name, double bal, double rate)
        : BankAccount(num, name, bal) {
        interestRate = rate;
    }

    void calculateInterest() const {
        double interest = balance * interestRate / 100.0;
        cout << "Savings Interest: " << interest << endl;
    }
};

class CheckingAccount : public BankAccount {
private:
    double overdraftLimit;

public:
    CheckingAccount() : BankAccount() { overdraftLimit = 0.0; }

    CheckingAccount(const char* num, const char* name, double bal, double limit)
        : BankAccount(num, name, bal) {
        overdraftLimit = limit;
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance + overdraftLimit) {
            balance -= amount;
        } else {
            cout << "Overdraft limit exceeded.\n";
        }
    }
};

class FixedDepositAccount : public BankAccount {
private:
    int durationMonths;
    double interestRate;

public:
    FixedDepositAccount() : BankAccount() {
        durationMonths = 0;
        interestRate = 0.0;
    }

    FixedDepositAccount(const char* num, const char* name, double bal, int months, double rate)
        : BankAccount(num, name, bal) {
        durationMonths = months;
        interestRate = rate;
    }

    void calculateInterest() const {
        double interest = balance * interestRate * durationMonths / 12.0 / 100.0;
        cout << "Fixed Deposit Interest: " << interest << endl;
    }
};

int main() {
    BankAccount* accounts[10];
    int count = 0;
    int choice;

    do {
        cout << "\n--- Bank Account Menu ---\n";
        cout << "1. Create Savings Account\n";
        cout << "2. Create Checking Account\n";
        cout << "3. Create Fixed Deposit Account\n";
        cout << "4. Display All Accounts\n";
        cout << "5. Deposit\n";
        cout << "6. Withdraw\n";
        cout << "7. Calculate Interest\n";
        cout << "8. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(1000, '\n');

        if (choice == 1) {
            char num[30], name[50];
            double bal, rate;
            cout << "Enter Account Number: "; cin.getline(num, 30);
            cout << "Enter Holder Name: "; cin.getline(name, 50);
            cout << "Enter Balance: "; cin >> bal;
            cout << "Enter Interest Rate (%): "; cin >> rate; cin.ignore(1000, '\n');
            accounts[count++] = new SavingsAccount(num, name, bal, rate);
        }
        else if (choice == 2) {
            char num[30], name[50];
            double bal, limit;
            cout << "Enter Account Number: "; cin.getline(num, 30);
            cout << "Enter Holder Name: "; cin.getline(name, 50);
            cout << "Enter Balance: "; cin >> bal;
            cout << "Enter Overdraft Limit: "; cin >> limit; cin.ignore(1000, '\n');
            accounts[count++] = new CheckingAccount(num, name, bal, limit);
        }
        else if (choice == 3) {
            char num[30], name[50];
            double bal, rate;
            int months;
            cout << "Enter Account Number: "; cin.getline(num, 30);
            cout << "Enter Holder Name: "; cin.getline(name, 50);
            cout << "Enter Balance: "; cin >> bal;
            cout << "Enter Duration (months): "; cin >> months;
            cout << "Enter Interest Rate (%): "; cin >> rate; cin.ignore(1000, '\n');
            accounts[count++] = new FixedDepositAccount(num, name, bal, months, rate);
        }
        else if (choice == 4) {
            for (int i = 0; i < count; i++) {
                cout << "\n--- Account " << i + 1 << " ---\n";
                accounts[i]->displayAccountInfo();
            }
        }
        else if (choice == 5) {
            int index;
            double amount;
            cout << "Enter account index (1-" << count << "): ";
            cin >> index;
            cout << "Enter amount: ";
            cin >> amount;
            cin.ignore(1000, '\n');
            if (index >= 1 && index <= count) accounts[index - 1]->deposit(amount);
        }
        else if (choice == 6) {
            int index;
            double amount;
            cout << "Enter account index (1-" << count << "): ";
            cin >> index;
            cout << "Enter amount: ";
            cin >> amount;
            cin.ignore(1000, '\n');
            if (index >= 1 && index <= count) accounts[index - 1]->withdraw(amount);
        }
        else if (choice == 7) {
            int index;
            cout << "Enter account index (1-" << count << "): ";
            cin >> index;
            cin.ignore(1000, '\n');
            if (index >= 1 && index <= count) accounts[index - 1]->calculateInterest();
        }

    } while (choice != 8);

    for (int i = 0; i < count; i++) delete accounts[i];
    return 0;
}
