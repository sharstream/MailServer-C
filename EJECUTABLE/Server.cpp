//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("Interfaz.cpp", Form1);
USEFORM("CrearDomain.cpp", frmCrearDominio);
USEFORM("CrearCuenta.cpp", frmCrearCuenta);
USEFORM("Reportes.cpp", frmReportes);
USEFORM("AccederCuenta.cpp", frmAccederCuenta);
USEFORM("BuzonUsuario.cpp", frmBuzon);
USEFORM("Mensajeria.cpp", frmMensajeria);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TForm1), &Form1);
                 Application->CreateForm(__classid(TfrmCrearDominio), &frmCrearDominio);
                 Application->CreateForm(__classid(TfrmCrearCuenta), &frmCrearCuenta);
                 Application->CreateForm(__classid(TfrmReportes), &frmReportes);
                 Application->CreateForm(__classid(TfrmAccederCuenta), &frmAccederCuenta);
                 Application->CreateForm(__classid(TfrmBuzon), &frmBuzon);
                 Application->CreateForm(__classid(TfrmMensajeria), &frmMensajeria);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------
