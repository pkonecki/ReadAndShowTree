#include <iostream>
#include <cstring>

#include "huffTree.h"
#include "bitFile.h"
#include "treeFile.h"
#include "encode.h"
#include "decode.h"

using namespace std;

bool validOption(string option) {
  return option == "-c" || option == "-C" ||
         option == "-d" || option == "-D";
}

// Le fichier existe-t-il?
bool existFile(string fName) {
  return ifstream(fName);
}

// Renvoie la taille en octets du fichier
unsigned long fileSize(const string & fileName) {
  ifstream fin(fileName, fstream::binary | fstream::ate);
  return fin.tellg();
}

// Ecrire bit par bit tous les octets de lg
void putULongToFile(unsigned long lg, oBitFile & obf) {
  for(int k = sizeof(lg) - 1; k >= 0; --k)
    put8Bits(obf, lg >> (8 * k) & 255);
}

// Lecture bit par bit des octets d'un unsigned long
unsigned long getULongFromFile(iBitFile & ibf) {
  unsigned long result = 0;
  for(unsigned k = 0; k < sizeof(result); ++k)
    result = (result << 8) | get8Bits(ibf);
  return result;
}

// Codage de Huffman
void encode(string fNameIn, string fNameOut) {
  HuffTree ht = makeTreeFromFile(fNameIn);  // Comptage + construction arbre
  showTree(ht);
  oBitFile obf; initBitFile(obf, fNameOut); // Préparation fichier output
  putULongToFile(fileSize(fNameIn), obf);   // Sauver longueur
  putTreeToFile(ht, obf);                   // Sauver arbre
  doCode(fNameIn, obf, ht);                 // Codage
}

// Décodage
void decode(string fNameIn, string fNameOut) {
  iBitFile ibf; initBitFile(ibf, fNameIn);  // Préparation input
  auto fs = getULongFromFile(ibf);          // Lecture longueur
  HuffTree ht = getTreeFromFile(ibf);       // Lecture arbre
  doDecode(ibf, fs, ht, fNameOut);          // Décodage
}

int main(int argc, char *argv[]) {
  if(argc != 4)
    cout << "Ligne de Commande: Huffman [-c|-d] NomFichOrig NomFichDest\n";
  else if(!validOption(argv[1]))
    cout << "Option invalide:\n" <<
            "Utilier -c ou -C pour comprimer, -d ou -D pour decomprimer\n";
  else if(!existFile(argv[2]))
    cout << "Fichier " << argv[2] <<
            " introuvable. Verifier le nom et le chemin.\n";
  else {
    string cmd = argv[1];
    if(cmd == "-c" || cmd == "-C")
      encode(argv[2], argv[3]);
    else
      decode(argv[2], argv[3]);
  }
}


