#include <iostream>
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
    hf=new HuffNode();
    hf->left=nullptr;
    hf->right=nullptr;
    return true;
  }
    //else//si je mets pas de ifgetbit je suis pas sûr que le getbit avance
}
HuffTree constructTree(HuffTree hf,iBitFile &ibf){//le considère comme une procédure
  //on détecte si y a quelque chose qui suit car ça veut dire qu'on s'est déjà occupé de ce qu'il y avait après
  if(hf==nullptr){
    hf=(constructNode(hf,ibf))?hf:hf;
  }
  else if(hf->left!=nullptr){//va à droite//isLeaf?
    //on construit le node suivant
    if (constructNode(hf->right,ibf))
     hf=hf->right;
    else
     return hf;
  }
  else{//si à gauche c'est vide
    hf=(constructNode(hf->left,ibf))?hf->left:hf;
  //on appelle de nouveau la fonction pour avancer du pas qu'on vient de créer si c'est un 1
  }
  while (ibf.inputfile.good()){
    if ((hf->right==nullptr) || (hf->left==nullptr))
     constructTree(hf,ibf);
    else
     return hf;
  }
  //je ne sais pas comment terminer la fonction pour que la récursivité s'arrête?
  return hf;
}

HuffTree getTreeFromFile(iBitFile & ibf){
//volonté de faire du récursif
    HuffTree hf=nullptr;
    if(ibf.inputfile.good())
     hf=constructTree(hf,ibf);
    return hf;
}

void browseList(List_Frequence &frequence_list,unsigned k){
  while ((frequence_list->next_frequence != nullptr)
   && (frequence_list->next_frequence->frequence < k))
   frequence_list=frequence_list->next_frequence;
}

void createNode(List_Frequence &ls, HuffTree &NodeCar){
    List_Car tmp=new Node();
    tmp->Huffcar=NodeCar;
    tmp->next=ls->charList;
    ls->charList=tmp;
}
void addFreqNode(List_Frequence &frequence_list,unsigned k, HuffTree &addum ){
  List_Frequence frequence_temp;
  if (frequence_list->next_frequence != nullptr){
   if ((frequence_list->frequence != k)
    && (frequence_list->next_frequence->frequence != k)){
       //au milieu de liste
    frequence_temp = new Frequence_Node();
    frequence_temp->frequence = k;
    frequence_temp->next_frequence = frequence_list->next_frequence;
    frequence_temp->charList=nullptr;
    frequence_list->next_frequence = frequence_temp;
    createNode(frequence_temp, addum);
   }
   else if(frequence_list->frequence == k){
          createNode(frequence_list,addum);
      }
      else if(frequence_list->next_frequence->frequence == k){
         frequence_list=frequence_list->next_frequence;
         createNode(frequence_list,addum);
      }
  }
  else{
   if (frequence_list->frequence != k){
    frequence_temp = new Frequence_Node();
    frequence_temp->frequence =k;
    frequence_temp->next_frequence = nullptr;
    frequence_temp->charList = nullptr;

    frequence_list->next_frequence = frequence_temp;
    createNode(frequence_temp, addum);
   }
   else{
    createNode(frequence_list,addum);
   }
   // Premier élément ou tout dernier élément
  }
}

void removeNode(List_Frequence &ls){
  List_Car tmp=ls->charList;
  ls->charList=tmp->next;
  delete tmp;
}
void cleanUpList( List_Frequence ls){//démarrage au tampon
  List_Frequence lsd=ls->next_frequence;
  while(lsd->next_frequence!=nullptr){
    if(lsd->charList==nullptr){
      ls->next_frequence=lsd->next_frequence;
      List_Frequence work=lsd;
      lsd=ls->next_frequence;
      delete work;
    }
    else{
      ls =ls->next_frequence;
      lsd=lsd->next_frequence;
    }
  }
}

void reOrganizeNodeList(List_Frequence &ls,List_Frequence &lst){
//les noeuds à supprimer se retrouveront tj au début dû aux suppressions préc
  removeNode(ls);
  removeNode(lst);
}
HuffTree replacemenTree(List_Car &ln, List_Car &lnt){
  HuffTree work=new HuffNode();
  work->left=ln->Huffcar;
  work->right=lnt->Huffcar;
  return work;
}
void  assemble2by2(const List_Frequence &ls){
    List_Frequence tfp=ls->next_frequence;//start après tampon
    if(tfp->next_frequence != nullptr){//parcourscolonne
      List_Car tnp=tfp->charList;//si il y a un noeudFreq il y a un NoeudChar
      if(tnp->next!=nullptr){//il y a donc au moins deux NoeudChar
        HuffTree work=replacemenTree(tnp,tnp->next);
        unsigned i=(tfp->frequence)*2;
        reOrganizeNodeList(tfp,tfp);//liste de Noeud hufftree réorganisé
        List_Frequence tfptmp=tfp;
        browseList(tfptmp, i);
        addFreqNode(tfptmp,i ,work);
        cleanUpList(ls);
      }
      else{//moins de deuxn noeuds sur une même ligne
        HuffTree work=replacemenTree(tnp,tfp->next_frequence->charList);
        unsigned i=(tfp->frequence)+(tfp->next_frequence->frequence);
        reOrganizeNodeList(tfp,tfp->next_frequence);//liste de Noeud hufftree réorganisé
        List_Frequence tfptmp=tfp;
        browseList(tfptmp, i);
        addFreqNode(tfptmp,i ,work);
        cleanUpList(ls);
      }
      assemble2by2(ls);
    }
    else{//si moins de deux noeudcol
      List_Car tnp=tfp->charList;
      if(tnp->next!=nullptr){//il y a donc au moins deux NoeudChar
        HuffTree work=replacemenTree(tnp,tnp->next);
        unsigned i=(tfp->frequence)*2;
        reOrganizeNodeList(tfp,tfp);//liste de Noeud hufftree réorganisé
        List_Frequence tfptmp=tfp;
        browseList(tfptmp, i);
        addFreqNode(tfptmp,i ,work);
        cleanUpList(ls);
        assemble2by2(ls);
      }
    }
}

