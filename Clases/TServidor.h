//---------------------------------------------------------------------------

#ifndef TServidorH
#define TServidorH

#include "TPerson.h"
#include "TFichero.h"
#include "TCuenta.h"

#include "EstructuraListas.h"
//---------------------------------------------------------------------------
class TDomain
{
  protected:
    AnsiString aNameDomain;
  public:
    TDomain(){}
    TDomain(AnsiString pNameDomain){aNameDomain = pNameDomain;}
    virtual ~TDomain(){}

    AnsiString NameDomain(){return aNameDomain;}
    void NameDomain(AnsiString pNameDomain){aNameDomain = pNameDomain;}
};
//---------------------------------------------------------------------------
class TServidor : public TDomain
{
  private:
    TGLinkedList* aCuentas;
    int aTope;       // Tamaño de el buzon de una cuenta
    int aMax;       //maximo tamaño de elcorreo a envia
  public:
    TServidor(){aCuentas = new TGLinkedList();}
    TServidor(AnsiString pName,int pTope, int pMax);
    virtual ~TServidor();

    TGLinkedList* Cuentas(){return aCuentas;}
    void Cuentas(TGLinkedList* pCuentas){aCuentas = pCuentas;}

    int Tope(){return aTope;}
    void Tope(int pTope){aTope = pTope;}

    int Max(){return aMax;}
    void Max(int pMax){aMax = pMax;}
};
//--------------------------------------------------------------------------
#endif
 