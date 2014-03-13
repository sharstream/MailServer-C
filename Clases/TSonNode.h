//---------------------------------------------------------------------------

#ifndef TSonNodeH
#define TSonNodeH

#include <vcl.h>
#include "EstructuraListas.h"
//---------------------------------------------------------------------------
class TSonNode
{
  private:
    AnsiString nombre;
    TGLinkedList* listaHijos;

  public:
    TSonNode(){}
    ~TSonNode(){}

    AnsiString Nombre(){return nombre;}
    TGLinkedList* ListaHijos(){return listaHijos;}

    void Nombre(AnsiString pNombre){nombre = pNombre;}
    void ListaHijos(TGLinkedList* lista){listaHijos = lista;}
};
//---------------------------------------------------------------------------
#endif
 