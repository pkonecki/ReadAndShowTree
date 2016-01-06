#ifndef CODES_H_INCLUDED
#define CODES_H_INCLUDED

#include <vector>
#include <algorithm>
#include "huffTree.h"

const int NBSYMB = 256;

typedef std::vector<Byte> Code;
typedef std::vector<Code> Codes;

void putCodeInCodes(Byte data, Codes &codes,Code &buff);
void changePathToBuff(Code &buff, unsigned i, unsigned cpt);
void addPathToBuff(Code &buff, unsigned i);
void browseTree(HuffTree hf, Codes &codes, Code &buffer);
// Construit le tableau de codes au départ de l'arbre hf
void makeCodes(HuffTree hf, Codes & codes);

// Affiche sur cout chaque caractère présent dans le tableau avec son code
void showCodes(const Codes & codes);

#endif // CODES_H_INCLUDED
