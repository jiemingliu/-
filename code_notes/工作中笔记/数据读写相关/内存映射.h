/********************************************************************
	��������:	2008/05/07
	�ļ�·��:	e:\My Task\simtools\CommonData\Tools
	�� �� ��:	DataRead_inline
	�ļ���׺:	h
	��    ��:	iuhiao	
	˵��:	  ��ȡ�ļ�ʱʹ�õ���������
*********************************************************************/
#pragma once
#include "EclHeadStruct.h"
#include "DataPoStruct.h"
#include "..\Data\GridRecive.h"
#include "ProjectManger.h"
typedef std::vector<float> Grids;
#include "DataRoot.h"
#include "ProgressControl/ProgressControl.h"
#include "..\..\CommonTools\Tools\Path.h"

/**
* ����:	���ö�ȡ����ʱ��Ӧ��ȡ��ʵ��������
* ȫ��:	Setndatas
* ����:	inline 
* 
* @���� 	2008/05/07
* @����  iuhiao
* @���� 	int ndatas
* @�������� 	void
*/
inline void Setndatas(int& ndatas)
{
	ndatas = ndatas + (ndatas/1000) * 2;
}
/************************************************************************/
/*      �ַ������á�����                               */
/************************************************************************/
inline void rmSpace(char *ss, int len)
{
	int  i, j1, j2, k;
	char str[256];
	if(len >= 8 && lstrcmpi(ss, ":+:+:+:+") == 0){
		lstrcpy(ss, "");
		return;
	}
	j1 = 0;
	j2 = -1;
	for(i = 0; i < len; i++)
		if(ss[i] != ' '){ j1 = i; break; }
	for(i = ( len - 1 ); i >= 0; i--)
		if(ss[i] != ' ' && ss[i] != '\n' && ss[i] != '\r'){ j2 = i; break; }
	k = 0;
	if(j2 >= 0)
		for(i = j1; i <= j2; i++){ str[k] = ss[i]; k++; }
	str[k] = '\0';
	lstrcpy(ss, str);
}
/*************************************************************
*	������+4
************************************************************/
inline int intread(int* nk,char* lpbMapAddress)
{
	unsigned char cc[5], ss[5];
	for (int ic = 0;ic < 4;++ic)///��4���ֽ����ݣ�����һ�����ͱ���
	{
		cc[ic] = *(lpbMapAddress + ic);
	}	
	ss[0] = cc[3]; ss[1] = cc[2]; ss[2] = cc[1]; ss[3] = cc[0];
	ss[4] = '\0';
	*nk = *((int*)ss);
	if(*nk < 0) return(0);
	return(1);
}
/******************************************************
*	��ʵ��+4
*****************************************************/
inline void realread(float *fval,char* lpbMapAddress)
{
	unsigned char cc[5], ss[5];
	for (int ic = 0;ic < 4;++ic)///��4���ֽ����ݣ�����һ�����ͱ���
	{
		cc[ic] = *(lpbMapAddress + ic);
	}
	ss[0] = cc[3]; ss[1] = cc[2]; ss[2] = cc[1]; ss[3] = cc[0];
	ss[4] = '\0';
	*fval = *((float*)ss);
	return;
}

