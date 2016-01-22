#include "decode.h"
#include <fstream>

using namespace std;

// Décode 1 symbole de ibf vers fout en utilisant l'arbre de Huffman ht
static void decode1(iBitFile & ibf, HuffTree ht, ofstream & fout) {
  HuffNode * p = ht;
  while(!isLeaf(p))      // Parcours de l'arbre depuis la racine
    if(getBit(ibf) == 0) // Si bit à 0
      p = p->left;       // Descendre à gauche
    else                 // Sinon
      p = p->right;      // Descendre à droite
  fout.put(p->data);     // Ecrire le symbole dans la feuille
}

// Décode fs codes lus de ibf en écrivant le symbole correspondant
// dans fNameOut en utilisant l'arbre de Huffman ht
void doDecode(iBitFile & ibf, unsigned long fs,
              HuffTree ht, const string fNameOut) {
  ofstream fout(fNameOut, fstream::binary);
  for(unsigned long k = 0; k < fs; ++k) // Recommencer fs fois
    decode1(ibf, ht, fout);             // Décodage d'un symbole
}

