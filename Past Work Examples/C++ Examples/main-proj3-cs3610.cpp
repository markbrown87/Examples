/**
 * @file main.cpp
 * @author Modified by Mark Brown (provided by CS3610)
 * @brief Main file used to run through an AVL tree list
 * @date October 06, 2016
 */

#include <iostream>
#include "binary.h"
using namespace std;

int main() {

  BinaryTree* tree = new BinaryTree;

  char option; // Menu option
  int key; // Key for insert and remove

  do {
    cin >> option;
    switch(option) {
      case 'i':
        cin >> key;
        tree->insert(key);
        break;
      case 'r':
        cin >> key;
        tree->remove(key);
        break;
      case 'p':
        tree->print_keys();
        break;
      case 'h':
        tree->print_heights();
        break;
      default:
        break;
    }
  } while(option != 'q');

  delete tree;

}