/*************************************************
*	��˫������+8
************************************************/
inline void doubread(double *fval,char* lpbMapAddress)
{
	int    i;
	unsigned char cc[9], ss[9];
	for (int ic = 0;ic < 8;++ic)///��8���ֽ����ݣ�����һ�����ͱ���
	{
		cc[ic] = *(lpbMapAddress + ic);
	}
	for(i = 0; i < 8; i++) 
	{
		ss[i] = cc[7-i];
	}
	ss[8] = '\0';
	*fval = *((double*)ss);
	return;
}
/*****************************************************
*	��ȡ��EclHead���ṹ��+24
*****************************************************/
inline  int read_eh(char* lpbMapAddress,EclHead* eh,int* nOffset)
{
	int  iesc, n;
	char ch[9], ct[5];
	//�ȴ��ļ���һ������
	if(intread(&iesc,lpbMapAddress) <= 0) 
	{
		lpbMapAddress = lpbMapAddress + 4;	
		*nOffset = 4;
		return(0); 
	}
	*nOffset = 4;
	lpbMapAddress = lpbMapAddress + 4;	
	if(iesc != 16) return(0);
	///��8���ֽڵ��ַ���
	for (int ic = 0;ic < 8;++ic)
	{
		ch[ic] = *(lpbMapAddress + ic);
	}
	lpbMapAddress = lpbMapAddress + 8;	
	*nOffset = 8;
	ch[8] = '\0';///���ϴ��Ľ�����
	rmSpace(ch, 8);
	if(intread(&n, lpbMapAddress) <= 0) 
	{
		*nOffset = 16;
		lpbMapAddress = lpbMapAddress + 4;	
		return(0);///��һ������
	}
	lpbMapAddress = lpbMapAddress + 4;
	////��4���ֽڵ��ַ���
	for (int ic = 0;ic < 4;++ic)
	{
		ct[ic] = *(lpbMapAddress + ic);
	}
	lpbMapAddress = lpbMapAddress + 4;
	///���ϴ��Ľ�����
	ct[4] = '\0';
	rmSpace(ct, 4);
	*nOffset = 20;
	if(lstrcmpi(ch, "") == 0) return(0); 
	//��EclHead���ṹ�帳ֵ
	lstrcpy(eh->ch, ch);
	//��EclHead���ṹ�帳ֵ
	eh->n = n;         
	//��EclHead���ṹ�帳ֵ
	lstrcpy(eh->ct, ct);  

	if(intread(&iesc, lpbMapAddress) <= 0) 
	{
		*nOffset = 24;
		lpbMapAddress = lpbMapAddress + 4;
		///��һ������
		return(0);
	}
	*nOffset = 24;
	lpbMapAddress = lpbMapAddress + 4;	
	return(1);	
}
/****************************************************************
*	����¼
****************************************************************/
inline void read_ecl_record(char* lpbMapAddress,char ct[],double ebuf[],char crt[])
{
	int    idi, ilog;
	float  ral;
	double dou;
	char   cr[10];
	/*���ݴ����ctֵ��ͬ����ebuf����ֵͬ */
	if(lstrcmpi(ct, "INTE") == 0)
	{		
		(void)intread(&idi, lpbMapAddress);
		lpbMapAddress = lpbMapAddress + 4;	
		ebuf[0]=(double)idi;
	}
	else if(lstrcmpi(ct, "REAL") == 0)
	{
		realread(&ral, lpbMapAddress);
		lpbMapAddress = lpbMapAddress + 4;	
		ebuf[1]=(double)ral;
	}
	else if(lstrcmpi(ct, "LOGI") == 0)
	{
		(void)intread(&ilog, lpbMapAddress);
		lpbMapAddress = lpbMapAddress + 4;	
		ebuf[2]=(double)ilog;
	}
	else if(lstrcmpi(ct, "DOUB") == 0)
	{
		doubread(&dou, lpbMapAddress);
		lpbMapAddress = lpbMapAddress + 8;	
		ebuf[3]=(double)dou;
	}
	else if(lstrcmpi(ct, "CHAR") == 0)
	{
		for (int ic = 0;ic < 8;++ic)///��8���ֽ����ݣ�����һ�����ͱ���
		{
			cr[ic] = *(lpbMapAddress + ic);
		}
		lpbMapAddress = lpbMapAddress + 8;	
		cr[8] = '\0';
		rmSpace(cr, 8);
		lstrcpy(crt, cr);		
	}
}

