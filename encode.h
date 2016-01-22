#ifndef ENCODE_H_INCLUDED
#define ENCODE_H_INCLUDED

#include "bitFile.h"
#include "huffTree.h"

// Encode bit par bit dans obf le contenu du fichier fNameIn en
// utilisant le code défini par l'arbre de Huffman ht
void doCode(std::string fNameIn, oBitFile & obf, HuffTree ht);

#endif // ENCODE_H_INCLUDED
