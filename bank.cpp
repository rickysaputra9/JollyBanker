//
// Created by Ricky Saputra on 3/8/2020
//

#include <sstream>
#include "bank.h"

// empty

Bank::Bank() = default;

Bank::~Bank() = default;

void Bank::readTransactions(const string& fileName) {
    ifstream FileIn(fileName);
    string String;

    while (getline(FileIn, String)) {
        istringstream Line(String);
        char TransactionChar;
        Line >> TransactionChar;

        if (TransactionChar == 'O') {
            string LastName, FirstName;
            int ID;
            Line >> LastName >> FirstName >> ID;
            Transactions Temp(TransactionChar, LastName, FirstName, ID);
            Transaction.push(Temp);

        } else if (TransactionChar == 'D' || TransactionChar == 'W') {
            int ID, Amount;
            Line >> ID >> Amount;
            Transactions Temp(TransactionChar, ID, Amount);
            Transaction.push(Temp);

        } else if (TransactionChar == 'T') {
            int ID, Amount, DestinationID;
            Line >> ID >> Amount >> DestinationID;
            Transactions Temp(TransactionChar, ID, Amount, DestinationID);
            Transaction.push(Temp);

        } else if (TransactionChar == 'H') {
            int ID;
            Line >> ID;
            Transactions Temp(TransactionChar, ID);
            Transaction.push(Temp);

        } else {
            cout << "Invalid Transaction Type!" << endl;
        }
    }
}

// Displays all the processed transactions
void Bank::displayAllBankBalances() const {
    cout << "\nProcessing Done. Final Balances." << endl;
    accounts.display();
}

// Runs and processes the transactions
void Bank::processTransactions() {
    while (!Transaction.empty()) {

        Transactions Temp = Transaction.front();

        if (Temp.getType() == 'O') {
            auto *NewAccount = new Account(Temp.getFirstName(), Temp.getLastName(), Temp.getID());
            if (NewAccount->getID() < 0 || NewAccount->getID() > 9999) {
                cerr << "ERROR: The account number must be 4 digits. "
                        "It must be between 0 and 9999." << endl;
                delete NewAccount;
            }
            if (!accounts.insert(NewAccount)) {
                cerr << "ERROR: Account " << Temp.getID() <<
                     " is already open. Transaction refused." << endl;
                delete NewAccount;
            }

        } else if (Temp.getType() == 'D') {
            int FundID = Temp.getID() % 10;
            int AccountID = Temp.getID() / 10;
            Account *Account;
            accounts.retrieve(AccountID, Account);
            Account->deposit(Temp.getAmount(), FundID);
            Account->recordTransaction(Temp, FundID);

        } else if (Temp.getType() == 'W') {
            int FundID = Temp.getID() % 10;
            int AccountID = Temp.getID() / 10;
            Account *Account;
            accounts.retrieve(AccountID, Account);

            if (Account->withdraw(Temp.getAmount(), FundID)) {
                Temp.setTransactionSuccess(true);
            } else {
                Temp.setTransactionSuccess(false);
                cerr << "ERROR: Insufficient balance to withdraw " << Temp.getAmount() <<
                     " from " << Account->getLastName() << " " << Account->getFirstName() <<
                     " " << Account->getFundName(FundID) << endl;
            }
            if (!Account->getInsertCheck()) {
                Account->recordTransaction(Temp, FundID);
            }

        } else if (Temp.getType() == 'T') {
            int FundID = Temp.getID() % 10;
            int AccountID = Temp.getID() / 10;
            int DestinationFundID = Temp.getDestinationID() % 10;
            int DestinationAccountID = Temp.getDestinationID() / 10;
            int Amount = Temp.getAmount();

            Account *Account, *AccountDestination;
            accounts.retrieve(AccountID, Account);
            accounts.retrieve(DestinationAccountID, AccountDestination);

            if (accounts.retrieve(AccountID, Account)) {
                if (accounts.retrieve(DestinationAccountID, AccountDestination)) {
                    if (Account->withdraw(Amount, FundID)) {
                        AccountDestination->deposit(Amount, DestinationFundID);
                        Transactions Deposit('D', Temp.getDestinationID(), Amount);
                        AccountDestination->recordTransaction(Deposit, DestinationFundID);
                        Account->recordTransaction(Temp, FundID);
                    } else {
                        cerr << "ERROR: Insufficient balance to transfer from the "
                                "account number " <<
                             Account->getID() << " type " << Account->getFundName(FundID)
                             << " to account number " << AccountDestination->getID()
                             << " type " << AccountDestination->getFundName(DestinationFundID)
                             << " of the amount " << Temp.getAmount() << endl;
                    }
                } else {
                    cerr << "ERROR: Could not find account " << DestinationAccountID <<
                         ". Transfer cancelled" << endl;
                }
            } else {
                cerr << "ERROR: Could not find account " << AccountID <<
                     ". Action cancelled" << endl;
            }

        } else if (Temp.getType() == 'H') {
            if (Temp.getID() > 999 && Temp.getID() < 10000) {
                Account *Account;
                if (accounts.retrieve(Temp.getID(), Account)) {
                    cout << "Displaying Transaction History for " << Account->getLastName()
                         << " " << Account->getFirstName() << " by fund." << endl;
                    Account->printFullHistory();
                } else {
                    cerr << "ERROR: Could not find account " << Temp.getID()
                         << ". Action cancelled." << endl;
                }

            } else if (Temp.getID() > 9999 && Temp.getID() < 100000) {
                int FundID = Temp.getID() % 10;
                int AccountID = Temp.getID() / 10;
                Account *Account;
                if (accounts.retrieve(AccountID, Account)) {
                    cout << "Displaying Transaction History for " << Account->getLastName()
                         << " " << Account->getFirstName() << "'s ";
                    Account->printFundHistory(FundID);
                } else {
                    cerr << "ERROR: Could not find account " << AccountID
                         << ". Action cancelled." << endl;
                }
            }
        }
        Transaction.pop();
    }
}