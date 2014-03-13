//---------------------------------------------------------------------------


#pragma hdrstop

#include "TPerson.h"


//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------
TPerson :: TPerson(AnsiString pName, AnsiString pApellidos, int pAge, char pSexo,Ocupation pOcupation)
{
  aName = pName;
  aApellidos = pApellidos;
  aAge = pAge;
  aSexo= pSexo;
  aOcupation=pOcupation;
}
//---------------------------------------------------------------------------
TPerson :: ~TPerson()
{
  aName = "";
  aApellidos = "";
  aAge = 0;
  aSexo = ' ';
  //aOcupation = 0;
}
//---------------------------------------------------------------------------
