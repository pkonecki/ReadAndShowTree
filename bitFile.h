#ifndef BITFILE_H_INCLUDED
#define BITFILE_H_INCLUDED

#include <fstream>
#include <string>

typedef /* A COMPLETER */unsigned char Byte;


// Structure pour la lecture bit à bit dans un fichier
// buff est un tampon rempli byte par byte au départ du fichier
// et dans lequel les bits sont pris 1 à 1.
struct iBitFile {
  // A COMPLETER
  Byte buffi;
  int nb/*ibit*/;
  std::ifstream inputfile;
};

// Structure pour écrire bit à bit dans un fichier
// buff est un tampon pour accumuler 8 bits avant de les envoyer dans le fichier
struct oBitFile {
  // A COMPLETER
  Byte buffo;
  int nb/*obit*/;
  std::ofstream outputfile;
};


// Ouverture du fichier filename et préparation du tampon
void initBitFile(iBitFile & ibf, const std::string & filename);

// Extraction de 1 bit du fichier par l'intermédiaire du tampon
// Renvoie un Byte à 1 ou 0 selon le bit extrait
Byte getBit(iBitFile & ibf);

// Ouverture du fichier filename et préparation du tampon
void initBitFile(oBitFile & obf, const std::string & filename);

// Ecriture du bit dans le fichier par l'intermédiaire du tampon
// bit doit valoir 1 ou 0
void putBit(oBitFile & obf, Byte bit);

// Vidange dans le fichier des derniers bits en suspens dans le tampon
// Des bits résiduels à 0 peuvent être ajoutés pour remplir un Byte
void flushBits(oBitFile & obf);

// Ferme le fichier
void pushBuffi(iBitFile &ibf);
void closeFile(iBitFile & ibf);
void closeFile(oBitFile & obf);
Byte transByteToBit(int &cpt,Byte data);
void put8Bits(oBitFile & obf, Byte data);
Byte get8Bits(iBitFile &ibf);
#endif
