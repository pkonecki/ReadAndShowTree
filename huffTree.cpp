#include "huffTree.h"
#include <iostream>
using namespace std;

HuffTree newLeaf() {
  // A COMPLETER
  HuffTree ht=new HuffNode();
  ht->data=0;
  ht->left=nullptr;
  ht->right=nullptr;
  return ht;
}

bool isLeaf(HuffTree ht) {
  // A COMPLETER
  return ht->left==nullptr && ht->right==nullptr;
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
