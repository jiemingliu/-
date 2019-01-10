/******************************************************************************
* �ļ���: jcsharemem.h 
* ����: �ڴ�ӳ���ļ�(�����ڴ�)
* Copyright(c)2014-2020 JCDZ Co.,Ltd.
*
* �޸ļ�¼:
* --------------------
* v1.0   2017/01/16 20:42:50, lys �����ļ�
*
******************************************************************************/
#ifndef _JCSHAREMEM_H_
#define _JCSHAREMEM_H_

#include <windows.h>
#include <string>
#include "jcnonecopy.h"
#include "jcbase.h"


class DLL_EXPORT JCShareMem : public JCNonecopy
{
	struct JCSMHead
	{
		unsigned int	m_nSize;
		unsigned int    m_nHeadVer;
		JCSMHead() : m_nSize(0), m_nHeadVer(0)
		{
		}
	};
public:
	JCShareMem();
	~JCShareMem();

	bool Create(std::string &strName, unsigned int nSize);
	void Destory();
	bool Attach(std::string &strName, unsigned int nSize);
	bool Detach();
	unsigned char* GetDataPtr();
	unsigned int GetMemSize();
	bool SetHeadVersion(unsigned int nVer);
	unsigned int GetHeadVersion();
	bool CopyIn(unsigned char* pSrc, unsigned int nSize);
	bool CopyOut(unsigned char* pDest, unsigned int nSize);

private:
	HANDLE m_hShareMem;
	unsigned char* m_pHeader;
	unsigned char* m_pDataPtr;
	unsigned int m_nMemSize;
};

#endif

