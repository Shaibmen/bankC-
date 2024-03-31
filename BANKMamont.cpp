
#include <iostream>

using namespace std;



class BankAccount { // class banka

private:
    int accountNumber;
    double balance;
    double interestRate;

public:
    BankAccount(int accountNumber, double balance) {
        this->accountNumber = accountNumber;
        this->balance = balance;
        this->interestRate = 0.0;
    }

    void deposit(double amount) {
        if (amount < 0) {
            cout << "Ошибка: невозможно внести отрицательную сумму." << endl;
            return;
        }
        this->balance += amount;
    }

    bool withdraw(double amount) {
        if (amount < 0) {
            cout << "Ошибка: невозможно снять отрицательную сумму." << endl;
            return false;
        }
        if (amount > this->balance) {
            cout<< "Ошибка: недостаточно средств на счете." << endl;
            return false;
        }
        this->balance -= amount;
        return true;
    }

    double getBalance() {
        return this->balance;
    }

    double getInterest() {
        return this->balance * this->interestRate * (1.0 / 12.0);
    }

    void setInterestRate(double interestRate) {
        if (interestRate < 0) {
            cout << "Ошибка: процентная ставка не может быть отрицательной." << endl;
            return;
        }
        this->interestRate = interestRate;
    }
    int getAccountNumber() {
        return this->accountNumber;
    }

    friend bool transfer(BankAccount& from, BankAccount& to, double amount);
};

bool transfer(BankAccount& from, BankAccount& to, double amount) {
    if (amount < 0) {
        cout << "Ошибка: невозможно перевести отрицательную сумму." << endl;
        return false;
    }
    if (from.withdraw(amount)) {
        to.deposit(amount);
        return true;
    }
    return false;
}

//метод для "дурачка"
bool handleInputError() {
    if (cin.fail()) {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout << "Ошибка: введите числовое значение.\n";
        return true; 
    }
    return false; 
}


int main() {

    setlocale(LC_ALL, "RUS");

    BankAccount account(12345, 1000.0);

    account.setInterestRate(0.05);

    BankAccount anotherAccount(67890, 500.0);

    int choice;
    double amount;
    double newInterestRate;


    do {
        cout << "\nВыберите действие:\n";
        cout << "1. Внести средства\n";
        cout << "2. Снять средства\n";
        cout << "3. Перевести средства\n";
        cout << "4. Обновить процентную ставку\n";
        cout << "5. Рассчитать проценты\n";
        cout << "6. Получить номер счета\n";
        cout << "7. Выйти\n";

        cin >> choice;

        if (handleInputError()) continue; 

        switch (choice) {
        case 1:
            cout << "Введите сумму для внесения: ";
            cin >> amount;
            if (handleInputError()) break; 
            account.deposit(amount);
            break;
        case 2:
            cout << "Введите сумму для снятия: ";
            cin >> amount;
            if (handleInputError()) break; 
            account.withdraw(amount);
            break;
        case 3:
            cout << "Введите сумму для перевода: ";
            cin >> amount;
            if (handleInputError()) break;
            transfer(account, anotherAccount, amount);
            break;
        case 4:
            cout << "Введите новую процентную ставку: ";
            cin >> newInterestRate;
            if (handleInputError()) break; 
            account.setInterestRate(newInterestRate);
            break;
        case 5:
            cout << "Проценты по счету: " << account.getInterest() << endl;
            break;
        case 6:
            cout << "Номер счета: " << account.getAccountNumber() << endl;
            break;
        case 7:
            cout << "Выход из программы.\n";
            break;
        default:
            cout << "Неверный выбор. Попробуйте еще раз.\n";
            break;
        }

        cout << "Текущий баланс: " << account.getBalance() << endl;

    } while (choice != 7);

    return 0;
}
