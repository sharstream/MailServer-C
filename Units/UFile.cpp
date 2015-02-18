//---------------------------------------------------------------------------
#include <vcl.h>

#pragma hdrstop

#include "UFile.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
TFile::TFile(AnsiString pFileName)
{
 aFileName = pFileName;
 aOpen = false;
}
//---------------------------------------------------------------------------
TFile::~TFile()
{
  try
  {
    Close();
  }
  catch(...)
  {
  };

}
//---------------------------------------------------------------------------
void TFile::Open(const char *pMode)
{
 fFile = fopen( aFileName.c_str(), pMode);
 if (fFile == NULL)
   throw ENoOpen();
 aOpen = True;
}
//---------------------------------------------------------------------------
bool TFile::Eof()
{
 return feof(fFile);
}
//---------------------------------------------------------------------------
void TFile::Remove()
{
 if (!aOpen)
 {
   if(remove(aFileName.c_str()) != 0)
     throw ENoRemove();
  }
  else
    throw ENoClose();
}
//---------------------------------------------------------------------------
bool TFile::FileExists()
{
 return ::FileExists(aFileName);
}
//---------------------------------------------------------------------------
void TFile::Close()
{
  if (aOpen)
  {
   if(fclose(fFile) == 0)
     aOpen = false;
   else
     throw ECantClose();
  }
}
//---------------------------------------------------------------------------
int TFile::Write(void *pInfo, size_t pSize, size_t pCount)
{
  return fwrite(pInfo, pSize, pCount, fFile);
}
//---------------------------------------------------------------------------
int TFile::Read(void* pInfo, size_t pSize, size_t pCount)
{
  return fread(pInfo, pSize, pCount, fFile);
}
//---------------------------------------------------------------------------
void TFile::SeekTo(long pPosition)
{
  if (fseek(fFile, pPosition, SEEK_SET) != 0)
    throw ENoSeek();
}
//---------------------------------------------------------------------------
void TFile::SeekFromCur(long pPositions)
{
 if(fseek(fFile, pPositions, SEEK_CUR) != 0)
   throw ENoSeek();
}
//---------------------------------------------------------------------------
void TFile::SeekFromEnd(long pPosition)
{
 if(fseek(fFile, pPosition, SEEK_END) != 0)
   throw ENoSeek();
}
//---------------------------------------------------------------------------
long TFile::FilePos()
{
 return ftell(fFile);
}
//---------------------------------------------------------------------------
long TFile::FileSize()
{
  long position = ftell(fFile);

  fseek(fFile, 0, SEEK_END);
  long result = ftell(fFile);

  fseek(fFile, position, SEEK_SET);

  return result;
}
//---------------------------------------------------------------------------
void TFile::Rename(AnsiString pName)
{
 if (!aOpen)
 {
  if(rename(aFileName.c_str(),pName.c_str()) != 0)
    throw ENoRename();
  else
    aFileName = pName;
 }
 else
    throw ENoClose();
}
//---------------------------------------------------------------------------
void TFile::WriteS(char pString[])
{
  fputs(pString,fFile);
}
//---------------------------------------------------------------------------
bool TFile::WriteC(char pInfo)
{
  if(pInfo == fputc(pInfo,fFile))
    return true; return false;
}
//---------------------------------------------------------------------------
