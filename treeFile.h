#ifndef TREEFILE_H_INCLUDED
#define TREEFILE_H_INCLUDED

#include "bitFile.h"
#include "huffTree.h"

// Ecrit l'arbre hTree dans le fichier obf de la fa�on d�crite dans
// l'�nonc� du projet Huffman
// Pr�condition: hTree est non vide
//               Le fichier doit �tre pr�t � �tre �crit bit par bit
//               tel qu'apr�s un appel de initBitFile
void putTreeToFile(HuffTree hTree, oBitFile & obf);

bool constructNode(HuffTree& hf,iBitFile &ibf);
void constructTree(HuffTree hf,iBitFile &ibf);

// Retourne: l'arbre lu dans le fichier ibf (cf. �nonc� projet Huffman).
// Pr�condition: Le fichier doit �tre pr�t � lire bit par bit tel qu'apr�s
//               un appel de initBitFile
HuffTree getTreeFromFile(iBitFile & ibf);

#endif // TREEFILE_H_INCLUDED
