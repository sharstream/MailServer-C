//---------------------------------------------------------------------------

#ifndef TCuentaH
#define TCuentaH

#include "EstructuraListas.h"
#include "TPerson.h"
#include "TFichero.h"

#include <vcl.h>
//---------------------------------------------------------------------------
class TCuenta
{
  private:
    AnsiString aUsuario;
    AnsiString aPassword;
    AnsiString aAddress;
    int aCuotaMax;       //cuota que le asigna el servidor (cuota max)
    int aCuotafree;    //cuota actual de espacio libre en el buzon de correos
    bool aInternacional;              // salida internacional
    TPerson* aPerson;
    TGLinkedList* aCorreos;
    TGLinkedList* aAgendas;

  public:
    TCuenta(){aCorreos = new TGLinkedList(),aAgendas = new TGLinkedList(),aPerson = new TPerson();}
    TCuenta(AnsiString pUsuario, AnsiString pPassword,AnsiString pAddress, int pCuotaMax,
    TPerson* pPerson,bool pInternacional=true) ;
    ~TCuenta();

    AnsiString Usuario(){return aUsuario;}
    void Usuario(AnsiString pUsuario){aUsuario = pUsuario;}

    AnsiString Password(){return aPassword;}
    void Password(AnsiString pPassword){aPassword = pPassword;}

    AnsiString Address(){return aAddress;}
    void Address(AnsiString pAddress){aAddress = pAddress;}

    TPerson* Person(){return aPerson;}
    void Person(TPerson* pPerson){aPerson = pPerson;}

    int Cuota(){return aCuotaMax;}
    void Cuota(int pCuotaMax){aCuotaMax = pCuotaMax;}

    int Cuotafree(){return aCuotafree;}
    void Cuotafree(int pCuotafree){aCuotafree = pCuotafree;}

    bool Salida(){return aInternacional;}
    void Salida(bool pInternacional){aInternacional = pInternacional;}

    TGLinkedList* Correos(){return aCorreos;}
    void Correos(TGLinkedList* pCorreos){aCorreos = pCorreos;}

    TGLinkedList* Agendas(){return aAgendas;}
    void Agendas(TGLinkedList* pAgendas){aAgendas = pAgendas;}

    void AddAgendaElectronic(AnsiString pNameAgend);

    //Metodos de Acesso a un correo
    bool InsertMail(TMail* pMail);
    int CuotaOcupM();  //espacio ocupado actualmente por esa cuenta
    
};
//---------------------------------------------------------------------------
#endif
 