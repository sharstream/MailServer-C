//---------------------------------------------------------------------------

#ifndef UFileH
#define UFileH

#include <stdio.h>
#include <time.h>
#include <system.hpp>
//---------------------------------------------------------------------------
/*         aMode  type

                r	Open for reading only.
                w	Create for writing. .
                a	Append; open for writing at end-of-file or create for writing if the file does not exist.
                r+	Open an existing file for update (reading and writing).
                w+	Create a new file for update (reading and writing).
                a+	Open for append; open (or create if the file does not exist) for update at the end of the file.
                b       Binary
                t       Text

*/


// File Exceptions
class EFile
{
private:
  int aErrorCode;
  AnsiString aErrorMsg;
public:
  EFile()
  {
    aErrorCode = 0;
    aErrorMsg = "";
  };
  EFile(int pErrorCode)
  {
    aErrorCode = pErrorCode;
    aErrorMsg = "";
  };
  EFile(int pErrorCode,AnsiString pErrorMsg)
  {
    aErrorCode = pErrorCode;
    aErrorMsg = pErrorMsg;
  };
  int ErrorCode()
  {
    return aErrorCode;
  };
  AnsiString ErrorMsg()
  {
    return aErrorMsg;
  };
};
class ENoClose:EFile
{
};
class ECantClose:EFile
{
};
class ENoRemove:EFile
{
};
class ENoRename:EFile
{
};
class ENoSeek:EFile
{
};
class ENoOpen:EFile
{
};

class TFile
{
protected:
  AnsiString aFileName;
  bool aOpen;
  FILE *fFile;
public:
  TFile(AnsiString pFileName);
  ~TFile();
  void Close();
  bool Eof();
  bool FileExists();
  long FilePos();
  long FileSize();
  bool IsOpen()
  {
    return aOpen;
  }
  void Open(const char *pMode);
  int Read(void *pInfo, size_t pSize, size_t pCount = 1);
  void Remove();
  void Rename(AnsiString pName);
  void SeekFromCur(long pPositions);
  void SeekFromEnd(long pPosition);
  void SeekTo(long pPosition);
  int Write(void *pInfo, size_t pSize, size_t pCount = 1);
  void WriteS(char pString[]);
  bool WriteC(char pInfo);
};
//---------------------------------------------------------------------------

#endif

