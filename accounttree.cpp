//
// Created by Ricky Saputra on 3/8/2020
//

#include "accounttree.h"

AccountTree::AccountTree() : root{nullptr} {}

// Delete all nodes in BST
AccountTree::~AccountTree(){
    clear(root);
}

// Insert new account
bool AccountTree::insert(Account* account) {
    return recursiveInsert(account, root);
}

// Works as a helper function. Inserts a node recursively
bool AccountTree::recursiveInsert(Account *Target, AccountTree::Node *&RootPtr) {
    if (RootPtr == nullptr) {
        RootPtr = new Node(Target);
        RootPtr->account = Target;
        RootPtr->left = nullptr;
        RootPtr->right = nullptr;
        return true;
    } else {
        if (RootPtr->account->getID() > Target->getID()) {
            if (RootPtr->left == nullptr) {
                Node *Temp = new Node(Target);
                Temp->account = Target;
                Temp->left = nullptr;
                Temp->right = nullptr;
                RootPtr->left = Temp;
                return true;
            } else {
                return recursiveInsert(Target, RootPtr->left);
            }
        } else if (RootPtr->account->getID() < Target->getID()) {
            if (RootPtr->right == nullptr) {
                Node *Temp = new Node(Target);
                Temp->account = Target;
                Temp->left = nullptr;
                Temp->right = nullptr;
                RootPtr->right = Temp;
                return true;
            } else {
                return recursiveInsert(Target, RootPtr->right);
            }
        } else {
            return false;
        }
    }
}

// Retrieve account
// returns true if successful AND *account points to account
bool AccountTree::retrieve(const int& accountNumber, Account*& account) const {
    account = recursiveRetrieve(root, accountNumber);
    return account != nullptr;
}

// Works as a helper function. Searches a node recursively
Account *AccountTree::recursiveRetrieve(AccountTree::Node *RootPtr, int Target) const {
    if (RootPtr == nullptr) {
        return nullptr;
    } else if (RootPtr->account->getID() == Target) {
        return RootPtr->account;
    } else if (Target < RootPtr->account->getID()) {
        return recursiveRetrieve(RootPtr->left, Target);
    } else {
        return recursiveRetrieve(RootPtr->right, Target);
    }
}

// Displays information on all accounts
void AccountTree::display() const {
    display(root);
}

// Display information on all accounts
void AccountTree::display(AccountTree::Node *RootPtr) const {
    if (RootPtr != nullptr) {
        display(RootPtr->left);
        cout << RootPtr->account->getLastName() << " " <<
             RootPtr->account->getFirstName()
             << " Account ID: " << RootPtr->account->getID() << endl;

        for (int I = 0; I < 10; ++I) {
            cout << "       " << RootPtr->account->getFundName(I) << ": $" <<
                 RootPtr->account->getFundBalance(I) << endl;
        }
        cout << endl;
        display(RootPtr->right);
    }
}

// delete all information in AccountTree
void AccountTree::clear(Node *Node) {
    if (Node) {
        clear(Node->left);
        clear(Node->right);
        delete Node;
    }
}

// check if tree is empty
bool AccountTree::isEmpty() const {
    return root == nullptr;
}