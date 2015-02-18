//---------------------------------------------------------------------------

#ifndef BuzonUsuarioH
#define BuzonUsuarioH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>

#include "Administradora.h"
#include "Mensajeria.h"

#include <jpeg.hpp>
#include <ComCtrls.hpp>

//---------------------------------------------------------------------------
class TfrmBuzon : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu1;
        TMenuItem *Inicio1;
        TMenuItem *Herramientas1;
        TMenuItem *mbtnOpenMail;
        TMenuItem *mbtnSaveMail;
        TMenuItem *VolveralInicio1;
        TImage *Image1;
        TListBox *lbxBuzon;
        TButton *btnRedact;
        TButton *btnDelete;
        TButton *btnView;
        TLabel *Label4;
        TLabel *Label3;
        TLabel *Label5;
        TLabel *lbSizeTop;
        TLabel *lbSizeInUse;
        TLabel *lbSizeFree;
        TLabel *lbOwner;
        TLabel *lbUser;
        void __fastcall btnRedactClick(TObject *Sender);
        void __fastcall lbxBuzonClick(TObject *Sender);
        void __fastcall btnViewClick(TObject *Sender);
        void __fastcall VolveralInicio1Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall btnDeleteClick(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall lbxBuzonDblClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TfrmBuzon(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmBuzon *frmBuzon;
//---------------------------------------------------------------------------
#endif
