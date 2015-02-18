
#include <vcl.h>
#pragma hdrstop


//--------------------------------------------------------------------------
#include "EstructuraBinGral.h"

namespace GeneralTreeDaemons
{
  bool IsThere(TBinTreeNode* pCursor, void* pReference)
  {
     if(pCursor == (TBinTreeNode*)pReference)
       return true;
     return false;
  }

  void Leaves(TBinTreeNode* pCursor, void* pReference)  //hechar un vistazo si da una exepcion
  {
    if (!pCursor->Left())
    {
      ///TNode* node = new TNode(pCursor);
      ((TGLinkedList*)pReference)->Insert(pCursor);
    }
  }

  bool Prev(TBinTreeNode* pCursor, void* pReference)
  {
    return ((pCursor->Left() == pReference) || (pCursor->Right() == pReference));
  }
} // Fin Demonios

//----------------------------------
// Implementación de TNodoBinGral
//----------------------------------
int TGBinTreeNode::Degree()
{
  int degree = 0;
  TBinTreeNode* cursor = Left();
  while (cursor)
  {
     degree++;
     cursor = cursor->Right();
  }
  return degree;
}
//----------------------------------
// Implementación de TArbolBinGral
//----------------------------------
void* TGBinTree::DeleteNode(TGBinTreeNode* pNode)
// Se busca el nodo que lo apunta. Su lugar lo ocupa el nodo que es apuntado por la derecha.
// Si no existe ninguno, se trata de la raíz.
{
  TBinTreeNode* prev = PreOrderFirstThat(aRoot, GeneralTreeDaemons::Prev, pNode);
  if (prev)
  {
    if (prev->Left() == pNode)
      prev->Left(pNode->Right());
    else
      prev->Right(pNode->Right());
  }
  else  // Es la raíz
    Root(pNode->Right());
  return pNode->Info();
}
//---------------------------------------------------------------------------
TBinTreeNode* TGBinTree::GetFather(TBinTreeNode* pNode)
{
  if (Empty() || aRoot == pNode)
     return NULL;
  else
  {
     TBinTreeNode* prev = PreOrderFirstThat(aRoot, GeneralTreeDaemons::Prev, pNode);
     if (prev->Right() == pNode)
       return GetFather(prev);
     else
       return prev;
  }
}
//---------------------------------------------------------------------------
TGLinkedList* TGBinTree::GetLeaves()
{
  if (!Empty())
  {
     TGLinkedList* leavesList = new TGLinkedList();
     PreOrderForEach(aRoot, GeneralTreeDaemons::Leaves, leavesList);
     return leavesList;
  }
  else
    return NULL;
}
//---------------------------------------------------------------------------
TGLinkedList* TGBinTree :: GetSons(TBinTreeNode* pNode)
{
  if (pNode->Left())
  {
    TGLinkedList* sonsList = new TGLinkedList();
    //TNode* newNode = new TNode(pNode->Left()->Info());
    sonsList->Insert(pNode->Left());
    if (pNode->Left()->Right())
    {
      pNode = pNode->Left();
      while (pNode->Right())
      {
        //TNode* newNode = new TNode(pNode->Right()->Info());
        sonsList->Insert(pNode->Right());
        pNode = pNode->Right();
      }
    }
    return sonsList;
  }
  else
    return NULL;
}
//---------------------------------------------------------------------------
bool TGBinTree::InsertNode(TGBinTreeNode* pNode, TGBinTreeNode* pFather)
{
  if  (Empty())
  {
    if (!pFather)
    {
       aRoot = pNode;
       return true;
    }
    else
      return false;
  }
  else
  {
     if (pFather)
     {
       TBinTreeNode* isFather = PreOrderFirstThat(aRoot, GeneralTreeDaemons::IsThere, pFather);
       if (isFather)
       {
          TBinTreeNode* cursor = pFather->Left();
          if (!cursor)
             pFather->Left(pNode);
          else
          {
             while (cursor->Right())
               cursor = cursor->Right();
             cursor->Right(pNode);
          }
       }
       return isFather;
     }
     else
     { // Insertarlo como último hermano de la raíz
       if (aRoot->Right())
       {
         TBinTreeNode* cursor = aRoot->Right();
         while (cursor->Right())
           cursor = cursor->Right();
         cursor->Right(pNode);
       }
       else
         aRoot->Right(pNode);
       return true;
     }
   }
}
//---------------------------------------------------------------------------

