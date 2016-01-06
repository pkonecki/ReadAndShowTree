#include "bitFile.h"
#include <iostream>

using namespace std;

void initBitFile(iBitFile & ibf, const string & filename) {
  // A COMPLETER
  ibf.buffi=0;
  ibf.nb=0;
  ibf.inputfile.open(filename,ifstream::binary);
}
void pushBuffi(iBitFile &ibf){
    ibf.buffi=ibf.inputfile.get();// le get sait où il en est, c'est comme un itérateur
    ibf.nb=8;
}
Byte transBit(iBitFile &ibf){
    char unsigned c;
    c=1<<(ibf.nb-1);//mets à 1 et fais circuler d'un certain nombre de positions
    c&=ibf.buffi;//faire une addition entre C et buffi en transformant c;
    --ibf.nb;
    return c!=0?1:0;
}
Byte getBit(iBitFile & ibf) {
  // A COMPLETER
  if(ibf.nb==0){
    pushBuffi(ibf);
  }
  return transBit(ibf);
}

void initBitFile(oBitFile & obf, const string & filename) {
  // A COMPLETER
  obf.buffo=0;
  obf.nb=8;
  obf.outputfile.open(filename,ofstream::binary);
}
void putInBuffo(oBitFile &obf, Byte bit){//dans le code principal :unsigned bit = getBit(ibf);
    //comment faire pourle remettre à 1 ou 0 si il ne correspond pas à 1 ou 0
    bit=bit<<(obf.nb-1);
    obf.buffo|=bit;
    --obf.nb;
}
void putBit(oBitFile & obf, Byte bit) {
  // A COMPLETER
  putInBuffo(obf,bit);
  if(obf.nb==0){
    obf.outputfile.put(obf.buffo);//peut-être utiliser autre chose
    obf.buffo=0;
    obf.nb=8;
  }
}

void flushBits(oBitFile & obf) {//normalement ne peut servir qu'une seule fois quand buffer n'est pas terminé
    //et qu'on veut terminer le programme
  // A COMPLETER
  if(obf.nb<8)
    obf.outputfile.put(obf.buffo);
}

void closeFile(iBitFile & ibf) {
  // A COMPLETER
  ibf.inputfile.close();
}

void closeFile(oBitFile & obf) {
  // A COMPLETER
  obf.outputfile.close();
}

void put8Bits(oBitFile & obf, Byte data){
  for(int i=0;i<8;++i)
    putBit(obf,data);
}

Byte get8Bits(iBitFile &ibf){
    Byte buff=0;
    for(int i=7;i>=0;--i)
        buff|=(getBit(ibf) << i);//ajout dans un tampon
    return buff;
}
