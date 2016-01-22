#ifndef TREEFILE_H_INCLUDED
#define TREEFILE_H_INCLUDED

#include <vector>
#include <algorithm>
#include "bitFile.h"
#include "huffTree.h"

const int NBELEMENTS = 256;

struct Node{
    HuffTree Huffcar;
    Node * next;

    Node()
        : Huffcar(nullptr)
        , next(nullptr)
    {

    }
};

struct Frequence_Node{
 unsigned frequence;
 //Node *start_node;
// Node *end_node;
 Node *charList;
 Frequence_Node * next_frequence;

 Frequence_Node()
     :charList(nullptr)
 {

 }
};

typedef std::vector<unsigned> Frequence;
typedef std::vector<HuffTree> TreeNodes;
typedef Node * List_Car;
typedef Frequence_Node * List_Frequence;

// Ecrit l'arbre hTree dans le fichier obf de la fa�on d�crite dans
// l'�nonc� du projet Huffman
// Pr�condition: hTree est non vide
//               Le fichier doit �tre pr�t � �tre �crit bit par bit
//               tel qu'apr�s un appel de initBitFile
void putTreeToFile(HuffTree hTree, oBitFile & obf);

bool constructNode(HuffTree &hf,iBitFile &ibf);
HuffTree constructTree(HuffTree hf,iBitFile &ibf);

// Retourne: l'arbre lu dans le fichier ibf (cf. �nonc� projet Huffman).
// Pr�condition: Le fichier doit �tre pr�t � lire bit par bit tel qu'apr�s
//               un appel de initBitFile
HuffTree getTreeFromFile(iBitFile & ibf);
void browseList(List_Frequence &frequence_list,unsigned k);
void createNode(List_Frequence &ls, HuffTree &NodeCar);
void addFreqNode(List_Frequence &frequence_list,unsigned k, HuffTree &addum );
void removeNode(List_Frequence &ls);
void cleanUpList( List_Frequence ls);
void reOrganizeNodeList(List_Frequence &ls,List_Frequence &lst);
HuffTree replacemenTree(List_Car &ln, List_Car &lnt);
void assemble2by2(const List_Frequence &ls);
void printList(List_Frequence ls);

void sortFrequenceCharacters(Frequence & Frequences, TreeNodes & Characters);
void buildCharactersVector(const std::string fName,Frequence & Frequences, TreeNodes & Characters);

HuffTree makeTreeFromFile(const std::string fName);
#endif // TREEFILE_H_INCLUDED
