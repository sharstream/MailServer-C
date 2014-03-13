//---------------------------------------------------------------------------

#pragma hdrstop

#include "TServidor.h"

#pragma package(smart_init)
//---------------------------------------------------------------------------
TServidor :: TServidor(AnsiString pName,int pTope, int pMax):TDomain(pName)
{
   aTope=pTope;
   aMax=pMax;
   aCuentas= new TGLinkedList();
}
//---------------------------------------------------------------------------
TServidor :: ~TServidor()
{
  aMax = 0;
  aTope = 0;
  aCuentas->~TGLinkedList();
}
//---------------------------------------------------------------------------

