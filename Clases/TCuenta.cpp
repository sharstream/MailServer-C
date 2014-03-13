//---------------------------------------------------------------------------

#pragma hdrstop

#include "TCuenta.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
namespace Daemon
{
 void Zise(void* pCursor,void* pReference)
  {
    TMail* mail =(TMail*)pCursor;
    (*(int*)pReference) += mail->Size();
  }
}
//---------------------------------------------------------------------------
TCuenta :: TCuenta(AnsiString pUsuario, AnsiString pPassword,AnsiString pAddress, int pCuotaMax,
                   TPerson* pPerson,bool pInternacional)
{
  aUsuario = pUsuario;
  aPassword = pPassword;
  aAddress= pAddress;
  aCuotaMax = pCuotaMax;
  aCuotafree = pCuotaMax;
  aPerson= new TPerson();
  aPerson= pPerson;
  aCorreos = new TGLinkedList();
  aAgendas = new TGLinkedList();
  aInternacional = pInternacional;
}
//---------------------------------------------------------------------------
TCuenta :: ~TCuenta()
{
  aPerson = NULL;
  aUsuario = "";
  aPassword = "";
  aCuotaMax = 0;
  aCuotafree = 0;
  aInternacional = false;
  aCorreos->~TGLinkedList();
  aAgendas->~TGLinkedList();
}
//---------------------------------------------------------------------------
int TCuenta::CuotaOcupM()
{
  int ocup=0;
  aCorreos->ForEach(Daemon::Zise,&ocup);
  return ocup;
}
//---------------------------------------------------------------------------
bool TCuenta :: InsertMail(TMail* pMail)
{
  if (aCuotafree > pMail->Size())
  {
    aCorreos->Insert(pMail);
    aCuotafree = aCuotaMax - CuotaOcupM();
    return true;
  }
  return false;
}
//-----------------------------------------------------------------------------
void TCuenta :: AddAgendaElectronic(AnsiString pNameAgend)
{
  aAgendas->Insert(&pNameAgend);
}
//-----------------------------------------------------------------------------
