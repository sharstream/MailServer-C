//---------------------------------------------------------------------------

#ifndef AccederCuentaH
#define AccederCuentaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>

#include "Administradora.h"
#include "BuzonUsuario.h"
//---------------------------------------------------------------------------
class TfrmAccederCuenta : public TForm
{
__published:	// IDE-managed Components
        TImage *Image1;
        TImage *Image2;
        TLabel *Label1;
        TLabel *Label2;
        TButton *btnOk;
        TButton *btnCancelar;
        TComboBox *cbxAccederServer;
        TLabel *Label3;
        TEdit *edtPassUser;
        TEdit *edtUser;
        void __fastcall btnOkClick(TObject *Sender);
        void __fastcall btnCancelarClick(TObject *Sender);
        void __fastcall edtUserChange(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
        __fastcall TfrmAccederCuenta(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAccederCuenta *frmAccederCuenta;
//---------------------------------------------------------------------------
#endif
