//---------------------------------------------------------------------------

#ifndef AdministradoraH
#define AdministradoraH

#include "TServidor.h"
#include "EstructuraArbolSec.h"
#include "EstructuraBinGral.h"
//inclui la clase nodo hijo que me manipula a la lista de hijo para pintar el arbol en el tree view
#include "TSonNode.h"
#include "UClassDBF.h"

#include  "UFile.h"
//---------------------------------------------------------------------------

#define MAX 10
#define max 20

struct TSAdmin
{
  char user[10];
  char pass[6];
};
//---------------
struct TSDBF
{
  char username[10];
  char password[6];
  char address[20];
};
//---------------
struct TSPosName
{
  AnsiString name;
  int pos;
};     
//---------------
struct TSServerInfo
{
  char Name[MAX];
  int Tope;
  int MaxMail;
};
//---------------
struct TSDomainInfo
{
  char Name[MAX];
  int LinkedRight;
  bool End;
};
//---------------
struct TSAdjunt
{
  char adress[max];
  char tipo[max];
  int length;
};
//---------------
struct TSMail
{
  char asunto[max];
  char remitente[max];
  char parrafo[200];
  int size;
  int adjunts;
};
//---------------
struct TSPerson
{
  char name[max];
  char apellidos[max];
  char sexo;
  Ocupation ocupation;
  int age;
};
//---------------
struct TSAccount
{
  char server[max];
  char usuario[max];
  char password[max];
  char address[max];
  TSPerson persona;
  float cuota;
  float cuotafree;
  bool internacional;
  int emails;
  int agendas;
};
//---------------

//-----------------------------------------------------------------------------
//:::::::::::::CLASE CONTROLADORA QUE RSPONDE MENSAJES DE INTERFAZ:::::::::::::
//-----------------------------------------------------------------------------
class TAdministradora
{
  private:
    TGBinTree* aTree;
    TGLinkedList* aInternacionales;
    TGLinkedList* aNacionalesServers;
    TSeqPreOrderTree* aDomainsPreOrderList;

    //Metodos de accesos
    TServidor* aServerOn;
    TCuenta* aCuentaIn;
    TMail* aMailIn;
    TFichero* afile;
    AnsiString aAdjunto;

    //Administrador
    AnsiString aUsuario;
    AnsiString aPassWord;
    //Caminos del nombre del  ultimo  fichero de cargado/guardado para salvar/cargar por defecto
    AnsiString   aPathSaveFileNDomains;//..camino del file de diagrama de dominio nacional..
    AnsiString   aPathSaveFileNServers;//..del file de servidores nacionales..
    AnsiString   aPathSaveFileIServers;//..del file de servidores Internacional..
    AnsiString   aPathSaveFileAccaounts;//..del file de las cuentas de todos los servidores..
  public:
    TAdministradora(){
                      aTree = new TGBinTree();
                      aInternacionales = new TGLinkedList();
                      aNacionalesServers = new TGLinkedList();
                      aDomainsPreOrderList= new TSeqPreOrderTree(aTree);
                      aServerOn = new TServidor();
                      aMailIn = new TMail();
                      afile = new TFichero();
                      aCuentaIn = new TCuenta();
                      }
    ~TAdministradora(){
                       aTree->~TGBinTree();
                       aInternacionales->~TGLinkedList();
                       aNacionalesServers->~TGLinkedList();
                       delete aDomainsPreOrderList;
                       afile->~TFichero();
                       aMailIn->~TMail();
                       aCuentaIn->~TCuenta();
                       aServerOn->~TServidor();
                      }

//-----------------------------------------------------------------------------
//::::::::::::::::::::::::::::Get/Set de los Atributos:::::::::::::::::::::::::
//-----------------------------------------------------------------------------
    TGBinTree* Tree(){return aTree;}
    void Tree(TGBinTree* pTree){aTree = pTree;}

    TGLinkedList* Internacionales(){return aInternacionales;}
    void Internacionales(TGLinkedList* pInternacionales){aInternacionales = pInternacionales;}