/**
 * ����:	���ļ����ؼ�����Ϣ��
 * ȫ��:	<PoClass>::ReadFile
 * ����:	public 
 * 
 * @���� 	2008/09/16
 * @����  iuhiao
 * @���� 	CString strFile  �ļ���
 * @���� 	PoClass * pPoClass���ļ������
 * @���� 	PoGlobalData & poGloablData��ȫ������
 * @���� 	CGridRecive & gridRecive���������ݶ���
 * @���� 	int nFileType�����ļ�����
 * @�������� 	void
 */
template<class PoClass>
inline void ReadFile(CString strFile,PoClass* pPoClass ,PoGlobalData& poGloablData  ,
					 CDataRoot* pDataRoot , int nFileType = 0)
{
	//��������Ϣ
	CString strProgressInfo;
	CPath path(strFile);
	strProgressInfo.Format("���ڶ�ȡ�ļ���%s",path.GetFileName());
	//try
	{
		//nFileType = 0Ϊ�����ļ���=1Ϊ�����ļ�
		int	  nk;//�ؼ���������
		int  ifid;//�ؼ�����ռ�ռ��ֽ���
		EclHead  eh;
		///�ؼ�����
		CString strTitle;
		//�ؼ�������
		CString strtype;
		//�ؼ�������
		CString strdata;
		// �����ļ�����
		HANDLE hFile = ::CreateFile(strFile, GENERIC_READ,FILE_SHARE_READ, NULL, 
			OPEN_EXISTING, FILE_FLAG_RANDOM_ACCESS, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			TRACE("�����ļ�����ʧ��,�������:%d\r\n", GetLastError());
			return;
		}
		// �����ļ�ӳ�����
		HANDLE hFileMap = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
		if (hFileMap == NULL)
		{
			//�ر��ļ�����
			CloseHandle(hFile);	
			TRACE("�����ļ�ӳ�����ʧ��,�������:%d\r\n", GetLastError());		
			return;
		}

		// �õ��ļ��ߴ�
		DWORD dwFileSizeHigh;
		__int64 qwFileSize = GetFileSize(hFile, &dwFileSizeHigh);
		qwFileSize |= (((__int64)dwFileSizeHigh) << 32);///MSDN
		// ƫ�Ƶ�ַ 
		__int64 qwFileOffset = 0;

		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		// �õ�ϵͳ��������
		SYSTEM_INFO SysInfo;
		GetSystemInfo(&SysInfo);
		DWORD dwGran = SysInfo.dwAllocationGranularity;
		__int64 T_newmap = 1200 * dwGran;
		// ���С
		DWORD dwBlockBytes = 1500 * dwGran;//�ļ����ݷֶδ�С
		if (qwFileSize - qwFileOffset < dwBlockBytes)
		{
			dwBlockBytes = (DWORD)qwFileSize;
		}

		// ӳ����ͼ
		char *lpbMapAddress = (char *)MapViewOfFile(hFileMap,FILE_MAP_READ,
			(DWORD)(qwFileOffset >> 32), (DWORD)(qwFileOffset & 0xFFFFFFFF),dwBlockBytes);
		if (lpbMapAddress == NULL)
		{
			//�ر��ļ�����
			CloseHandle(hFile);	
			// �ر��ļ�ӳ�������
			CloseHandle(hFileMap);
			TRACE("ӳ���ļ�ӳ��ʧ��,�������:%d ", GetLastError());
			return;
		} 		
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		///////////���ļ�����
		//���ڶ�EchHeadʱ�Ĳ�ͬ���������ƫ��
		int eh_offset = 0;
		//��ǰ����������Ӧ��gridRecive
		CGridRecive* gridRecive = &(pDataRoot->GetGridData().GetGridRecive());
		//��ǰ��ȡ�Ŀ��Ƿ�������������
		BOOL bLgrData = FALSE;
		//LGR��ʶ
		CString strNLGR;
		CString strLgrName;
		//�Ƿ��ļ������һ��ӳ��
		BOOL bLastBlock;
		try
		{
			while(qwFileOffset < qwFileSize)
			{
				/********************            ���ļ�             ***************************/
				//���ڶ�EchHeadʱ�Ĳ�ͬ���������ƫ��
				eh_offset = 0;
				eh.n = 0;
				eh.ch[0] = '\0';
				ASSERT(qwFileSize - qwFileOffset > 0);
				//��ȡ�ؼ���ͷ��Ϣ
				read_eh(lpbMapAddress, &eh ,&eh_offset);
				qwFileOffset += eh_offset;		
				lpbMapAddress = lpbMapAddress + eh_offset;
				//���ݶ�ȡ����ctֵ��ͬ����*ifid����ֵͬ �ж�ÿ�����ݵ���ռ�ֽ�
				if(lstrcmpi(eh.ct, "DOUB") == 0 || lstrcmpi(eh.ct, "CHAR") == 0)
				{
					ifid = 8;
				}
				else 
				{
					ifid = 4;
				}
				//////////////////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////////////////
				if (qwFileOffset + eh.n * ifid + 4 > T_newmap)
				{
					//�����ݶ���80%ʱ,Ϊ���������,��Ҫӳ������������  T_newmap
					//�ͷŵ�ǰӳ��
					UnmapViewOfFile(lpbMapAddress);
					bLastBlock = FALSE;					
					int nGran = qwFileOffset / dwGran;
					__int64 fileOff = nGran * dwGran;
					if ((DWORD)(qwFileSize - fileOff) < dwBlockBytes)
					{ 
						dwBlockBytes = (DWORD)(qwFileSize - fileOff);
						bLastBlock = TRUE;
					}
					lpbMapAddress = (char *)MapViewOfFile(hFileMap,FILE_MAP_READ,
						(DWORD)(fileOff >> 32), (DWORD)(fileOff & 0xFFFFFFFF),dwBlockBytes);
					if (lpbMapAddress == NULL)
					{
						//�ر��ļ�����
						CloseHandle(hFile);	
						// �ر��ļ�ӳ�������
						CloseHandle(hFileMap);
						TRACE("ӳ���ļ�ӳ��ʧ��,�������:%d ", GetLastError());
						return;
					} 
					// ��������
					lpbMapAddress = lpbMapAddress + ( qwFileOffset - nGran * dwGran );
					if (bLastBlock)
					{
						T_newmap = qwFileSize;
					}
					else
					{
						T_newmap = fileOff  + 1200 * dwGran;
					}
				}
				//////////////////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////////////////
				/*
				*	��һ���ؼ���,�ؼ��ֺ�����������Ϊһ������д��һ����Ӧ���ݽṹ,���뵽m_dataObjs
				*/
				strTitle = eh.ch;
				strtype = eh.ct;
				if (_T("ENDLGR") == strTitle)
				{
					gridRecive = &(pDataRoot->GetGridData().GetGridRecive());
					bLgrData = FALSE;
				}
				///������������ʵ��..........................................�ؼ�����
				if (strTitle == "SWAT" && (strFile.Find(".SLN") != -1))
				{
					//���������е�SWAT�ؼ���
					strTitle = "LINE_SWAT";
				}
				if(eh.n <= 0) 
				{
					continue;
				}
				//nkΪ�����ĸ��ֶ����ֽ���
				if(intread(&nk, lpbMapAddress) <= 0) 
				{
					qwFileOffset += 4;
					lpbMapAddress = lpbMapAddress + 4;	
					continue;
				}
				qwFileOffset += 4;
				lpbMapAddress = lpbMapAddress + 4;
				//�����ļ��в�Ӧ�ó��ֵĹؼ���
				if (strTitle == _T("TRANX") || strTitle == _T("TRANY") || strTitle == _T("TRANZ"))
				{
					if (strFile.Find(_T(".UNRST")) != -1 || strFile.Find(_T(".X")) != -1)
					{
						qwFileOffset = qwFileOffset + eh.n * ifid + 4;
						lpbMapAddress = lpbMapAddress + eh.n * ifid + 4;
						continue;
					}
				}
				if (bLgrData)
				{
					//���LGR��ʶ
					strTitle = strNLGR + strTitle;
				}
				//��ȡ�ؼ�����������
				CDataPoEntity* pPoEntity = pPoClass->FindPoEntity(strTitle);
				if (NULL == pPoEntity)
				{
					if (bLgrData)
					{
						//ʵ�ʹؼ�����
						strTitle = strTitle.Mid(strNLGR.GetLength() , strTitle.GetLength() - 3);
					}
					//������ǰ�ؼ��ʶ���(û��ע��Ĺؼ��ʾͷ���NULL)
					pPoEntity = CDataObjFactory::CreateDataPoEntity(strTitle);
					if (pPoEntity != NULL)
					{
						if (bLgrData)
						{
							if (gridRecive->m_SimTimes.size() < poGloablData.times.size())
							{
								gridRecive->m_SimTimes = poGloablData.times;
							}
							pPoEntity->SetTitle(strNLGR + strTitle);
						}
						///���뵽vector
						pPoClass->GetDataObjs ().push_back(pPoEntity);
					}			
				}
				//��Ҫ�Ĺؼ�������
				if (pPoEntity == NULL )
				{
					qwFileOffset = qwFileOffset + eh.n * ifid + 4;
					lpbMapAddress = lpbMapAddress + eh.n * ifid + 4;
					continue;
				}			
				//��ȡ����
				//////////////////////////////////////////////////////////////////////////
				//���ý�����
				int curPer = int((qwFileOffset - 4 - eh_offset) * 100/qwFileSize);
				CProgressControl::getSingletonPtr()->StepProgress(curPer ,strProgressInfo,
					_T("���ڶ�ȡ���ԣ�")  + strTitle);
				//////////////////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////////////////
				if (strTitle == _T("LGR"))
				{
					std::vector<char> LgrData;
					LgrData.resize(eh.n * sizeof(char) * 8);	
					memcpy((char*)&LgrData[0],(char*)lpbMapAddress,eh.n * sizeof(char) * 8);
					char keywords[10];
					for (int ic = 0;ic < 8;++ic)
					{
						//��ȡKEYWORDS���ݡ�����������(��������)
						keywords[ic] = LgrData[ic];
					}
					keywords[8] = '\0';
					//��":+:+:+:+"����Ϊ��
					rmSpace(keywords, 8);
					strLgrName = keywords;
					gridRecive = &(pDataRoot->GetLgrGridData(strLgrName).GetGridRecive());
					bLgrData = TRUE;
					strNLGR = _T("LGR") + strLgrName;
				}
				//û��ʹ��CGridPropUnit��������������ֵ(�磺����)
				//int nData = eh.n;
				//Setndatas(nData);
				////08.10.28�޸ģ���ǰ���ܶ����������ˣ�û�ж�Ӧ������������
				//pPoEntity->SetDatas(lpbMapAddress, nData , poGloablData  , gridRecive );
				pPoEntity->SetDatas(lpbMapAddress,eh.n , poGloablData  , *gridRecive );
				pPoEntity->SetDatas(lpbMapAddress,eh.n , poGloablData  , *gridRecive , strNLGR.GetLength());
				//ʹ��CGridPropUnit����������ֻ����������Ϣ
				if (bLgrData)
				{
					pPoEntity->SetDatas(strFile , qwFileOffset - 4 - eh_offset , gridRecive ,strNLGR.GetLength());
					pPoEntity->SetDatas(pDataRoot->GetLgrData() , strLgrName);
				}
				else
				{
					pPoEntity->SetDatas(strFile , qwFileOffset - 4 - eh_offset , gridRecive );
				}
				//////////////////////////////////////////////////////////////////////////
				//��������������� ��ֱ���˳�,����㾭�����񿽱�����ز���
				if (strTitle == "DIMENS" && nFileType == 1)
				{
					//�������ļ�ʱ����ֻ��DIMENS
					//�ͷ�������ݿ�ӳ��
					UnmapViewOfFile(lpbMapAddress);
					//�ر��ļ�����
					CloseHandle(hFile);	
					// �ر��ļ�ӳ�������
					CloseHandle(hFileMap);
					return;
				}
				//////////////////////////////////////////////////////////////////////////
				//����������
				pPoEntity->SetDataType(eh.ct);
				pPoEntity->SetDatas(strFile , qwFileOffset - 4 - eh_offset , &pDataRoot->GetFlowLineData());
				//����ָ��
				qwFileOffset = qwFileOffset + eh.n * ifid + 4;
				lpbMapAddress = lpbMapAddress + eh.n * ifid + 4;
				//���ý�����
				curPer = int(qwFileOffset * 100/qwFileSize);
				CProgressControl::getSingletonPtr()->StepProgress(curPer ,strProgressInfo,
					_T("���ڶ�ȡ���ԣ�")  + strTitle);
			} 
			//�ͷ�������ݿ�ӳ��
			UnmapViewOfFile(lpbMapAddress);
			//�ر��ļ�����
			CloseHandle(hFile);	
			// �ر��ļ�ӳ�������
			CloseHandle(hFileMap);	
			CProgressControl::getSingletonPtr()->StepProgress(100 ,strProgressInfo,
				_T(" "));
			return;
		}
		catch (...)
		{
			TRACE("�������:%d ", GetLastError());
			//�ͷ�������ݿ�ӳ��
			UnmapViewOfFile(lpbMapAddress);
			// �ر��ļ�ӳ�������
			//�ر��ļ�����
			CloseHandle(hFile);	
			CloseHandle(hFileMap);	
			CProgressControl::getSingletonPtr()->StepProgress(100 ,strProgressInfo,
				_T(" "));
			//if (strTitle == _T("ICON"))
			//{
			//	AfxMessageBox(_T("��ȡ���켣���ݴ���"));
			//	return;
			//}
			AfxMessageBox(_T("��ȡ�����������ݴ���"));
			return;
		}
	}
}

