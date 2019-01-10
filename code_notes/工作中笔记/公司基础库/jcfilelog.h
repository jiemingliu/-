/******************************************************************************
* �ļ���: jcfilelog.h
* ����: �ļ���־(ֻ���ṩ�ļ���¼����,û�������̰߳�ȫ����)
* Copyright(c)2014-2016 JCDZ Co.,Ltd.
*
* �޸ļ�¼:
* --------------------
* v1.0   2014/03/27 11:27:35, lys �����ļ�
*
******************************************************************************/
#ifndef _JCFILELOG_H_
#define _JCFILELOG_H_

#include <string>
#include "jcbase.h"

using namespace std;


#define FILE_MAX_SIZE (10*1024*1024)
#define LOG_MSG_HEAD_LEN     128
#define LOG_MSG_CONTENT_LEN  4096
#define MSG_LEN       (LOG_MSG_HEAD_LEN + LOG_MSG_CONTENT_LEN)

class DLL_EXPORT JCFileLog
{
public:
	JCFileLog();
	~JCFileLog();

	bool IsOpen();
	string &GetFilePath();
	bool SetFilePath(const string &strFilePath);
	void SetMaxFileSize(unsigned int nMaxFileSize);
	bool Create(const string &strFilePath, unsigned int nMaxFileSize = FILE_MAX_SIZE);//MAX 10Mbyte
	bool Logf(const string &strMsg);
private:
	void StartNewLogFile();
#if defined(WIN32)
	bool Makepathlimit(char *pPath, const char *pDrive, const char *pDir, const char *pFname, const char *pExt);
#endif
	bool Log(const string &strMsg, int nLen = -1);
	bool Open();
	bool Close();

protected:
	FILE *m_fp;
	string m_strFilePath;
	unsigned int m_nBytesWritten;
	unsigned int m_nMaxFileSize;
	bool m_bInOpenCall;
};


#endif /* _JCFILELOG_H_ */

