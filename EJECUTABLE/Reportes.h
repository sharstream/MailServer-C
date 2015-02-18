//---------------------------------------------------------------------------

#ifndef ReportesH
#define ReportesH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include "Administradora.h"
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TfrmReportes : public TForm
{
__published:	// IDE-managed Components
        TImage *Image1;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *lbOcupation;
        TLabel *lbContar;
        TLabel *Label9;
        TLabel *Label10;
        TLabel *Label13;
        TLabel *Label12;
        TButton *Button1;
        TButton *Button2;
        TButton *Button3;
        TButton *Button5;
        TButton *Button6;
        TButton *Button4;
        TListBox *lbxUsuarios;
        TListBox *lbsPersons;
        TListBox *lbxServidores;
        TListBox *lbxPersonas;
        TComboBox *cbxOcupation;
        TComboBox *cbxServer;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall cbxOcupationKeyPress(TObject *Sender, char &Key);
        void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TfrmReportes(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmReportes *frmReportes;
//---------------------------------------------------------------------------
#endif
