//---------------------------------------------------------------------------
#ifndef EstructuraArbolBinH
#define EstructuraArbolBinH
//---------------------------------------------------------------------------
#include  "EstructuraListas.h"

typedef AnsiString TCad;

struct TSCad
{
  TCad sCad;
};

struct TSParents
{
  TCad sPersonName;
  TCad sParents;
};

//-----------------------
// class TNodoArbol
//-----------------------
class TBinTreeNode
{
  protected:
    void* aInfo;
    TBinTreeNode* aLeft;
    TBinTreeNode* aRight;
  public:
    TBinTreeNode(){}
    TBinTreeNode(void* pInfo) : aInfo(pInfo), aLeft(NULL), aRight(NULL) {}
   ~TBinTreeNode(){}
    virtual int Degree();
    void* Info() {return aInfo;}
    void Info(void* pInfo) {aInfo=pInfo;}
    virtual bool IsLeaf() {return (!aLeft && !aRight);}  //  Degree() == 0
    TBinTreeNode* Left() {return aLeft;}
    void Left(TBinTreeNode* pNode) {aLeft = pNode;}
    TBinTreeNode* Right() {return aRight;}
    void Right(TBinTreeNode* pNode) {aRight = pNode;}
};
struct TSSons
{
  TBinTreeNode* sLeft;
  TBinTreeNode* sRight;
};

struct TSSubTree
{
  TCad sPersonName;
  TBinTreeNode* sLocation;
  TGLinkedList* sAncestors;
};

struct TSFather
{
   TBinTreeNode* sNode;
   TBinTreeNode* sFather;
};
//----------------------
// class TArbol
//----------------------
class TBinTree
{
  typedef void (*TActionFunction)(TBinTreeNode* pCursor, void* pReference = NULL);
  typedef bool (*TConditionalFunction)(TBinTreeNode* pCursor, void*  pReference = NULL);

  private:
    bool AllNodesDegreeTwo();
    virtual void DeleteNotRoot(TBinTreeNode*, int, TBinTreeNode*);
    virtual void DeleteRoot(TBinTreeNode*, int);
    TBinTreeNode* FirstIncompletedNode(TBinTreeNode*);
    void GetNodeSubTree(TBinTreeNode*, TBinTreeNode*, TBinTree* &);
    int Level(TBinTreeNode*);
    void PreOrderFirstIncompletedNode(TBinTreeNode*, TBinTreeNode* &);
  protected:
     TBinTreeNode* aRoot;
  public:
     TBinTree() {aRoot = NULL;}
     ~TBinTree();
     void* DeleteNode(TBinTreeNode*);   // no vitual
     bool DivideTree(TBinTreeNode*, TBinTree* &, TBinTree* &);
     bool Empty(){return !aRoot;}
     TBinTreeNode* GetFather(TBinTreeNode*); // no vitual
     TGLinkedList* GetLeaves();              // no vitual
     TSSons* GetSons(TBinTreeNode*);         // no vitual
     TGLinkedList* GetSubTree(TBinTreeNode*, char);
     bool InsertNode(TBinTreeNode*, char, TBinTreeNode*);  // no vitual
     int NodeLevel(TBinTreeNode*);
     virtual void PostOrderForEach(TBinTreeNode*, TActionFunction, void*);
     virtual void PostOrderInvertedForEach(TBinTreeNode*, TActionFunction, void*);
     virtual TBinTreeNode* PreOrderFirstThat(TBinTreeNode*, TConditionalFunction, void*);
     virtual void PreOrderForEach(TBinTreeNode*, TActionFunction, void*);
     TBinTreeNode* Root() {return aRoot;}
     void Root(TBinTreeNode* pRoot) {aRoot = pRoot;}
     virtual void SymmetricForEach(TBinTreeNode*, TActionFunction, void*);
     int TotalNodes();
     int TreeDegree();
     int TreeLevel();
};
//---------------------------------------------------------------------------
#endif

