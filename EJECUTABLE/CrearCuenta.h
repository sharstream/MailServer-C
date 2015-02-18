//---------------------------------------------------------------------------

#ifndef CrearCuentaH
#define CrearCuentaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include "Administradora.h"

#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TfrmCrearCuenta : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu1;
        TSaveDialog *dlgSaveCuentas;
        TOpenDialog *dlgOpenCuentas;
        TMenuItem *Satrts1;
        TMenuItem *mbtnAbrir;
        TMenuItem *mbtnGuardar;
        TMenuItem *mbtnSaveAll;
        TMenuItem *mbtnBack;
        TImage *Image1;
        TLabel *lbServers;
        TComboBox *cbxServer;
        TLabel *lbShowMaxBuzon;
        TLabel *lbShowMaxMail;
        TLabel *Label13;
        TLabel *Label12;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label11;
        TEdit *edtUsuario;
        TEdit *edtPassword;
        TEdit *edtConfirmar;
        TEdit *edtCuota;
        TCheckBox *cbInternacional;
        TLabel *Label7;
        TLabel *Label6;
        TLabel *Label5;
        TLabel *Label9;
        TComboBox *cbxOcupacion;
        TComboBox *cbxSexo;
        TLabel *Label8;
        TEdit *edtEdad;
        TEdit *edtApellidos;
        TEdit *edtNombre;
        TListBox *lbxCuentas;
        TButton *btnCrear;
        TButton *btnEliminar;
        TButton *btnModificar;
        TImage *Image2;
        TImage *Image3;
        void __fastcall btnCrearClick(TObject *Sender);
        void __fastcall btnModificarClick(TObject *Sender);
        void __fastcall edtCuotaKeyPress(TObject *Sender, char &Key);
        void __fastcall btnEliminarClick(TObject *Sender);
        void __fastcall lbxCuentasClick(TObject *Sender);
        void __fastcall cbxServerClick(TObject *Sender);
        void __fastcall mbtnBackClick(TObject *Sender);
        void __fastcall edtUsuarioChange(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall mbtnGuardarClick(TObject *Sender);
        void __fastcall mbtnAbrirClick(TObject *Sender);
        void __fastcall cbxSexoKeyPress(TObject *Sender, char &Key);
        void __fastcall edtUsuarioKeyPress(TObject *Sender, char &Key);
        void __fastcall edtConfirmarEnter(TObject *Sender);
        void __fastcall mbtnSaveAllClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TfrmCrearCuenta(TComponent* Owner);
        void __fastcall RefreshCuentaLBX();
        void __fastcall RefreshEdit(TServidor* pServer);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCrearCuenta *frmCrearCuenta;
//---------------------------------------------------------------------------
#endif
