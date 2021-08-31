//
// Created by Ricky Saputra on 3/8/20.
//

#ifndef BANKER_FUND_H
#define BANKER_FUND_H

#include <string>
#include <vector>
#include "transaction.h"

using namespace std;

class fund {
public:
    // Constructor
    fund();

    // Destructor
    ~fund();

    // Returns the balance of an account
    int getBalance() const;

    // Returns true or false and sets the balance of an account
    bool setBalance(int Amount);

    // Returns the name of the fund type
    string getFundName() const;

    // Sets the name of the fund type
    bool setFundName(string Name);

    // Displays the history of the fund
    void printFundHistory() const;

    // Adds an amount of money
    bool deposit(int Amount);

    // Withdraws an amount of money
    bool withdraw(int Amount);

    // Checks whether the money is enough to withdraw or not
    bool isWithdrawalEnough(int Amount) const;

    // Adds the transaction
    bool addTransaction(const Transactions &Transaction);

private:
    string FundName;
    int Balance;
    vector<Transactions> History;
};


#endif //BANKER_FUND_H
