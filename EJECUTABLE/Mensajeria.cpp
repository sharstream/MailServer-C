//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Mensajeria.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMensajeria *frmMensajeria;
TMail* mail= NULL;
TMail* rebotMail= NULL;
//---------------------------------------------------------------------------
__fastcall TfrmMensajeria::TfrmMensajeria(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmMensajeria::FormActivate(TObject *Sender)
{
  cbxAddres->Clear();
  for(int i = 0; i < Admin->CuentaIn()->Agendas()->Length(); i++)
  {
    String agend = *((String*)Admin->CuentaIn()->Agendas()->ItemInfo(i));
    cbxAddres->Items->Add(agend);
  }

  lbFrom->Caption = Admin->CuentaIn()->Address();
  if(Admin->MailIn()->Remitente() != Admin->CuentaIn()->Address())           //si se esta revisando un correo
  {
    cbxAddres->Text = Admin->MailIn()->Remitente();
    mmParagraph->Text =  Admin->MailIn()->Parrafo();
    edtAsunto->Text =  Admin->MailIn()->Asunto();
    lbFileSizeCant->Caption = Admin->MailIn()->Size();
  }
  else
  {
    lbFileSizeCant->Caption=" ";
    mmParagraph->Text= " ";
    edtAsunto->Text= " Hello ";
    edtAdjunto->Text= " ";
    edtCCO->Text = " ";
    edtCC->Text = " ";
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMensajeria::btnSendClick(TObject *Sender)
{
  rebotMail = new TMail(mmParagraph->Text,"Rebote",lbFrom->Caption);   //correo tuyo
  mail = new TMail(mmParagraph->Text,edtAsunto->Text,lbFrom->Caption);  //correo destino
  if(Admin->SendEmail(rebotMail,mail,cbxAddres->Text,Admin->CuentaIn()->Salida()))
     ShowMessage("Le ha Enviado un Email a la deireccion " + cbxAddres->Text + " exitosamente");
  else
  {
    if(!Admin->CuentaIn()->InsertMail(rebotMail))
      ShowMessage(" Usted tiene su buzon lleno, no podra recibir ningun correo rebote mientras no libere espacio ");
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMensajeria::btnAtachBrowseClick(TObject *Sender)
{
  if(dlgAtach->Execute())
    edtAdjunto->Text = dlgAtach->FileName;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMensajeria::btnAtachClick(TObject *Sender)
{
  int index = edtAdjunto->Text.Length(); // se usa el metodo para extraer..
  AnsiString ext = Admin->ExtractString(edtAdjunto->Text,index);
  if(ext != "")
  {
    cbAddFileName->Caption = edtAdjunto->Text;
    lbExtension->Caption = ext;
    int size = Admin->SizeFileAdd(edtAdjunto->Text);  // calcula el tamaño de el fichero adjunto
    lbAddsizeCant->Caption = IntToStr(size);
    TFichero* Adjunto = new TFichero(edtAdjunto->Text,size,ext);
    Admin->MailIn()->InsertAdjunt(Adjunto);
    cbAddFileName->Enabled = true;
  }
  else
    ShowMessage("La extension de el archivo adjunto no es del tipo TXT, RAR o JPG ");
}
//---------------------------------------------------------------------------
void __fastcall TfrmMensajeria::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  lbFrom->Caption = " ";
}
//---------------------------------------------------------------------------
void __fastcall TfrmMensajeria::btnAddAgendsClick(TObject *Sender)
{
  String adjunt = cbxAddres->Text;
  Admin->CuentaIn()->Agendas()->Insert(&adjunt);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMensajeria::btnDetachClick(TObject *Sender)
{
  if(cbAddFileName->Checked)
  {
    int i = 0;
    bool del = false;
    while(i < Admin->MailIn()->Adjunts()->Length() && !del)
    {
      TFichero* fich = (TFichero*)Admin->MailIn()->Adjunts()->ItemInfo(i);
      if(fich->Adress() == cbAddFileName->Caption)
      {
        del = true;
        Admin->MailIn()->Adjunts()->Delete(i);
        cbAddFileName->Caption = " ";
        lbAddsizeCant->Caption = " ";
        lbExtension->Caption = " ";
        cbAddFileName->Enabled = false;
      }
      i++;
    }
  }
  else
    ShowMessage(" Seleccione el fichero que desea desajuntar ");
}
//---------------------------------------------------------------------------


