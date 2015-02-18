//---------------------------------------------------------------------------


#pragma hdrstop

#include "UClassDBF.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

char END_HEADER = 30;
char FileName[] = "ALM_20.DBF";
char FileTemp[] = "filetempdbf.dbf";

TDBF::TDBF(AnsiString Name)
{
  DbfFile = new TFile(Name);
  UpdateHeader(0,0);
  GeneralH.aHeaderSize = 4*32+ 1;
  GeneralH.aIdent = 3;
  GeneralH.aRecCount= 0;
  GeneralH.aRecSize = 36;
  FieldD = new TSDbfFieldDescriptor;
}

TDBF::~TDBF()
{
 Close();
 delete FieldD;
 delete DbfFile;
}
//-----------------------------------------------------------------------------
void TDBF::FillDescriptor()    //crea un DBF nuevo con sus descriptores
 {
   DbfFile->Open("wb");
   WriteGH();

   AnsiString Name = "UserName";
   strcpy(FieldD->aName,Name.c_str());
   FieldD->aType = 'C';
   FieldD->aRelPosition = 1;
   FieldD->aDecimal= 0;
   FieldD->aLong = 10;
   DbfFile->Write(FieldD,sizeof(TSDbfFieldDescriptor));

   Name = "Password";
   strcpy(FieldD->aName,Name.c_str());
   FieldD->aType = 'C';
   FieldD->aRelPosition = 11;
   FieldD->aDecimal= 0;
   FieldD->aLong = 6;
   DbfFile->Write(FieldD,sizeof(TSDbfFieldDescriptor));

   Name = "Address";
   strcpy(FieldD->aName,Name.c_str());
   FieldD->aType = 'C';
   FieldD->aRelPosition = 18;
   FieldD->aDecimal= 0;
   FieldD->aLong = 20;
   DbfFile->Write(FieldD,sizeof(TSDbfFieldDescriptor));

   DbfFile->Write(&END_HEADER,1);
   DbfFile->Close();
}
//-------------------------------------------------------------------------------------------------------
bool TDBF::IsDbf()
{
 DbfFile->SeekTo(0);
 DbfFile->Read(&GeneralH,sizeof(TSDbfGeneralHeader));
 if(GeneralH.aIdent != 3 && GeneralH.aIdent != 131)
  {
   DbfFile->Close();
   return false;
  }
 return true;
}
void TDBF::Open()
{
  DbfFile->Open("r+b");
}
bool TDBF::EndFileDBF()
{
  DbfFile->Eof();
}
int TDBF::GetRecSize(void)
{
 return GeneralH.aRecSize;
}


int TDBF::GetFieldCount(void)
{
 return (GeneralH.aHeaderSize - sizeof(TSDbfGeneralHeader))/sizeof(TSDbfFieldDescriptor);
}
void TDBF::ReadHeader()
{
  if(!IsDbf())  return;
  DbfFile->SeekTo(0);
  DbfFile->Read(&GeneralH,sizeof(TSDbfGeneralHeader));
  int FieldDescCount = GetFieldCount();
  FieldD = new TSDbfFieldDescriptor[FieldDescCount];
  DbfFile->Read(FieldD,sizeof(TSDbfFieldDescriptor),FieldDescCount);
}

void TDBF::WriteHeader()
{
  if(!IsDbf()) return;
  DbfFile->SeekTo(0);
  DbfFile->Write(&GeneralH,sizeof(TSDbfGeneralHeader));
  int FieldDescCount = GetFieldCount();
  DbfFile->Write(FieldD,sizeof(TSDbfFieldDescriptor),FieldDescCount);
  DbfFile->Write(&END_HEADER,sizeof(END_HEADER));
}

void TDBF::MoveToRec(int RecNo)
{
 int pos = GeneralH.aHeaderSize;
 pos = pos + (GetRecSize() * RecNo);
 DbfFile->SeekTo(pos);
}

void TDBF::ReadRec(char* pBuff,int RecSize)
{
  DbfFile->Read(pBuff,sizeof(char),RecSize);
}

void TDBF::WriteRec( char * pBuff, int RecSize)
{
 DbfFile->Write(pBuff,sizeof(char),RecSize);
}

void TDBF::PosRead(int pos, char* &Buff)
{
 MoveToRec(pos);
 Read(Buff);
}
void TDBF::Read (char* &pBuff)
{
  char * Buff = new char[GeneralH.aRecSize];
 memset(Buff,32,GeneralH.aRecSize);
 memset(pBuff,32,GeneralH.aRecSize);
 ReadRec(Buff,GeneralH.aRecSize);
 memcpy(pBuff,Buff + 1,GeneralH.aRecSize-1);
}

void TDBF::UpdateHeader(int DelCount, int AddRec)
{
 unsigned char d,m,a;
struct date dt;
 getdate(&dt);
 d = dt.da_day;
 m = dt.da_mon;
 a = (char)(dt.da_year - 2000);
 GeneralH.aDay = d;
 GeneralH.aMonth = m;
 GeneralH.aYear = a;
 GeneralH.aRecCount -= DelCount;
 GeneralH.aRecCount += AddRec;
}

void TDBF::ReadRecInfo( int RecNo, char * pBuff, int RecSize)
{
  MoveToRec(RecNo);
  ReadRec(pBuff,RecSize);
}

void TDBF::DeleteRec( int RecNo) //Logical Erase//
{
 char * Buff = new char[GetRecSize()];
 if(!IsDbf()) return;
 ReadRecInfo(RecNo,Buff,GetRecSize());
 Buff[0] = '*';
 MoveToRec(RecNo);
 WriteRec(Buff,GetRecSize());
}

 void TDBF::WriteGH()
{
  DbfFile->SeekTo(0);
  DbfFile->Write(&GeneralH,sizeof(TSDbfGeneralHeader));
}

void TDBF::Write(char * pBuff)
{
 char * Buff = new char[GeneralH.aRecSize];
 memset(Buff,32,GeneralH.aRecSize);
 memcpy(Buff + 1,pBuff,GeneralH.aRecSize-1);
 WriteRec(Buff,GeneralH.aRecSize);
 delete Buff;
 }

 void TDBF::RemoveRec(int RecNo)
{
 if(RecNo >= 0 && RecNo < GeneralH.aRecCount)
   DeleteRec(RecNo);
}

 void TDBF::AppendRec(char* Buff )
{
  MoveToRec(GeneralH.aRecCount);
  Write(Buff);
  UpdateHeader(0,1);
  WriteGH();
}

void TDBF::Write(void* pBuff, int pPos)
{
if (pPos != -1)
  DbfFile->SeekTo(GeneralH.aHeaderSize + pPos*GeneralH.aRecSize);
//if (DbfFile->Eof())
  GeneralH.aRecCount = GeneralH.aRecCount + 1;
DbfFile->Write(pBuff,pPos*GeneralH.aRecSize);

DbfFile->SeekTo(0);
DbfFile->Write(&GeneralH,32);
}


void TDBF::Create()
{
 FillDescriptor();
}

void TDBF::Close()
{
DbfFile->Close();
}
