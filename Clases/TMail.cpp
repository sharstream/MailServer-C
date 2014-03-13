//---------------------------------------------------------------------------

#pragma hdrstop

#include "TMail.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
///////////////////////DEMONIOS CORREOS//////////////////////////////////////
//---------------------------------------------------------------------------
namespace Daemon
{
 void ZiseAdj(void* pInfo,void* pReference)
 {
   TFichero* file =(TFichero*)pInfo;
   (*(int*)pReference) += file->Size();
 }
}
//---------------------------------------------------------------------------
TFichero :: TFichero(AnsiString pAdress, int pSize, AnsiString pTipo)
{
  aTipo = pTipo;
  aAdress = pAdress;
  aSize = pSize;
}
//---------------------------------------------------------------------------
TFichero :: ~TFichero()
{
  aTipo = "";
  aAdress="";
  aSize = 0;
}
//---------------------------------------------------------------------------
TMail :: TMail(AnsiString pParrafo,AnsiString pAsunto,AnsiString pRemitente)
{
  aParrafo = pParrafo;
  aAsunto = pAsunto;
  aRemitente = pRemitente;      //es de donde proviene el mensaje
  aAdjunts = new TGLinkedList();
  int tamAdj = 0;
  aAdjunts->ForEach(Daemon :: ZiseAdj,&tamAdj);
  aSize = ((aAsunto.Length() + aParrafo.Length())*2) + tamAdj;
}
//---------------------------------------------------------------------------
TMail :: ~TMail()
{
  aParrafo = "";
  aSize = 0;
  aAsunto = "";
  aRemitente = "";      //es de donde proviene el mensaje
  aAdjunts->~TGLinkedList();
}
//---------------------------------------------------------------------------
void TMail :: InsertAdjunt(TFichero* pFichero)
{
  aAdjunts->Insert(pFichero);
}
//--------------------------------------------------------------------------


