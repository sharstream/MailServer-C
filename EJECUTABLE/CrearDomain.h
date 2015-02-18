//---------------------------------------------------------------------------

#ifndef CrearDomainH
#define CrearDomainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include "CuentaAdmin.h"
#include "CrearCuenta.h"
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TfrmCrearDominio : public TForm
{
__published:	// IDE-managed Components
        TOpenDialog *dlgOpen;
        TSaveDialog *dlgSave;
        TTabSheet *TabDomain;
        TTabSheet *TabInternacional;
        TPageControl *Tab;
        TMainMenu *mmDomains;
        TMenuItem *Inicio;
        TMenuItem *mbtnOpen;
        TMenuItem *mbtnSave;
        TMenuItem *mbtnSaveAll;
        TMenuItem *mbtnBack;
        TListBox *lbxInternacional;
        TButton *btnInsertI;
        TButton *btnModificarInter;
        TButton *btnEliminarInter;
        TImage *Image1;
        TLabel *lbDominio;
        TEdit *edtSubDominio;
        TLabel *lbSubDomain;
        TCheckBox *cbServer;
        TLabel *Label3;
        TEdit *edtSizeBuzon;
        TEdit *edtMaxMailSize;
        TLabel *Label4;
        TTreeView *TreeView;
        TButton *btnInsertN;
        TButton *btnModificarDominio;
        TButton *btnEliminarDominio;
        TComboBox *cbxNacional;
        TComboBox *cbxDomains;
        TLabel *lbServer;
        TMenuItem *mbtnAccaounts;
        TMenuItem *mbtnAccaountsManage;
        TMenuItem *Administrador1;
        void __fastcall btnInsertNClick(TObject *Sender);
        void __fastcall btnInsertIClick(TObject *Sender);
        void __fastcall edtSizeBuzonKeyPress(TObject *Sender, char &Key);
        void __fastcall cbServerClick(TObject *Sender);
        void __fastcall cbxNacionalClick(TObject *Sender);
        void __fastcall btnModificarDominioClick(TObject *Sender);
        void __fastcall btnModificarInterClick(TObject *Sender);
        void __fastcall btnEliminarInterClick(TObject *Sender);
        void __fastcall btnEliminarDominioClick(TObject *Sender);
        void __fastcall mbtnSaveClick(TObject *Sender);
        void __fastcall mbtnSaveAllClick(TObject *Sender);
        void __fastcall mbtnOpenClick(TObject *Sender);
        void __fastcall mbtnBackClick(TObject *Sender);
        void __fastcall lbxInternacionalClick(TObject *Sender);
        void __fastcall TabInternacionalShow(TObject *Sender);
        void __fastcall TabDomainShow(TObject *Sender);
       // void __fastcall cbxNacionalClick(TObject *Sender);
        void __fastcall edtSubDominioKeyPress(TObject *Sender, char &Key);
        void __fastcall edtSubDominioChange(TObject *Sender);
        void __fastcall mbtnAccaountsManageClick(TObject *Sender);
        void __fastcall mbtnAccaountsClick(TObject *Sender);
        void __fastcall Administrador1Click(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
private:	// User declarations
public:		// User declarations

        __fastcall TfrmCrearDominio(TComponent* Owner);
        void __fastcall PintarHijos(TSonNode* nodo, TTreeNode* padre);
        void __fastcall PintarArbol();
        void __fastcall RefreshNacionalCBX();
        void __fastcall RefreshInterLBX();

};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCrearDominio *frmCrearDominio;
//---------------------------------------------------------------------------
#endif
