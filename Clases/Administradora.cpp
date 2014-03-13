//---------------------------------------------------------------------------

#pragma hdrstop

#include "Administradora.h"

#include "EstructuraArbolSec.cpp"
#include "EstructuraArbolBin.cpp"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//-----------------------------------------------------------------------------
TAdministradora* Admin;
//-----------------------------------------------------------------------------
//::::::::::::::::::::::::::::::Administrador:::::::::::::::::::::::::::::::::::
//-----------------------------------------------------------------------------
void TAdministradora :: SaveAdministradorCuenta(AnsiString pNameFile)
{
  TFile* administr = new TFile(pNameFile);
  administr->Open("wb");
  if(administr->IsOpen())
  {
    TSAdmin admin;
    strcpy(admin.user,aUsuario.c_str());
    strcpy(admin.pass,aPassWord.c_str());
    administr->Write(&admin,sizeof(TSAdmin));
  }
  administr->Close();
  delete administr;
}
//-----------------------------------------------------------------------------
void TAdministradora :: LoadAdministradorCuenta(AnsiString pNameFile)
{
  TFile* administr = new TFile(pNameFile);
  administr->Open("rb");
  if(administr->IsOpen())
  {
    TSAdmin admin;
    administr->Read(&admin,sizeof(TSAdmin));
    strcpy(aUsuario.c_str(),admin.user);
    AnsiString User = aUsuario.c_str();
    Usuario(User);
    strcpy(aPassWord.c_str(),admin.pass);
    AnsiString Pass = aPassWord.c_str();
    PassWord(Pass);
  }
  administr->Close();
  delete administr;
}
//-----------------------------------------------------------------------------
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//:::::::::::::::::::  METODOS DE CONTROL DE DOMINIOS::::::::::::::::::::::::::
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//::::::::::::::::::::::::::::::VALIDACION:::::::::::::::::::::::::::::::::::
//-----------------------------------------------------------------------------
bool TAdministradora :: serverexist()
{
  if( !( aTree->PreOrderFirstThat(aTree->Root(),Daemon::FindServerTree,NULL) ) && aInternacionales->Empty())
    return false;
  return true;
}
//------------------------------------------------------------------------------
//::::::::::::::::::::::::METODO UTIL DE AYUDA DE FUNCIONES:::::::::::::::::::::
//-----------------------------------------------------------------------------
//---------------------------------------------------------------------------
//.......FILTRO de DOMINIOS.........
void TAdministradora :: FiltrarDominiosNacional(TGLinkedList* pList)
{
    aTree->PreOrderForEach(aTree->Root(),Daemon::ListingDomainTree,pList);
}
//-----------------------------------------------------------------------------
//.......FILTRO de SRVIDORES..........
void TAdministradora :: FiltrarServerNacional() //flitra la lista de hojas del arbol
{
  TGLinkedList*List = new  TGLinkedList();                                           // de dominios y saca solamente los servidores
  for(int i = 0; i < aTree->GetLeaves()->Length(); i++)
  {
    TGBinTreeNode* node = (TGBinTreeNode*)aTree->GetLeaves()->ItemInfo(i);
    if(typeid(*((TDomain*)node->Info())) == typeid(TServidor))
    {
      TServidor* server = (TServidor*)node->Info();
      List->Insert(server);
      aNacionalesServers= List;
    }
  }
}
//-----------------------------------------------------------------------------
//::::::::::::::::::::::::::::::RECURSIVIDAD:::::::::::::::::::::::::::::::::::
//-----------------------------------------------------------------------------
TGLinkedList* TAdministradora :: HijosEsteNodo (TGBinTreeNode* node)
{
  if(!node->IsLeaf())
  {
    TGLinkedList* nodosHijos = aTree->GetSons((TBinTreeNode*)node);

    TGLinkedList* listaHijos = new TGLinkedList();  //del tipo hijoNodos

    for(int i = 0; i < nodosHijos->Length(); i++)
    {
      TBinTreeNode* nodoActual = (TBinTreeNode*)nodosHijos->ItemInfo(i);
      void* elemento = nodoActual->Info();

      TSonNode* nuevoNodo = new TSonNode();

      nuevoNodo->Nombre(((TDomain*)elemento)->NameDomain());

      //buscar el deseado

      TGLinkedList* hijos = HijosEsteNodo((TGBinTreeNode*)nodoActual);

      nuevoNodo->ListaHijos(hijos);

      listaHijos->Insert(nuevoNodo);
    }
    return listaHijos;
  }
  return NULL;
}
//----------------------------------------------------------------------------
TGLinkedList* TAdministradora :: NodosDelArbol()
{
  TBinTreeNode* root = aTree->Root();
  if(root)
    return HijosEsteNodo((TGBinTreeNode*)root);
  return NULL;
}
//-----------------------------------------------------------------------------
//::::::::::::::::::::::::::::::METODOS BUSCADORES::::::::::::::::::::::::::::::::::
//-----------------------------------------------------------------------------
TDomain* TAdministradora::FindDomainNacional(AnsiString pNameDomain)
{
  TGBinTreeNode* domain = (TGBinTreeNode*)aTree->PreOrderFirstThat(aTree->Root(),Daemon::FindNodeName,&pNameDomain);
  if(domain)
    return (TDomain*)domain->Info();
  return NULL;
}
//-----------------------------------------------------------------------------
TServidor* TAdministradora::FindServerNacional(AnsiString pNameServer)
{
   TGBinTreeNode* server = (TGBinTreeNode*)aTree->PreOrderFirstThat(aTree->Root(),Daemon::FindServerNacional,&pNameServer);
   if(server)
     return (TServidor*)server->Info();
   return NULL;
}
//-----------------------------------------------------------------------------
TDomain* TAdministradora:: FindDomainFather(AnsiString pNameDomain)
{
   TBinTreeNode* DomainNode= new TBinTreeNode();
   TDomain* DomainInfo=new TDomain();
   TGBinTreeNode* Subdomain = (TGBinTreeNode*)aTree->PreOrderFirstThat(aTree->Root(),Daemon::FindNodeName,&pNameDomain);
   if(Subdomain)
   {
     DomainNode = aTree->GetFather((TBinTreeNode*)Subdomain);
     if(DomainNode)
       DomainInfo=((TDomain*)DomainNode->Info());
   }
   return DomainInfo;
}
//-----------------------------------------------------------------------------
TServidor* TAdministradora :: FindServerInternacional(AnsiString pNameServer)
{
  TServidor* server = (TServidor*)aInternacionales->FirstThat(Daemon::FindNameList,&pNameServer);
  if(server)
    return server;
  else
    return NULL;
}
//-----------------------------------------------------------------------------
TServidor* TAdministradora :: FindServer(AnsiString pName)
{
  if(FindServerNacional(pName))
    return FindServerNacional(pName);
  else
    return  FindServerInternacional(pName);
}
//-----------------------------------------------------------------------------
//::::::::::::::::::::::::::::::METODOS CREADORES::::::::::::::::::::::::::::::::::
 //-----------------------------------------------------------------------------
