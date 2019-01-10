/******************************************************************************
* �ļ���: jcfile.h
* ����: -
* Copyright(c)2014-2016 JCDZ Co.,Ltd.
*
* �޸ļ�¼:
* --------------------
* v1.0   2014/03/21 15:39:0, gaopeng �����ļ�
*
******************************************************************************/
#ifndef _JCFILE_H_
#define _JCFILE_H_

#include <string>
#include <vector>
#include <list>
#include <map>
#include <stdio.h>
#include <sys/stat.h>
#include <fstream>

#if defined(__linux) || defined(__APPLE__) || defined(__CYGWIN__)
#include <sys/io.h>
#include <sys/unistd.h>
#include <dlfcn.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <iconv.h>
#include <errno.h>
#include "SimpleIni.h"

#define _access access
#define _stat	stat
#define _chmod  chmod
#define _mkdir	mkdir
#define _getcwd getcwd
#define _unlink	unlink
#define _rmdir	rmdir
#define _S_IREAD S_IRUSR|S_IROTH
#define _S_IWRITE S_IWUSR|S_IWOTH
#define PATHSEPARATOR "/"
#else
#include <direct.h>
#include <io.h>
#include <AclAPI.h>
#include <lm.h>
#define PATHSEPARATOR "\\"
#endif

#include "jcbase.h"

using namespace std;

/* ��io.h�ļ򵥷�װ������fstream�ļ����� */
class DLL_EXPORT JCFile
{
public:
	JCFile();
	~JCFile();

	enum FILEMODE{
		EXIST	= 0x00,
		WRITEONLY = 0x02,
		READONLY = 0x04,
		RDWR = 0x06
	};

public:
	static bool Exists(const string& fileName);
	static bool IsFolder(const string& fileName);
	static bool ChangeMode(const string& fileName, FILEMODE mode);
	static bool MakeDIR(const string& path);
	static bool MakeFullDIR(const string& path);
	static string GetCurrentDir();
	static string GetExeDir();

	static bool Copy(const string& sourceFile, const string& destFile, bool overwrite = false);
	static bool CopyDir(const string& sourceFile, const string& destFile, bool overwrite = false);
	static bool RemoveFile(const string& filename);
	static bool RemoveDir(const string& pathName);
	static bool RemoveDirAndFile(const string& pathName); /* ɾ�� ��ǰĿ¼�Լ�Ŀ¼�������ļ� */
	static int	RemoveFullDir(const string& pathName);
	static int	RemoveFullDirOtherTry(const string& pathName);
	static int  ClearFolder(const string& folder);
	static bool GetAllDir(const string& pathName,vector< string >& strPathVec);/* ��ȡ��ǰĿ¼�µ������ļ�Ŀ¼ */
	static bool GetFilesByExtend(const string& pathName,vector< string >& strFileVec,const string& strExtend);/* ��ȡ��ǰĿ¼��ָ����׺���ļ��б� */

	static bool Move(const string& sourceFile, const string& destFile);
	static bool CanRead(const string& path);
	static bool CanWrite(const string& path);
	static size_t FileSize(const string& path);
	static time_t ModifyTime(const string& path);
	static bool Search(const string& condition, vector< string >& files);
	static bool IsFolderEmpty(const string& fileName);

	/*���ص�������"|"Ϊ�ָ���*/
	static bool Search(const string& condition, vector< string >& filesRet, bool attrRet);

	static unsigned long CRC32(const unsigned char *data, int len);
	static unsigned long CRC(const string& fileName);
	static string ws2s(wstring& inputws);
	static wstring s2ws(const string& s);
	static string U2G(const string& utf8);
	static string G2U(const string& gb2312);

#if defined(__linux) || defined(__APPLE__) || defined(__CYGWIN__)
	static int code_convert(string from_charset, 
		string to_charset,
		char *inbuf,
		size_t inlen,
		char *outbuf,
		size_t outlen);
#endif

public:
	bool CreatFile(const string fileName, bool overWrite=false);
	bool LoadFile(const string& fileName,ios_base::openmode mode=ios::in|ios::out|ios::binary);
	bool GetLine(string& line);
	int GetBuffer(char* pBuf, int bufSize);
	string GetString();
	bool GetChar(char& ret);
	bool IsEndOfFile();
	void PutChar(char c);
	void PutString(const string& str, char delim=0);
	bool PutBuffer(char* pBuf, int bufSize);

