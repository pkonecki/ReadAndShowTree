#include "huffTree.h"
#include "treeFile.h"

void putTreeToFile(HuffTree hTree, oBitFile & obf) {
  if(isLeaf(hTree)) {
    putBit(obf, 0);
    put8Bits(obf, hTree->data);
  }
  else {
    putBit(obf, 1);
    putTreeToFile(hTree->left, obf);
    putTreeToFile(hTree->right, obf);
  }
}
bool constructNode(HuffTree &hf,iBitFile &ibf){
  if(getBit(ibf)==0){
    hf=newLeaf();
    hf->data=get8Bits(ibf);//en espérant que ce soit dans le bon ordre
    return false;
  }
  else{
    hf=new HuffNode;//default value pointer?
    hf->left=nullptr;
    hf->right=nullptr;
    return true;
  }
    //else//si je mets pas de ifgetbit je suis pas sûr que le getbit avance
}
void constructTree(HuffTree &hf,iBitFile &ibf){//le considère comme une procédure
  //on détecte si y a quelque chose qui suit car ça veut dire qu'on s'est déjà occupé de ce qu'il y avait après
  if(hf==nullptr)
    hf=(constructNode(hf,ibf))?hf:hf;
  else if(hf->left!=nullptr)//va à droite//isLeaf?
    //on construit le node suivant
    hf=(constructNode(hf->right,ibf))?hf:hf->right;
  else//si à gauche c'est vide
    hf=(constructNode(hf->left,ibf))?hf:hf->left;
  //on appelle de nouveau al fonction pour avancer du pas qu'on vient de créer si c'est un 1
  if(ibf.inputfile.good())
    constructTree(hf,ibf);
  //je ne sais pas comment terminer la fonction pour que la récursivité s'arrête?
}
HuffTree getTreeFromFile(iBitFile & ibf){
//volonté de faire du récursif
    HuffTree hf=nullptr;
    if(ibf.inputfile.good())
        constructTree(hf,ibf);
    return hf;
/*
    if(ibf.inputfile.good())
    {
        if (getBit(ibf) == 0)
        {
            if (isLeaf(hf))
                hf=newLeaf();
            hf->data=get8Bits(ibf);
        }
        else
        {
            if(ibf.inputfile.good())
                hf->left=getTreeFromFile(ibf);
            if(ibf.inputfile.good())
                hf->right=getTreeFromFile(ibf);
        }
    }
    return hf;


*/

}
//premier postulat on est tj sur un noeud interne
//deuxième postulat on doit aller à gauche dès que possible
//si on rempli une feuille on ne bouge pas
//getbit avance automatiquement?