void TAdministradora :: CrearServidoresInternacionales(AnsiString pNameServer, int pTopBuzon, int pMailSze)
{
  TServidor* Server = new TServidor(pNameServer,pTopBuzon,pMailSze);
  aInternacionales->Insert(Server);
}
//-----------------------------------------------------------------------------
bool  TAdministradora::CrearDominioTree(AnsiString pName,AnsiString pParentName)
{
  bool create = false;
  TGBinTreeNode* DomainNode;
  TDomain* domain= new TDomain();
  domain->NameDomain(pName);
  DomainNode = new TGBinTreeNode(domain);
  if(aTree->Empty())        //si el arbol esta vacio es por que es la raiz ,y seinsrta como tal
  {
    aTree->Root(DomainNode);
    create = true;
  }
  else
  {    //sino esta vacio el arbol se insertara como subdominio de el padre,que tiene nombre igual aParentName
    TGBinTreeNode* DomainFather = (TGBinTreeNode*)aTree->PreOrderFirstThat(aTree->Root(),Daemon::FindNodeName,&pParentName);
    if(DomainFather)
      create=aTree->InsertNode(DomainNode,DomainFather);
  }
  return create;
}
//-----------------------------------------------------------------------------
bool  TAdministradora::CrearServerTree(AnsiString pName,AnsiString pParentName,int pTopBuzon,int pMailSize)
{
  bool create = false;
  TServidor* servidor = new TServidor(pName,pTopBuzon,pMailSize);
  TGBinTreeNode* DomainNode = new TGBinTreeNode(servidor);

  if(aTree->Empty())  //si el arbol esta vacio es por que es la raiz ,y se inserta como tal
  {
    aTree->Root(DomainNode);
    create = true;
  }
  else
  {   //sino esta vacio el arbol se insertara como subdominio de el padre,que tiene nombre igual aParentNAme
    TGBinTreeNode* DomainFather=(TGBinTreeNode*)aTree->PreOrderFirstThat(aTree->Root(),Daemon::FindNodeName,&pParentName);
    if(DomainFather && DomainNode->IsLeaf())
      create = aTree->InsertNode(DomainNode,DomainFather);
  }
  //aNacionalesServers->Insert(servidor);
  return create;
}
//-----------------------------------------------------------------------------
void TAdministradora :: AllServers(TGLinkedList* pList)
{
  for(int i = 0; i < aNacionalesServers->Length();i++)
    pList->Insert((TServidor*)aNacionalesServers->ItemInfo(i));
  for(int j = 0; j < aInternacionales->Length();j++)
    pList->Insert((TServidor*)aInternacionales->ItemInfo(j));
}
//-----------------------------------------------------------------------------
//::::::::::::::::::::::::::::::METODOS MODIFICADORES::::::::::::::::::::::::::::::::::
//-----------------------------------------------------------------------------
TDomain* TAdministradora :: ModificarDominioNacional(AnsiString Domain,AnsiString pModifyDomain)
{
  TDomain* dominio= NULL;
  dominio = FindDomainNacional(Domain);
  if(dominio)   //si lo encontro
  {
    dominio->NameDomain(pModifyDomain);

  }
  return dominio;
}
//-----------------------------------------------------------------------------
TServidor*  TAdministradora :: ModificarServerNacional(AnsiString Domain,AnsiString pModifyDomain,int pModifyTope,int ModifyMax)
{
  TServidor* Server= NULL;
  Server = FindServer(Domain);
  if(Server)   //si lo encontro
  {
    Server->NameDomain(pModifyDomain);
    Server->Tope(pModifyTope);
    Server->Max(ModifyMax);
    //FiltrarServerNacional();
  }
  return Server;
}
//-----------------------------------------------------------------------------
TServidor* TAdministradora :: ModificarServerInternacional(AnsiString pServer,AnsiString pModifyServer,int pModifyTope,int ModifyMax)
{
  TServidor* Server = FindServerInternacional(pServer);
  if(Server)   //si lo encontro
  {
    Server->NameDomain(pModifyServer);
    Server->Tope(pModifyTope);
    Server->Max(ModifyMax);
  }
  return Server;
}
//-----------------------------------------------------------------------------
//::::::::::::::::::::::::::::::METODOS ELIMINADORES::::::::::::::::::::::::::::::::::
//-----------------------------------------------------------------------------
TDomain* TAdministradora :: EliminarDominioNacional(AnsiString pNameDomain)
{
  TDomain* Domain=NULL;
  TSPosName posname;
  posname.name = pNameDomain;
  posname.pos = -1;
  TGBinTreeNode* node = (TGBinTreeNode*)aTree->PreOrderFirstThat(aTree->Root(),Daemon::FindNodeName,&pNameDomain);
  if(node)
    Domain=(TDomain*)aTree->DeleteNode(node);
  return Domain;
}
//-----------------------------------------------------------------------------
TServidor* TAdministradora :: EliminarServerInternacional(AnsiString pNameServer)
{
  TSPosName posname;
  posname.name = pNameServer;
  posname.pos = -1;
  TServidor* server = (TServidor*)Admin->Internacionales()->FirstThat(Daemon::FindPosNameListServer,&posname);
  if(server)
    server =(TServidor*)aInternacionales->Delete(posname.pos);
  return server;
}
//-----------------------------------------------------------------------------
//::::::::::::::::::: FIN DE METODOS DE CONTROL DE DOMINIOS:::::::::::::::::::
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//::::::::::::::::::: METODOS DE CONTROL DE CUENTAS:::::::::::::::::::
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//::::::::::::::::::::::::::::BUSCADORES DE CUENTAS:::::::::::::::::::::::::::::::::::::
//-----------------------------------------------------------------------------
TCuenta* TAdministradora :: FindCuenta(AnsiString pServidor,AnsiString pUserName)
{
  TServidor* Server = FindServer(pServidor);
  if(Server)
  {
    TCuenta* cuenta = (TCuenta*)Server->Cuentas()->FirstThat(Daemon::FindCuenta,&pUserName);
    if(cuenta)
      return cuenta;
    else
      return NULL;
  }
  else
    return NULL;
}
//-----------------------------------------------------------------------------
//::::::::::::::::::::::::::::CREADORES DE CUENTAS:::::::::::::::::::::::::::::::::::::
//-----------------------------------------------------------------------------
AnsiString TAdministradora :: CreateDirection(TBinTreeNode* pServer,AnsiString pUserNameServer)
{
  AnsiString email = pUserNameServer;
   while(pServer != aTree->Root())
   {
     TDomain* Domain = (TDomain*)pServer->Info();
     email = email + "." + Domain->NameDomain();
     pServer=aTree->GetFather(pServer);
   }
   return email= email +  "." + ( (TDomain*)aTree->Root()->Info() )->NameDomain();
}
//-----------------------------------------------------------------------------
AnsiString TAdministradora :: AccountAdress(AnsiString pNameServer,AnsiString pUserName )
{
  AnsiString  Adress;
  TBinTreeNode* server = aTree->PreOrderFirstThat(aTree->Root(),Daemon::FindServerNacional,&pNameServer);
  if(server)
  {
     TServidor* Servidor= (TServidor*)server->Info();
     AnsiString UserNameServer = pUserName + "@" + Servidor->NameDomain();
     server = aTree->GetFather(server);
     if(server)
       Adress = CreateDirection(server, UserNameServer);
     else
       Adress= UserNameServer;
  }
  else
  {
    TServidor* server = (TServidor*)aInternacionales->FirstThat(Daemon::FindNameList,&pNameServer);
    if(server)
    {
      Adress = pUserName + "@" + server->NameDomain();
    }
  }
  return Adress;
}
//-----------------------------------------------------------------------------
bool TAdministradora :: CrearCuenta(TCuenta* pCuenta, AnsiString pServer)
{
  bool create = false;
  TServidor* server = FindServer(pServer);
  if(server)
  {
    server->Cuentas()->Insert(pCuenta);
    create = true;
  }
  return create;
}
//-----------------------------------------------------------------------------
//::::::::::::::::::::::::::::MODIFICAR UNA CUENTA:::::::::::::::::::::::::::::::::::::
//-----------------------------------------------------------------------------
//Modificar cuenta
TCuenta* TAdministradora :: ModificarCuenta(AnsiString pAccount,TCuenta* pCuenta,AnsiString pServer)
{
  TServidor* Server= FindServer(pServer);
  if(Server)
  {
    TCuenta* cuenta = FindCuenta(pServer,pAccount);
    if(cuenta)
    {
      cuenta->Person(pCuenta->Person());
      cuenta->Usuario(pCuenta->Usuario());
      cuenta->Password(pCuenta->Password());
      cuenta->Cuota(pCuenta->Cuota());
      cuenta->Cuotafree(pCuenta->Cuotafree());
    }
    return cuenta;
  }
  else
    return NULL;
}
//-----------------------------------------------------------------------------
//::::::::::::::::::::::::::::ELIMINAR UNA CUENTA:::::::::::::::::::::::::::::::::::::
//-----------------------------------------------------------------------------
//Elimina Cuenta
TCuenta* TAdministradora :: EliminarCuenta(AnsiString pServer,AnsiString pCuenta)
{
  TSPosName posname;
  posname.name = pCuenta;
  posname.pos = -1;
  TServidor* server = FindServer(pServer);
  if(server)
  {
    TCuenta* cuenta = (TCuenta*)server->Cuentas()->FirstThat(Daemon::FindPosCuenta,&posname);
    if(cuenta)
    {
      void* info = server->Cuentas()->Delete(posname.pos);
      return (TCuenta*)info;
    }
  }
  return NULL;
}
//-----------------------------------------------------------------------------
//::::::::::::::::::::::::::::METODOS DE MANDAR UN CORREO:::::::::::::::::::::::::::::::::::::
//-----------------------------------------------------------------------------
AnsiString TAdministradora :: ExtractString(AnsiString pName, int &pTam)
{
  AnsiString Name;
  char TempArr[20];
  int i=0;
  while( (i <= pTam) && (pName.c_str()[pTam - i] != '.') && (pName.c_str()[pTam - i] != '@') )
  {
    TempArr[i] = pName.c_str()[ pTam-i];
    i++;
  }
  for( int j= 0; j < i; j++)
    Name += TempArr[(i-1)-j];
  pTam = (pTam-i)-1;              // para comerme el pto o la @
  return  Name;
}
//-----------------------------------------------------------------------------
                             //correo de rebote /correo destino / dir de buzon destino /acceso
