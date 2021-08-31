//
// Created by Ricky Saputra on 3/8/2020.
//

#ifndef ASS5_BANKER_TRANSACTION_H
#define ASS5_BANKER_TRANSACTION_H
#include <string>

using namespace std;

class Transactions {
    // Displays the output of transaction
    friend ostream &operator<<(ostream &output, const Transactions &transaction);

public:
    // Constructor to open account
    Transactions(char Type, string LastName, string FirstName, int ID);

    // Constructor for deposits and withdrawals
    Transactions(char Type, int ID, int Amount);

    // Constructor to transfer money
    Transactions(char Type, int ID, int Amount, int DestinationAccount);

    // Constructor to display history
    Transactions(char Type, int ID);

    // Destructor
    ~Transactions();

    // Returns the type of fund
    char getType() const;

    // Returns the first name
    string getFirstName() const;

    // Returns the last name
    string getLastName() const;

    // Returns the account number
    int getID() const;

    // Returns an amount of money
    int getAmount() const;

    // Returns the destination account number
    int getDestinationID() const;

    // Returns true or false to know whether the transaction is successful or not
    bool getTransactionSuccess() const;

    // Returns true or false to determine the success rate of a transaction
    bool setTransactionSuccess(bool Statement);

private:
    char Type{}; // Fund type variable
    int ID;
    int Amount{};
    int DestinationID{};
    string LastName;
    string FirstName;
    bool SuccessRate = false;
};

#endif //ASS5_BANKER_TRANSACTION_H