const int 		MAX_SEG_DATA_NUM = 1000;
const int 		MAX_SEG_KEY_NUM = 105;
const int		INT_KEY_HEAD_NUM = 16;
const int		SPACE_HEX = 0x20;

inline int GetTypeSize(CString sType) {

	int nSize = 4;

	if (_T("DOUB") == sType ||
		_T("CHAR") == sType) {
		nSize = 8;
	}

	return nSize;
}

inline void TransNumberByte(char* in, char* out, int nSize)
{
	for (int i = 0; i < nSize; ++i) {
		*(out + i) = *(in + nSize - 1 - i);
	}
}

inline void intwrite(int value, CFile* pFile)
{
	char bytes[4];
	TransNumberByte((char*)(&value), bytes, 4);
	pFile->Write(bytes, 4);
}

inline void realwrite(float value, CFile* pFile)
{
	char bytes[4];
	TransNumberByte((char*)(&value), bytes, 4);
	pFile->Write(bytes, 4);
}

inline void doublewrite(double value, CFile* pFile)
{
	char bytes[8];
	TransNumberByte((char*)(&value), bytes, 8);
	pFile->Write(bytes, 8);
}

inline void stringwrite(char* chars, int nLength, CFile* pFile)
{
	pFile->Write(chars, nLength);
}

