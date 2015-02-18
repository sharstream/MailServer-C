#ifndef EstructuraBinGralH
#define EstructuraBinGralH


#include "EstructuraArbolBin.h"
//---------------------------------------------------------------------------
//Clase TArbolGeneral
//---------------------------------------------------------------------------
class TGBinTreeNode: public TBinTreeNode
{
  public:
    TGBinTreeNode(){}
    TGBinTreeNode(void* pInfo): TBinTreeNode(pInfo) {}
    bool IsLeaf() {return !aLeft;}     // virtual
    int Degree();                      // virtual
};
//---------------------------------------------------------------------------
class TGBinTree: public TBinTree
{
  private:
  public:
     TGBinTree(){}
    ~TGBinTree(){}
    void* DeleteNode(TGBinTreeNode*);
    void* DeleteNodeYDescendientes(TGBinTreeNode* pNode);
    TBinTreeNode* GetFather(TBinTreeNode*);            // virtual
    TGLinkedList* GetLeaves();                         // virtual
    TGLinkedList* GetSons(TBinTreeNode*);
    bool InsertNode(TGBinTreeNode*, TGBinTreeNode*);
    bool InsertNodeLeft(TGBinTreeNode* pNode, TGBinTreeNode* pFather);
};
//---------------------------------------------------------------------------
#endif