    TGLinkedList* Nacionales(){return aNacionalesServers;}
    void Nacionales(TGLinkedList* pNacionalesServers){aNacionalesServers = pNacionalesServers;}

    TSeqPreOrderTree*  DomainsPreOrderList(){return aDomainsPreOrderList;}
    void  DomainsPreOrderList(TSeqPreOrderTree* pDomainsPreOrderList){aDomainsPreOrderList=pDomainsPreOrderList;}
//-----------------------------------------------------------------------------
//::::::::::::::::::::::::::::::Administrador:::::::::::::::::::::::::::::::::::
//-----------------------------------------------------------------------------
    AnsiString Usuario(){return aUsuario;}
    void Usuario(AnsiString pUsuario){aUsuario = pUsuario;}

    AnsiString PassWord(){return aPassWord;}
    void PassWord(AnsiString pPassWord){aPassWord = pPassWord;}

    //ficherito del administrador
    void SaveAdministradorCuenta(AnsiString pNameFile);
    void LoadAdministradorCuenta(AnsiString pNameFile);
//-----------------------------------------------------------------------------
//:::::::::::::::::::::::::::::: PathSaveFile:::::::::::::::::::::::::::::::::::
//-----------------------------------------------------------------------------
   //..camino del file de diagrama de dominio nacional..
   AnsiString PathSaveFileNDomains(){return aPathSaveFileNDomains;}
   void PathSaveFileNDomains(AnsiString pPathSaveFileNDomains){aPathSaveFileNDomains = pPathSaveFileNDomains;}

   //..del file de servidores nacionales..
   AnsiString PathSaveFileNServers(){return aPathSaveFileNServers;}
   void PathSaveFileNServers(AnsiString pPathSaveFileNServers){aPathSaveFileNServers = pPathSaveFileNServers;}

   //..del file de servidores Internacional..
   AnsiString PathSaveFileIServers(){return aPathSaveFileIServers;}
   void PathSaveFileIServers(AnsiString pPathSaveFileIServers){aPathSaveFileIServers = pPathSaveFileIServers;}

    //..del file de las cuentas de todos los servidores..
   AnsiString PathSaveFileAccaounts(){return aPathSaveFileAccaounts;}
   void PathSaveFileAccaounts(AnsiString pPathSaveFileAccaounts){aPathSaveFileAccaounts = pPathSaveFileAccaounts;}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//<<<<<<<<<<<<<<<<<<<<<<<TRABAJO CON DIAGRAMA DE DOMINIOS>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//-----------------------------------------------------------------------------
//::::::::::::::::::::::::::::FILTRO::::::::::::::::::::::::::::::::::::
//-----------------------------------------------------------------------------
    void FiltrarDominiosNacional(TGLinkedList* pList);
    void FiltrarServerNacional();
//-----------------------------------------------------------------------------
//::::::::::::::::::::::::::::::METODOS PARA ACCEDER AL BUZON Y AL MENSAJE:::::::::::::::::::::::::::::::::::
//-----------------------------------------------------------------------------
    TServidor* ServerOn(){return aServerOn;}
    void ServerOn(TServidor* pServerOn){aServerOn = pServerOn;}

    TCuenta* CuentaIn(){return aCuentaIn;}
    void CuentaIn(TCuenta* pCuentaIn){aCuentaIn = pCuentaIn;}

    TMail* MailIn(){return aMailIn;}
    void MailIn(TMail* pMailIn){aMailIn = pMailIn;}

    TFichero* File(){return afile;}
    void File(TFichero* pfile){afile = pfile;}

    AnsiString Adjunto(){return aAdjunto;}
    void Adjunto(AnsiString pAdjunto){aAdjunto = pAdjunto;}