inline void stringwrite(CString str, CFile* pFile)
{
	int nLength = str.GetLength();
	char* chars = str.GetBuffer();

	stringwrite(chars, nLength, pFile);

	str.ReleaseBuffer();
}

inline void charStringwrite(CString str, CFile* pFile)
{
	int nLength = str.GetLength();
	ASSERT(nLength <= 8);

	if (nLength == 8) {
		stringwrite(str, pFile);
	}
	else {
		char chars[8];
		memset(chars, SPACE_HEX, 8);
		char* oriChars= str.GetBuffer();
		memcpy(chars, oriChars, nLength);
		stringwrite(chars, 8, pFile);
		str.ReleaseBuffer();
	}

}

inline void keyStringwrite(CString str, CFile* pFile)
{
	charStringwrite(str, pFile);
}

inline void writeEVerNum(CFile* pFile)
{
	intwrite(INT_KEY_HEAD_NUM, pFile);
}

inline void writeDataType(CString sType, CFile* pFile)
{
	char* chars = sType.GetBuffer();
	pFile->Write(chars, sType.GetLength());
	sType.ReleaseBuffer();
}

inline void writeIntegerArray(std::vector<int> datas, CFile* pFile)
{
	int nTypeSize = 4;
	int nTotalSize = (int)datas.size();
	{
		int nSize;
		int nCount = 0;
		for (int i = 0; i < nTotalSize; ++i) {
			if (nCount == 0) {
				int nLeftSize = nTotalSize - i;
				if (nLeftSize > MAX_SEG_DATA_NUM)
					nLeftSize = MAX_SEG_DATA_NUM;

				nSize = nLeftSize * nTypeSize;
				intwrite(nSize, pFile);
			}

			intwrite(datas[i], pFile);

			if (++nCount == MAX_SEG_DATA_NUM || i == nTotalSize-1) {
				intwrite(nSize, pFile);
				nCount = 0;
			}
		}
	}
}

