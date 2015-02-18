//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CuentaAdmin.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmCrearCuentaAdmin *frmCrearCuentaAdmin;
//---------------------------------------------------------------------------
__fastcall TfrmCrearCuentaAdmin::TfrmCrearCuentaAdmin(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmCrearCuentaAdmin::btnCancelClick(TObject *Sender)
{
  Close();        
}
//---------------------------------------------------------------------------
void __fastcall TfrmCrearCuentaAdmin::btnOkClick(TObject *Sender)
{
  if(dlgSaveAdmin->Execute())
  {
    Admin->Usuario(edtUser->Text);
    Admin->PassWord(edtPass->Text);
    Admin->SaveAdministradorCuenta(dlgSaveAdmin->FileName);
  }
}
//---------------------------------------------------------------------------
