#include <iostream>
#include <string>

#include "huffTree.h"
#include "treeFile.h"
#include "codes.h"

using namespace std;

// Un noeud interne
HuffTree inNode(HuffTree left, HuffTree right) {
  HuffTree ht = new HuffNode;
  ht->left    = left;
  ht->right   = right;
  return ht;
}

// Une feuille
HuffTree leaf(Byte data) {
  HuffTree ht = new HuffNode;
  ht->data    = data;
  ht->left    = nullptr;
  ht->right   = nullptr;
  return ht;
}

// L'arbre de l'�nonc� construit � la main
HuffTree mkSimpleTree() {
  return inNode(leaf('A'), inNode(leaf('B'),
           inNode(inNode(inNode(
             inNode(leaf('E'), leaf('F')) , leaf('D')),
               inNode(leaf('G'), leaf('H'))), leaf('C'))));
}

const string fName = "testGetTreeFromFile.bin";

void sauvegarde() {
  HuffTree hTree = mkSimpleTree();

  showTree(hTree); cout << endl << endl;

  oBitFile obf;
  initBitFile(obf, fName);
  putTreeToFile(hTree, obf);
  flushBits(obf);
}

void restaure() {
  iBitFile ibf;
  initBitFile(ibf, fName);
  HuffTree hTree = getTreeFromFile(ibf);

  showTree(hTree); cout << endl << endl;
  Codes codes;
  makeCodes(hTree, codes);
  showCodes(codes);
}

int main() {
  sauvegarde();

  cout << "VOUS DEVEZ VOIR DEUX FOIS LE MEME ARBRE QUE DANS L'ENONCE.\n\n" <<
          "Si c'est le cas, votre fonction getTreeFromFile est ok.\n" <<
          "Si vous avez termine makeCodes() ils doivent aussi s'afficher\n\n";

  restaure();
}
