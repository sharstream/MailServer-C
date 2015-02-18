//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Reportes.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmReportes *frmReportes;
//---------------------------------------------------------------------------
__fastcall TfrmReportes::TfrmReportes(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmReportes::Button1Click(TObject *Sender)
{
  Ocupation Ocup;
  if(cbxOcupation->ItemIndex != -1)
  {
    switch (cbxOcupation->ItemIndex)
   {
    case 0: Ocup=Trabajador ; break;
    case 1: Ocup=Estudiante ; break;
    case 2: Ocup=Retirado ; break;
   }
   int i = Admin->TienenCorreos(Ocup);
   lbOcupation->Caption = IntToStr(i);
  }
  else
    ShowMessage("LLene los datos requeridos");
}
//---------------------------------------------------------------------------
void __fastcall TfrmReportes::Button2Click(TObject *Sender)
{
  if(cbxServer->ItemIndex != -1)
  {
   int i =  Admin->ContarCuentas(cbxServer->Text);
   lbContar->Caption = IntToStr(i);
  }
  else
    ShowMessage("LLene los datos requeridos");
}
//---------------------------------------------------------------------------
void __fastcall TfrmReportes::Button3Click(TObject *Sender)
{
  if(cbxServer->ItemIndex != -1)
  {
    TGLinkedList* list = Admin->ShowPerson(cbxServer->Text);
    for(int i = 0; i < list->Length(); i++)
      lbxPersonas->Items->Add(((TPerson*)list->ItemInfo(i))->Name());
  }
  else
    ShowMessage("LLene los datos requeridos");
}
//---------------------------------------------------------------------------
void __fastcall TfrmReportes::Button4Click(TObject *Sender)
{
  if(cbxServer->ItemIndex != -1)
  {
    TGLinkedList* list = Admin->ShowUsuariosAscendentes(cbxServer->Text);
    for(int i = 0; i < list->Length(); i++)
      lbxUsuarios->Items->Add(((TCuenta*)list->ItemInfo(i))->Usuario());
  }
  else
    ShowMessage("LLene los datos requeridos");
}
//---------------------------------------------------------------------------
void __fastcall TfrmReportes::Button5Click(TObject *Sender)
{
  Admin->FiltrarServerNacional();
  if(Admin->Nacionales())
  {
    for(int i = 0; i < Admin->Nacionales()->Length(); i++)
      lbxServidores->Items->Add(((TServidor*)Admin->Nacionales()->ItemInfo(i))->NameDomain());
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmReportes::Button6Click(TObject *Sender)
{
  if(cbxServer->ItemIndex != -1)
  {
    TGLinkedList* list = Admin->BuzonLleno(cbxServer->Text);
    if(list)
    {
      for(int i = 0; i < list->Length(); i++)
        lbsPersons->Items->Add(((TPerson*)list->ItemInfo(i))->Name());
    }
  }
  else
    ShowMessage("LLene los datos requeridos");
}
//---------------------------------------------------------------------------
void __fastcall TfrmReportes::cbxOcupationKeyPress(TObject *Sender,
      char &Key)
{
  Key = 0;
}
//---------------------------------------------------------------------------
void __fastcall TfrmReportes::FormShow(TObject *Sender)
{
  lbxPersonas->Clear();
  lbxUsuarios->Clear();
  lbxServidores->Clear();
  lbsPersons->Clear();
  cbxServer->Clear();
  TGLinkedList* list = new TGLinkedList();
  Admin->AllServers(list);
  lbContar->Caption = " ";
  lbOcupation->Caption = " ";
  if(list)
  {
    for(int i = 0; i < list->Length(); i++)
      cbxServer->Items->Add(((TServidor*)list->ItemInfo(i))->NameDomain());
  }
}
//---------------------------------------------------------------------------

