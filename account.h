//
// Created by Ricky Saputra on 3/8/2020
//

#pragma once

#include "fund.h"
#include "transaction.h"
#include <vector>
#include <iostream>

using namespace std;

class Account {
public:
    //Constructor
    Account(string FirstName, string LastName, int ID);

    // Destructor
    ~Account();

    // Returns the first name
    string getFirstName() const;

    // Returns the last name
    string getLastName() const;

    // Returns the Account number
    int getID() const;

    // Returns the name of the fund
    string getFundName(int FundsID) const;

    // Returns the balance of a specific fund type
    int getFundBalance(int FundsID) const;

    // Adds an amount of money
    void deposit(int Amount, int FundsID);

    // Takes an amount of money
    bool withdraw(int Amount, int FundsID);

    // Displays the whole transaction history
    void printFullHistory();

    // Displays the transaction history of a specific fund type
    void printFundHistory(int FundsID);

    // Records Transaction
    void recordTransaction(const Transactions &Transaction, int FundsID);

    // Checks whether it is true or false
    bool getInsertCheck() const;

private:
    string FirstName, LastName;
    int ID;
    fund FundTypes[10];
    bool Check;
};
