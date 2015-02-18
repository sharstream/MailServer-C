//---------------------------------------------------------------------------

#ifndef MensajeriaH
#define MensajeriaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include "Administradora.h"
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TfrmMensajeria : public TForm
{
__published:	// IDE-managed Components
        TOpenDialog *dlgAtach;
        TImage *Image1;
        TLabel *lbFromRe;
        TLabel *lbFrom;
        TLabel *lbTo;
        TLabel *lbCC;
        TLabel *lbCCO;
        TLabel *lbTopic;
        TEdit *edtCC;
        TEdit *edtCCO;
        TEdit *edtAsunto;
        TMemo *mmParagraph;
        TLabel *lbAdjunt;
        TEdit *edtAdjunto;
        TButton *btnSend;
        TButton *btnAddAgends;
        TButton *btnCancel;
        TLabel *lbFileSize;
        TLabel *lbAddSize;
        TLabel *lbExten;
        TLabel *lbFileSizeCant;
        TLabel *lbAddsizeCant;
        TLabel *lbExtension;
        TButton *btnDetach;
        TButton *btnAtach;
        TButton *btnAtachBrowse;
        TCheckBox *cbAddFileName;
        TComboBox *cbxAddres;
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall btnSendClick(TObject *Sender);
        void __fastcall btnAtachBrowseClick(TObject *Sender);
        void __fastcall btnAtachClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall btnAddAgendsClick(TObject *Sender);
        void __fastcall btnDetachClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TfrmMensajeria(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMensajeria *frmMensajeria;
//---------------------------------------------------------------------------
#endif