void printList(List_Frequence ls){
  while (ls!= nullptr)
  {
   std::cout << ls->frequence << ": ";
   List_Car tmp =ls->charList;

   while(tmp != nullptr)
   {
     std::cout << tmp << " :- (" << (unsigned) tmp->Huffcar->data << ") - ";
     tmp=tmp->next;
   }
   std::cout << std::endl;
   ls=ls->next_frequence;
  }
}
void printVect(Frequence &Frequences){
    for(unsigned i : Frequences)
    {
     if (i != 0)
        std::cout << i << std::endl;
    }
}

HuffTree BuidTree(Frequence & Frequences, TreeNodes & Characters) {
 for (unsigned i = 0; i<Frequences.size();++i) {
  if(Frequences[i]!=0) {
   if(i!=Frequences.size()-1) {
    HuffTree work = new HuffNode();
    unsigned tmp=Frequences[i] + Frequences[i+1];
    work->left=Characters[i];
    work->right=Characters[i+1];
    Frequences[i]=0;
    Frequences[i+1]=0;
    Characters[i]=nullptr;
    Characters[i+1]=nullptr;
    Frequences.insert(Frequences.begin(),tmp);
    Characters.insert(Characters.begin(),work);
    sortFrequenceCharacters(Frequences,Characters);
    if(i != Frequences.size())
     i=0;
   }
   else{
    return Characters[i];
   }
  }
 }
}

void sortFrequenceCharacters(Frequence & Frequences, TreeNodes & Characters) {

// Bubble sort of Frequences vectors
 // erase the 6th element

 for (unsigned i = 0; i < Frequences.size()-1; ++i) {
  for (unsigned j = 0; j < Frequences.size()-1; ++j) {
   if (Frequences[j] > Frequences[j + 1])
   {
    std::swap(Frequences[j], Frequences[j + 1]);
    std::swap(Characters[j], Characters[j + 1]);
   }
  }
 }
}

void buildCharactersVector(const std::string fName,Frequence & Frequences, TreeNodes & Characters){
  iBitFile ibf;
  initBitFile(ibf, fName);
  pushBuffi(ibf);
  while (ibf.inputfile.good())
  {
   if(Frequences.at((unsigned) ibf.buffi) < 1)
   {
    HuffTree hTreeCharacter;
    hTreeCharacter = new HuffNode();
    hTreeCharacter->data = (Byte) ibf.buffi;
    Characters[(unsigned) ibf.buffi] = hTreeCharacter;
   }

   Frequences.at((unsigned) ibf.buffi)++;

   pushBuffi(ibf);
  }

  closeFile(ibf);
  sortFrequenceCharacters(Frequences, Characters);
}

HuffTree makeTreeFromFile(const std::string fName) {

  Frequence Frequences;
  Frequences.resize(NBELEMENTS);

  TreeNodes Characters;
  Characters.resize(NBELEMENTS);

  buildCharactersVector(fName, Frequences, Characters);
  return BuidTree(Frequences, Characters);
}



/*
HuffTree makeTreeFromFile(const std::string fName) {
  // A COMPLETER
  Frequence Frequences;
  Frequences.resize(NBELEMENTS);

  TreeNodes Characters;
  Characters.resize(NBELEMENTS);


  List_Frequence frequence_list = new Frequence_Node();
  frequence_list->next_frequence = nullptr;
  List_Frequence Freq_start = frequence_list;

  buildCharactersVector(fName,Frequences,Characters);
  for(unsigned k = 0; k < Frequences.size(); ++k)
  {
   if(Frequences.at(k) != 0)
   {
    frequence_list=Freq_start;
    browseList(frequence_list, Frequences.at(k));
    addFreqNode(frequence_list,Frequences.at(k),Characters[k]);
   }
  }
  frequence_list=Freq_start;
  assemble2by2(frequence_list);
  printList(Freq_start->next_frequence);
  return Freq_start->next_frequence->charList->Huffcar;//todoavec aprèsassemble2by2
}
*/

//premier postulat on est tj sur un noeud interne
//deuxième postulat on doit aller à gauche dès que possible
//si on rempli une feuille on ne bouge pas
//getbit avance automatiquement?
