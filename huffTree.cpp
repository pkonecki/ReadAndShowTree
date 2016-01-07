#include "huffTree.h"
#include <iostream>
using namespace std;

HuffTree newLeaf() {
  // A COMPLETER
  //HuffNode sup;
  HuffTree ht= new HuffNode();
  ht->data=0;
  ht->left=nullptr;
  ht->right=nullptr;
  return ht;
}

bool isLeaf(HuffTree ht) {
  // A COMPLETER
  return ht->data != 0;
}

void showTree(HuffTree ht) {
  if(isLeaf(ht))
    cout << char(ht->data);
  else {
    cout << '(';
    showTree(ht->left);
    cout << " ^ ";
    showTree(ht->right);
    cout << ')';
  }
}