    //Calcular tamaño archivo adjunto
    int SizeFileAdd(AnsiString);

//-----------------------------------------------------------------------------
//::::::::::::::::::::::::::::::RECURSIVIDAD:::::::::::::::::::::::::::::::::::
//-----------------------------------------------------------------------------
    TGLinkedList* HijosEsteNodo (TGBinTreeNode* node);
    TGLinkedList* NodosDelArbol();
//-----------------------------------------------------------------------------
//::::::::::::::::::::::::::::::BUSCADORES::::::::::::::::::::::::::::::::::::::
//-----------------------------------------------------------------------------
    TDomain* FindDomainNacional(AnsiString pNameDomain);
    TServidor* FindServerNacional(AnsiString pNameServer);
    TDomain* FindDomainFather(AnsiString pNameDomain);
    TServidor* FindServerInternacional(AnsiString pNameServer);
    TServidor* FindServer(AnsiString pName);
//-----------------------------------------------------------------------------
//:::::::::::::::::::::::::::::CREADORES:::::::::::::::::::::::::::::::::::::::
//-----------------------------------------------------------------------------
    //crear servidores internacionales
    void CrearServidoresInternacionales(AnsiString pNameServer, int pTopBuzon, int pMailSze);
    
   //crear dominios en el arbol
    bool CrearDominioTree(AnsiString pName,AnsiString pParent);//crea un dominio en el arbol Nacional
    bool CrearServerTree(AnsiString pName,AnsiString pParentName,int pTopBuzon,int pMailSize);//crea un servidor en el arbol Nacional

    //une las dos listas de servidores
    void AllServers(TGLinkedList* pList);
//-----------------------------------------------------------------------------
//::::::::::::::::::::::::::::VALIDACIONES::::::::::::::::::::::::::::::::::::
//-----------------------------------------------------------------------------
    bool serverexist();
    bool VerificarHijoServidor(AnsiString pNameFather); //no hace falta
    bool VerificarCamino(AnsiString pCamino);           //faltan
    AnsiString SeparadaCadena(AnsiString pCadena);     //faltan
//-----------------------------------------------------------------------------
//::::::::::::::::::::::::::::MODIFICADORES::::::::::::::::::::::::::::::::::::
//-----------------------------------------------------------------------------
    //Modificar la informacion en los dominios del arbol
   TDomain* ModificarDominioNacional(AnsiString Domain,AnsiString pModifyDomain);
   TServidor*  ModificarServerNacional(AnsiString Domain,AnsiString pModifyDomain,int pModifyTope,int ModifyMax);

