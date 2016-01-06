#include <iostream>
#include <cstring>
#include <string>

#include "huffTree.h"
#include "treeFile.h"
#include "codes.h"
#include "bitFile.h"
using namespace std;

static bool existFile(string fName) {
  return ifstream(fName);
}

using namespace std;

const string fName = "HuffTreeCodes.bin";

int main() {
  if(!existFile(fName))
    cout << "Fichier " << fName << " introuvable\n";
  else {
    iBitFile ibf;
    initBitFile(ibf, fName);
    HuffTree hTree = getTreeFromFile(ibf);
    showTree(hTree); cout << endl << endl;
//    Codes codes;
//    makeCodes(hTree, codes);
//    showCodes(codes);
  }
}
