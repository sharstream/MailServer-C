//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CrearDomain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TfrmCrearDominio *frmCrearDominio;


//---------------------------------------------------------------------------
__fastcall TfrmCrearDominio::TfrmCrearDominio(TComponent* Owner)
        : TForm(Owner)
{
}
//-----------------------------------------------------------------------------
//::::::::::::::::::::::::::::Funciones de la Iterfaz :::::::::::::
//-----------------------------------------------------------------------------
void __fastcall TfrmCrearDominio::RefreshNacionalCBX()   //refresca cbxNacional
{
  cbxNacional->Clear();
  cbxDomains->Clear();
  TSeqPreOrderTree* preorder = new TSeqPreOrderTree(Admin->Tree());
  if(preorder)
  {
    for(int i = 0; i < preorder->Length(); i++)
    {
      TPreOrderNode* node = (TPreOrderNode*)preorder->ItemInfo(i);
      if(node)
      {
        if(typeid(*((TDomain*)node->Info())) != typeid(TServidor))
          cbxDomains->Items->Add(((TDomain*)node->Info())->NameDomain());
        cbxNacional->Items->Add(((TDomain*)node->Info())->NameDomain());
      }
    }
  }
}
//-----------------------------------------------------------------------------
void __fastcall TfrmCrearDominio::RefreshInterLBX()
{
  lbxInternacional->Clear();
  for(int i = 0; i < Admin->Internacionales()->Length(); i++)
  {
    TServidor* server = (TServidor*)Admin->Internacionales()->ItemInfo(i);
    lbxInternacional->Items->Add(server->NameDomain());
  }
}
//-----------------------------------------------------------------------------
void __fastcall TfrmCrearDominio :: PintarHijos(TSonNode* nodo, TTreeNode* padre)//Recursiva de Pintar TreeView
{
  TGLinkedList* lista = nodo->ListaHijos();

  if(lista)
  {
    for (int i = 0; i < lista->Length(); i++)
    {
      TSonNode* nodo = (TSonNode*)lista->ItemInfo(i);

      TTreeNode* nodoActual = TreeView->Items->AddChild(padre, nodo->Nombre());

      PintarHijos(nodo, nodoActual);
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCrearDominio :: PintarArbol()
{
  TreeView->Items->Clear();

  if(Admin->Tree()->Root()!= NULL)
    TreeView->Items->Add(NULL, ((TDomain*)Admin->Tree()->Root()->Info())->NameDomain()); //crear la raiz

  TGLinkedList* lista = Admin->NodosDelArbol();

  if(lista)
    for (int i = 0; i < lista->Length(); i++)
    {
      TSonNode* nodo = (TSonNode*)lista->ItemInfo(i);

      TTreeNode* nodoActual = TreeView->Items->AddChild(TreeView->Items->Item[0], nodo->Nombre());

      PintarHijos(nodo, nodoActual);
    }
}
//-----------------------------------------------------------------------------
//::::::::::::::::::::::::::::VALIDACIONES:::::::::::::::::::::::::::::::::::::
//-----------------------------------------------------------------------------
void __fastcall TfrmCrearDominio::edtSizeBuzonKeyPress(TObject *Sender,
      char &Key)
{
  if( !( (Key>='0'&&Key<='9') || Key==8)) Key=0;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCrearDominio::cbServerClick(TObject *Sender)
{
  if(cbServer->Checked)
  {
    edtMaxMailSize->Enabled = true;
    edtSizeBuzon->Enabled = true;
  }
  else
  {
    edtMaxMailSize->Enabled = false;
    edtSizeBuzon->Enabled = false;
  }
}
//-----------------------------------------------------------------------------
void __fastcall TfrmCrearDominio::cbxNacionalClick(TObject *Sender)
{
  edtSubDominio->Clear();
  edtMaxMailSize->Clear();
  edtSizeBuzon->Clear();

  TDomain* Domain = Admin->FindDomainFather(cbxNacional->Text);   //busca el padre
  if(Domain)
  {
    cbxDomains->Text= Domain->NameDomain();
    btnModificarDominio->Enabled = true;
    btnEliminarDominio->Enabled = true;
  }
  TDomain* SubDomain= Admin->FindDomainNacional(cbxNacional->Text);
  TServidor* Server= Admin->FindServer(cbxNacional->Text);
  if(Server)
  {
    edtSubDominio->Text=Server->NameDomain();
    cbServer->Checked=true;
    edtMaxMailSize->Text=Server->Max();
    edtSizeBuzon->Text=Server->Tope();
  }
  else    //si no encontro un servidor
  {
    if(SubDomain)
      edtSubDominio->Text= SubDomain->NameDomain();
  } 
}
//-----------------------------------------------------------------------------
//::::::::::::::::::::::::::::INSERTAR DOMINIOS/SERVIDORES::::::::::::::::::::::
//-----------------------------------------------------------------------------
void __fastcall TfrmCrearDominio::btnInsertNClick(TObject *Sender)//entalla faltan algunas validaciones
{
  if( (Admin->FindDomainNacional(cbxDomains->Text)) ||(Admin->Tree()->Empty()) )//si encontro el dominio o la raiz esta vacia inserta un Subdominio
  {
    if(!Admin->FindServerNacional(cbxDomains->Text) )//Si dicho servidor o dominio ya estan insertados
    {
      //BUsco ese Subdominio haber si NO se ha insertado ya..
     if(!Admin->FindDomainNacional(edtSubDominio->Text)||(Admin->Tree()->Empty()))
     {
        if((cbServer->Checked == false ))     //insertar un dominio
       {
          if(Admin->CrearDominioTree(edtSubDominio->Text,cbxDomains->Text))//insertar
          {
           PintarArbol();
           RefreshNacionalCBX();
          }
       }
       else     //si es un servidor a insertar
       {
         if((edtMaxMailSize->Text.Length()>0)&&(edtSizeBuzon->Text.Length()>0))    //campos llenos
         {
           if(Admin->CrearServerTree(edtSubDominio->Text,cbxDomains->Text,StrToInt(edtSizeBuzon->Text),StrToInt(edtMaxMailSize->Text)))
           {
             PintarArbol();
             RefreshNacionalCBX();
           }
         }
         else
          ShowMessage("Introduzca tamaño de  buzon y correo");
        }
      }
      else
       ShowMessage("NO puede insertar Dominios o Servidores con el mismo Nombre ");
    }
    else
      ShowMessage("NO puede insertar Dominios o Servidores como Subdominio de un Servidor ");
  }
  else
    ShowMessage("Especifique un Dominio que ya se haya insertado en el arbol para insertar un Subdominio");
}
//---------------------------------------------------------------------------
void __fastcall TfrmCrearDominio::btnInsertIClick(TObject *Sender)
{
   if( ( edtMaxMailSize->Text.Length()>0) && (edtSizeBuzon->Text.Length()>0) )
   {
     if(!Admin->FindServer(edtSubDominio->Text))
     {
       Admin->CrearServidoresInternacionales(edtSubDominio->Text + ".com", StrToInt(edtSizeBuzon->Text), StrToInt(edtMaxMailSize->Text));
       RefreshInterLBX();
     }
     else
      ShowMessage("Ya inserto un servidor con ese nombre");
   }
   else
     ShowMessage("Introduzca tamaño de correo y buzon");
}
//-----------------------------------------------------------------------------
//::::::::::::::::::::::::::::MODIFICAR DOMINIOS/SERVIDORES::::::::::::::::::::::
//-----------------------------------------------------------------------------
void __fastcall TfrmCrearDominio::btnModificarDominioClick(TObject *Sender)  //arreglar ,refrescar el combobox
{
  btnModificarDominio->Enabled= false;
  btnEliminarDominio->Enabled=false;
  cbxDomains->Enabled=true;
  if(cbServer->Checked == false)
  {
    TDomain* Domain=  Admin->ModificarDominioNacional(cbxNacional->Text,edtSubDominio->Text);
    if(Domain)
      ShowMessage("Se Modifico el Dominio"+ cbxNacional->Text + " con nuevo nombre y datos " + Domain->NameDomain() +" Correctamente");
  }
  else
  {
    if((edtMaxMailSize->Text.Length()>0)&&(edtSizeBuzon->Text.Length()>0))//campos llenos
    {
      TServidor* Server = Admin->ModificarServerNacional(cbxNacional->Text,edtSubDominio->Text,StrToInt(edtSizeBuzon->Text),StrToInt(edtMaxMailSize->Text));
      if(Server)
        ShowMessage("Se Modifico el Servidor " + cbxNacional->Text + " con nuevo nombre y datos " +Server->NameDomain() + " Correctamente");
    }
    else
      ShowMessage("Inserte el tope de buzon y tamaño de correo");
  }
  PintarArbol();
  RefreshNacionalCBX();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCrearDominio::btnModificarInterClick(TObject *Sender)
{
  btnEliminarInter->Enabled=false;
  btnModificarInter->Enabled=false;
  if((edtMaxMailSize->Text.Length()>0)&&(edtSizeBuzon->Text.Length()>0))
  {
    if(lbxInternacional->ItemIndex>-1)
    {
      TServidor* server = (TServidor*)Admin->Internacionales()->ItemInfo(lbxInternacional->ItemIndex);
      AnsiString ServName = server->NameDomain();
      AnsiString newName = edtSubDominio->Text + ".com";
      TServidor* servermodif = Admin->ModificarServerInternacional(ServName,newName,StrToInt(edtSizeBuzon->Text),StrToInt(edtMaxMailSize->Text));
      if(servermodif)
      {
        ShowMessage("Se Modifico el Servidor" +ServName+ "con los datos y nombre" + servermodif->NameDomain() + " Correctamente");
        RefreshInterLBX();
      }
    }
    else
      ShowMessage("Seleccione un servidor de la lista");
  }
  else
    ShowMessage("Inserte el tope de buzon y tamaño de correo");
}
//-----------------------------------------------------------------------------
//::::::::::::::::::::::::::::ELIMINAR DOMINIOS/SERVIDORES::::::::::::::::::::::
//-----------------------------------------------------------------------------
void __fastcall TfrmCrearDominio::btnEliminarDominioClick(TObject *Sender)// funciona
{
  cbxDomains->Enabled=true;
  TDomain* domain = Admin->EliminarDominioNacional(cbxNacional->Text);
  if(domain)
  {
    edtSubDominio->Clear();
    edtSizeBuzon->Clear();
    edtMaxMailSize->Clear();
    cbServer->Checked = false;
    ShowMessage("Se ha eliminado el dominio " + domain->NameDomain() + " correctamente");
  }
  else
    ShowMessage("No existe tal Dominio, es posible que nunca se haya creado o que el nombre sea incorrecto");
  if(Admin->Tree()->Empty())
  {
    Admin->Nacionales()->~TGLinkedList();
  }
  PintarArbol();
  RefreshNacionalCBX();
  btnEliminarDominio->Enabled= false;
  btnModificarDominio->Enabled= false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCrearDominio::btnEliminarInterClick(TObject *Sender)
{
  btnEliminarInter->Enabled=false;
  btnModificarInter->Enabled=false;
  if(lbxInternacional->ItemIndex>-1)
  {
   TServidor* server = (TServidor*)Admin->Internacionales()->ItemInfo(lbxInternacional->ItemIndex);
   if(Admin->EliminarServerInternacional(server->NameDomain()))
   {
      RefreshInterLBX();
      edtSubDominio->Clear();
      edtMaxMailSize->Clear();
      edtSizeBuzon->Clear();
      cbServer->Checked = false;
      cbServer->Checked = true;
      ShowMessage("Se ha borrado el servidor "+ server->NameDomain()+ " correctamente" );
   }
  }
  else
   ShowMessage("Seleccione un servidor de la lista");
}
//-----------------------------------------------------------------------------
//::::::::::::::::::::::::::::GUARDAR/CARGAR DOMINIOS/SERVIDORES::::::::::::::::::::::
//-----------------------------------------------------------------------------
void __fastcall TfrmCrearDominio::mbtnOpenClick(TObject *Sender)
{
  Admin->~TAdministradora();//la destruyo para cargar des de el fichero una nueva clase con instancias de atributos(info) diferentes
  Admin = new TAdministradora();
  if(dlgOpen->Execute())
  {
    Admin->LoadDomainsNacionales(dlgOpen->FileName);
    if(dlgOpen->Execute())
    {
      Admin->LoadServersNacionales(dlgOpen->FileName);
      Admin->MountNacionalServDiagram();
      PintarArbol();
      RefreshNacionalCBX();
      if(dlgOpen->Execute())
      {
        Admin->LoadServersInternacional(dlgOpen->FileName);
        RefreshInterLBX();
      }
    }
    ShowMessage("Finished Load File");
  }
}
//-----------------------------------------------------------------------------
void __fastcall TfrmCrearDominio::mbtnSaveClick(TObject *Sender)
{
  if(dlgSave->Execute())
  {
    Admin->SaveDominioTree(dlgSave->FileName);
    Admin->PathSaveFileNDomains(dlgSave->FileName);

    if(dlgSave->Execute())
    {
      Admin->SaveServersNacionales(dlgSave->FileName);
      Admin->PathSaveFileNServers(dlgSave->FileName);
      if(dlgSave->Execute())
      {
       Admin->SaveServersInternacional(dlgSave->FileName);
       Admin->PathSaveFileIServers(dlgSave->FileName);
       mbtnSaveAll->Enabled=true;
      }
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCrearDominio::mbtnSaveAllClick(TObject *Sender)
{
  Admin->SaveDominioTree(Admin->PathSaveFileNDomains());
  Admin->SaveServersNacionales(Admin->PathSaveFileNServers());
  Admin->SaveServersInternacional( Admin->PathSaveFileIServers());
}
//-----------------------------------------------------------------------------
void __fastcall TfrmCrearDominio::mbtnBackClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCrearDominio::lbxInternacionalClick(TObject *Sender)
{
  edtSubDominio->Clear();
  edtMaxMailSize->Clear();
  edtSizeBuzon->Clear();
  cbServer->Checked = false;
  TServidor* server = (TServidor*)Admin->Internacionales()->ItemInfo(lbxInternacional->ItemIndex);
  if(server)
  {
    if(lbxInternacional->ItemIndex != -1)
    {
      btnModificarInter->Enabled = true;
      btnEliminarInter->Enabled = true;
    }
    edtSubDominio->Text=server->NameDomain();
    cbServer->Checked=true;
    edtMaxMailSize->Text=server->Max();
    edtSizeBuzon->Text=server->Tope();
  }
  else
    ShowMessage("No es posible encontrar ese Servidor");
}
//---------------------------------------------------------------------------
void __fastcall TfrmCrearDominio::TabInternacionalShow(TObject *Sender)
{
  cbxDomains->Hide();
  lbDominio->Hide();
  lbSubDomain->Hide();
  lbServer->Visible= true;
  cbServer->Hide();
  edtMaxMailSize->Enabled = true;
  edtSizeBuzon->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCrearDominio::TabDomainShow(TObject *Sender)
{
  cbxDomains->Visible = true;
  lbDominio->Visible = true;
  lbSubDomain->Visible = true;
  cbServer->Visible = true;
  lbServer->Visible= false;
  cbServer->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCrearDominio::edtSubDominioKeyPress(TObject *Sender,
      char &Key)
{
  if( !( (Key>='a'&&Key<='z') || (Key>='A' && Key<='Z') ||Key=='Ñ' ||Key=='ñ'||Key==8 || Key==' ')) Key=0;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCrearDominio::edtSubDominioChange(TObject *Sender)
{
  if( edtSubDominio->Text.Length() > 0)
  {
    btnInsertN->Enabled = true;
    if(cbxNacional->ItemIndex != -1)
      btnInsertN->Enabled = false;

    btnInsertI->Enabled = true;
  }
  else
  {
    btnInsertN->Enabled = false;
    btnInsertI->Enabled = false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCrearDominio::mbtnAccaountsManageClick(TObject *Sender)
{
  frmCrearCuenta->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCrearDominio::mbtnAccaountsClick(TObject *Sender)
{
  if(Admin->serverexist())
    mbtnAccaountsManage->Enabled = true;
  else
    mbtnAccaountsManage->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCrearDominio::Administrador1Click(TObject *Sender)
{
  frmCrearCuentaAdmin->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCrearDominio::FormActivate(TObject *Sender)
{
  Admin->MountNacionalServDiagram();
  PintarArbol();
  RefreshNacionalCBX();
  RefreshInterLBX();
}
//---------------------------------------------------------------------------


