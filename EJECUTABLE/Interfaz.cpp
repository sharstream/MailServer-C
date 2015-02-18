//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Interfaz.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TfrmPrincipal *frmPrincipal;
//---------------------------------------------------------------------------
__fastcall TfrmPrincipal::TfrmPrincipal(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::FormCreate(TObject *Sender)
{
  Admin = new TAdministradora();
  Admin->LoadAdministradorCuenta("adminsitrador.dat");
  Admin->LoadDomainsNacionales("Nacionales.dat");
  Admin->LoadServersNacionales("Servidores Nacionales.dat");
  Admin->LoadServersInternacional("Servidores internacionales.dat");
  Admin->LoadAccounts("cuenta con correos y sin agenda.dat");
  Admin->PathSaveFileAccaounts("cuenta con correos y sin agenda.dat");
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::FormClose(TObject *Sender, TCloseAction &Action)
{
  delete Admin;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::Incisos1Click(TObject *Sender)
{
  frmReportes->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::RevisarCorreo1Click(TObject *Sender)
{
  frmAccederCuenta->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::mbtnSaveFilesClick(TObject *Sender)
{
  frmSaveDBFXML->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnAceptarClick(TObject *Sender)
{
 if( edtPass->Text == Admin->PassWord() && edtUser->Text == Admin->Usuario())
   frmCrearDominio->ShowModal();
 else
   ShowMessage("Verifique su Nombre de Usuario y/o Contraseña y que tenga privilegios de Administrador");
}
//---------------------------------------------------------------------------




