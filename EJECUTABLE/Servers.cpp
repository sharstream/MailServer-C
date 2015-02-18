//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("Interfaz.cpp", frmPrincipal);
USEFORM("CrearDomain.cpp", frmCrearDominio);
USEFORM("CrearCuenta.cpp", frmCrearCuenta);
USEFORM("Reportes.cpp", frmReportes);
USEFORM("AccederCuenta.cpp", frmAccederCuenta);
USEFORM("BuzonUsuario.cpp", frmBuzon);
USEFORM("Mensajeria.cpp", frmMensajeria);
USEFORM("SalvarFiles.cpp", frmSaveDBFXML);
USEFORM("CuentaAdmin.cpp", frmCrearCuentaAdmin);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TfrmPrincipal), &frmPrincipal);
                 Application->CreateForm(__classid(TfrmCrearDominio), &frmCrearDominio);
                 Application->CreateForm(__classid(TfrmCrearCuenta), &frmCrearCuenta);
                 Application->CreateForm(__classid(TfrmReportes), &frmReportes);
                 Application->CreateForm(__classid(TfrmAccederCuenta), &frmAccederCuenta);
                 Application->CreateForm(__classid(TfrmBuzon), &frmBuzon);
                 Application->CreateForm(__classid(TfrmMensajeria), &frmMensajeria);
                 Application->CreateForm(__classid(TfrmSaveDBFXML), &frmSaveDBFXML);
                 Application->CreateForm(__classid(TfrmCrearCuentaAdmin), &frmCrearCuentaAdmin);
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
