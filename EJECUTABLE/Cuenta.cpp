//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Cuenta.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

bool cuentas = false;

TfrmCrearCuenta *frmCrearCuenta;
//---------------------------------------------------------------------------
__fastcall TfrmCrearCuenta::TfrmCrearCuenta(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
//::::::::::::::::::::::::::::::::::METODOS DE LA INTERFAZ::::::::::::::::::::
//---------------------------------------------------------------------------
void __fastcall TfrmCrearCuenta::RefreshCuentaLBX()
{
  lbxCuentas->Clear();

  TServidor* este = (TServidor*)Admin->FindServer(cbxServer->Text);
  if(este)
  {
    for(int i = 0; i < este->Cuentas()->Length(); i++)
      lbxCuentas->Items->Add(((TCuenta*)este->Cuentas()->ItemInfo(i))->Usuario());
  }
  else
    ShowMessage("NO existe tal Servidor en este dominio");
}
//---------------------------------------------------------------------------
void __fastcall TfrmCrearCuenta::RefreshEdit(TServidor* pServer)
{
  if(pServer)
  {
    TCuenta* cuenta = (TCuenta*)pServer->Cuentas()->ItemInfo(lbxCuentas->ItemIndex);
    if(cuenta)
    {
      edtUsuario->Text = cuenta->Usuario();
      edtPassword->Text = cuenta->Password();
      edtConfirmar->Text = cuenta->Password();//verlo
      edtCuota->Text = cuenta->Cuota();
      cbInternacional->Checked = cuenta->Salida();
      edtNombre->Text = cuenta->Person()->Name();
      edtApellidos->Text = cuenta->Person()->Apellidos();
      edtEdad->Text = cuenta->Person()->Age();
      cbxSexo->Text = cuenta->Person()->Sexo();

      switch (cuenta->Person()->Ocupacion())
      {
        case Trabajador: cbxOcupacion->Text = "Trabajador" ; break;
        case Estudiante: cbxOcupacion->Text = "Estudiante" ; break;
        case Retirado: cbxOcupacion->Text = "Retirado" ; break;
      }
    }
    else
      ShowMessage("No se ha encontrado esa Cuenta, es posible que no se haya insertado todavia o no existe");
  }
  else
    ShowMessage("No se ha encontrado ese Servidor, es posible que no se haya insertado todavia o no existe");
}
//---------------------------------------------------------------------------
//::::::::::::::::::::::::::::::::::Insert Cuenta:::::::::::::::::::::::::::::
//---------------------------------------------------------------------------
void __fastcall TfrmCrearCuenta::btnCrearClick(TObject *Sender)
{
  if(cbxServer->Text.Length() > 0)
  {
    Ocupation Ocup;
    switch (cbxOcupacion->ItemIndex)
    {
      case 0: Ocup=Trabajador ; break;
      case 1: Ocup=Estudiante ; break;
      case 2: Ocup=Retirado ; break;
    }
    AnsiString Adress = Admin->AccountAdress( cbxServer->Text,edtUsuario->Text);
    TPerson* person = new TPerson(edtNombre->Text,edtApellidos->Text,StrToInt(edtEdad->Text),*(cbxSexo->Text.c_str()),Ocup);
    TCuenta* cuenta = new TCuenta(edtUsuario->Text, edtPassword->Text,Adress,StrToFloat(edtCuota->Text),0,
                                  person,cbInternacional->Checked );

    if(Admin->CrearCuenta(cuenta, cbxServer->Text))
      RefreshCuentaLBX();
    else
      ShowMessage("NO existe tal Servidor en este dominio");
  }
  else
    ShowMessage("Necesita Especificar un Servidor");
}
//---------------------------------------------------------------------------
void __fastcall TfrmCrearCuenta::btnModificarClick(TObject *Sender)
{
  if(cbxServer->Text.Length() > 0)
  {
    Ocupation Ocup;
    switch (cbxOcupacion->ItemIndex)
    {
      case 0: Ocup=Trabajador ; break;
      case 1: Ocup=Estudiante ; break;
      case 2: Ocup=Retirado ; break;
    }
    TPerson* person = new TPerson(edtNombre->Text,edtApellidos->Text,StrToInt(edtEdad->Text),*(cbxSexo->Text.c_str()),Ocup);
    AnsiString Adress = Admin->AccountAdress( cbxServer->Text,edtUsuario->Text);
    TCuenta* cuenta = new TCuenta(edtUsuario->Text, edtPassword->Text,Adress,StrToFloat(edtCuota->Text),0,
                                  person,cbInternacional->Checked );
    if(cuenta)
    {
      TServidor* server = Admin->FindServer(cbxServer->Text);
      TCuenta* change = (TCuenta*)server->Cuentas()->ItemInfo(lbxCuentas->ItemIndex);
      if(Admin->ModificarCuenta(change->Usuario(),cuenta,cbxServer->Text))
        RefreshCuentaLBX();
      else
        ShowMessage("No se ha encontrado esa cuenta, es posible que no se haya insertado todavia o no existe");
    }
  }
  else
    ShowMessage("No se ha encontrado ese Servidor");
}
//---------------------------------------------------------------------------
void __fastcall TfrmCrearCuenta::btnEliminarClick(TObject *Sender)
{
  if(cbxServer->Text.Length() > 0)
  {
    Ocupation Ocup;
    switch (cbxOcupacion->ItemIndex)
    {
      case 0: Ocup=Trabajador ; break;
      case 1: Ocup=Estudiante ; break;
      case 2: Ocup=Retirado ; break;
    }
    TPerson* person = new TPerson(edtNombre->Text,edtApellidos->Text,StrToInt(edtEdad->Text),*(cbxSexo->Text.c_str()),Ocup);
    AnsiString Adress = Admin->AccountAdress( cbxServer->Text,edtUsuario->Text);
    TCuenta* cuenta = new TCuenta(edtUsuario->Text, edtPassword->Text,Adress,StrToFloat(edtCuota->Text),0,
                                  person,cbInternacional->Checked );

    if(Admin->EliminarCuenta(cbxServer->Text,cuenta->Usuario()))
      RefreshCuentaLBX();
    else
      ShowMessage("No se ha encontrado esa cuenta, es posible que no se haya insertado todavia o no existe");
  }
  else
    ShowMessage("No se ha encontrado ese Servidor");
}
//---------------------------------------------------------------------------
void __fastcall TfrmCrearCuenta::edtServerNameKeyPress(TObject *Sender,
      char &Key)
{
  if( !( (Key>='a'&&Key<='z') || (Key>='A' && Key<='Z') ||Key=='Ñ' ||Key=='ñ'||Key==8 || Key==' ')) Key=0;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCrearCuenta::edtCuotaKeyPress(TObject *Sender,
      char &Key)
{
  if( !( (Key>='0'&&Key<='9') || Key==8)) Key=0;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCrearCuenta::lbxCuentasClick(TObject *Sender)
{
  btnModificar->Enabled = true;
  btnEliminar->Enabled = true;
  TServidor* server = Admin->FindServer(cbxServer->Text);
  if(server)
    RefreshEdit(server);
}
//---------------------------------------------------------------------------
void __fastcall TfrmCrearCuenta::cbxServerClick(TObject *Sender)
{
  lbxCuentas->Clear();
  TServidor* server = (TServidor*)Admin->FindServer(cbxServer->Text);
  if(server)
  {
    lbShowMaxBuzon->Caption="MaxBuzon: " + IntToStr(server->Tope()) + " Bytes ";
    lbShowMaxMail->Caption="MaxMail: " + IntToStr(server->Tope()) + " Bytes";
    for(int i = 0; i < server->Cuentas()->Length();i++)
    {
      TCuenta* cuenta = (TCuenta*)server->Cuentas()->ItemInfo(i);
      lbxCuentas->Items->Add(cuenta->Usuario());
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCrearCuenta::mbtnBackClick(TObject *Sender)
{
  Close();
  cbxServer->Clear();
  cbxOcupacion->Clear();
  lbxCuentas->Clear();
  edtUsuario->Clear();
  edtPassword->Clear();
  edtConfirmar->Clear();      //verlo
  edtCuota->Clear();
  cbInternacional->Checked = false;
  edtNombre->Clear();
  edtApellidos->Clear();
  edtEdad->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCrearCuenta::mbtnSaveXMLClick(TObject *Sender)
{
  if(sdSaveXml->Execute())
  {
    TGLinkedList* listxml = new TGLinkedList();
    Admin->AllServers(listxml);
    if(listxml)
      Admin->SaveXMLServidores(listxml,sdSaveXml->FileName);
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCrearCuenta::edtUsuarioChange(TObject *Sender)
{
  if(lbxCuentas->ItemIndex == -1)
  {
    btnModificar->Enabled = false;
    btnEliminar->Enabled = false;
  }
  else
  {
    btnModificar->Enabled = true;
    btnEliminar->Enabled = true;
  }
  if (edtUsuario->Text.Length() > 0 && edtConfirmar->Text.Length() >0 && edtPassword->Text.Length() > 0 && edtCuota->Text.Length()>0 && edtNombre->Text.Length()>0 && edtApellidos->Text.Length() > 0 && edtEdad->Text.Length() > 0 && cbxSexo->Text.Length()>0 && cbxOcupacion->Text.Length() > 0)
    btnCrear->Enabled = true;
  else
    btnCrear->Enabled = false;

  if(edtConfirmar->Text.Length() > 0 && edtConfirmar->Text != edtPassword->Text)
    ShowMessage ("Confirme bien la Contaseña antes de entrar");
}
//---------------------------------------------------------------------------
void __fastcall TfrmCrearCuenta::FormActivate(TObject *Sender)
{
  TGLinkedList* lista = Admin->Internacionales();
  Admin->FiltrarServerNacional();
  TGLinkedList* list = Admin->Nacionales();
  for(int i = 0; i < lista->Length(); i++)
  {
    TServidor* server = (TServidor*)lista->ItemInfo(i);
    cbxServer->Items->Add(server->NameDomain());
  }
  //lista =Admin->Internacionales();
  for(int j = 0; j < list->Length(); j++)
  {
    TServidor* server = (TServidor*)list->ItemInfo(j);
    cbxServer->Items->Add(server->NameDomain());
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCrearCuenta::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  Close();
  cbxServer->Clear();
  cbxOcupacion->Clear();
  lbxCuentas->Clear();
  edtUsuario->Clear();
  edtPassword->Clear();
  edtConfirmar->Clear();      //verlo
  edtCuota->Clear();
  cbInternacional->Checked = false;
  edtNombre->Clear();
  edtApellidos->Clear();
  edtEdad->Clear();
}
//---------------------------------------------------------------------------

