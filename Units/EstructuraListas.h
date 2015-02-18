//---------------------------------------------------------------------------
#ifndef EstructuraListasH
#define EstructuraListasH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <typeinfo.h>
#include <vcl.h>

//---------------------------------------------------------------------------
// comun
//---------------------------------------------------------------------------
class EListException{};
class EListOutOfMemory : public EListException{};
class EListOutOfRange : public EListException{};
class EEmpty : public EListException{};
//--------------------------------------------------
//  Lista Base
//--------------------------------------------------
class TBaseList
{
public:
  TBaseList() {aLength = 0;}
  bool Empty() const { return !aLength; }
  int IndexOf(void*);
  virtual void Insert(void*) = 0;
  virtual void* ItemInfo(int) const = 0 ;
  int Length()const{return aLength;}
protected:
  int aLength;
private:
};
//---------------------------------------------------------------------------
// Lista Secuencial
//---------------------------------------------------------------------------
class TSeqList : public TBaseList
{
private:
protected:
  void** arrItems;
  int aInc;
  int aSize;
  void Expand();
public:
  TSeqList(){}
  TSeqList(const int);
  TSeqList(const int, const int);
  ~TSeqList();
  bool Full() const { return aSize == aLength; }
  virtual  void* ItemInfo(int pIndex)const{ return arrItems[pIndex]; }
  void Insert(void*);
};
//---------------------------------------------------------------------------
// Lista General Secuencial
//---------------------------------------------------------------------------
class TGSeqList : public TSeqList
{
typedef void (*TDFunctionAction)(void*, void*);
typedef bool (*TDFunctionConditional)(void*, void*);
private:
protected:
public:
  TGSeqList(){}
  TGSeqList(int pSize) : TSeqList(pSize){}
  ~TGSeqList(){}
  void* Delete(int);
  void* FirstThat(TDFunctionConditional, void*);
  void ForEach(TDFunctionAction, void*);
  void Insert(void* pItemInfo)  { TSeqList::Insert(pItemInfo); }
  void Insert(void*, int);
  virtual void* ItemInfo(int) const;
};
//---------------------------------------------------------------------------
// Nodo de la Lista Enlazada
//---------------------------------------------------------------------------
class TNode
{
private:
protected:
  void* aInfo;
  TNode* aNext;
public:
  TNode(){}
  TNode( void* pInfo) :  aInfo(pInfo), aNext(NULL){}
  void* Info() const { return aInfo; }
  void Info(void* pInfo) { aInfo = pInfo; }
  TNode* Next() const { return aNext; }
  void Next(TNode* pNext) { aNext = pNext; }
};

//---------------------------------------------------------------------------
// Lista Enlazada
//---------------------------------------------------------------------------
class TLinkedList : public TBaseList
{
private:
protected:
  TNode* aFirst;
public:
  TLinkedList() : TBaseList(), aFirst(NULL) {}
  ~TLinkedList();
  TNode* First() const{ return aFirst;}
  void Insert(void*);
};
//---------------------------------------------------------------------------
// Lista General Enlazada
//---------------------------------------------------------------------------
class TGLinkedList : public TLinkedList
{
typedef void (*TDFunctionAction)(void*, void*);
typedef bool (*TDFunctionConditional)(void*, void*);
private:
protected:
public:
  TGLinkedList() : TLinkedList(){}
  void* Delete(int);
  void Insert(void* pItem);
  void Insert(void*, int);
  void* FirstThat(TDFunctionConditional, void*);
  void ForEach(TDFunctionAction, void*);
  TNode* Item(int) const;
  virtual void* ItemInfo(int) const;
};
//---------------------------------------------------------------------------
// Lista Enlazada Circular
//---------------------------------------------------------------------------
class TCircLinked : public TGLinkedList
{
private:
protected:
public:
  TCircLinked() : TGLinkedList() {}
  ~TCircLinked();
  void* Delete(int);
  void Insert(void*);
  void Insert(void*, int);
};
//---------------------------------------------------------------------------
// Nodo de la Lista DoblementeEnlazada
//---------------------------------------------------------------------------
class TDoubleNode : public TNode
{
private:
  TDoubleNode* aPrev;
public:
  TDoubleNode(void* pItemInfo) : TNode(pItemInfo), aPrev(NULL){}
  TDoubleNode* Prev(){return aPrev;}
  void Prev(TDoubleNode* pPrev){aPrev = pPrev;}
};
//---------------------------------------------------------------------------
// Lista DoblementeEnlazada
//---------------------------------------------------------------------------
class TDoubleList : public TGLinkedList
{
public:
  TDoubleList(): TGLinkedList() {}
  void* Delete(int);
  void Insert(void*);
  void Insert(void*, int);
};
//---------------------------------------------------------------------------
// Lista Doblemente Enlazada Circular
//---------------------------------------------------------------------------
class TDoubleCirc : public TDoubleList
{
public:
  TDoubleCirc() : TDoubleList() {}
  ~TDoubleCirc();
  void* Delete(int);
  void Insert(void*);
  void Insert(void*, int);
};
//--------------------------------------------------
//  Pila Secuencial
//--------------------------------------------------
class TSeqStack : public TSeqList
{
private:
protected:
public:
  TSeqStack(int pSize) : TSeqList(pSize) { }
  void* Delete();
//  void Insert(void* pInfo) { TSeqList::Insert(pInfo); }
 virtual  void* ItemInfo(int pIndex = 0) const{return Top();}
 void* Top() const;
};
//--------------------------------------------------
//  Pila Enlazada
//--------------------------------------------------
/*class TLinkedStack : public TLinkedList
{
public:
  TLinkedStack() : TLinkedList(){}
  void* Delete();
  void Insert(void*);
  void* Top() const;
protected:
private:
};*/
//--------------------------------------------------
//  Cola Secuencial
//--------------------------------------------------
/*class TSeqQueue : public TSeqList
{
public:
  TSeqQueue(int pSize) : TSeqList(pSize), aFirst(0), aLast(0){ }
  void* Delete();
  void* FirstItem() const;
  void Insert(void*);
protected:
private:
  int aFirst;
  int aLast;
  void Expand();
};*/
//--------------------------------------------------
//  Cola Enlazada
//--------------------------------------------------
/*class TLinkedQueue : public TLinkedList
{
public:
  TLinkedQueue() : TLinkedList(), aLast(NULL){}
  void* Delete();
  void* FirstItem() const;
  void Insert(void*);
protected:
private:
  TNode* aLast;
};*/
//---------------------------------------------------------------------------
#endif

