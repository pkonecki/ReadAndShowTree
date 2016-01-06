#ifndef TREEFILE_H_INCLUDED
#define TREEFILE_H_INCLUDED

#include "bitFile.h"
#include "huffTree.h"

// Ecrit l'arbre hTree dans le fichier obf de la façon décrite dans
// l'énoncé du projet Huffman
// Précondition: hTree est non vide
//               Le fichier doit être prêt à être écrit bit par bit
//               tel qu'après un appel de initBitFile
void putTreeToFile(HuffTree hTree, oBitFile & obf);

bool constructNode(HuffTree &hf,iBitFile &ibf);
void constructTree(HuffTree &hf,iBitFile &ibf);

// Retourne: l'arbre lu dans le fichier ibf (cf. énoncé projet Huffman).
// Précondition: Le fichier doit être prêt à lire bit par bit tel qu'après
//               un appel de initBitFile
HuffTree getTreeFromFile(iBitFile & ibf);

#endif // TREEFILE_H_INCLUDED
