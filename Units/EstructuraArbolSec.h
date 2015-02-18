#ifndef EstructuraArbolSecH
#define EstructuraArbolSecH
//---------------------------------------------------------------------------
#include "EstructuraBinGral.h"
#include "EstructuraListas.h"
#include <vcl.h>
//---------------------------------------------------------------------------
typedef int TIndex;

struct TSArray {
  void** array;
  void** links;
  TIndex index;
};

struct TSIndex {
  TIndex indexNode;
  TIndex indexFather;
  TIndex index;
};

struct TSSeqNode
{
  int info;
  TIndex pos;
};

struct TSStack
{
  int degree;
};
//---------------------------------------------------------------------------
class TPreOrderNode   //usaremos esta class como nodo a almacenar en la lista y el en el fichero
{
private:
  bool aEnd;
  void* aInfo;
  TIndex aRightLink;
public:
  TPreOrderNode(){};
  TPreOrderNode(void* pInfo, TIndex pRightLink, bool pEnd) :
                aInfo(pInfo), aRightLink (pRightLink), aEnd(pEnd){}
  bool End() {return aEnd;}
  void  End(bool pEnd){aEnd=pEnd;}
  void* Info() {return aInfo;}
  void  Info(void* pInfo){aInfo=pInfo;}
  TIndex RightLink () {return aRightLink;}
  void RightLink(TIndex pRightLink) {aRightLink = pRightLink;}
};
//---------------------------------------------------------------------------
class TSeqPreOrderTree : public TGSeqList  // y esta como recorrido en el arbol
{
public:
  TSeqPreOrderTree(){}
  TSeqPreOrderTree(TGBinTree*);
  void Brothers(TIndex, TGSeqList*);
  void Sons(TIndex, TGSeqList*);
  TIndex Father(TIndex);
  void Cousins(TIndex, TGSeqList*);
  void Nephews(TIndex, TGSeqList*);
  void Uncles(TIndex, TGSeqList*);
};
//---------------------------------------------------------------------------
class TFamilyNode
{
private:
  bool aFamily;
  void* aInfo;
  TIndex aLeftLink;
public:
  TFamilyNode(void* pInfo, TIndex pLeftLink, bool pFamily) :
              aInfo(pInfo), aLeftLink(pLeftLink), aFamily(pFamily){}
  bool Family() {return aFamily;}
  void* Info() {return aInfo;}
  void Info(void* pInfo) { aInfo = pInfo;}
  TIndex LeftLink () {return aLeftLink;}
  void LeftLink (TIndex pLeftLink) {aLeftLink = pLeftLink;}
};
//---------------------------------------------------------------------------
class TPostOrderNode
{
private:
  int aDegree;
  void* aInfo;
public:
  TPostOrderNode(void* pInfo, int pDegree) : aInfo(pInfo),
                                             aDegree(pDegree){}
  int Degree() {return aDegree;}
  void* Info() {return aInfo;}
};
  //---------------------------------------------------------------------------
class TSeqFamilyTree : public TGSeqList
{
public:
  TSeqFamilyTree(TGBinTree*);
  void Brothers(TIndex, TGSeqList*);
  void Sons(TIndex, TGSeqList*);
  TIndex Father(TIndex);
  void Cousins(TIndex, TGSeqList*);
  void Nephews(TIndex, TGSeqList*);
  void Uncles(TIndex, TGSeqList*);
};
//---------------------------------------------------------------------------
class TSeqPostOrderTree : public TGSeqList
{
public:
  TSeqPostOrderTree(TGBinTree*);
  void Brothers(TIndex, TGSeqList*);
  void Sons(TIndex, TGSeqList*);
  TIndex Father(TIndex);
  void Cousins(TIndex, TGSeqList*);
  void Nephews(TIndex, TGSeqList*);
  void Uncles(TIndex, TGSeqList*);
};
//---------------------------------------------------------------------------
#endif
