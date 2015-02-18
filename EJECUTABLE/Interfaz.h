//---------------------------------------------------------------------------

#ifndef InterfazH
#define InterfazH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>

#include "CrearDomain.h"
#include "Reportes.h"
#include "AccederCuenta.h"
#include "SalvarFiles.h"

#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TfrmPrincipal : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu1;
        TMenuItem *Correo1;
        TMenuItem *RevisarCorreo1;
        TMenuItem *Reportes1;
        TMenuItem *Incisos1;
        TMenuItem *mbtnSaveFiles;
        TImage *Image1;
        TEdit *edtUser;
        TEdit *edtPass;
        TButton *btnAceptar;
        TLabel *Label1;
        TLabel *Label2;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Incisos1Click(TObject *Sender);
        void __fastcall RevisarCorreo1Click(TObject *Sender);
        void __fastcall mbtnSaveFilesClick(TObject *Sender);
        void __fastcall btnAceptarClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TfrmPrincipal(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmPrincipal *frmPrincipal;
//---------------------------------------------------------------------------
#endif
