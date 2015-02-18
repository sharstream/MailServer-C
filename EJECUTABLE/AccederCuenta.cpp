//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AccederCuenta.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmAccederCuenta *frmAccederCuenta;
//---------------------------------------------------------------------------
__fastcall TfrmAccederCuenta::TfrmAccederCuenta(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmAccederCuenta::btnOkClick(TObject *Sender)
{
   TServidor* server = Admin->FindServer(cbxAccederServer->Text);
   if(server)
   {
    Admin->ServerOn(server);
    TCuenta* cuenta = Admin->FindCuenta(cbxAccederServer->Text,edtUser->Text);
    if(cuenta)
    {
      Admin->CuentaIn(cuenta);
      if(cuenta->Password() == edtPassUser->Text)
       frmBuzon->ShowModal();
      else
       ShowMessage("Introduzca la contraseña correcta");
    }
    else
      ShowMessage("La Cuenta "+ edtUser->Text +" no existe, compruebe de nuevo");
  }
  else
    ShowMessage("El Servidor "+ cbxAccederServer->Text +" no existe, vuelva a probar");
}
//---------------------------------------------------------------------------

void __fastcall TfrmAccederCuenta::btnCancelarClick(TObject *Sender)
{
  Close();        
}
//---------------------------------------------------------------------------
void __fastcall TfrmAccederCuenta::edtUserChange(TObject *Sender)
{
  if(edtPassUser->Text.Length() > 0 && edtUser->Text.Length() > 0 && cbxAccederServer->Text.Length() > 0)
  {
    btnOk->Enabled = true;
    btnCancelar->Enabled = true;
  }
  else
  {
    btnOk->Enabled = false;
    btnCancelar->Enabled = false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmAccederCuenta::FormActivate(TObject *Sender)
{
  cbxAccederServer->Clear();
  TGLinkedList* lista = Admin->Internacionales();
  TGLinkedList* list = Admin->Nacionales();
  for(int i = 0; i < lista->Length(); i++)
  {
    TServidor* server = (TServidor*)lista->ItemInfo(i);
    cbxAccederServer->Items->Add(server->NameDomain());
  }
  for(int j = 0; j < list->Length(); j++)
  {
    TServidor* server = (TServidor*)list->ItemInfo(j);
    cbxAccederServer->Items->Add(server->NameDomain());
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmAccederCuenta::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  cbxAccederServer->Clear();
  edtUser->Clear();
  edtPassUser->Clear();
}
//---------------------------------------------------------------------------