    //Modificar la informacion de servidores de la lista internacional
    TServidor* ModificarServerInternacional(AnsiString pServer,AnsiString pModifyServer,int pModifyTope,int ModifyMax);
//-----------------------------------------------------------------------------
//::::::::::::::::::::::::::::ELIMINADORES:::::::::::::::::::::::::::::::::::::
//-----------------------------------------------------------------------------
    TServidor* EliminarServerNacional(AnsiString pNameServer);
    TDomain* EliminarDominioNacional(AnsiString pNameServer);
    TServidor* EliminarServerInternacional(AnsiString pNameServer);  //Hecho
//-----------------------------------------------------------------------------

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//<<<<<<<<<<<<<<<<<<<<<<<TRABAJO CON CUENTAS>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//-----------------------------------------------------------------------------
//::::::::::::::::::::::::::::CREADORES UNA DIRECCION:::::::::::::::::::::::::::::::::::::
//-----------------------------------------------------------------------------
    //crea la direccion en un servidor con su cuenta
    AnsiString CreateDirection(TBinTreeNode* pServer,AnsiString pUserNameServer);
    AnsiString AccountAdress(AnsiString pNameServer,AnsiString pUserName);
//-----------------------------------------------------------------------------
//::::::::::::::::::::::::::::BUSCAR UNA CUENTA:::::::::::::::::::::::::::::::::::::
//-----------------------------------------------------------------------------
    TCuenta* FindCuenta(AnsiString pServidor,AnsiString pUserName);
//-----------------------------------------------------------------------------
//::::::::::::::::::::::::::::CREA UNA CUENTA:::::::::::::::::::::::::::::::::::::
//-----------------------------------------------------------------------------
    //crear una cuenta en ambos servidores
    bool CrearCuenta(TCuenta* pCuenta, AnsiString pServer);
//-----------------------------------------------------------------------------
//::::::::::::::::::::::::::::MODIFICA UNA CUENTA:::::::::::::::::::::::::::::::::::::
//-----------------------------------------------------------------------------
    //Modificar la información de una cuenta en ambos servidores
    TCuenta* ModificarCuenta(AnsiString pAccount,TCuenta* pCuenta,AnsiString pServer);
//-----------------------------------------------------------------------------
//::::::::::::::::::::::::::::ELIMINA UNA CUENTA:::::::::::::::::::::::::::::::::::::
//-----------------------------------------------------------------------------
    //Elimina la informacion de una cuenta en ambos servidores
    TCuenta* EliminarCuenta(AnsiString pServer,AnsiString pCuenta);
//-----------------------------------------------------------------------------
//::::::::::::::::::::::::::::METODOS DE ENVIAR UN CORREO:::::::::::::::::::::::::::::::::::::
//-----------------------------------------------------------------------------
    AnsiString ExtractString(AnsiString pName,int &pTam);
    bool SendEmail(TMail* pRebote,TMail* pMail,AnsiString pDestiny,bool IntAccess);
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<FICHEROS>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//-----------------------------------------------------------------------------
//::::::::::::::::::::::::::::NACIONALES::::::::::::::::::::::::::::::::::::::
//-----------------------------------------------------------------------------
    void SaveDominioTree(AnsiString pNameDomain);
    void LoadDomainsNacionales(AnsiString pDomainNacional); //Cargar arbol de dominios nacionales.cu
//-----------------------------------------------------------------------------
    void SaveServersNacionales(AnsiString pServerName);
    void LoadServersNacionales(AnsiString pServerName);
    void PreOrderConvertListToTree(TPreOrderNode* pNode,TPreOrderNode* pFather,TSeqPreOrderTree* pList);
    void MountNacionalServDiagram();
//-----------------------------------------------------------------------------
//::::::::::::::::::::::::::::INTERNACIONALES:::::::::::::::::::::::::::::::::::
//-----------------------------------------------------------------------------
    void SaveServersInternacional(AnsiString pNameFile);
    void LoadServersInternacional(AnsiString pNameFile);
//-----------------------------------------------------------------------------
//::::::::::::::::::::TRABAJO CON LOS FICHEROS CUENTAS::::::::::::::::::::::::::
//::::::::::::::::::::::::::::::::CARGA/GUARDA::::::::::::::::::::::::::::::::::
//-----------------------------------------------------------------------------
    //TGLinkedList* AgendaElectronic(TCuenta* pCuenta);
    //Salvar las cuentas de todos los servidores
    void SaveAccounts(AnsiString pFileName);

    //carga las cuentas de todos los servidores
    void LoadAccounts(AnsiString pFileName);
//-----------------------------------------------------------------------------
//::::::::::::::::::::::::::::::::::FICHERO DBF::::::::::::::::::::::::::::::::::
//-----------------------------------------------------------------------------
    void CrearFileDBF(AnsiString pServerName,AnsiString pFileName);
//-----------------------------------------------------------------------------
//::::::::::::::::::::::::::::::::::FICHERO XML::::::::::::::::::::::::::::::::::
//-----------------------------------------------------------------------------
    void SaveXMLServidores(TGLinkedList* pList, AnsiString pFileName);

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<REPORTES DEL PROYECTO>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

    int TienenCorreos(Ocupation pOcupation); //a)Cuantas personas de un tipo de ocupacion dado tienen correo

    int ContarCuentas(AnsiString pServidor); //b)Conocer cuantas cuentas de correo existen por servidor

    TGLinkedList* ShowPerson(AnsiString pServidor); //c)Mostar las personas de un servidor dado que tienen correo con salidad internacional

    TGLinkedList* ShowUsuariosAscendentes(AnsiString pServidor); //d)Dado un servidor mostrar un listado organizado de usuarios teniendo en cuenta la edad de manera ascendente