inline void writeRealArray(std::vector<float> datas, CFile* pFile)
{
	int nTypeSize = 4;
	int nTotalSize = (int)datas.size();
	{
		int nSize;
		int nCount = 0;
		for (int i = 0; i < nTotalSize; ++i) {
			if (nCount == 0) {
				int nLeftSize = nTotalSize - i;
				if (nLeftSize > MAX_SEG_DATA_NUM)
					nLeftSize = MAX_SEG_DATA_NUM;

				nSize = nLeftSize * nTypeSize;
				intwrite(nSize, pFile);
			}

			realwrite(datas[i], pFile);

			if (++nCount == MAX_SEG_DATA_NUM || i == nTotalSize-1) {
				intwrite(nSize, pFile);
				nCount = 0;
			}
		}
	}
}

inline void writeDoubleArray(std::vector<double> datas, CFile* pFile)
{
	int nTypeSize = 8;
	int nTotalSize = (int)datas.size();
	{
		int nSize;
		int nCount = 0;
		for (int i = 0; i < nTotalSize; ++i) {
			if (nCount == 0) {
				int nLeftSize = nTotalSize - i;
				if (nLeftSize > MAX_SEG_DATA_NUM)
					nLeftSize = MAX_SEG_DATA_NUM;

				nSize = nLeftSize * nTypeSize;
				intwrite(nSize, pFile);
			}

			doublewrite(datas[i], pFile);

			if (++nCount == MAX_SEG_DATA_NUM || i == nTotalSize-1) {
				intwrite(nSize, pFile);
				nCount = 0;
			}
		}
	}
}

inline void writeCharArray(std::vector<CString> datas, CFile* pFile, int nMaxSegNum)
{
	int nTypeSize = 8;
	int nTotalSize = (int)datas.size();
	{
		int nSize;
		int nCount = 0;
		for (int i = 0; i < nTotalSize; ++i) {
			if (nCount == 0) {
				int nLeftSize = nTotalSize - i;
				if (nLeftSize > nMaxSegNum)
					nLeftSize = nMaxSegNum;

				nSize = nLeftSize * nTypeSize;
				intwrite(nSize, pFile);
			}

			charStringwrite(datas[i], pFile);

			if (++nCount == nMaxSegNum || i == nTotalSize-1) {
				intwrite(nSize, pFile);
				nCount = 0;
			}
		}
	}
}