//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "BuzonUsuario.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmBuzon *frmBuzon;
//---------------------------------------------------------------------------
__fastcall TfrmBuzon::TfrmBuzon(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuzon::btnRedactClick(TObject *Sender)
{
  TMail* correo = new TMail(NULL,NULL,Admin->CuentaIn()->Address());
  Admin->MailIn(correo);
  frmMensajeria->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuzon::lbxBuzonClick(TObject *Sender)
{
  if(lbxBuzon->ItemIndex > -1)
  {
    btnView->Enabled = true;
    btnDelete->Enabled = true;
  }
  else
  {
    btnView->Enabled = false;
    btnDelete->Enabled = false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuzon::lbxBuzonDblClick(TObject *Sender)
{
  if(lbxBuzon->ItemIndex != -1)
  {
    Admin->MailIn( (TMail*)Admin->CuentaIn()->Correos()->ItemInfo(lbxBuzon->ItemIndex));
    frmMensajeria->ShowModal();
  }
  else
    ShowMessage("Seleccione los datos correctos");
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuzon::btnViewClick(TObject *Sender)
{
  if(lbxBuzon->ItemIndex > -1)
  {
    Admin->MailIn( (TMail*)Admin->CuentaIn()->Correos()->ItemInfo(lbxBuzon->ItemIndex));
    frmMensajeria->ShowModal();
  }
  else
    ShowMessage("Seleccione los datos correctos");
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuzon::VolveralInicio1Click(TObject *Sender)
{
  Close();
  lbxBuzon->Clear();
  lbSizeTop->Caption = " ";
  lbSizeFree->Caption = " ";
  lbSizeInUse->Caption = " ";
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuzon::FormClose(TObject *Sender, TCloseAction &Action)
{
  Close();
  lbxBuzon->Clear();
  lbSizeTop->Caption = " ";
  lbSizeFree->Caption = " ";
  lbSizeInUse->Caption = " ";
  Admin->SaveAccounts(Admin->PathSaveFileAccaounts());
}
//---------------------------------------------------------------------------

void __fastcall TfrmBuzon::btnDeleteClick(TObject *Sender)
{
  if(lbxBuzon->ItemIndex > -1)
  {
    Admin->CuentaIn()->Correos()->Delete(lbxBuzon->ItemIndex);
    lbxBuzon->Clear();
    for(int i = 0; i < Admin->CuentaIn()->Correos()->Length(); i++)
    {
      AnsiString remitent = ((TMail*)Admin->CuentaIn()->Correos()->ItemInfo(i))->Remitente();
      AnsiString subject = ((TMail*)Admin->CuentaIn()->Correos()->ItemInfo(i))->Asunto();
      lbxBuzon->Items->Add(subject + "                        " + remitent);
    }
  }
  else
    ShowMessage("Seleccione el correo que desea borrar");
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuzon::FormActivate(TObject *Sender)
{
  lbxBuzon->Clear();
  TServidor* server = Admin->ServerOn();
  TCuenta* cuenta = Admin->CuentaIn();
  if(cuenta && server)
  {
    lbUser->Caption=  cuenta->Usuario();
    lbSizeTop->Caption = cuenta->Cuota();
    lbSizeFree->Caption = cuenta->Cuotafree();
    lbSizeInUse->Caption = cuenta->CuotaOcupM();

    for(int i = 0; i < cuenta->Correos()->Length(); i++)
    {
      AnsiString mensaje = ((TMail*)cuenta->Correos()->ItemInfo(i))->Asunto() + "                         " +((TMail*)cuenta->Correos()->ItemInfo(i))->Remitente();
      lbxBuzon->Items->Add(mensaje);
    }
  }
  if(cuenta->Cuotafree() == 0)
    ShowMessage("Su Cuenta esta al Tope de Correos, desea liberar espacio en su Buzon");
}
//---------------------------------------------------------------------------



