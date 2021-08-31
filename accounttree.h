//
// Created by Ricky Saputra on 3/8/2020
//

#pragma once

#include "account.h"
#include <iostream>

class AccountTree {
  public:
    // Create BST
    AccountTree();

    // Delete all nodes in BST
    ~AccountTree();

    // Insert new account
    bool insert(Account* account);

    // Retrieve account
    // returns true if successful AND *Account points to account
    bool retrieve(const int& accountNumber, Account*& account) const;

    // Display information on all accounts
    void display() const;

    // delete all information in AccountTree
    void clear();

    // check if tree is empty
    bool isEmpty() const;

  private:
    class Node {
      public:
        //Node constructor
        explicit Node(Account* account)
            : account{account}, right{nullptr}, left{nullptr} {};
        ~Node() {
            delete account;
        }
        Account* account;
        Node* right;
        Node* left;
    };

    Node* root;

    // Works as a helper function. Searches a node recursively
    Account *recursiveRetrieve(Node *RootPtr, int Target) const;

    // Works as a helper function. Adds a node recursively
    bool recursiveInsert(Account *Target, Node *&RootPtr);

    // Works as a helper function. Displays information on all accounts recursively
    void display(Node *Root) const; // Helper function

    // delete all information in AccountTree
    void clear(Node *Node);
};
