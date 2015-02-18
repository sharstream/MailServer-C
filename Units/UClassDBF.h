//---------------------------------------------------------------------------

#ifndef UClassDBFH
#define UClassDBFH

#include "UFile.h"

#define SIZE_HEADER     2
#define SIZE_NAME       11
#define RESERVED_HEADER 20
#define RESERVED_DES    14
#include <dos.h>
#include <conio.h>
#include <iostream.h>
#include <stdio.h>
#include <time.h>
//---------------------------------------------------------------------------
#define RESERVED_HEADER 20
#define RESERVED_DES 14
#define SIZE_NAME 11
#define MAX_REC_SIZE 4000
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

typedef char FieldName[SIZE_NAME];

//Encabezamiento general
typedef struct
{
 unsigned char  aIdent,
                aYear,
                aMonth,
                aDay;
 int            aRecCount;
 unsigned short	aHeaderSize,
                aRecSize;
 char           aReserved[RESERVED_HEADER];
} TSDbfGeneralHeader ;

//descripcion de los campos
typedef struct
{
 FieldName      aName;
 unsigned char  aType;
 int            aRelPosition;
 unsigned char  aLong,
                aDecimal;
 char           aReserved[RESERVED_DES];
} TSDbfFieldDescriptor ;


class TDBF
{
 protected:
        TFile * DbfFile;
        TSDbfGeneralHeader GeneralH;
        TSDbfFieldDescriptor* FieldD;
 public:
       TDBF(AnsiString Name);
       ~TDBF();
       TFile* GetDbfFile(){return DbfFile;};
       void Close();
       void Open();
       bool IsDbf();
       int GetFieldCount(void) ;
       void FillDescriptor();
       void ReadHeader();
       void WriteHeader();
       int GetRecSize(void);
       void MoveToRec( int RecNo = 0);
       void ReadRec(char* pBuff,int RecSize);
       void WriteRec( char * pBuff, int RecSize);
       void Read (char* &pBuff);
       bool EndFileDBF();
       void UpdateHeader(int DelCount = 0, int AddRec = 0);
       void ReadRecInfo( int RecNo, char * pBuff, int RecSize);
       void DeleteRec( int RecNo); //Logical Erase
       void RemoveRec(int RecNo);
       void Write(char * pBuff);
       void Write(void* pBuff, int pPos = -1);  //escribe el record en la posicion dada
       void WriteGH();
       void PosRead(int pos, char* &Buff);
       void AppendRec(char* Buff );
       void Create();

};



#endif
 