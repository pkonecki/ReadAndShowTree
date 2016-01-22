#include "encode.h"
#include "treeFile.h"
#include "codes.h"
#include <fstream>

using namespace std;

// Ecrit bit par bit dans obf le code
static void encode1(const Code & code, oBitFile & obf) {
  for(auto b: code) // Pour chaque bit du code
    putBit(obf, b); // Ecriture du bit dans obf
}

// Encode bit par bit dans obf le contenu du fichier fNameIn en
// utilisant le code défini par l'arbre de Huffman ht
void doCode(string fNameIn, oBitFile & obf, HuffTree ht) {
  Codes codes;
  makeCodes(ht, codes);
  ifstream fin(fNameIn, fstream::binary);
  Byte b = fin.get();       // Lecture octet par octet
  while(fin.good()) {
    encode1(codes[b], obf); // Encodage bit par bit de l'octet
    b = fin.get();
  }
  flushBits(obf);           // Ecriture des derniers bits
}

