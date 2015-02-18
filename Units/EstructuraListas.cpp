#include "EstructuraListas.h"
#pragma hdrstop
#pragma package(smart_init)
//---------------------------------------------------------------------------
// Lista Base
//---------------------------------------------------------------------------
int TBaseList::IndexOf(void* pInfo)
{
  if (pInfo)
  {
    int i = 0;
    while (i < Length() && ItemInfo(i) != pInfo)
      i++;
    return (i < Length())? i : -1;
  }
  else
    return -1;
}
//---------------------------------------------------------------------------
// Lista Secuencial
//---------------------------------------------------------------------------
TSeqList::TSeqList(const int pSize) : TBaseList()
{
  aSize = pSize;
  arrItems = new void*[pSize];
  aInc = pSize / 10 + 1;
}
//---------------------------------------------------------------------------
TSeqList::TSeqList(const int pSize, const int pInc) : TBaseList()
{
  aSize = pSize;
  arrItems = new void*[pSize];
  aInc = pInc;
}
//---------------------------------------------------------------------------
TSeqList::~TSeqList()
{
  aSize = 0;
  for(int i = 0; i < aLength; i++)
    {
     delete arrItems[i];
    }

  aLength = 0;
  aInc = 0;
  delete[] arrItems;
}
//---------------------------------------------------------------------------
void TSeqList::Expand()
{
  aSize += aInc;
  void** arrTemp = new void*[aSize];
  for (int i = 0; i <= aLength; i++)
    arrTemp[i] = arrItems[i];
  delete[] arrItems;
  arrItems = arrTemp;
}
//---------------------------------------------------------------------------
void TSeqList::Insert(void* pItemInfo)
{
  if (Full())
    Expand();
  arrItems[aLength++] = pItemInfo;
}
//---------------------------------------------------------------------------
// Lista General Secuencial
//---------------------------------------------------------------------------
void* TGSeqList::Delete(int pPos)
{
  if ((pPos < 0) || (pPos >= aLength)) throw EListOutOfRange(); //Posición fuera de rango
  void* deleted = arrItems[pPos];
  for (int i = pPos + 1; i < aLength; i++)
    arrItems[i - 1] = arrItems[i];
  aLength--;
  return deleted;
}
//---------------------------------------------------------------------------
void* TGSeqList::FirstThat(TDFunctionConditional pCondition, void* pReference = NULL)
{
  int i = 0;
  bool found = false;
  while ((i < aLength) && (!found))
    if (pCondition(arrItems[i], pReference))
      found = true;
    else
      i++;
  return ((found)?arrItems[i]:NULL);
}
//---------------------------------------------------------------------------
void TGSeqList::ForEach(TDFunctionAction pAction, void* pReference = NULL)
{
  for (int i = 0; i < aLength; i++)
    pAction(arrItems[i], pReference);
}
//---------------------------------------------------------------------------
void TGSeqList::Insert(void* pItemInfo, int pPos)
{
  if (pPos < 0 || pPos > aLength) throw EListOutOfRange();
  if (Full())
  {
    aSize += aInc;
    void** arrTemp = new void*[aSize];
    for (int i = 0; i < pPos; i++)                // copiar hasta pos
      arrTemp[i] = arrItems[i];
    arrTemp[pPos] = pItemInfo;                        // colocar el nuevo elemento
    for (int i = pPos + 1; i < aLength + 1; i++)  // copiar de pos al final
      arrTemp[i] = arrItems[i - 1];
    delete [] arrItems;
    arrItems = arrTemp;
  }
  else
  {
    for (int i = aLength; i > pPos; i--)
      arrItems[i] = arrItems[i - 1];
    arrItems[pPos] = pItemInfo;
  }
  aLength++;
}
//---------------------------------------------------------------------------
void* TGSeqList::ItemInfo(int pPos) const
{
 if ((pPos < 0) || (pPos >= aLength)) throw EListOutOfRange(); //Posición fuera de rango
 return arrItems[pPos];
}
//---------------------------------------------------------------------------
// Lista Enlazada
//---------------------------------------------------------------------------
TLinkedList::~TLinkedList()
{
 /* TNode* cursor=new TNode();
  TNode* del=new TNode();
  cursor = aFirst;
  while(cursor)
  {
    del = cursor;
    cursor = cursor->Next();
    delete del;
  }*/

  TNode* cursor=new TNode();
  while(aFirst)
  {
    aLength = 0;
    cursor = aFirst;
    aFirst = aFirst->Next();
    delete cursor;
  }
  aLength = 0;
}
//---------------------------------------------------------------------------
void TLinkedList::Insert(void* pItem)
{
  TNode* node = new TNode(pItem);
  if (Empty())
    aFirst = node;
  else
  {
    TNode* cursor = aFirst;
    while (cursor->Next())
      cursor = cursor->Next();
    cursor->Next(node);
  }
  aLength++;
}
//--------------------------------------------------------------
// Lista General Enlazada
//--------------------------------------------------------------
void* TGLinkedList::Delete(int pPos)
{
  if ((pPos < 0) || (pPos >= Length())) throw EListOutOfRange(); //Posición fuera de rango
  TNode* cursor = Item(pPos);
  if (pPos != 0)
    Item(pPos - 1)->Next(cursor->Next());
  else          // Eliminar el primer nodo
    aFirst = aFirst->Next();
  void* deleted = cursor->Info();
  // destruir el nodo
  delete cursor;
  aLength--;
  return deleted;
}
//---------------------------------------------------------------------------
void* TGLinkedList::FirstThat(TDFunctionConditional pCondition, void* pReference = NULL)
{
  TNode* cursor = aFirst;
  bool found = false;
  int i = 0;
  while ((i < aLength) && (!found))
    if (pCondition(cursor->Info(), pReference))
      found = true;
    else
    {
      cursor = cursor->Next();
      i++;
    }
  return (found ? cursor->Info() : NULL);
}
//---------------------------------------------------------------------------
void TGLinkedList::ForEach(TDFunctionAction pAction, void* pReference = NULL)
{
  TNode* cursor = aFirst;
  int i = 0;
  while (i < aLength)
  {
    pAction(cursor->Info(), pReference);
    cursor = cursor->Next();
    i++;
  }
}
//---------------------------------------------------------------------------
void TGLinkedList::Insert(void* pItem)
{
  TNode* node = new TNode(pItem);
  if (Empty())
    aFirst = node;
  else
    Item(aLength - 1)->Next(node);
  aLength++;
}
//---------------------------------------------------------------------------
void TGLinkedList::Insert(void* pItem, int pPos)
{
  if ((pPos < 0) || (pPos > Length())) throw EListOutOfRange(); //Posición fuera de rango
  if (pPos != 0)
  {
    TNode* cursor = Item(pPos - 1);
    ((TNode*)pItem)->Next(cursor->Next());
    cursor->Next((TNode*)pItem);
  }
  else
  {
    // Insertar en la primera posición
    ((TNode*)pItem)->Next(aFirst);
    aFirst = (TNode*)pItem;
  }
  aLength++;
}
//---------------------------------------------------------------------------
TNode* TGLinkedList::Item(int pPos) const
{
  if ((pPos < 0) || (pPos >= Length())) throw EListOutOfRange(); //Posición fuera de rango
  TNode* cursor = aFirst;
  for (int i = 0; i < pPos; i++)
    cursor = cursor->Next();
  return cursor;
}
//---------------------------------------------------------------------------
void* TGLinkedList::ItemInfo(int pPos) const
{
  if ((pPos < 0) || (pPos >= Length())) throw EListOutOfRange(); //Posición fuera de rango
  TNode* cursor = aFirst;
  for (int i = 0; i < pPos; i++)
    cursor = cursor->Next();
  return cursor->Info();
}
//----------------------------------------------------------------------------
// Lista DoblementeEnlazada
//----------------------------------------------------------------------------
void* TDoubleList :: Delete(int pPos)
{
  if ((pPos < 0) || (pPos >= Length())) throw EListOutOfRange(); //Posición fuera de rango
  void* deleted = TGLinkedList::Delete(pPos);
  if (!Empty())
  {
    if (pPos == 0)
      ((TDoubleNode*)Item(0))->Prev(NULL);
    else
       if (pPos < Length())   // Nodo intermedio
         ((TDoubleNode*)Item(pPos))->Prev((TDoubleNode*)Item(pPos - 1));
  }
  return deleted;
}
//---------------------------------------------------------------------------
void TDoubleList::Insert(void* pItem)
{
  TGLinkedList::Insert(pItem);
  TNode* inserted = ((TDoubleNode*)Item(Length() - 1));
  if (Length() > 1)   // Actualizar el Prev() con la direccion del nodo anterior
    ((TDoubleNode*)inserted)->Prev((TDoubleNode*)Item(Length() - 2));
  else
    ((TDoubleNode*)inserted)->Prev(NULL);
}
//---------------------------------------------------------------------------
void TDoubleList::Insert(void* pItem, int pPos)
{
  if ((pPos < 0) || (pPos > Length())) throw EListOutOfRange();
  TDoubleNode* prev;
  if (pPos == 0)
    prev = NULL;
  else
    prev = ((TDoubleNode*)Item(pPos - 1));
  TGLinkedList::Insert(pItem, pPos);
  TDoubleNode* insertedNode = ((TDoubleNode*)Item(pPos));
  insertedNode->Prev(prev);
  if (pPos != (aLength - 1))        // No es el ultimo nodo
    ((TDoubleNode*)insertedNode->Next())->Prev(insertedNode);
}
//---------------------------------------------------------------------------
// Lista Enlazada Circular
//---------------------------------------------------------------------------
TCircLinked::~TCircLinked()
{
  if (!Empty())
  {
    TNode* cursor;
    TNode* saved = aFirst;
    // ejecutar si hay más de 1 elemento
    while(aFirst->Next() != saved )
    {
      cursor = aFirst;
      aFirst = aFirst->Next();
      delete cursor;
    }
    delete aFirst;
    aFirst = NULL;
    aLength = 0;
  }
}
//---------------------------------------------------------------------------
void* TCircLinked::Delete(int pPos)
{
  if ((pPos < 0) || (pPos >= Length())) throw EListOutOfRange();
  void* deleted = TGLinkedList::Delete(pPos);
  if (Empty())
    aFirst = NULL;
  else
    if (pPos == 0) // Casos extremo: el primero.
      Item(aLength - 1)->Next(aFirst);
  return deleted;
}
//---------------------------------------------------------------------------
void TCircLinked::Insert(void* pItem)
{
  TGLinkedList::Insert(pItem);
  Item(aLength - 1)->Next(aFirst);
}
//---------------------------------------------------------------------------
void TCircLinked::Insert(void* pItem, int pPos)
{
  if (pPos == aLength)
    Insert(pItem);
  else
  {
    TGLinkedList::Insert(pItem, pPos);
    if (pPos == 0)
      Item(aLength - 1)->Next(aFirst);
  }
}
//---------------------------------------------------------------------------
// Lista Doblemente Enlazada Circular
//---------------------------------------------------------------------------
TDoubleCirc::~TDoubleCirc()
{
  if (aFirst)
  {
    TDoubleNode* cursor;
    TDoubleNode* saved = (TDoubleNode*)aFirst;
    // ejecutar si hay más de 1 elemento
    while(aFirst->Next() != saved)
    {
      cursor = (TDoubleNode*)aFirst;
      aFirst = aFirst->Next();
      delete cursor;
    }
    delete aFirst;
    aFirst = NULL;
    aLength = 0;
  }
}
//---------------------------------------------------------------------------
void* TDoubleCirc::Delete(int pPos)
{
  if ((pPos < 0) || (pPos >= Length())) throw EListOutOfRange();
  void* deleted = TDoubleList::Delete(pPos);
  if (Empty())
    aFirst = NULL;
  else
    if ((pPos == 0) || (pPos == aLength)) // Casos extremos: primero y último
    {
      ((TDoubleNode*)aFirst)->Prev((TDoubleNode*)Item(aLength - 1));
      Item(aLength - 1)->Next(aFirst);
    }
  return deleted;
}
//---------------------------------------------------------------------------
void TDoubleCirc::Insert(void* pItem)
{
  TDoubleList::Insert(pItem);
  Item(aLength - 1)->Next(aFirst);
  ((TDoubleNode*)aFirst)->Prev((TDoubleNode*)Item(aLength - 1));
}
//---------------------------------------------------------------------------
void TDoubleCirc::Insert(void* pItem, int pPos)
{
  TDoubleList::Insert(pItem, pPos);
  if ((pPos == 0) || (pPos == Length() - 1)) // Casos extremos: primero y último
  {
    TDoubleNode* last = (TDoubleNode*)Item(aLength - 1);
    ((TDoubleNode*)aFirst)->Prev(last);
    last->Next(aFirst);
  }
}
//---------------------------------------------------------------------------
// Pila Secuencial
//---------------------------------------------------------------------------
void* TSeqStack :: Delete()
{
  if (Empty()) throw EEmpty();
  void* deleted = Top();
  aLength--;
  return deleted;
}

void* TSeqStack :: Top() const
{
  if (Empty()) throw EEmpty();
  return arrItems[aLength - 1];
}

