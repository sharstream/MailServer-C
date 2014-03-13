//---------------------------------------------------------------------------

#ifndef TMailH
#define TMailH

#include  "UFile.h"
#include  "EstructuraListas.h"

#include <vcl.h>
//---------------------------------------------------------------------------
class TFichero    //la tratamos despues
{
  private:
    AnsiString aTipo;
    AnsiString aAdress;
    int aSize;

  public:
    TFichero(){}
    TFichero(AnsiString pAdress, int pSize, AnsiString pTipo);
    ~TFichero();

    AnsiString Tipo(){return aTipo;}
    void Tipo(AnsiString pTipo){aTipo = pTipo;}

    AnsiString Adress(){return aAdress;}
    void Adress(AnsiString pAdress){aAdress = pAdress;}

    int Size(){return aSize;}
    void Size(int pSize){aSize = pSize;}
};
//---------------------------------------------------------------------------
class TMail
{
  private:
    AnsiString aParrafo;
    int aSize;
    AnsiString aAsunto;
    AnsiString aRemitente;      //es de donde proviene el mensaje
    TGLinkedList* aAdjunts;    //lista de ficheros adjuntos

  public:
    TMail(){aAdjunts = new TGLinkedList();}
    TMail(AnsiString pParrafo,AnsiString pAsunto,AnsiString pRemitente);
    ~TMail();

    AnsiString Parrafo(){return aParrafo;}
    void Parrafo(AnsiString pParrafo){aParrafo = pParrafo;}

    int Size(){return aSize;}
    void Size(int pSize){aSize = pSize;}

    AnsiString Asunto(){return aAsunto;}
    void Asunto(AnsiString pAsunto){aAsunto = pAsunto;}

    AnsiString Remitente(){return aRemitente;}
    void Remitente(AnsiString pRemitente){aRemitente = pRemitente;}

    TGLinkedList* Adjunts(){return aAdjunts;}
    void Adjunts(TGLinkedList* pAdjunts){aAdjunts = pAdjunts;}

    void InsertAdjunt(TFichero* pFichero);
};
//---------------------------------------------------------------------------

#endif
