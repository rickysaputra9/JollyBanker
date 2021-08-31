//
// Created by Ricky Saputra on 3/8/2020
//

#pragma once

#include "accounttree.h"
#include "transaction.h"
#include <vector>
#include <queue>
#include <fstream>
#include <string>

using namespace std;

class Bank {
  public:
    //Constructor
    Bank();

    //Destructor
    ~Bank();

    //Runs and processes all the transactions
    void readTransactions(const string& fileName);

    //Displays all the processed transactions
    void displayAllBankBalances() const;

    // Runs and processes all the transactions
    void processTransactions();

  private:
    AccountTree accounts;
    queue <Transactions> Transaction;
};
