//---------------------------------------------------------------------------

#ifndef SalvarFilesH
#define SalvarFilesH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>

#include "Administradora.h"
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TfrmSaveDBFXML : public TForm
{
__published:	// IDE-managed Components
        TImage *Image1;
        TSpeedButton *sbtnXml;
        TSpeedButton *sbtnDfb;
        TComboBox *cbxservers;
        TSaveDialog *dlgSave;
        void __fastcall sbtnDfbClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall sbtnXmlClick(TObject *Sender);
        void __fastcall cbxserversKeyPress(TObject *Sender, char &Key);
private:	// User declarations
public:		// User declarations
        __fastcall TfrmSaveDBFXML(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSaveDBFXML *frmSaveDBFXML;
//---------------------------------------------------------------------------
#endif
