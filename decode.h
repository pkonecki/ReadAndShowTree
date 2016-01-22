#ifndef DECODE_H_INCLUDED
#define DECODE_H_INCLUDED

#include "bitFile.h"
#include "huffTree.h"
#include <string>

// D�code fs codes lus de ibf en �crivant le symbole correspondant
// dans fNameOut en utilisant l'arbre de Huffman ht
void doDecode(iBitFile & ibf, unsigned long fs, HuffTree ht, const std::string fNameOut);

#endif // DECODE_H_INCLUDED
