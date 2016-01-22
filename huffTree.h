#ifndef HUFFTREE_H_INCLUDED
#define HUFFTREE_H_INCLUDED

#include "bitFile.h"

struct HuffNode {
  Byte data;
  HuffNode * left;
  HuffNode * right;
};

typedef HuffNode * HuffTree;

// Renvoie un nouvel arbre singleton (un simple noeud) sans fils
// formant une feuille. Le champ data est indéfini
HuffTree newLeaf();

// Détermine si ht est une feuille
bool isLeaf(HuffTree ht);

// Affiche une représentation "lisible" de ht sur cout
void showTree(HuffTree ht);

#endif // HUFFTREE_H_INCLUDED
