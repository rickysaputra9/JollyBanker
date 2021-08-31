//
// Created by Ricky Saputra on 3/8/2020.
//

#include "fund.h"
#include <iostream>

// Constructor
fund::fund() : Balance{0} {}

// Destructor
fund::~fund() = default;

// Returns the balance of an account
int fund::getBalance() const {
    return Balance;
}

// Sets the balance of an account
bool fund::setBalance(int Amount) {
    Balance = Amount;
    return true;
}

// Returns the name of the fund type
string fund::getFundName() const {
    return FundName;
}

// Sets the name of the fund type
bool fund::setFundName(string Name) {
    FundName = Name;
    return true;
}

// Displays the history of the fund
void fund::printFundHistory() const {
    cout << FundName << ": $" << Balance << endl;

    for (const auto &I : History) {
        cout << "  " << I;
    }
}

// Adds an amount of money to the balance
bool fund::deposit(int Amount){
    Balance += Amount;
    return true;
}

// Reduces an amount of money from the balance
bool fund::withdraw(int Amount){
    if (isWithdrawalEnough(Amount)) {
        Balance -= Amount;
        return true;
    }
    return false;
}

// Checks whether balance is enough to withdraw money or not
bool fund::isWithdrawalEnough(int Amount) const {
    return Balance >= Amount;
}

// Adds a transaction
bool fund::addTransaction(const Transactions& Transaction) {
    History.push_back(Transaction);
    return true;
}