bool TAdministradora :: SendEmail(TMail* pRebote,TMail* pMail,AnsiString pDestiny, bool IntAccess)//Modoficarlo
{
  AnsiString Problema = " No se pudo mandar el correo a "+ pDestiny +" por la razon siguiente: ";
  AnsiString VerAdministrador = " Por si tiene alguna duda puede contactar con su administrador ";
  void* TempPtr;
  int tam = pDestiny.Length()-1;
  AnsiString RootName = ExtractString(pDestiny,tam);
  //servidor nacional
  if( ((TDomain*)aTree->Root()->Info())->NameDomain() == RootName )         // si coincide con la raiz
  {
    TGBinTreeNode* node = (TGBinTreeNode*)aTree->Root();
    AnsiString NameDomain;
    bool found = true;
    while( !node->IsLeaf() && (found)) //ciclo que recorre el camino buscando el camino de subdominios hasta el servidor donde esta la
    {                                 //cuenta de esa direccion
      NameDomain = ExtractString(pDestiny,tam);
      node = (TGBinTreeNode*)aTree->GetSons(node)->FirstThat(Daemon::FindDomainNameList,&NameDomain);
      if(!node)
      {
        pRebote->Parrafo(Problema + "No hay servidores en ese dominio" + VerAdministrador + pMail->Parrafo());
        found = false;
      }
    }    //en este instante, la direccion solo es el nombre del usuario
         //estas en el server
    if(!found)
      return false;
    if( ((TServidor*)node->Info())->Max() < pMail->Size() )  // si el correo es mayor que lo que admite el servidor destino
    {
      pRebote->Parrafo(Problema + " El tamaño del correo es mayor que el asignado por el servidor de correo a la direccion donde escribio " + VerAdministrador + pMail->Parrafo());
      return false;
    }
    //se busca la cuenta en el server con el ultimo nombre
    TCuenta* cuentadestino = (TCuenta*)((TServidor*)node->Info())->Cuentas()->FirstThat(Daemon::FindCuenta,&NameDomain);
    if(!cuentadestino)
    {
      pRebote->Parrafo(Problema + " La direccion donde escribio el correo es incorrecta o no existe " + VerAdministrador + pMail->Parrafo());
      return false;
    }
    else
    {
      int tamRemit = pRebote->Remitente().Length()-1;   //si es distinto a la raiz nacional es que es internacional
      AnsiString Remit = pRebote->Remitente();
      AnsiString NameDominio = ExtractString(Remit,tamRemit);
      //si del correo que tu le estas escribiendo no es nacional y la cuenta de el no tiene salida internacional entonces
      //no puedes mandar el correo
      if( ((TDomain*)aTree->Root()->Info())->NameDomain() != NameDominio && !cuentadestino->Salida())
      {
        pRebote->Parrafo(Problema + " La cuenta a la que le estas escribiendo no tiene permiso de salida internacional  y no puede responder a usurios externos al cu" + VerAdministrador + pMail->Parrafo());
        return false;
      }
      if(!cuentadestino->InsertMail(pMail))     // dice si el buzon estaba lleno o no
      {
        pRebote->Parrafo(Problema + " El buzon del destinatario esta lleno o desabilitado " + VerAdministrador + pMail->Parrafo());
        return false;
      }
      else
       return true;
    }
  }
   //sino /////////////////
  else
  {
  // servidor internacional/////////////////////////////////////////////////////// david@ yahoo.com
    AnsiString InterName = ExtractString(pDestiny, tam);  //yahoo
    InterName = InterName + '.' + RootName;                      // me da un servidor internacional   yahoo.com
    AnsiString account = ExtractString(pDestiny, tam);
    TServidor* server = (TServidor*)aInternacionales->FirstThat(Daemon::FindNameList,&InterName);
    if(!server)
    {
      pRebote->Parrafo(Problema + " No existe el servidor " + InterName + "para ese Dominio Internacional en esa direccion " + VerAdministrador + pMail->Parrafo());
      return false;
    }
    else
    {
      if(!IntAccess)
      {
        pRebote->Parrafo(Problema + "Esta cuenta no tiene esta autorizada con permiso para Salida Internacional" + VerAdministrador + pMail->Parrafo());
        return false;
      }

      if( server->Max() < pMail->Size() )
      {
        pRebote->Parrafo(Problema + " El tamaño del correo es mayor al asignado por el servidor a su cuenta " + VerAdministrador + VerAdministrador + pMail->Parrafo());
        return false;
      }
    }
    TCuenta* cuenta = (TCuenta*)server->Cuentas()->FirstThat(Daemon::FindCuenta,&account);
    if(!cuenta)
    {
      pRebote->Parrafo(Problema + " El nombre de Usuario "+ account + " no existe en la direccion a donde escribio el correo " + VerAdministrador + pMail->Parrafo());
      return false;
    }
    else
    {
      if(!cuenta->InsertMail(pMail))
     {
      pRebote->Parrafo(Problema + " El buzon del destinatario esta lleno o desabilitado " + VerAdministrador + pMail->Parrafo());
      return false;
     }
     else
      return true;
    }
  }
}
//-----------------------------------------------------------------------------
//::::::::::::::::::: FIN DE LOS METODOS DE CONTROL DE CUENTAS::::::::::::::::::
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//::::::::::::::::::: METODOS DE GUARDAR/CARGAR EN FICHEROS:::::::::::::::::::
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//-----------------------------------------------------------------------------
//Nacionales Domains
void TAdministradora :: SaveDominioTree(AnsiString pNameDomain)
{
  TFile* TreeFile = new TFile(pNameDomain);
  TreeFile->Open("wb");
  TreeFile->SeekTo(0);

  TSeqPreOrderTree* preorder = new TSeqPreOrderTree(aTree);

  if(TreeFile->IsOpen())
  {
    TSDomainInfo SDominio;
    for(int i = 0; i < preorder->Length(); i++)
    {
      TPreOrderNode* node = (TPreOrderNode*)preorder->ItemInfo(i);
      SDominio.End = node->End();
      SDominio.LinkedRight = node->RightLink();
      TDomain* domain = (TDomain*)node->Info();
      strcpy(SDominio.Name,domain->NameDomain().c_str());
      TreeFile->Write(&SDominio,sizeof(TSDomainInfo));
    }
  }
  TreeFile->Close();
  delete TreeFile;
}
//-----------------------------------------------------------------------------
void TAdministradora :: LoadDomainsNacionales(AnsiString pDomainNacional)
{
  TFile* TreeFile = new TFile(pDomainNacional);
  TreeFile->Open("rb+");
  TreeFile->SeekTo(0);

  if(TreeFile->IsOpen())
  {
    TSDomainInfo SDominio;
    TreeFile->Read(&SDominio,sizeof(TSServerInfo));

    while(!TreeFile->Eof())
    {
      TPreOrderNode* node = new  TPreOrderNode();
      TDomain* domain = new TDomain();
      node->End(SDominio.End);
      node->RightLink(SDominio.LinkedRight);
      domain->NameDomain(SDominio.Name);
      node->Info(domain);
      aDomainsPreOrderList->Insert(node);
      TreeFile->Read(&SDominio,sizeof(TSDomainInfo));
    }
  }
  TreeFile->Close();
  delete TreeFile;
}
//-----------------------------------------------------------------------------
//::::::::::::::::::::::::::::LOAD/SAVE SERVERS::::::::::::::::::::::::::::::::::::
//-----------------------------------------------------------------------------
//Nacionales Servers
void TAdministradora :: SaveServersNacionales(AnsiString pServerName)
{
  TFile* serverFile = new TFile(pServerName);
  serverFile->Open("wb");
  serverFile->SeekTo(0);

  if(serverFile->IsOpen())
  {   FiltrarServerNacional();
      TSServerInfo server;

    for(int i = 0; i < aNacionalesServers->Length(); i++)
    {
      TServidor* servidor = (TServidor*)aNacionalesServers->ItemInfo(i);
      server.Tope = servidor->Tope();
      server.MaxMail = servidor->Max();
      strcpy(server.Name,servidor->NameDomain().c_str());
      serverFile->Write(&server,sizeof(TSServerInfo));
    }
  }
  serverFile->Close();
  delete serverFile;
}
//-----------------------------------------------------------------------------
void TAdministradora :: LoadServersNacionales(AnsiString pServerName)
{
  TFile* serverFile = new TFile(pServerName);
  serverFile->Open("rb+");
  serverFile->SeekTo(0);

  if(serverFile->IsOpen())
  {
    TSServerInfo server;
    serverFile->Read(&server,sizeof(TSServerInfo));

    while(!serverFile->Eof())
    {
      TServidor* Servidor = new TServidor();
      Servidor->Tope(server.Tope);
      Servidor->Max(server.MaxMail);
      Servidor->NameDomain(server.Name);
      aNacionalesServers->Insert(Servidor);
      serverFile->Read(&server,sizeof(TSServerInfo));
    }
  }
  serverFile->Close();
  delete serverFile;
}
//-----------------------------------------------------------------------------
void TAdministradora :: PreOrderConvertListToTree(TPreOrderNode* pNode,TPreOrderNode* pFather,TSeqPreOrderTree* pList)
{
  int pos=pList->IndexOf(pNode);
  TDomain* SubDomain= new TDomain();
  TDomain* Domain=new TDomain();
  if(pos >= 0)
  {
    SubDomain= ( TDomain*)( (TPreOrderNode*)pList->ItemInfo(pos) )->Info();
    TGBinTreeNode* Node= new TGBinTreeNode(SubDomain);
    if(!pFather && pos == 0)
    {
      aTree->Root(Node);
      TPreOrderNode* PreNode=(TPreOrderNode*)pList->ItemInfo(pos+1);
      TPreOrderNode* PreNodeFather=(TPreOrderNode*)pList->ItemInfo(pos);
      PreOrderConvertListToTree(PreNode,PreNodeFather,pList);
    }
    else
    {
      int posfather = pList->IndexOf(pFather);
      Domain = (TDomain*)( (TPreOrderNode*)pList->ItemInfo(posfather) )->Info();
      TGBinTreeNode* NodeFather= (TGBinTreeNode*)aTree->PreOrderFirstThat(aTree->Root(),Daemon::FindNodeName,&(Domain->NameDomain()));

      if(NodeFather)
      {
        if(aTree->InsertNode(Node,NodeFather))
        {
          int link=pNode->RightLink();
          if(link > -1)
          {
            TPreOrderNode* PreNode=(TPreOrderNode*)pList->ItemInfo(link);
            PreOrderConvertListToTree(PreNode,pFather,pList);
          }
          if(!(pNode->End()))
          {
           TPreOrderNode* PreNode=(TPreOrderNode*)pList->ItemInfo(pos+1);
           TPreOrderNode* PreNodeFather=(TPreOrderNode*)pList->ItemInfo(pos);
           PreOrderConvertListToTree(PreNode,PreNodeFather,pList);
          }
        }
      }
    }
  }
}
//-----------------------------------------------------------------------------
void TAdministradora :: MountNacionalServDiagram()
{
  TPreOrderNode* preorder = (TPreOrderNode*)aDomainsPreOrderList->ItemInfo(0);
  PreOrderConvertListToTree(preorder,NULL,aDomainsPreOrderList);


  for(int i = 0; i < aNacionalesServers->Length(); i++)
  {
    TServidor* servidor = (TServidor*)aNacionalesServers->ItemInfo(i);
    TGBinTreeNode* node = (TGBinTreeNode*)aTree->PreOrderFirstThat(aTree->Root(),Daemon::FindNodeName,&(servidor->NameDomain()));
    if(node)
      node->Info(servidor);
  }
}
//-----------------------------------------------------------------------------
//Internacionales Servers
void TAdministradora :: SaveServersInternacional(AnsiString pNameFile)
{
  TFile* internacional = new TFile(pNameFile);
  internacional->Open("wb");
  internacional->SeekTo(0);

  if(internacional->IsOpen())
  {
    TSServerInfo server;

    for(int i = 0; i < aInternacionales->Length(); i++)
    {
      TServidor* servidor = (TServidor*)aInternacionales->ItemInfo(i);
      server.Tope = servidor->Tope();
      server.MaxMail = servidor->Max();
      strcpy(server.Name,servidor->NameDomain().c_str());
      internacional->Write(&server,sizeof(TSServerInfo));
    }
  }
  internacional->Close();
  delete internacional;
}
//-----------------------------------------------------------------------------
void TAdministradora::LoadServersInternacional(AnsiString pNameFile)
{
  TFile* internacional = new TFile(pNameFile);
  internacional->Open("rb+");
  internacional->SeekTo(0);

  if(internacional->IsOpen())
  {
    TSServerInfo server;
    internacional->Read(&server,sizeof(TSServerInfo));

    while(!internacional->Eof())
    {
      TServidor* Servidor = new TServidor();
      Servidor->Tope(server.Tope);
      Servidor->Max(server.MaxMail);
      Servidor->NameDomain(server.Name);
      aInternacionales->Insert(Servidor);
      internacional->Read(&server,sizeof(TSServerInfo));
    }
  }
  internacional->Close();
  delete internacional;
}
//-----------------------------------------------------------------------------
//::::::::::::::FIN METODOS DE GUARDAR/CARGAR EN FICHEROS::::::::::::::::::::::::
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//::::::::::::::::::::TRABAJO CON LOS FICHEROS CUENTAS::::::::::::::::::::::::::
//::::::::::::::::::::::::::::::::CARGA/GUARDA::::::::::::::::::::::::::::::::::
//-----------------------------------------------------------------------------
void TAdministradora :: SaveAccounts(AnsiString pFileName) //ver lo del buffer cuando voy a escribir un parrafo
{                                                          //eso hay que arreglarlo
  TFile* AccountFile = new TFile(pFileName);
  AccountFile->Open("wb");
  AccountFile->SeekTo(0);

  if(AccountFile->IsOpen())
  {
    TGLinkedList* servidores = new TGLinkedList();
    AllServers(servidores);
    for(int i = 0; i < servidores->Length(); i++)
    {
      TServidor* Server = (TServidor*)servidores->ItemInfo(i);
      if(Server)
      {
        for(int j = 0; j < Server->Cuentas()->Length(); j++)
        {
          TCuenta* account = (TCuenta*)Server->Cuentas()->ItemInfo(j);
          if(account)
          {
            TSPerson person;
            strcpy(person.name,account->Person()->Name().c_str());
            strcpy(person.apellidos,account->Person()->Apellidos().c_str());
            person.sexo = account->Person()->Sexo();
            person.ocupation = account->Person()->Ocupacion();
            person.age = account->Person()->Age();

            TSAccount cuenta;
            strcpy(cuenta.server,Server->NameDomain().c_str());
            strcpy(cuenta.usuario,account->Usuario().c_str());
            strcpy(cuenta.password,account->Password().c_str());
            strcpy(cuenta.address,account->Address().c_str());
            cuenta.persona = person;
            cuenta.cuota = account->Cuota();
            cuenta.cuotafree = account->Cuotafree();
            cuenta.internacional = account->Salida();
            cuenta.emails = account->Correos()->Length();
            cuenta.agendas = account->Agendas()->Length();

            AccountFile->Write(&cuenta,sizeof(TSAccount)); //primera escritura

            for(int k = 0; k < account->Correos()->Length(); k++)
            {
              TMail* mail = (TMail*)account->Correos()->ItemInfo(k);
              if(mail)
              {
                TSMail correo;
                strcpy(correo.parrafo,mail->Parrafo().c_str());
                strcpy(correo.asunto,mail->Asunto().c_str());
                strcpy(correo.remitente,mail->Remitente().c_str());
                correo.size = mail->Size();
                correo.adjunts = mail->Adjunts()->Length();

                AccountFile->Write(&correo,sizeof(TSMail)); //segunda escritura

                for(int l = 0; l < mail->Adjunts()->Length(); l++)
                {
                  TFichero* file = (TFichero*)mail->Adjunts()->ItemInfo(l);
                  if(file)
                  {
                    TSAdjunt adjunto;
                    strcpy(adjunto.adress,file->Adress().c_str());
                    strcpy(adjunto.tipo,file->Tipo().c_str());
                    adjunto.length = file->Size();

                    AccountFile->Write(&adjunto,sizeof(TSAdjunt)); //tercera escritura
                  }
                }
              }
            }
            for(int c = 0; c < cuenta.agendas; c++)
            {
              AnsiString* name = (AnsiString*)account->Agendas()->ItemInfo(c);
              AnsiString aqui = *name;
              char direccion[36];
              strcpy(direccion,aqui.c_str());
              AccountFile->Write(&direccion,aqui.Length()-1);
            }
          }
        }
      }
    }
  }
  AccountFile->Close();
  delete AccountFile;
}
//-----------------------------------------------------------------------------
void TAdministradora :: LoadAccounts(AnsiString pFileName)//ver lo del buffer cuando voy a escribir un parrafo
{                                                          //eso hay que arreglarlo
  TFile* AccountFile = new TFile(pFileName);
  AccountFile->Open("rb+");
  AccountFile->SeekTo(0);

  if(AccountFile->IsOpen())
  {
    TGLinkedList* Servers = new TGLinkedList();
    AllServers(Servers);
    if(Servers)
    {
      while(AccountFile->FilePos() < AccountFile->FileSize())
      {
        TSAccount account;
        AccountFile->Read(&account,sizeof(TSAccount)); //primera lectura
        AnsiString ServidorNombre = account.server;
        TServidor* Server = (TServidor*)Servers->FirstThat(Daemon::FindNameList,&ServidorNombre);
        if(Server)
        {
          TCuenta* cuenta = new TCuenta();
          cuenta->Usuario(account.usuario);
          cuenta->Password(account.password);
          cuenta->Address(account.address);

          TSPerson person;
          cuenta->Person()->Name(account.persona.name);
          cuenta->Person()->Apellidos(account.persona.apellidos);
          cuenta->Person()->Sexo(account.persona.sexo);
          cuenta->Person()->Ocupacion(account.persona.ocupation);
          cuenta->Person()->Age(account.persona.age);
          cuenta->Cuota(account.cuota);
          cuenta->Cuotafree(account.cuotafree);
          cuenta->Salida(account.internacional);
          Server->Cuentas()->Insert(cuenta);

          int i = 0;
          while(i < account.emails)
          {
            TSMail mail;

            AccountFile->Read(&mail,sizeof(TSMail)); //segunda lectura

            TMail* Mail = new TMail();
            Mail->Parrafo(mail.parrafo);
            Mail->Asunto(mail.asunto);
            Mail->Remitente(mail.remitente);
            Mail->Size(mail.size);
            cuenta->Correos()->Insert(Mail);
            i++;

            int j = 0;
            while(j < mail.adjunts)
            {
              TSAdjunt adjunt;
              AccountFile->Read(&adjunt,sizeof(TSAdjunt)); //tercera lectura
              TFichero* fichero = new TFichero();
              fichero->Adress(adjunt.adress);
              fichero->Tipo(adjunt.tipo);
              fichero->Size(adjunt.length);
              Mail->InsertAdjunt(fichero);
              j++;
            }
          }
          int c = 0;
          while(c < account.agendas)
          {
            char direccion[36];
            AccountFile->Read(&direccion,36);
            AnsiString nombre = direccion;
            cuenta->Agendas()->Insert(&nombre);
          }
        }
      }
    }
  }
  AccountFile->Close();
  delete AccountFile;
}
//-----------------------tamano del fichero adjunto--------------------------------
int TAdministradora :: SizeFileAdd( AnsiString pFileName)
{
  TFile* fileadd = new TFile(pFileName);
  fileadd->Open("rb");
  int size = fileadd->FileSize();
  fileadd->Close();
  delete fileadd;
  return size;
}
//-----------------------------------------------------------------------------
//::::::::::::::::::::::::::::::::::FICHERO DBF::::::::::::::::::::::::::::::::::
//-----------------------------------------------------------------------------
void TAdministradora :: CrearFileDBF(AnsiString pServerName,AnsiString pFileName)
{    //buscar el server
  TServidor* server = FindServer(pServerName);
  if(server)
  {
    TDBF* FileDBF = new TDBF(pFileName);
    char *Buff= new char[36];
    FileDBF->FillDescriptor();
    FileDBF->Open();
    int length = server->Cuentas()->Length();

    for(int i = 0; i < length; i++)
    {
      TCuenta* cuenta = (TCuenta*)server->Cuentas()->ItemInfo(i);

      char  User[10];
      char Pass[6];
      char Add[20];
      strcpy(User,cuenta->Usuario().c_str());
      strcpy(Pass, cuenta->Password().c_str());
      strcpy(Add,cuenta->Address().c_str());


       for(int i = 0; i < 10; i++)
       {
        if(i<cuenta->Usuario().Length())
         {Buff[i]=User[i];}
         else
         {Buff[i]=' ';}
       }
      for(int i = 10; i < 16; i++)
       {
        if(i-10<cuenta->Password().Length())
         {Buff[i]=Pass[i-10];}
         else
         {Buff[i]=' ';}
       }
      for(int i = 16; i < 36; i++)
       {
        if(i-16<cuenta->Address().Length())
         {Buff[i]=Add[i-16];}
         else
         {Buff[i]=' ';}
       }

    FileDBF->AppendRec(Buff);
    }

    FileDBF->Close();
    delete FileDBF;
  }
}
//-----------------------------------------------------------------------------
//::::::::::::::::::::::::::::::::::FICHERO XML::::::::::::::::::::::::::::::::::
//-----------------------------------------------------------------------------
void TAdministradora :: SaveXMLServidores(TGLinkedList* pList, AnsiString pFileName)
{
  TFile* fOut = new TFile(pFileName);
  fOut->Open("wt");

  fOut->WriteS("<?xml version=\"1.0\"?>");
  fOut->WriteS("\n");
  fOut->WriteS("<XML>");
  fOut->WriteS("\n"); //bien hasta aqui

  fOut->WriteS("<SERVERS>");
  fOut->WriteS("\n");

  for (int i = 0; i < pList->Length(); i++)
  {
    TServidor* server = (TServidor*)pList->ItemInfo(i);

    fOut->WriteS("<SERVER>");
    fOut->WriteS("\n");

   fOut->WriteS("<NAME_SERVER>");
    fOut->WriteS("\n");

    fOut->WriteS(server->NameDomain().c_str());
    fOut->WriteS("\n");

    fOut->WriteS("</NAME_SERVER>");
    fOut->WriteS("\n");

    fOut->WriteS("<TOP_ACCOUNTS>");
    fOut->WriteS("\n");

    fOut->WriteS(IntToStr(server->Tope()).c_str());
    fOut->WriteS("\n");

    fOut->WriteS("</TOP_ACCOUNTS>");
    fOut->WriteS("\n");


    fOut->WriteS("<LENGTH_EMAIL>");
    fOut->WriteS("\n");

    fOut->WriteS(IntToStr(server->Max()).c_str());
    fOut->WriteS("\n");

    fOut->WriteS("</LENGTH_EMAIL>");
    fOut->WriteS("\n");

    fOut->WriteS("<ACCOUNTS>");
    fOut->WriteS("\n");

    for(int j = 0; j < server->Cuentas()->Length();j++)
    {
      TCuenta* cuenta = (TCuenta*)server->Cuentas()->ItemInfo(j);

      fOut->WriteS("<ACCOUNT>");
      fOut->WriteS("\n");

      fOut->WriteS("<USER>");
      fOut->WriteS("\n");

      fOut->WriteS(cuenta->Usuario().c_str());
      fOut->WriteS("\n");

      fOut->WriteS("</USER>");
      fOut->WriteS("\n");

      fOut->WriteS("<CUOTA>");
      fOut->WriteS("\n");

      fOut->WriteS(IntToStr(cuenta->Cuota()).c_str());
      fOut->WriteS("\n");

      fOut->WriteS("</CUOTA>");
      fOut->WriteS("\n");


      fOut->WriteS("<PERSON>");
      fOut->WriteS("\n");


      fOut->WriteS("<NAME>");
      fOut->WriteS("\n");

      fOut->WriteS(cuenta->Person()->Name().c_str());
      fOut->WriteS("\n");

       fOut->WriteS("</NAME>");
      fOut->WriteS("\n");

      fOut->WriteS("<APELLIDOS>");
      fOut->WriteS("\n");

      fOut->WriteS(cuenta->Person()->Apellidos().c_str());
      fOut->WriteS("\n");

      fOut->WriteS("</APELLIDOS>");
      fOut->WriteS("\n");

      fOut->WriteS("<SEXO>");
      fOut->WriteS("\n");

      fOut->WriteC(cuenta->Person()->Sexo());
      fOut->WriteS("\n");

      fOut->WriteS("</SEXO>");
      fOut->WriteS("\n");

      fOut->WriteS("</PERSON>");
      fOut->WriteS("\n");

      fOut->WriteS("</ACCOUNT>");
      fOut->WriteS("\n");

    }

    fOut->WriteS("</ACCOUNTS>");
    fOut->WriteS("\n");

    fOut->WriteS("</SERVER>");
    fOut->WriteS("\n");
  }

   fOut->WriteS("</SERVERS>");
   fOut->WriteS("\n");

  fOut->WriteS("</XML>");
  fOut->WriteS("\n");

  fOut->Close();
}
//-----------------------------------------------------------------------------
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//:::::::::::::::::::METODOS DE REPORTES DE EL PROYECTO:::::::::::::::::::
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//-----------------------------------------------------------------------------
int TAdministradora :: TienenCorreos(Ocupation pOcupation) //inciso a)
{
  int count = 0;
  TGLinkedList* list = new TGLinkedList();
  AllServers(list);
  if(list)
  {
    for(int i = 0; i < list->Length(); i++)
    {
      TServidor* server = (TServidor*)list->ItemInfo(i);
      if(server)
      {
        for(int j = 0; j < server->Cuentas()->Length(); j++)
        {
          TCuenta* cuenta = (TCuenta*)server->Cuentas()->ItemInfo(j);
          if( (cuenta) && (cuenta->Person()->Ocupacion() == pOcupation) )
            count++;
        }
      }
    }
  }
  return count;
}
//-----------------------------------------------------------------------------
int TAdministradora :: ContarCuentas(AnsiString pServidor)  //inciso b)
{
  int count = -1;
  TGLinkedList* list = new TGLinkedList();
  AllServers(list);
  if(list)
  {
    TServidor* server = (TServidor*)list->FirstThat(Daemon::FindNameList,&pServidor);
    if(server)
      count = server->Cuentas()->Length();
  }
  return count;
}
//-----------------------------------------------------------------------------
TGLinkedList* TAdministradora :: ShowPerson(AnsiString pServidor) //inciso c)
{
  TGLinkedList* Consalidas = new TGLinkedList();

  TServidor* server = FindServer(pServidor);
  if(server)
  {
    for(int i=0; i < server->Cuentas()->Length(); i++)
    {
      TCuenta* cuneta = (TCuenta*)server->Cuentas()->ItemInfo(i);
      if(cuneta->Salida() == true)
        Consalidas->Insert(((TCuenta*)server->Cuentas()->ItemInfo(i))->Person());
    }
  }
  return Consalidas;
}
//-----------------------------------------------------------------------------
TGLinkedList* TAdministradora :: ShowUsuariosAscendentes(AnsiString pServidor)//inciso d) ordenar de menor a mayor
{
  TGLinkedList* ordenada = new TGLinkedList();
  TServidor* server = FindServer(pServidor);
  if(server)
  {                                          //metodo de ordenamiento por las "Burbujas"
    for(int i=0; i < server->Cuentas()->Length(); i++)
    {
      TCuenta* cuenta = (TCuenta*)server->Cuentas()->ItemInfo(i);
      for(int j=i+1; j < server->Cuentas()->Length(); j++)
      {
        TCuenta* cuenta1 = (TCuenta*)server->Cuentas()->ItemInfo(j);
        if( cuenta->Person()->Age() < cuenta1->Person()->Age())
        {
          cuenta = cuenta1;
          ordenada->Insert(cuenta);
        }
      }
      if(server->Cuentas()->Length() == 1)
        ordenada->Insert(cuenta);
    }
  }
  return ordenada;
}                                              //el inciso e) no hace falta solo llamas FilterServerNational
//-----------------------------------------------------------------------------
TGLinkedList* TAdministradora :: BuzonLleno(AnsiString pServidor) //inciso f)
{
  TGLinkedList* llenos = new TGLinkedList();
  TServidor* server = FindServer(pServidor);
  if(server)
  {
    for(int i = 0; i < server->Cuentas()->Length(); i++)
    {
      TCuenta* cuenta = (TCuenta*)server->Cuentas()->ItemInfo(i);
      if(cuenta->Cuota() == server->Tope())
        llenos->Insert(cuenta->Person());
    }
  }
  return llenos;
}
//-----------------------------------------------------------------------------
//:::::::::::::::::::FIN DE REPORTES DE EL PROYECTO:::::::::::::::::::::::::::::
//-----------------------------------------------------------------------------






