    TGLinkedList* ListarServer();    //e)Listado de los servidores del "cu" organizados por cantidad de usuarios descendentemente

    TGLinkedList* BuzonLleno(AnsiString pServidor); //f)Dado un servidor conocer quienes son las personas que tienen el buzon lleno
};
//---------------------------------------------------------------------------
extern TAdministradora* Admin;
//---------------------------------------------------------------------------

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<DEMONIOS DE LAS CLASES>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

namespace Daemon
{
//-----------------------------------------------------------------------------
//:::::::::::::::::::::::::::DEMONIOS DE EL ARBOL:::::::::::::::::::::::::::::::
//-----------------------------------------------------------------------------

  bool FindNodeName(TBinTreeNode* pCursor, void* pReference)
  {
    if (((TDomain*)pCursor->Info())->NameDomain() == *(AnsiString*)pReference)
      return true;
    else
      return false;
  }

  bool FindServerNacional(TBinTreeNode* pCursor, void* pReference)
  {
    if(typeid(*((TDomain*)pCursor->Info())) == typeid(TServidor))
    {
      TServidor* server = (TServidor*)pCursor->Info();
      if(server->NameDomain() == *(AnsiString*)pReference)
        return true;
      else
        return false;
    }
    else
      return false;
  }

  bool FindServerTree(TBinTreeNode* pCursor, void* pReference)
  {
   return (typeid(*((TDomain*)pCursor->Info())) == typeid(TServidor));
  }

  void ListingDomainTree(TBinTreeNode* pCursor, void* pReference)
  {
    if(typeid(*((TDomain*)pCursor->Info())) != typeid(TServidor))
    {
      ((TGLinkedList*)pReference)->Insert((TDomain*)pCursor->Info());
    }
  }

//-----------------------------------------------------------------------------
//:::::::::::::::::::::::::::DEMONIOS DE LISTAS:::::::::::::::::::::::::::::::
//-----------------------------------------------------------------------------

  bool FindNameList(void* pCursor, void* pReference)//busca tanto servidores nacionales como internacionales a la misma vez
  {
    if(((TServidor*)pCursor)->NameDomain() == *(AnsiString*)pReference)
      return true;
    else
      return false;
  }

  bool FindDomainNameList(void* pCursor, void* pReference)
  {
    if( ((TDomain*)((TGBinTreeNode*)pCursor)->Info())->NameDomain() == *(AnsiString*)pReference)
      return true;
    return false;
  }

  bool FindCuenta(void* pCursor, void* pReference)
  {
    return (((TCuenta*)pCursor)->Usuario() == *(AnsiString*)pReference);
  }

  bool FindServerList(void* pCursor, void* pReference)
  {
    return ((TServidor*)pCursor == (TServidor*)pReference);
  }

    bool FindPosNameListServer(void* pCursor, void* pReference)
  {
    TSPosName* PosN = (TSPosName*)pReference;
    PosN->pos++;
    if(((TServidor*)pCursor)->NameDomain() == PosN->name)
      return true;
    else
      return false;
  }

  bool FindPosNameListLeaves(void* pCursor, void* pReference) //utilizamos el Indexof(void*)
  {
    TNode* Node = (TNode*)pCursor;
    TBinTreeNode* TreeNode =(TBinTreeNode*)Node->Info();
    TServidor* server =(TServidor*)TreeNode->Info();
    TSPosName* PosN = (TSPosName*)pReference;
    PosN->pos++;
    if( server->NameDomain() == PosN->name)
      return true;
    else
      return false;
  }

  bool FindPosCuenta(void* pCursor, void* pReference)
  {
    TSPosName* Datos = (TSPosName*)pReference;
    Datos->pos++;
    if(((TCuenta*)pCursor)->Usuario() == Datos->name)
      return true;
    else
      return false;
  }
}
//-----------------------------------------------------------------------------
//::::::::::::::::::::::::::: FIN DE DEMONIOS :::::::::::::::::::::::::::::::::
//-----------------------------------------------------------------------------
#endif
