//---------------------------------------------------------------------------

#ifndef CuentaH
#define CuentaH
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
        TGroupBox *GroupBox4;
        TMainMenu *MainMenu1;
        TMenuItem *mbtnInicio;
        TMenuItem *mbtnAbrir;
        TMenuItem *mbtnGuardar;
        TMenuItem *mbtnSaveTodo;
        TLabel *Label10;
        TComboBox *cbxServer;
        TMenuItem *mbtnSaveXML;
        TMenuItem *mbtnBack;
        TSaveDialog *sdSaveXml;
        TImage *Image1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label11;
        TCheckBox *cbInternacional;
        TEdit *edtUsuario;
        TEdit *edtPassword;
        TEdit *edtConfirmar;
        TEdit *edtCuota;
        TLabel *Label5;
        TEdit *edtNombre;
        TEdit *edtApellidos;
        TLabel *Label6;
        TLabel *Label7;
        TEdit *edtEdad;
        TComboBox *cbxSexo;
        TLabel *Label8;
        TLabel *Label9;
        TComboBox *cbxOcupacion;
        TListBox *lbxCuentas;
        TButton *btnCrear;
        TButton *btnEliminar;
        TButton *btnModificar;
        TLabel *lbServers;
        TLabel *Label1;
        TLabel *Label12;
        TLabel *Label13;
        TLabel *lbShowMaxBuzon;
        TLabel *lbShowMaxMail;
        void __fastcall btnCrearClick(TObject *Sender);
        void __fastcall btnModificarClick(TObject *Sender);
        void __fastcall edtServerNameKeyPress(TObject *Sender, char &Key);
        void __fastcall edtCuotaKeyPress(TObject *Sender, char &Key);
        void __fastcall btnEliminarClick(TObject *Sender);
        void __fastcall lbxCuentasClick(TObject *Sender);
        void __fastcall cbxServerClick(TObject *Sender);
        void __fastcall mbtnBackClick(TObject *Sender);
        void __fastcall mbtnSaveXMLClick(TObject *Sender);
        void __fastcall edtUsuarioChange(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
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
