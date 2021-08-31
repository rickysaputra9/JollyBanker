//
// Created by Ricky Saputra on 3/8/2020.
//

#include "transaction.h"
#include <iostream>

// Displays the output of transaction
ostream &operator<<(ostream &Out, const Transactions &Transaction) {

    if (Transaction.getType() == 'D' || Transaction.getType() == 'W') {
        Out << "        " << Transaction.getType() << " " << Transaction.getID()
            << " " << Transaction.getAmount();
    } else if (Transaction.getType() == 'T') {
        Out << "        " << Transaction.getType() << " " << Transaction.getID() << " "
            << Transaction.getAmount() << " " << Transaction.getDestinationID();
    }

    // If Transaction fails, warning sign pops up.
    if (!Transaction.getTransactionSuccess()) {
        Out << " (Failed)";
    }

    return Out << endl;
}

// Constructor to open account
Transactions::Transactions(char Type, string LastName, string FirstName, int ID) :
        Type{Type}, LastName{LastName}, FirstName{FirstName}, ID{ID}, SuccessRate{true} {}

// Constructor for deposits and withdrawals
Transactions::Transactions(char Type, int ID, int Amount) :
        Type{Type}, ID{ID}, Amount{Amount}, SuccessRate{true} {}

// Constructor to transfer money
Transactions::Transactions(char Type, int ID, int Amount, int DestinationID) :
        Type{Type}, ID{ID}, Amount{Amount}, DestinationID{DestinationID},
        SuccessRate{true} {}

// Constructor to display history
Transactions::Transactions(char Type, int ID) : Type{Type}, ID{ID}, SuccessRate{true} {}

// Destructor
Transactions::~Transactions() = default;

// Returns the type of fund
char Transactions::getType() const {
    return Type;
}

// Returns the first name
string Transactions::getFirstName() const {
    return FirstName;
}

// Returns the last name
string Transactions::getLastName() const {
    return LastName;
}

// Returns the account number
int Transactions::getID() const {
    return ID;
}

// Returns an amount of money
int Transactions::getAmount() const {
    return Amount;
}

// Returns the destination account number
int Transactions::getDestinationID() const {
    return DestinationID;
}

// Returns true or false to know whether the transaction is successful or not
bool Transactions::getTransactionSuccess() const {
    return SuccessRate;
}

// Returns true or false to determine the success rate of a transaction
bool Transactions::setTransactionSuccess(bool Statement) {
    SuccessRate = Statement;
    return true;
}

