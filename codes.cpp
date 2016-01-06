#include <iostream>
#include "codes.h"

using namespace std;

void putCodeInCodes(Byte data, Codes &codes,Code &buff){
	Code lettre;//le vector va t il disparaitre dès la fermeture de la fonction
	copy(buff.begin(),buff.end(),lettre.begin());
	codes[(int)data]=lettre;
}
/*bool foundLeaf(HuffTree &hf){
	if(!isLeaf(hf))
		return true;
	else
		return false;
}*/
//ce qui suit pourriat être pas mal à faire
/*void browseTree(HuffTree hf, Codes &codes){
	if(!isLeaf(hf->left))
		browseTree(hf->left,codes);
	else if(!isLeaf(hf->right){
		browseTree(hf->right,codes);
		putCodeInCodes(hf->left);
	}
	else{
		putCodeInCodes(hf->left);
		putCodeInCodes(hf->right);
	}
}*/
void changePathToBuff(Code &buff, unsigned i, unsigned cpt){
	buff[cpt]=i;
}
void addPathToBuff(Code &buff, unsigned i){
	buff.push_back(i);
}
void browseTree(HuffTree hf, Codes &codes, Code &buffer, unsigned cpt){
  if(isLeaf(hf->left)){
  	//va chercher code à gauche
  	//va à droite
  	addPathToBuff(buffer, 0);
  	putCodeInCodes(hf->left->data,codes,buffer);
	changePathToBuff(buffer,1,cpt);
	if(isLeaf(hf->right))
		putCodeInCodes(hf->right->data,codes,buffer);//normalement =fin de la procédure
	else
		browseTree(hf->right, codes, buffer,cpt);
  }
  else{
  	//va gauche
  	//puis il faut vérifier si à droite = feuille
  	//si non aller à droite
  	addPathToBuff(buffer,0);
  	browseTree(hf->left, codes, buffer,++cpt);
  }
  //pas sûr que cette procédure se termine
  //peut-être nécéssité de faire un compteur pour déterminer la place où il est poru la modification dans le Code

}
void makeCodes(HuffTree hf, Codes & codes) {
  // A COMPLETER
	Code buffer;
	unsigned cpt=0;
	if(!isLeaf(hf))
		browseTree(hf,codes,buffer,cpt);
  	}
void showCodes(const Codes & codes) {
  for(unsigned k = 0; k < codes.size(); ++k)
    if(!codes[k].empty()) {
      	cout << char(k) << ": ";
      	for(Byte b: codes[k])
        	cout << (int)b;
     	cout << endl;
    }
}
