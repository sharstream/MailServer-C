//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SalvarFiles.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmSaveDBFXML *frmSaveDBFXML;
//---------------------------------------------------------------------------
__fastcall TfrmSaveDBFXML::TfrmSaveDBFXML(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmSaveDBFXML::sbtnDfbClick(TObject *Sender)
{
  if(cbxservers->ItemIndex != -1)
  {
    if(dlgSave->Execute())
    {
      TServidor* server = Admin->FindServer(cbxservers->Text);
      Admin->CrearFileDBF(server->NameDomain(),dlgSave->FileName);
    }
  }
  else
    ShowMessage(" Debe especificar un Servidor ");
}
//---------------------------------------------------------------------------
void __fastcall TfrmSaveDBFXML::FormShow(TObject *Sender)
{
  cbxservers->Clear();
  if(!Admin->Tree()->Empty())
  {
    TGLinkedList* servers = new TGLinkedList();
    Admin->FiltrarServerNacional();
    Admin->AllServers(servers);
    if(servers)
    {
      for(int i = 0; i < servers->Length(); i++)
      {
        TServidor* server = (TServidor*)servers->ItemInfo(i);
        cbxservers->Items->Add(server->NameDomain());
      }
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSaveDBFXML::sbtnXmlClick(TObject *Sender)
{
  if(dlgSave->Execute())
  {
    if(!Admin->Tree()->Empty())
    {
      TGLinkedList* servers = new TGLinkedList();
      Admin->FiltrarServerNacional();
      Admin->AllServers(servers);
      if(servers)
      {
        Admin->SaveXMLServidores(servers,dlgSave->FileName);
      }
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSaveDBFXML::cbxserversKeyPress(TObject *Sender,
      char &Key)
{
Key = 0;        
}
//---------------------------------------------------------------------------

