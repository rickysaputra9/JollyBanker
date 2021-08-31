
#include "account.h"

// Constructor
Account::Account(string FirstName, string LastName, int ID) :
        FirstName{FirstName}, LastName{LastName}, ID{ID} {
    Check = false;
    FundTypes[0].setFundName("Money Market");
    FundTypes[1].setFundName("Prime Money Market");
    FundTypes[2].setFundName("Long-Term Bond");
    FundTypes[3].setFundName("Short-Term Bond");
    FundTypes[4].setFundName("500 Index Fund");
    FundTypes[5].setFundName("Capital Value Fund");
    FundTypes[6].setFundName("Growth Equity Fund");
    FundTypes[7].setFundName("Growth Index Fund");
    FundTypes[8].setFundName("Value Fund");
    FundTypes[9].setFundName("Value Stock Index");

    for (auto &Fund : FundTypes) {
        Fund.setBalance(0);
    }
}

// Destructor
Account::~Account() = default;

// Returns the first name
string Account::getFirstName() const {
    return FirstName;
}

// Returns the last name
string Account::getLastName() const {
    return LastName;
}

// Returns the name of the fund
string Account::getFundName(int FundsID) const {
    return FundTypes[FundsID].getFundName();
}

// Returns the balance of a specific fund type
int Account::getFundBalance(int FundID) const {
    return FundTypes[FundID].getBalance();
}

// Checks whether it is true or false
bool Account::getInsertCheck() const {
    return Check;
}

// Returns the account number
int Account::getID() const {
    return ID;
}

// Adds an amount of money into a specific fund type
void Account::deposit(int Amount, int FundsID) {
    FundTypes[FundsID].deposit(Amount);
}

// Withdraws an amount of money into a specific fund type
bool Account::withdraw(int Amount, int FundsID) {
    if (FundTypes[FundsID].isWithdrawalEnough(Amount)) {
        FundTypes[FundsID].withdraw(Amount);
        return true;
    } else if (FundsID >= 0 && FundsID <= 3) {
        if (FundsID == 0) {
            if (FundTypes[FundsID].getBalance() + FundTypes[1].getBalance() >= Amount) {
                int Leftover = Amount - FundTypes[FundsID].getBalance();
                FundTypes[FundsID].withdraw(Amount - Leftover);
                FundTypes[1].withdraw(Leftover);
                auto *First = new Transactions('W', ID * 10 + FundsID,
                                               Amount - Leftover);
                auto *Second = new Transactions('W', (ID * 10) + 1, Leftover);
                FundTypes[FundsID].addTransaction(*First);
                FundTypes[1].addTransaction(*Second);
                Check = true;
                return true;
            }
        } else if (FundsID == 1) {
            if (FundTypes[FundsID].getBalance() + FundTypes[0].getBalance() >= Amount) {
                int Leftover = Amount - FundTypes[FundsID].getBalance();
                FundTypes[FundsID].withdraw(Amount - Leftover);
                FundTypes[0].withdraw(Leftover);
                auto *First = new Transactions('W', ID * 10 + FundsID,
                                               Amount - Leftover);
                auto *Second = new Transactions('W', (ID * 10) + 0, Leftover);
                FundTypes[FundsID].addTransaction(*First);
                FundTypes[0].addTransaction(*Second);
                Check = true;
                return true;
            }
        } else if (FundsID == 2) {
            if (FundTypes[FundsID].getBalance() + FundTypes[FundsID + 1].getBalance() >= Amount) {
                int Leftover = Amount - FundTypes[FundsID].getBalance();
                FundTypes[FundsID].withdraw(Amount - Leftover);
                FundTypes[3].withdraw(Leftover);
                auto *First = new Transactions('W', ID * 10 + FundsID,
                                               Amount - Leftover);
                auto *Second = new Transactions('W', (ID * 10) + 3, Leftover);
                FundTypes[FundsID].addTransaction(*First);
                FundTypes[3].addTransaction(*Second);
                Check = true;
                return true;
            }
        } else if (FundsID == 3) {
            if (FundTypes[FundsID].getBalance() + FundTypes[FundsID - 1].getBalance() >= Amount) {
                int Leftover = Amount - FundTypes[FundsID].getBalance();
                FundTypes[FundsID].withdraw(Amount - Leftover);
                FundTypes[2].withdraw(Leftover);
                auto *First = new Transactions('W', ID * 10 + FundsID,
                                               Amount - Leftover);
                auto *Second = new Transactions('W', (ID * 10) + 2, Leftover);
                FundTypes[FundsID].addTransaction(*First);
                FundTypes[2].addTransaction(*Second);
                Check = true;
                return true;
            }
        }
    }
    return false;
}

// Displays the whole transaction history
void Account::printFullHistory() {
    for (const auto &Fund : FundTypes) {
        Fund.printFundHistory();
    }
}

// Displays the transaction history of a specific fund type
void Account::printFundHistory(int FundsID) {
    FundTypes[FundsID].printFundHistory();
}

// Records a fund type transaction
void Account::recordTransaction(const Transactions &Transaction, int FundsID) {
    FundTypes[FundsID].addTransaction(Transaction);
}
