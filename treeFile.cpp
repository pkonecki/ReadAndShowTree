#include "huffTree.h"
#include "treeFile.h"

#include <iostream>

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
bool constructNode(HuffTree& hf,iBitFile &ibf){
  if(hf != nullptr)
    std::cout << "ERREUR DEVRAIT ETRE NULL" <<std::endl;
  if(getBit(ibf)==0){
    std::cout << "newLeaf" <<std::endl;
    hf=newLeaf();
    hf->data=get8Bits(ibf);//en espérant que ce soit dans le bon ordre
    return false;
  }
  else{
    std::cout << "newNode empty" << std::endl;
    hf=new HuffNode();//default value pointer?
    hf->data = 0;
    hf->left=nullptr;
    hf->right=nullptr;
    return true;
  }
    //else//si je mets pas de ifgetbit je suis pas sûr que le getbit avance
}
void constructTree(HuffTree hf,iBitFile &ibf){//le considère comme une procédure
  //on détecte si y a quelque chose qui suit car ça veut dire qu'on s'est déjà occupé de ce qu'il y avait après
  
  if(not ibf.inputfile.good())
    return;
  if(hf==nullptr)
    constructNode(hf,ibf);
  std::cout << "iteration " << hf << " gauche " << hf->left << " droite "<< hf->right << std::endl;
  //not leaf on doit remplir left et right
  if (isLeaf(hf))
  {  
    std::cout << "ISLEAF RETURN" << std::endl;
    return;
  }
  bool leftIsTree = constructNode(hf->left,ibf);
  std::cout << "construct gauche " << hf << " gauche " << hf->left << " droite "<< hf->right << std::endl;
  //std::cin.get();
  if (leftIsTree)
    constructTree(hf->left,ibf);
  bool rightIsTree = constructNode(hf->right,ibf);
  std::cout << "construct droite " << hf << " gauche " << hf->left << " droite "<< hf->right << std::endl;
  //std::cin.get();
  if (rightIsTree)
    constructTree(hf->right,ibf);
//   if(hf->left==nullptr)
//   {  
//     std::cout << "left" <<std::endl;
//     bool isNotLeaf = constructNode(hf->left,ibf);
//     if (isNotLeaf)
//       constructTree(hf->left,ibf);
//   }
//     if(hf->right==nullptr)//va à droite//isLeaf?
//   {
//     std::cout << "right" <<std::endl;
//     //on construit le node suivant
//     bool isNotLeaf = constructNode(hf->right,ibf);
//     if (isNotLeaf)
//       constructTree(hf->right,ibf);
//   }  
  //on appelle de nouveau al fonction pour avancer du pas qu'on vient de créer si c'est un 1

    
  //je ne sais pas comment terminer la fonction pour que la récursivité s'arrête?
}
HuffTree getTreeFromFile(iBitFile & ibf){
//volonté de faire du récursif
    HuffTree hf=nullptr;
    if(ibf.inputfile.good())
        constructTree(hf,ibf);
    std::cout << "FINI" << hf << std::endl;
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
