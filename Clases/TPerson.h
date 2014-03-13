//---------------------------------------------------------------------------

#ifndef TPersonH
#define TPersonH

#include <vcl.h>
//---------------------------------------------------------------------------
typedef enum {Trabajador,Estudiante,Retirado}Ocupation;
//---------------------------------------------------------------------------
class TPerson
{
  private:

    AnsiString aName;
    AnsiString aApellidos;
    int aAge;
    char aSexo;
    Ocupation aOcupation;

  public:

    TPerson(){}
    TPerson(AnsiString pName, AnsiString pApellidos, int pAge, char pSexo, Ocupation pOcupation);
    TPerson(TPerson &copy);
    ~TPerson();

    AnsiString Name(){return aName;}
    void Name(AnsiString pName){aName = pName;}

    AnsiString Apellidos(){return aApellidos;}
    void Apellidos(AnsiString pApellidos){aApellidos = pApellidos;}

    int Age(){return aAge;}
    void Age(int pAge){aAge = pAge;}

    char Sexo(){return aSexo;}
    void Sexo(char pSexo){aSexo = pSexo;}

    Ocupation Ocupacion(){return aOcupation;}
    void Ocupacion(Ocupation pOcupation ){aOcupation = pOcupation;} 
};
//---------------------------------------------------------------------------
#endif
