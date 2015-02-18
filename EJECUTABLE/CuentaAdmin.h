//---------------------------------------------------------------------------

#ifndef CuentaAdminH
#define CuentaAdminH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <Dialogs.hpp>

#include "Administradora.h"
//---------------------------------------------------------------------------
class TfrmCrearCuentaAdmin : public TForm
{
__published:	// IDE-managed Components
        TImage *Image1;
        TEdit *edtUser;
        TEdit *edtPass;
        TButton *btnOk;
        TButton *btnCancel;
        TLabel *Label1;
        TLabel *Label2;
        TSaveDialog *dlgSaveAdmin;
        void __fastcall btnCancelClick(TObject *Sender);
        void __fastcall btnOkClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TfrmCrearCuentaAdmin(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCrearCuentaAdmin *frmCrearCuentaAdmin;
//---------------------------------------------------------------------------
#endif