	int CurPos();
	int SeekPos(int pos);
	void Flush();
	void ResetFileState();
	void Close();

private:
	fstream m_tFstream;
};

enum ESHAREEXIST
{
	NOT_EXIST,			//�޹���
	EXIST_THIS_DIR,		//�й������ڵ�ǰĿ¼
	EXIST_NOT_THISDIR	//�й������ڵ�ǰĿ¼
};

#if defined(__linux) || defined(__APPLE__) || defined(__CYGWIN__)
#else
/******************************************************************************
* ������:JCNetShare
* ����: -��B5�ļ�ϵͳ��ֲ
*
//*----------------------------------------------------------------------------
//*��Ŀ���� ��JCM File System
//*�� �� �� ��1.0
//*----------------------------------------------------------------------------
//*----------------------------------------------------------------------------
//*�� �� �� ��NetShareAPI.h
//*��    �� ���ļ����ܺ���
//*˵    �� �����ڶ��ƶ��ļ��Ĺ���
//*��    �� ���ż�
//*��    �� ��1.0
//*����ʱ�� ��2013.07.20 15:00
//*״    ̬ ��1.0-Debug��
//*----------------------------------------------------------------------------
/
* �޸ļ�¼:
* --------------------
*    2014/03/30 21:25:51, gaopeng ��������
*
******************************************************************************/
class DLL_EXPORT JCNetShare
{
public:
	JCNetShare(const char* strPath, const char* strName);
	~JCNetShare(void);

	TCHAR               szShareName[255];
	WCHAR               wszShareName[255];
	TCHAR               szShareDir[255];
	WCHAR               wszShareDir[255];
	static const char* WToU(LPCWSTR str);
	static const LPWSTR AToW(LPCSTR str);
	void OpenServer();

	//���ù���Ȩ��
	BOOL SetNetUserAccessPower(string strUser,PSECURITY_DESCRIPTOR pSD);
	//��ӹ���
	DWORD  NetAddShare(string  strUser="Everyone");
	DWORD  AdjustAndShareFolder();

	//���ù���
	DWORD  SetNetSharePermission();
	//ɾ������
	DWORD  NetDelShare();
	//��ѯ����
	ESHAREEXIST  NetCheckShare();


	//�����ļ����˻�Ȩ��
	BOOL  EnableFileAccountPrivilege(const char* pszPath, const char* pszAccount);
};
#endif

class DLL_EXPORT KeyValue
{
public:
	KeyValue(string strKey, string strValue)
		:m_strKey(strKey),m_strValue(strValue)
	{}
	~KeyValue(){}

public:
	string m_strKey;
	string m_strValue;
};

typedef list<string> IniAppnameList;
typedef list<KeyValue> IniKeyValueList;

class DLL_EXPORT JCIniFileOper
{
public:
	JCIniFileOper(string inifilepath);
	JCIniFileOper();
	virtual ~JCIniFileOper();
public:
	bool           WriteIniFile(string appname, string keyname, string keyvalue);
	bool           ReadIniAppName(IniAppnameList& iniAppnamelist);
	bool           ReadIniSection(string appname, IniKeyValueList& inikeylist);
	string         ReadIniKeyData(string appname, string keyname);
	bool           WriteIniFile_MD5(string appname, string keyname, string keyvalue);

	bool           ReadKeyIntValue(string appname, string keyname, int& keyvalue);
	bool           ReadKeyDoubleValue(string appname, string keyname, double& keyvalue);
	bool           ReadKeyStringValue(string appname, string keyname, string& keyvalue);

private:
	string m_strIniFilePath;
	string m_strAppname;

#if defined(__linux) || defined(__APPLE__) || defined(__CYGWIN__)
	CSimpleIni m_tIniFileOper;
#endif
};

#endif /* _JCFILE_H_ */

