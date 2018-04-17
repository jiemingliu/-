#include "StdAfx.h"
#include ".\GridPropUnitPo.h"
#include "DataRoot.h"
#include "..\Tools\Datadispose_inline.h"
#include "..\..\CommonTools\Tools\LoadLib.h"
#include <boost/bind.hpp>
#include "..\..\CommonData\GlobalVar.h"
#include "ProgressControl/ProgressControl.h"
#include "HiSimHandle/HiSimHandle.h"
#include "HiSimHandle/KWMapper.h"
#include "Tools/DataEcl.h"
#include "PropTypes.h"

//////////////////////////////////////////////////////////////////////////
//��������,ÿ��ֻ��һ�����Ե�����
TimedGridProp CGridPropUnitPo::m_GridProps;
std::map<long , long> CGridPropUnitPo::m_realOffset;
std::map<long , long> CGridPropUnitPo::m_totalOffset;
std::map<long,long> CGridPropUnitPo::m_realGridIndexOffset;
CString CGridPropUnitPo::m_strCurStoreDataProp = _T("");
CString CGridPropUnitPo::m_strCurStoreDataCase = _T("");
BOOL CGridPropUnitPo::m_bCalcState = FALSE;
BOOL CGridPropUnitPo::m_bCalcAllProp = FALSE;
//////////////////////////////////////////////////////////////////////////

BOOL CGridPropUnitPo::InitOption(Structure::CALC_PARAMSOPTION& options)
{
	CString str;
	::GetModuleFileName(NULL,str.GetBuffer(128),128);
	char diver[5],dir[128];
	_splitpath(str,diver,dir,NULL,NULL);
	CString pathName = diver;
	pathName+=dir;
	pathName+="option.ini";
	return options.LoadOption(pathName, "CalcParams");
}

BOOL CGridPropUnitPo::MakeFileOpen(CString fileName)
{
	//�ļ����ر����ٴ�
	if (m_bFile)
	{
		if ( !m_bFileOpen )
		{
			::SetFileAttributes(fileName ,FILE_ATTRIBUTE_NORMAL); 
			//�򿪵�ǰʱ�����������ļ�
			if (m_file.Open(fileName , CFile::typeBinary | CFile::modeReadWrite | CFile::shareDenyNone))
			{
				m_bFileOpen = TRUE;
				return TRUE;
			}
		}
	}
	else
	{
		if ( !m_bFileOpen )
		{
			::SetFileAttributes(fileName ,FILE_ATTRIBUTE_NORMAL); 
			//�򿪵�ǰʱ�����������ļ�
			if (m_dateFile.Open(fileName , CFile::typeBinary | CFile::modeRead | CFile::shareDenyNone))
			{
				m_bFileOpen = TRUE;
				return TRUE;
			}
		}
		else
		{
			return TRUE;
		}
	}
	return FALSE;
}

CGridPropUnitPo::CGridPropUnitPo(void)
{
	m_strPropName = "";
	//�Ƿ���д���ļ�
	m_bFile = FALSE;
	m_bNewProp = FALSE;
	m_bReadNewProp = FALSE;
	m_bFlush = FALSE;
	m_pretime.SetDate(0,0,0);
	m_dataType = TRUE;
	m_dateFile.m_hFile = INVALID_HANDLE_VALUE;
	m_file.m_hFile = INVALID_HANDLE_VALUE;
	m_bFileOpen = FALSE;
	m_bTotalGridData = false; //���ݺ�
}

CGridPropUnitPo::CGridPropUnitPo( const CString& strPropName)
	:CGridPropUnit(strPropName)
{
	m_strPropName = strPropName;
	//�Ƿ���д���ļ�
	m_bFile = FALSE;
	m_bNewProp = FALSE;
	m_bReadNewProp = FALSE;
	m_bFlush = FALSE;
	m_pretime.SetDate(0,0,0);
	m_dataType = TRUE;
	m_dateFile.m_hFile = INVALID_HANDLE_VALUE;
	m_file.m_hFile = INVALID_HANDLE_VALUE;
	m_bFileOpen = FALSE;
}
CGridPropUnitPo::~CGridPropUnitPo(void)
{
	if (m_dateFile.m_hFile != INVALID_HANDLE_VALUE)
	{
		//�򿪹��ļ�
		m_dateFile.Close();
	}
	if (m_file.m_hFile != INVALID_HANDLE_VALUE)
	{
		m_file.Flush();
		m_file.Close();
	}
}

void CGridPropUnitPo::ClearData()
{
	//�����ʱ����
	m_namedGridProps.clear();
}

void CGridPropUnitPo::CreateGridPropData( const CGridRecive& gridRev,const COleDateTime& time,
									   const CString& strPropName )
{
	if (m_strPropName.IsEmpty())
	{
		m_strPropName = strPropName;
	}
	ASSERT(!m_strPropName.IsEmpty());
	ASSERT(strPropName == m_strPropName);	
	//ֱ�Ӹ��������������ڴ�
	long lISize = 0;
	long lJSize = 0;
	long lKSize = 0;
	gridRev.GetGridSize(lISize ,lJSize ,lKSize);
	ASSERT(lISize * lJSize * lKSize != 0);

	if ( m_strCurStoreDataProp != m_strPropName )
	{
		//ֻ����ʱȡ������,����m_namedGridProps,��д���ļ�
		//ȷ��δ��ȡ����ʱ��
		ASSERT(m_namedGridProps.find(time) == m_namedGridProps.end());
		////����������С��
		//m_namedGridProps[time].resize(lISize * lJSize * lKSize,UNACTVALUE);
	}
	else
	{
		//ȷ��δ��ȡ����ʱ��
		ASSERT(m_GridProps.find(time) == m_GridProps.end());
		////����������С��
		//m_GridProps[time].resize(lISize * lJSize * lKSize,UNACTVALUE);
	}	
	if (m_dataOffsets.empty())
	{
		//�½�������
		m_bNewProp = TRUE;
	}
	if (m_bNewProp && !m_bReadNewProp )
	{
		//�½����ԣ��Ҳ��Ƕ�����ʱ����
		//�����½����Ե��ļ���Ϣ
		m_dataOffsets[time] = 0;
		m_strFiles[time] = _T("");
		WriteData();
	}
}

void CGridPropUnitPo::AddGridPropData( const CGridRecive& gridRev,const COleDateTime& time,const GridNo& gridNo,const double& dValue )
{
	//����������Ϊ��
	ASSERT(!m_strPropName.IsEmpty());
	//������뿪ʼ(�൱�ڶ��̵߳Ļ�����)
	//ASSERT(gridRev.IsTransactionData());	
	long ISize = 0;
	long JSize = 0;
	long lKsize = 0;
	gridRev.GetGridSize(ISize,JSize,lKsize);
	//������������
	long gridIndex = gridNo.noK * JSize  * ISize  + gridNo.noJ * ISize + gridNo.noI;

	if (!m_bTotalGridData)
	{
		gridIndex = gridRev.GetGridValueIndex(gridIndex);
	}

	//1  gridNo.noK * JSize  * ISize  + gridNo.noJ * ISize + gridNo.noI
	//2  gridNo.noK * JSize  * ISize  + gridNo.noI * JSize + gridNo.noJ
	//������Ѳ�ֵ��ȫ�����ݣ������ֵ
	if ( m_strCurStoreDataProp != m_strPropName )
	{
		//ֻ����ʱȡ������,����m_namedGridProps,��д���ļ�
		//��ǰʱ�䲽�����ݱ������
		ASSERT(m_namedGridProps.find(time) != m_namedGridProps.end());
		m_namedGridProps[time][gridIndex] = dValue;
	}
	else
	{
		//��ǰʱ�䲽�����ݱ������
		ASSERT(m_GridProps.find(time) != m_GridProps.end());
		m_GridProps[time][gridIndex] = dValue;
	}
	m_bRecal = TRUE;
}

void CGridPropUnitPo::FlushFile()
{
	if ( !m_bFlush )
	{
		//�ļ�����δд��
		m_file.Flush();
		//��д���ļ�
		m_bFlush = TRUE;
	}
}

//�޸���������
void CGridPropUnitPo::ModifyGridPropData( CGridRecive& gridRev,const COleDateTime& time,
									   const GridNo& gridNo,const double& dValue )									  
{
	ASSERT(!m_strPropName.IsEmpty());	
	
	//��������Ƿ�Ҫ����
	double resVal;
	CheckAndCalcProp(resVal , gridNo , time ,TRUE);
	//��ȡ������
	long ISize = 0;
	long JSize = 0;
	long KSize = 0;
	gridRev.GetGridSize(ISize , JSize , KSize);
	//������������
	long gridIndex = gridNo.noK * JSize  * ISize  + gridNo.noJ * ISize + gridNo.noI;
	//����ָ�����������ֵ	
	COleDateTime  curtime = time;
	if (m_dataOffsets.find(time) == m_dataOffsets.end())
	{
		TimedDataOffset::iterator propIter = m_dataOffsets.end();
		--propIter;
		//ʱ����Ϊ���һ��ʱ��
		curtime = propIter->first;
	}

	if (!m_bTotalGridData)
	{
		gridIndex = gridRev.GetGridValueIndex(gridIndex);
	}

	if (gridIndex == -1) //��Ч����
	{
		return;
	}

	//�޸��ļ��е�����
	ModifyGridPropData( curtime, gridIndex, dValue );

	if ( m_strCurStoreDataProp != m_strPropName )
	{
		//ֻ����ʱ�޸ĵ�����,ֱ��д�ļ�
		if (m_bCalcState)
		{
			////����ʱ�޸�
			//if (m_namedGridProps.empty())
			//{
			//	ReadData();
			//}
			if (m_namedGridProps[curtime].size() <= gridIndex)
			{
				m_namedGridProps[curtime].resize(gridIndex+1, UNACTVALUE);
			}
			m_namedGridProps[curtime][gridIndex] = dValue; 
		}
		return;
	}

	//�޸��ڴ��е�����
	ASSERT(m_GridProps.find(curtime) != m_GridProps.end());
	if(m_GridProps[curtime].size() == 0)
	{
		m_GridProps[curtime].resize(ISize * JSize * KSize, UNACTVALUE);
	}

	m_GridProps[curtime][gridIndex] = dValue;

	//����Ҫ���¼������������Сֵ
	m_bRecal = TRUE;
}

double CGridPropUnitPo::GetPropValue( const CGridRecive& gridRev,const COleDateTime& time,const GridNo& gridNo )
{
	//��ѯ��������ʱ���Ȳ�ѯ����map�Ƿ�Ϊ��
	//���Ϊ�գ��ٲ�ѯ��������Ӧ���ļ���Ϣ�Ƿ�Ϊ��
	//���Ϊ��������������������ļ�
	//��ѯ������������
	double dbRes = UNACTVALUE;
	if (!m_bCalcState)
	{
		//���Ǽ���ʱȡֵ���ж��Ƿ���Ч����
		//����ʱ��ȡֵǰ���ж�
		if (!m_pReciveData->IsGridAct(GridNo(gridNo.noI+1 , gridNo.noJ + 1 ,gridNo.noK + 1)))
		{
			//��Ч����
			return dbRes;
		}
	}

	//����ֵʱ��	
	COleDateTime  curtime = time;
	//��������Ƿ�Ҫ����
	if (CheckAndCalcProp(dbRes , gridNo , curtime , m_bCalcAllProp))
	{
		return dbRes;
	}

	if (m_dataOffsets.find(curtime) == m_dataOffsets.end())
	{
		TimedDataOffset::iterator propIter = m_dataOffsets.end();
		--propIter;
		//ʱ����Ϊ���һ��ʱ��
		curtime = propIter->first;
	}

	//��ǰʱ�����������ļ���
	CString fileName;
	fileName = m_strFiles[curtime];
	MakeFileOpen(fileName);

	//������
	long ISize = 0;
	long JSize = 0;
	long KSize = 0;

	//��ȡ������
	gridRev.GetGridSize(ISize ,JSize ,KSize);

	//����ֵ���� ע����long long
	long long gridIndex = gridNo.noK * JSize  * ISize  + gridNo.noJ * ISize + gridNo.noI;

	if ( m_strCurStoreDataProp != m_strPropName )
	{
		if (m_bCalcState)
		{
			//����ʱȡֵ
			return GetCalcPropValue( curtime, gridIndex , TRUE ); 
		}

		//ֻ����ʱȡ������,����m_namedGridProps,��д���ļ�
		if (!m_bFile)
		{
			//δ�����ļ�
			//����ֵʵ������
			if (m_realOffset.empty())
			{
				//δ����ʵ��������Ӧ��ϵ
				GetRealOffset( );
			}

			//��ǰ���Լ�¼������������ʱ
			if (!m_bTotalGridData)
			{
				gridIndex = m_realOffset[gridIndex];				
			}
			else
			{
				gridIndex = GetTotalGridValueOffset(gridIndex);
			}

			gridIndex += m_dataOffsets[curtime];
			//��ԭ�ļ���ȡ����
			float dbData;
			float dbDataRes;
			int    intDataRes;
			if (curtime != m_pretime)
			{
				if (m_bFileOpen )
				{
					if ( m_dateFile.GetFilePath() != fileName)
					{
						//�򿪹��ļ����ȹر�
						m_dateFile.Close();
						m_bFileOpen = FALSE;
					}					
				}

				if (!m_bFileOpen)
				{
					::SetFileAttributes(fileName ,FILE_ATTRIBUTE_NORMAL); 
					//�򿪵�ǰʱ�����������ļ�
					if (m_dateFile.Open(fileName , CFile::typeBinary | CFile::modeRead | CFile::shareDenyNone))
					{
						m_bFileOpen = TRUE;
					}
				}

				m_pretime = curtime;
			}

			if (!m_bFileOpen)
			{
				//AfxMessageBox("�ļ� " + fileName + " ��ʧ��");
				return UNACTVALUE;
			}

			m_dateFile.Seek(gridIndex , CFile::begin);
			m_dateFile.Read(&dbData , 4);

			if (m_dataRealType == _T("INTE"))
			{
				intread(&intDataRes,(char*)&dbData);
				return intDataRes;
			}
			else
			{
				realread(&dbDataRes,(char*)&dbData);
				return dbDataRes;
			}			
			//////////////////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////////////
		}
		else
		{
			//����д���ļ�
			FlushFile();
			//�����ļ��е�����
			dbRes = GetPropValue( curtime, gridIndex );
		}	

		return dbRes;
	}

	if (m_bCalcState)
	{
		//����ʱȡֵ
		return GetCalcPropValue( curtime, gridIndex , FALSE ); 
	}

	//����д���ļ�
	FlushFile();
	//��ȡָ����������ֵ�����ʱ����ֵ���򷵻����һ��ʱ���ֵ
	//double tempVal = GetCalcPropValue( curtime, gridIndex , FALSE );
	return GetCalcPropValue( curtime, gridIndex , FALSE ); 
}

std::vector<double> CGridPropUnitPo::getPropValues(const COleDateTime& time,const std::vector<GridNo>& gridNos){
	//����ֵʱ��	
	COleDateTime curtime = time;
	if(m_dataOffsets.find(curtime) == m_dataOffsets.end())
	{
		TimedDataOffset::iterator propIter = m_dataOffsets.end();
		--propIter;
		//ʱ����Ϊ���һ��ʱ��
		curtime = propIter->first;
	}
	std::vector<double> values;
	CString fileName = m_strFiles[time];
	//�ļ�����
	HANDLE handle = CreateFile(fileName,GENERIC_READ,FILE_SHARE_READ,NULL, OPEN_EXISTING, FILE_FLAG_RANDOM_ACCESS, NULL);
	if(INVALID_HANDLE_VALUE == handle)
		return values;
	//�ļ�ӳ�����
	HANDLE fileMap = CreateFileMapping(handle,NULL,PAGE_READONLY,0,0,NULL);
	if(NULL == fileMap){
		CloseHandle(handle);
		return values;
	}
	//�õ��ļ��ߴ�
	DWORD dwFileSizeHigh;
	__int64 qwFileSize = GetFileSize(handle, &dwFileSizeHigh);
	qwFileSize |= (((__int64)dwFileSizeHigh) << 32); //MSDN

	//ƫ����
	__int64 qwFileOffset = 0;

	//�õ�ϵͳ��������
	SYSTEM_INFO SysInfo;
	GetSystemInfo(&SysInfo);
	DWORD dwGran = SysInfo.dwAllocationGranularity;

	//���С
	DWORD dwBlockBytes = 1500 * dwGran;//�ļ����ݷֶδ�С
	if (dwBlockBytes > qwFileSize)
	{
		dwBlockBytes = (DWORD)qwFileSize;
	}

	//ӳ����ͼ
	char *lpbMapAddress = (char*)MapViewOfFile(fileMap, FILE_MAP_READ, (DWORD)(qwFileOffset >> 32), (DWORD)(qwFileOffset & 0xFFFFFFFF),dwBlockBytes);
	if (NULL == lpbMapAddress){
		CloseHandle(handle);	
		CloseHandle(fileMap);
		return values;
	}
	if (curtime != m_pretime)
		m_pretime = curtime;
	//��־λƫ����
	__int64 start = m_dataOffsets[curtime];
	//��ʼƫ����
	qwFileOffset = start + 28;
	//��ֹƫ����
	__int64 endOffset = qwFileOffset + m_dataCount*4 + m_dataCount/1000*8;
	//ƫ�Ƶ�ַ
	lpbMapAddress += qwFileOffset;
	//ת�������������
	float result;
	while(qwFileOffset < endOffset){
		if((qwFileOffset-start)/4%1000 == 0){
			qwFileOffset += 8;
			lpbMapAddress += 8;
			continue;
		}
		realread(&result,lpbMapAddress);
		values.push_back(result);
		qwFileOffset += 4;
		lpbMapAddress += 4;
	}
	CloseHandle(handle);	
	CloseHandle(fileMap);
	if (m_realGridIndexOffset.empty()){
		getGridIndexOffset();
	}
	//������
	long lIsize = 0;
	long lJsize = 0;
	long lKsize = 0;
	m_pReciveData->GetGridSize(lIsize,lJsize,lKsize);
	//��Ч�������
	long nUnAct = 0;
	std::vector<double> valueResult(0);
	for(std::vector<GridNo>::const_iterator iter = gridNos.begin();iter != gridNos.end(); ++iter){
		if(m_pReciveData->IsGridAct(*iter)){
			__int64 gridIndex = ((*iter).noK-1) * lIsize  * lJsize + ((*iter).noJ-1) * lIsize + (*iter).noI-1;
			valueResult.push_back(values[m_realGridIndexOffset[gridIndex]]);
			/*char str[50];
			sprintf(str,"����㣺I:%d,J:%d,K:%d,����ֵ��index:%d ,realIndex:%d\n",(*iter).noI,(*iter).noJ,(*iter).noK,gridIndex,m_realGridIndexOffset[gridIndex]);
			::OutputDebugString(str);*/
		}
		else
			valueResult.push_back(UNACTVALUE);
	}
	return valueResult;
}

double CGridPropUnitPo::GetPropValue( COleDateTime curtime, long gridIndex )
{
	double dbRes = UNACTVALUE;
	//�����ļ��е�����
	//ȡ����
	ASSERT(m_dataOffsets.find(curtime) != m_dataOffsets.end());
	//�����ļ�ָ�뵽����λ��
	m_file.Seek(8 * (gridIndex + 1) + m_dataOffsets[curtime] , CFile::begin); //���ݺ�
	m_file.Read( &dbRes , 8);
	return dbRes;
}

double CGridPropUnitPo::GetCalcPropValue( COleDateTime curtime, long gridIndex , BOOL btemp )
{
	try
	{
		//��ǰ���԰���������Ч��������ʱ�����ض�λ����ƫ��
		if (!m_bTotalGridData /*&& !m_bCalcState*/)
		{
			//���gridIndex=496, ǰ����4����Ч����
			gridIndex = m_pReciveData->GetGridValueIndex(gridIndex); //ִ������һ���gridIndex=492
			if (gridIndex == -1) //��Ч����
			{
				return UNACTVALUE;
			}
		}

		if (btemp)
		{
			//����Ҫ��ʾ�����ԣ���������ʱ��������������
			//����ʱȡֵ
			if (m_namedGridProps.find(curtime) == m_namedGridProps.end())
			{
				ReadData(curtime);
			}	

			if (m_strCurStoreDataProp == m_strPropName)
			{
				if (gridIndex < m_GridProps[curtime].size())
				{
					return m_GridProps[curtime][gridIndex]; 			
				}
				else
				{
					return UNACTVALUE;
				}
			}
			else
			{
				if (gridIndex < m_namedGridProps[curtime].size())
				{
					return m_namedGridProps[curtime][gridIndex]; 			
				}
				else
				{
					return UNACTVALUE;
				}
			}
		}

		//�Ǽ���ʱȡֵ
		TimedGridProp::iterator it = m_GridProps.find(curtime);
		if (it == m_GridProps.end())
		{
			ReadData(curtime);
		}

		if (gridIndex < m_GridProps[curtime].size())
		{
			return m_GridProps[curtime][gridIndex]; 		
		}
		else
		{
			return UNACTVALUE;
		}
	}
	catch (...)
	{
		//CString strTime = curtime.Format("%Y-%m-%d");
		//size_t n = m_GridProps[curtime].size();
		//CString projectName = CProjectManger::getSingletonPtr()->GetActiveCase()->GetTitle();
		//AfxMessageBox(projectName);
		//projectName.Format("%d" ,n);
		//AfxMessageBox(projectName);
		//AfxMessageBox(strTime);
		return UNACTVALUE;
	}
}

void CGridPropUnitPo::ReCalcPropMaxmin( )
{
	COleDateTime time = CProjectManger::getSingletonPtr()->GetActiveCase()->GetGridData().GetCurTime();

	//��ʼ�������С
	m_dMaxValue = m_dMinValue = UNACTVALUE;

	//TimedGridProp::iterator propIter = m_GridProps.begin();
	////��������ʱ�������
	//for (;propIter != m_GridProps.end() ; ++propIter)
	//{

	bool bFirstFlag = true;

	TimedGridProp::iterator propIter = m_GridProps.find(time);
	if (propIter != m_GridProps.end())
	{
		GridPropValue& timeVal = m_GridProps[propIter->first];
		for (size_t nProp = 0;nProp < timeVal.size();++nProp)
		{
			if (timeVal[nProp] == UNACTVALUE)
			{
				continue;
			}

			if (bFirstFlag)
			{
				m_dMaxValue = m_dMinValue = timeVal[nProp];
				bFirstFlag = false;
				continue;
			}

			m_dMaxValue = max(m_dMaxValue , timeVal[nProp]);
			m_dMinValue = min(m_dMinValue , timeVal[nProp]);
		}
	}

	//�����Ƿ�Ҫ���¼��������Сֵ
	m_bRecal = FALSE;
}

BOOL CGridPropUnitPo::GetKMinMaxValue(CGridRecive& gridRecive , const COleDateTime& time,long layer,double& dMaxValue,double& dMinValue)
{
	//���õ�ǰ��ʾ��������
	m_strCurStoreDataProp = m_strPropName;

	long ISize = 0;
	long JSize = 0;
	long KSize = 0;
	gridRecive.GetGridSize(ISize ,JSize ,KSize);

	//��ȡ��ǰʱ�䵱ǰ�����������Сֵ
	BOOL bInit = FALSE;
	long nSkip = layer * JSize * ISize;
	long surSize = JSize * ISize;

	double curVal = UNACTVALUE;
	for (long nIndex = 0; nIndex < surSize; ++nIndex)
	{
		int gridnoI;
		int gridnoJ;
		if ((nIndex + 1) % ISize == 0)
		{
			gridnoI = ISize;
			gridnoJ = (nIndex + 1) / ISize;
		}
		else
		{
			gridnoI = (nIndex + 1) % ISize;
			gridnoJ = (nIndex + 1) / ISize + 1;
		}

		GridNo gridNo(gridnoI, gridnoJ, layer + 1);
		if (gridRecive.IsGridAct(gridNo) == false) //��Ч����
		{
			continue;
		}

		int newIndex;
		if (!m_bTotalGridData)
		{
			//���nSkip + nIndex=496, ǰ����4����Ч����
			newIndex = gridRecive.GetGridValueIndex(nSkip + nIndex); //ִ������һ���newIndex=492
		}
		else
		{
			newIndex = nSkip + nIndex;
		}

		if (m_GridProps.size() == 1)
		{
			//���ھ�̬����DZNET, �л�ʱ���ʱ��, m_GridProps����ʼ��ֻ��һ��ʱ�������
			curVal = m_GridProps.begin()->second[newIndex];
		}
		else
		{
			curVal = m_GridProps[time][newIndex];
		}

		if (curVal != UNACTVALUE)
		{
			if (!bInit)
			{
				//δ��ʼ�����ʼ��
				dMaxValue = dMinValue = curVal;
				bInit = TRUE;
			}
			else
			{
				dMaxValue = max(dMaxValue , curVal);
				dMinValue = min(dMinValue , curVal);
			}
		}
	}

	return TRUE;
}

void CGridPropUnitPo::GetMinMaxValue( double& dMaxValue,double& dMinValue )
{
	if (m_strCurStoreDataProp != m_strPropName || m_strCurStoreDataCase != GetDataCaseName())
	{
		//�����л���
		m_GridProps.clear();
		//���õ�ǰ��ʾ��������
		m_strCurStoreDataProp = m_strPropName;
		m_strCurStoreDataCase = GetDataCaseName();
	}
	
	COleDateTime time = CProjectManger::getSingletonPtr()->GetActiveCase()->GetGridData().GetCurTime();
	TimedGridProp::iterator itData = m_GridProps.find(time);
	if (itData == m_GridProps.end())
	{
		//δ��ȡ����,���ȶ�ȡ����
		ReadData(time);
	}
	//����ʱ�����в������Сֵ
	if (m_bRecal)
	{
		//��Ҫ���¼��������Сֵ
		ReCalcPropMaxmin();
	}
	dMaxValue = m_dMaxValue;
	dMinValue = m_dMinValue;
}

void CGridPropUnitPo::BindGridFunction( CGridRecive& gridRev  /*, int nDataType */)
{
	//�󶨻ص�����
	GridFunction gridFun;
	gridFun.createGridPropData = boost::bind(&CGridPropUnitPo::CreateGridPropData, this , _1,_2,_3);
	gridFun.getKMinMaxValue = boost::bind(&CGridPropUnitPo::GetKMinMaxValue, this , _1,_2,_3,_4,_5);
	gridFun.setValue = boost::bind(&CGridPropUnitPo::ModifyGridPropData, this , _1,_2,_3,_4);
	gridFun.getValue = boost::bind(&CGridPropUnitPo::GetPropValue, this , _1,_2,_3);
	gridFun.getValues = boost::bind(&CGridPropUnitPo::getPropValues,this,_1,_2);
	gridFun.getMinMax = boost::bind(&CGridPropUnitPo::GetMinMaxValue, this , _1,_2);
	gridFun.clearData = boost::bind(&CGridPropUnitPo::ClearData, this );
	gridFun.getDataType = boost::bind(&CGridPropUnitPo::GetDataType, this );
	gridFun.isExistTime = boost::bind(&CGridPropUnitPo::IsExistTime, this ,_1);
	gridFun.checkCurPropData = boost::bind(&CGridPropUnitPo::CheckCurPropData, this );
//	gridFun.copyGridPropUnit = boost::bind(&CGridPropUnitPo::CopyObj, this , _1,_2);
	gridFun.closeFileHandle = boost::bind(&CGridPropUnitPo::CloseFileHandle, this );
	gridRev.SetGridFunction(m_strPropName , gridFun);
	//��������
	m_pReciveData = &gridRev;
	//���ɵ��ļ���
	//�ļ�������Ŀ��.������
	CString fileName;
	//�ļ���
	fileName.Format("%s\\%s.%s" , m_objPath , m_objName , m_strPropName);	
	//���ļ�
	if ( m_bFile )
	{
		// ���ļ��Ѵ����ȹر��ļ�
		if (m_bFileOpen)
		{
			m_file.Close();
		}

		//���ļ�
		if (m_file.Open(fileName , CFile::modeReadWrite | CFile::typeBinary ))
		{
			m_bFileOpen = TRUE;
		}
		else
		{
			//��ʧ��
			AfxMessageBox(fileName + "��ʧ�ܣ������¼���");
			m_bFile = FALSE;
			m_strFiles.clear();
			m_dataOffsets.clear();
		}
	}
}

void CGridPropUnitPo::SetTimePropDatas( CGridRecive& gridRecive ,GridValues& allPropvalues ,
									 const COleDateTime& time )
{
	long lIsize = 0;
	long lJsize = 0;
	long lKsize = 0;
	gridRecive.GetGridSize(lIsize,lJsize,lKsize);
	long nVals = (long)allPropvalues.size();
	if (nVals == 0)
	{
		//û�ж�������
		return;
	}
	//if (nVals == lIsize * lJsize * lKsize)
	{
		//������Ѳ�ֵ��ȫ�����ݣ������ֵ
		if ( m_strCurStoreDataProp != m_strPropName )
		{
			//ֻ����ʱȡ������,����m_namedGridProps,��д���ļ�
			m_namedGridProps[time] = allPropvalues;
		}
		else
		{
			m_GridProps[time] = allPropvalues;
		}
		//��������
		allPropvalues.clear();
		return;
	}
	//int nUnAct = 0;
	//long index = 0;
	//GridNo gridNo(0 ,0 ,0);
	////��ֵ
	//for (long kIndex = 0;kIndex < lKsize ;++kIndex)
	//{
	//	for (long jIndex = 0;jIndex < lJsize ;++jIndex)
	//	{
	//		for (long iIndex = 0;iIndex < lIsize ;++iIndex)
	//		{
	//			index = kIndex * lIsize  * lJsize + jIndex * lIsize + iIndex;
	//			//Ϊ���ⲿ�ӿ��ж������Ƿ���Чʱ������ʼ��ͳһ��1��ʼ�������1
	//			gridNo.noI = iIndex + 1;
	//			gridNo.noJ = jIndex + 1;
	//			gridNo.noK = kIndex + 1;
	//			if (gridRecive.IsGridAct(gridNo))
	//			{
	//				gridNo.noI = iIndex;
	//				gridNo.noJ = jIndex;
	//				gridNo.noK = kIndex;
	//				AddGridPropData(gridRecive ,time ,gridNo,allPropvalues[index - nUnAct] );
	//			}
	//			else
	//			{
	//				++nUnAct;
	//			}
	//		}
	//	}
	//}
	//allPropvalues.clear();
}
void CGridPropUnitPo::GetRealOffset(){
	//������
	long lIsize = 0;
	long lJsize = 0;
	long lKsize = 0;
	m_pReciveData->GetGridSize(lIsize,lJsize,lKsize);
	long nUnAct = 0;
	long index = 0;
	GridNo gridNo(0 ,0 ,0);
	//////////////////////////////////////////////////////////////////////////
	//��ֵ
	for (long kIndex = 0;kIndex < lKsize ;++kIndex)
	{
		for (long jIndex = 0;jIndex < lJsize ;++jIndex)
		{
			for (long iIndex = 0;iIndex < lIsize ;++iIndex)
			{
				index = kIndex * lIsize  * lJsize + jIndex * lIsize + iIndex;
				//Ϊ���ⲿ�ӿ��ж������Ƿ���Чʱ������ʼ��ͳһ��1��ʼ�������1
				gridNo.noI = iIndex + 1;
				gridNo.noJ = jIndex + 1;
				gridNo.noK = kIndex + 1;
				if (m_pReciveData->IsGridAct(gridNo))
				{
					//��Ч�����ʵ������
					//�ؼ��������Ϣ�ֽ���:24 + 4,��ReadPropData�����ڶ�����ǰ�Ĵ���
					//ÿ1000������Ҫ����8���ֽ�
					//*4�ǽ�ƫ�Ƶ������ݵ���ʼ�ֽ�
					m_realOffset[index] = ((index - nUnAct) * 4 + (( index - nUnAct ) / 1000) * 8) + 28;
				}
				else
				{
					//��Ч������
					++nUnAct;
				}
			}
		}
	}
}

void CGridPropUnitPo::getGridIndexOffset(){
	//������
	long lIsize = 0;
	long lJsize = 0;
	long lKsize = 0;
	m_pReciveData->GetGridSize(lIsize,lJsize,lKsize);
	long nUnAct = 0;
	long index = 0;
	GridNo gridNo(0 ,0 ,0);
	//////////////////////////////////////////////////////////////////////////
	//��ֵ
	for (long kIndex = 0;kIndex < lKsize ;++kIndex)
	{
		for (long jIndex = 0;jIndex < lJsize ;++jIndex)
		{
			for (long iIndex = 0;iIndex < lIsize ;++iIndex)
			{
				index = kIndex * lIsize  * lJsize + jIndex * lIsize + iIndex;
				//Ϊ���ⲿ�ӿ��ж������Ƿ���Чʱ������ʼ��ͳһ��1��ʼ�������1
				gridNo.noI = iIndex + 1;
				gridNo.noJ = jIndex + 1;
				gridNo.noK = kIndex + 1;
				if (m_pReciveData->IsGridAct(gridNo))
				{
					//��Ч�����ʵ������
					m_realGridIndexOffset[index] = index - nUnAct;
				}
				else
				{
					//��Ч������
					++nUnAct;
				}
			}
		}
	}
}

long CGridPropUnitPo::GetTotalGridValueOffset( long lGridIndex )
{
	std::map<long, long>::iterator itFind = m_totalOffset.find(lGridIndex);
	if (itFind != m_totalOffset.end())
	{
		return itFind->second;
	}

	long lOffset = lGridIndex * 4 + (lGridIndex / 1000) * 8 + 28;
	m_totalOffset[lGridIndex] = lOffset;
	return lOffset;
}

void CGridPropUnitPo::SetDataInfo( CString strPropName , CGridRecive* gridRecive ,CString strFile,	const COleDateTime& curTime ,__int64 dataOffset,__int64 dataCount)
{
	//����ʱ��
	if (m_dataOffsets.find( curTime ) != m_dataOffsets.end())
	{
		return;
	}
	//û�ж��������򱣴�������Ϣ
	//���������ļ���
	m_strFiles[curTime] = strFile;
	//��������
	m_pReciveData = gridRecive;
	//ʱ��
	m_dataOffsets[curTime] = dataOffset;
	//������
	m_strPropName = strPropName;
	//�������
	m_dataCount = dataCount;
	if(m_realGridIndexOffset.empty())
		getGridIndexOffset();
}

void CGridPropUnitPo::SetDataInfo(CString strPropName,CGridRecive* gridRecive ,const COleDateTime& curTime){
	//����ʱ��
	if (m_dataOffsets.find( curTime ) != m_dataOffsets.end())
	{
		return;
	}
	//û�ж��������򱣴�������Ϣ
	//���������ļ���
	//m_strFiles[curTime] = strFile;
	//��������
	m_pReciveData = gridRecive;
	//ʱ��
	//m_dataOffsets[curTime] = dataOffset;
	//������
	m_strPropName = strPropName;
}

BOOL CGridPropUnitPo::IsExistTime(const COleDateTime& time)
{
	if (m_dataOffsets.find( time ) == m_dataOffsets.end())
	{
		//��ʱ��û������
		if (m_bCalcState == TRUE)
		{
			double dbRes;
			CheckAndCalcProp(dbRes , GridNo(0 , 0 , 0) , time , TRUE);
		}
		if (m_dataOffsets.find( time ) == m_dataOffsets.end())
		{
			return FALSE;
		}
	}
	return TRUE;
}

void CGridPropUnitPo::ReadData(const COleDateTime& time)
{
	//��������Ƿ�Ҫ����
	if (m_strFiles.empty())
	{
		double resVal;
		GridNo gridNo(0,0,0);
		m_strCurStoreDataProp = m_strPropName;
		COleDateTime curTime;
		CheckAndCalcProp(resVal , gridNo , curTime , TRUE);
		return;
	}
	//��ȡ����ʱ�䲽����	
	TimedDataOffset::iterator it_dataIf = m_dataOffsets.begin();
	CString fileName;
	fileName = m_strFiles[it_dataIf->first];
	MakeFileOpen(fileName);
	if (m_bFile)
	{
		//AfxMessageBox("ȫ����ȡ");
		//������д���ļ�����ֱ�Ӷ�ȡ
		for (int nDate = 0; it_dataIf != m_dataOffsets.end() ;++it_dataIf, ++nDate)
		{
			//���ļ������������ļ��е���ʼλ����Ϣ����ȡ����
			//���һ��ʱ�䲽����
			m_bReadNewProp = TRUE;
			CreateGridPropData(*m_pReciveData , it_dataIf->first  ,m_strPropName);
			if (m_bFileOpen)
			{
				//�����ļ�ָ�뵽������ʼλ��
				m_file.Seek(it_dataIf->second , CFile::begin);
				//��ȡ����
				if ( m_strPropName != m_strCurStoreDataProp )
				{
					ULONGLONG nDataSize;
					m_file.Read(&nDataSize, 8);

					m_namedGridProps[it_dataIf->first].resize(nDataSize, UNACTVALUE);

					//ֻ����ʱȡ������,���ļ�����m_namedGridProps
// 					m_file.Read(&m_namedGridProps[it_dataIf->first][0] , ((int)m_namedGridProps[it_dataIf->first].size()) * 8 );
					m_file.Read(&m_namedGridProps[it_dataIf->first][0] , nDataSize * 8 );
				}
				else
				{
					ULONGLONG nDataSize;
					m_file.Read(&nDataSize, 8);

					if (m_GridProps[it_dataIf->first].size() == 0)
					{
						//��ȡ������
						long ISize = 0;
						long JSize = 0;
						long KSize = 0;
						m_pReciveData->GetGridSize(ISize , JSize , KSize);

						//m_GridProps[it_dataIf->first].resize(nDataSize, UNACTVALUE);
						m_GridProps[it_dataIf->first].resize(ISize * JSize * KSize, UNACTVALUE);
					}

					//���ļ�����m_GridProps
					m_file.Read(&m_GridProps[it_dataIf->first][0] , ((int)m_GridProps[it_dataIf->first].size()) * 8 );
				}
			}
		}

		m_bReadNewProp = FALSE;
		return;
	}

	//��ȡ����ʹ��
	ReadProp(time);
}

//������д���Զ����ļ�(SimDataCath)
void CGridPropUnitPo::WriteData()
{
	//����ǰʱ�������д���ļ�
	TimedGridProp::iterator it_time = m_GridProps.begin();	
	TimedDataOffset::iterator it_dataIf = m_dataOffsets.begin();
	if ( m_strCurStoreDataProp != m_strPropName )
	{
		//ֻ����ʱȡ������,����m_namedGridProps,��д���ļ�
		it_time = m_namedGridProps.begin();
	}
	//���ɵ��ļ���
	//�ļ�������Ŀ��.������
	CString fileName;
	//���ļ�
	if ( !m_bFile )
	{
		m_objPath = CProjectManger::getSingletonPtr()->GetPrjPath();
		m_objPath += _T("simCatche");
		m_objName = CProjectManger::getSingletonPtr()->GetActiveCase()->GetTitle();
		//�½��Զ���Ŀ¼
		::CreateDirectory(m_objPath , NULL);
		//�ļ���
		fileName.Format("%s\\%s.%s" , m_objPath , m_objName , m_strPropName);	
		//���ļ�
		CFileFind fileFind;
		if (fileFind.FindFile(fileName))
		{
			if (m_lgrName != "")
			{
				fileName.Format("%s\\%s.%s.%s" , m_objPath , m_objName ,m_lgrName, m_strPropName);
			}
		}
		m_file.Open(fileName , CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary );
		m_bFileOpen = TRUE;
	}
	if (m_bNewProp)
	{
		if (!m_namedGridProps.empty())
		{
			//д���½�����,ֻд���һ��ʱ�������
			it_time = m_namedGridProps.end();
			if (m_strCurStoreDataProp == m_strPropName)
			{
				//���ѡ��Ҫ���������
				it_time = m_GridProps.end();
			}
			--it_time;
			it_dataIf = m_dataOffsets.end();
			--it_dataIf;
			//�޸ĵ�ǰʱ���������Ϣ
			m_strFiles[it_dataIf->first] = fileName;
			//д���ļ���β
			it_dataIf->second = m_file.SeekToEnd();
			ULONGLONG nDataSize = it_time->second.size();
			m_file.Write(&nDataSize, 8);
			m_file.Write(&it_time->second[0] , (int)it_time->second.size() * 8 );
		}
	}
	else
	{
		for (int nDate = 0; it_dataIf != m_dataOffsets.end() ; ++it_dataIf, ++nDate)
		{
			//�޸ĵ�ǰʱ���������Ϣ
			m_strFiles[it_dataIf->first] = fileName;
			//д���ļ�
			it_dataIf->second = m_file.GetPosition();
			ULONGLONG nDataSize = it_time->second.size();
			m_file.Write(&nDataSize, 8);
			m_file.Write(&it_time->second[0] , (int)it_time->second.size() * 8 );		
		}
	}
	m_bFile = TRUE;
	//����д���ļ�
	m_file.Flush();
}

void CGridPropUnitPo::ModifyGridPropData( COleDateTime curtime, long gridIndex, const double& dValue )
{
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//����ֵʱ��	
	if (m_dataOffsets.find(curtime) == m_dataOffsets.end())
	{
		TimedDataOffset::iterator propIter = m_dataOffsets.end();
		--propIter;
		//ʱ����Ϊ���һ��ʱ��
		curtime = propIter->first;
	}
	//��ǰʱ�����������ļ���
	CString fileName;
	fileName = m_strFiles[curtime];
	MakeFileOpen(fileName);
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	if (!m_bFile)
	{
		if ((m_GridProps.empty() && m_strCurStoreDataProp == m_strPropName) ||
			(m_namedGridProps.empty() && m_strCurStoreDataProp != m_strPropName))
		{
			//��ǰ����δ������ʱ����δ��
			ReadData(curtime);
		}
		//δ�����ļ�
		WriteData();
	}
	ASSERT(m_dataOffsets.find(curtime) != m_dataOffsets.end());
	//�޸��ļ��е�����
	//�޸�����
	if (m_bFileOpen)
	{
		if (m_file.SeekToEnd() == 0)
		{
			m_file.SeekToBegin();
			ULONGLONG nDataSize = 1;
			m_file.Write(&nDataSize, 8);
		}
		else
		{
			m_file.Seek(m_dataOffsets[curtime], CFile::begin);
			ULONGLONG nDataSize;
			m_file.Read(&nDataSize, 8);
			nDataSize++;
			m_file.Seek(m_dataOffsets[curtime], CFile::begin);
			m_file.Write(&nDataSize, 8);
		}
		//��������������λ��
		m_file.Seek(8 * (gridIndex + 1) + m_dataOffsets[curtime] , CFile::begin);
		//�޸�����
		m_file.Write( &dValue , 8);
		m_bFlush = FALSE;
	}
}

BOOL CGridPropUnitPo::CheckAndCalcProp(double& resVal , GridNo gridNo, COleDateTime curTime ,BOOL bAllCalc /*= FALSE*/ )
{
	//��������m_strFiles(���������ļ�)����Ϊ��
	if (m_strFiles.empty())
	{
		//����״̬���õ������Էŵ���ʱ����������Ż������ٶ�
		m_bCalcState = TRUE;
		if (!bAllCalc)
		{
			//����Ϊȡ����Ϊ�Ǽ���״̬
			m_bCalcState = FALSE;
			++gridNo.noI;
			++gridNo.noJ;
			++gridNo.noK;
			if (!m_pReciveData->IsGridAct(gridNo))
			{
				//��Ч����ֱ�Ӹ���Чֵ
				return TRUE;
			}
			--gridNo.noI;
			--gridNo.noJ;
			--gridNo.noK;
		}
		//�ɼ��������
		if (m_strPropName == _T("DZNET"))
		{
			//����DZNET DZNET = NTG * DZ
			if (!bAllCalc)
			{
				GridFunction dzFunc = m_pReciveData->GetGridFunction(_T("DZ"));
				GridFunction ntgFunc = m_pReciveData->GetGridFunction(_T("NTG"));
				double dzVal = dzFunc.getValue(*m_pReciveData , curTime ,gridNo);
				double ntgVal = ntgFunc.getValue(*m_pReciveData ,curTime ,gridNo);
				if (dzVal == UNACTVALUE || ntgVal == UNACTVALUE)
				{
					return TRUE;
				}
				resVal = dzVal * ntgVal;
				return TRUE;
			}
			CalcData(boost::bind(&CGridPropUnitPo::DZNETdata ,this));
		}
		if (m_strPropName == _T("PORV"))
		{
			//����PORV//PORV = DX*DY*DZ*PORO*NTG
			if (!bAllCalc)
			{
				//ȡ�ø�����ֵ
				GridFunction dzFunc = m_pReciveData->GetGridFunction(_T("DZ"));
				GridFunction ntgFunc = m_pReciveData->GetGridFunction(_T("NTG"));
				GridFunction poroFunc = m_pReciveData->GetGridFunction(_T("PORO"));
				GridFunction dxFunc = m_pReciveData->GetGridFunction(_T("DX"));
				GridFunction dyFunc = m_pReciveData->GetGridFunction(_T("DY"));
				double dzVal = dzFunc.getValue(*m_pReciveData , curTime ,gridNo);
				double ntgVal = ntgFunc.getValue(*m_pReciveData , curTime ,gridNo) ;
				double dxVal = dxFunc.getValue(*m_pReciveData , curTime ,gridNo) ;
				double dyVal = dyFunc.getValue(*m_pReciveData , curTime ,gridNo) ;
				double poroVal = poroFunc.getValue(*m_pReciveData , curTime ,gridNo) ;
				//PORV = DX*DY*DZ*PORO*NTG
				if (dxVal == UNACTVALUE || dyVal == UNACTVALUE || poroVal == UNACTVALUE ||
					dzVal == UNACTVALUE || ntgVal == UNACTVALUE)
				{
					resVal = UNACTVALUE;
					return TRUE;
				}				
				resVal = dxVal * dyVal * dzVal * poroVal * ntgVal;
				return TRUE;
			}
			CalcData(boost::bind(&CGridPropUnitPo::PORVdata ,this));
		}


		if (m_strPropName == _T("SOIL"))
		{
			if (!bAllCalc)
			{
				//�����Իص�����
				GridFunction sgasFunc;
				if (m_pReciveData->IsExistGridFunction("SGAS"))
				{
					sgasFunc = m_pReciveData->GetGridFunction(_T("SGAS"));
				}
				
				GridFunction swatFunc = m_pReciveData->GetGridFunction(_T("SWAT"));			

				if (m_pReciveData->IsExistGridFunction("SGAS"))
				{
					double sgasVal = sgasFunc.getValue(*m_pReciveData , curTime ,gridNo);
					double swatVal = swatFunc.getValue(*m_pReciveData , curTime ,gridNo);
					if (sgasVal == UNACTVALUE || swatVal == UNACTVALUE )
					{
						return TRUE;
					}

					resVal = 1.0 - sgasVal - swatVal;

					return TRUE;
				}
				else
				{
					double swatVal = swatFunc.getValue(*m_pReciveData , curTime ,gridNo);
					if (swatVal == UNACTVALUE )
					{
						return TRUE;
					}

					resVal = 1.0 - swatVal;

					return TRUE;
				}
			}

			CalcData(boost::bind(&CGridPropUnitPo::SOILdata ,this));
		}


		//if (m_strPropName == _T("OGIP"))
		//{
		//	if (!bAllCalc)
		//	{
		//		//�����Իص�����
		//		GridFunction sgasFunc = m_pReciveData->GetGridFunction(_T("SGAS"));
		//		GridFunction porvFunc = m_pReciveData->GetGridFunction(_T("PORV"));
		//		///////////////////////////////////////////////////////////////////////////////////////////////////////
		//		//Ҫ�õ��ı���������Ƶ������
		//		double porvVal = porvFunc.getValue(*m_pReciveData , curTime ,gridNo) ;
		//		double sgasVal = sgasFunc.getValue(*m_pReciveData , curTime ,gridNo) ;
		//		if (sgasVal == UNACTVALUE || porvVal == UNACTVALUE )
		//		{
		//			return TRUE;
		//		}
		//		resVal = sgasVal * porvVal;
		//		return TRUE;
		//	}
		//	CalcData(boost::bind(&CGridPropUnitPo::OGIPdata ,this));
		//}
		//if (m_strPropName == _T("OWIP"))
		//{
		//	if (!bAllCalc)
		//	{
		//		//�����Իص�����
		//		GridFunction swatFunc = m_pReciveData->GetGridFunction(_T("SWAT"));
		//		GridFunction porvFunc = m_pReciveData->GetGridFunction(_T("PORV"));	
		//		///////////////////////////////////////////////////////////////////////////////////////////////////////
		//		//Ҫ�õ��ı���������Ƶ������
		//		double porvVal = porvFunc.getValue(*m_pReciveData , curTime ,gridNo) ;
		//		double swatVal = swatFunc.getValue(*m_pReciveData , curTime ,gridNo) ;
		//		if (porvVal == UNACTVALUE || swatVal == UNACTVALUE )
		//		{
		//			return TRUE;
		//		}
		//		resVal = swatVal * porvVal;
		//		return TRUE;
		//	}
		//	CalcData(boost::bind(&CGridPropUnitPo::OWIPdata ,this));
		//}
		//if (m_strPropName == _T("OOIP"))
		//{
		//	if (!bAllCalc)
		//	{
		//		//�����Իص�����
		//		GridFunction soilFunc = m_pReciveData->GetGridFunction(_T("SOIL"));
		//		GridFunction porvFunc = m_pReciveData->GetGridFunction(_T("PORV"));
		//		///////////////////////////////////////////////////////////////////////////////////////////////////////
		//		//Ҫ�õ��ı���������Ƶ������
		//		double porvVal = porvFunc.getValue(*m_pReciveData , curTime ,gridNo) ;
		//		double soilVal = soilFunc.getValue(*m_pReciveData , curTime ,gridNo) ;
		//		if (porvVal == UNACTVALUE || soilVal == UNACTVALUE )
		//		{
		//			return TRUE;
		//		}
		//		resVal = soilVal * porvVal;
		//		return TRUE;
		//	}
		//	CalcData(boost::bind(&CGridPropUnitPo::OOIPdata ,this));
		//}
		//if (m_strPropName == _T("TSAT"))
		//{
		//	if (!bAllCalc)
		//	{
		//		//�����Իص�����
		//		GridFunction soilFunc = m_pReciveData->GetGridFunction(_T("SOIL"));	
		//		GridFunction swatFunc = m_pReciveData->GetGridFunction(_T("SWAT"));
		//		GridFunction sgasFunc = m_pReciveData->GetGridFunction(_T("SGAS"));
		//		///////////////////////////////////////////////////////////////////////////////////////////////////////
		//		//Ҫ�õ��ı���������Ƶ������
		//		double swatVal = UNACTVALUE ;
		//		double soilVal = UNACTVALUE ;
		//		double sgasVal = UNACTVALUE ;
		//		swatVal = swatFunc.getValue(*m_pReciveData , curTime ,gridNo) ;
		//		soilVal = soilFunc.getValue(*m_pReciveData , curTime ,gridNo) ;
		//		sgasVal = sgasFunc.getValue(*m_pReciveData , curTime ,gridNo) ;
		//		if ( swatVal != UNACTVALUE && soilVal != UNACTVALUE && sgasVal != UNACTVALUE)
		//		{
		//			Structure::CALC_PARAMSOPTION options;
		//			InitOption(options);
		//			double a = options.m_TSATaValue;
		//			double b = options.m_TSATbValue;
		//			double c = options.m_TSATcValue;
		//			resVal =  a * swatVal + b * soilVal + c * sgasVal;
		//		}
		//		return TRUE;
		//	}
		//	CalcData(boost::bind(&CGridPropUnitPo::TSATdata ,this));
		//}

		//if (m_strPropName == _T("FIPOIL1"))
		//{
		//	if (!bAllCalc)
		//	{
		//		double gridArea = CProjectManger::getSingletonPtr()->GetActiveCase()->GetGridData().GetGridArea(GridNo(gridNo.noI+1 , gridNo.noJ + 1 ,gridNo.noK + 1));

		//		double fipoiltVal = UNACTVALUE;
		//		GridFunction fipoilFunc = m_pReciveData->GetGridFunction(_T("FIPOIL"));
		//		fipoiltVal = fipoilFunc.getValue(*m_pReciveData, curTime, gridNo);
		//		if (fipoiltVal != UNACTVALUE && gridArea != 0)
		//		{
		//			//ʣ���ͷ�� FIPOIL1 = FIPOIL / �������          ��λ�� ���/ƽ������
		//			resVal =  fipoiltVal / gridArea;
		//		}

		//		return TRUE;
		//	}

		//	CalcData(boost::bind(&CGridPropUnitPo::FIPOIL1data, this));
		//}

		//if (m_strPropName == _T("FIPOIL2"))
		//{
		//	if (!bAllCalc)
		//	{
		//		//FIPOIL2 (ʣ��ɶ��ʹ���) FIPOIL2 = FIPOIL * ( ( SOIL - SOR) / SOIL )   SOR Ϊ�������(ʣ���ͱ��Ͷ�)
		//		//�����Իص�����
		//		GridFunction fipoilFunc = m_pReciveData->GetGridFunction(_T("FIPOIL"));
		//		GridFunction soilFunc = m_pReciveData->GetGridFunction(_T("SOIL"));
		//		///////////////////////////////////////////////////////////////////////////////////////////////////////
		//		//Ҫ�õ��ı���������Ƶ������
		//		double fipoilVal = UNACTVALUE ;
		//		double soilVal = UNACTVALUE ;
		//		fipoilVal = fipoilFunc.getValue(*m_pReciveData , curTime ,gridNo) ;
		//		soilVal = soilFunc.getValue(*m_pReciveData , curTime ,gridNo) ;
		//		if ( fipoilVal != UNACTVALUE && soilVal != 0 && soilVal != UNACTVALUE)
		//		{
		//			Structure::CALC_PARAMSOPTION options;
		//			InitOption(options);
		//			double sor = options.m_SORValue;
		//			resVal =  fipoilVal * (soilVal - sor) / soilVal;
		//		}
		//		return TRUE;
		//	}
		//	CalcData(boost::bind(&CGridPropUnitPo::FIPOIL2data ,this));
		//}

		//if (m_strPropName == _T("fw"))
		//{
		//	if (!bAllCalc)
		//	{
		//		GridFunction WATKR_Func = m_pReciveData->GetGridFunction(_T("WATKR"));
		//		GridFunction WAT_VISC_Func = m_pReciveData->GetGridFunction(_T("WAT_VISC"));
		//		GridFunction OILKR_Func = m_pReciveData->GetGridFunction(_T("OILKR"));
		//		GridFunction OIL_VISC_Func = m_pReciveData->GetGridFunction(_T("OIL_VISC"));

		//		double WATKR = WATKR_Func.getValue(*m_pReciveData, curTime, gridNo);
		//		double WAT_VISC = WAT_VISC_Func.getValue(*m_pReciveData, curTime, gridNo);
		//		double OILKR = OILKR_Func.getValue(*m_pReciveData, curTime, gridNo);
		//		double OIL_VISC = OIL_VISC_Func.getValue(*m_pReciveData, curTime, gridNo);

		//		if (WATKR == UNACTVALUE || WAT_VISC == UNACTVALUE 
		//			|| OILKR == UNACTVALUE || OIL_VISC == UNACTVALUE)
		//		{
		//			return TRUE;
		//		}				

		//		if (WATKR < 1e-3 && OILKR < 1e-3) //����ʦ
		//		{
		//			resVal = 0;
		//		}
		//		else
		//		{
		//			resVal = 100 * (WATKR / WAT_VISC) / (WATKR / WAT_VISC + OILKR / OIL_VISC);
		//		}

		//		return TRUE;
		//	}

		//	CalcData(boost::bind(&CGridPropUnitPo::fwdata ,this));
		//}


		//����Ϊȡ����Ϊ�Ǽ���״̬
		m_bCalcState = FALSE;
		return FALSE;

	} //if (m_strFiles.empty())

	return FALSE;
}

void CGridPropUnitPo::CalcData( boost::function<BOOL ()> readFunc )
{
	try
	{
		//�Ƿ�Ҫ�ڴ˺����н���������
		BOOL bNeedEnd = FALSE;
		m_bCalcAllProp = TRUE;
		if (!CProgressControl::getSingletonPtr()->IsProgressRun())
		{
			CProgressControl::getSingletonPtr()->BeginProgress();
			bNeedEnd = TRUE;
		}
		readFunc();
		m_bCalcAllProp = FALSE;
		if (bNeedEnd)
		{
			CProgressControl::getSingletonPtr()->EndProgress();
		}
	}
	catch (...)
	{
		m_bCalcAllProp = FALSE;
	}
}

BOOL CGridPropUnitPo::DZNETdata()
{
	//��ʾ������
	CString strCurInfo;
	///////////////////////////////////////////////////////////////////////////////////////////
	//����DZNET
	//DZNET = NTG * DZ
	//���õ�ǰʱ�䣬��������ֵʱʹ�ó�ʼʱ��
	COleDateTime curTime = m_pReciveData->m_SimTimes[0];
	strCurInfo = curTime.Format("%Y-%m-%d");
	CProgressControl::getSingletonPtr()->StepProgress(0 , _T("���ڼ������ݣ�"),_T("��ǰ���ԣ�DZNET ,��ǰʱ�䣺") + strCurInfo);
	CreateGridPropData(*m_pReciveData, curTime ,m_strPropName);
	//û��DZNET��������㣬�����ȡ
	GridFunction dznetFunc = m_pReciveData->GetGridFunction(_T("DZNET"));
	GridFunction dzFunc = m_pReciveData->GetGridFunction(_T("DZ"));
	GridFunction ntgFunc = m_pReciveData->GetGridFunction(_T("NTG"));
	//Ҫ�õ��ı���������Ƶ������
	double dzVal = UNACTVALUE;
	double ntgVal = UNACTVALUE;
	GridNo gridNo(0 ,0 ,0 );
	// �����ģ
	long nI, nJ, nK;
	m_pReciveData->GetGridSize(nI, nJ, nK);

	//û��DZNET���������
	for (long kIndex = 0;kIndex < nK ;++kIndex)
	{
		for (long iIndex = 0;iIndex < nI ;++iIndex)
		{
			for (long jIndex = 0;jIndex < nJ ;++jIndex)
			{
				gridNo.noI = iIndex + 1;
				gridNo.noJ = jIndex + 1;
				gridNo.noK = kIndex + 1;
				if (!m_pReciveData->IsGridAct(gridNo))
				{
					//��Ч����ֱ�Ӹ���Чֵ
					continue;
				}
				gridNo.noI = iIndex;
				gridNo.noJ = jIndex;
				gridNo.noK = kIndex;
				dzVal = dzFunc.getValue(*m_pReciveData , curTime ,gridNo) ;
				ntgVal = ntgFunc.getValue(*m_pReciveData , curTime ,gridNo) ;
				if (dzVal == UNACTVALUE || ntgVal == UNACTVALUE)
				{
					continue;
				}
				dznetFunc.setValue(*m_pReciveData ,curTime ,gridNo, dzVal * ntgVal);
			}
		}	
		CProgressControl::getSingletonPtr()->StepProgress(_T("��ǰ���ԣ�DZNET"));
	}

	dznetFunc.clearData();
	dzFunc.clearData();
	ntgFunc.clearData();

	//////////////////////////////////////////////////////////////////////////
	//������������ʾ
	CProgressControl::getSingletonPtr()->StepProgress(100 , _T("������ݼ��㣡"),_T("��ǰ���ԣ�DZNET") );
	return TRUE;
}

BOOL CGridPropUnitPo::PORVdata()
{
	//��ʾ������
	CProgressControl::getSingletonPtr()->StepProgress(0 , _T("���ڼ������ݣ�"),_T("��ǰ���ԣ�PORV") );
	///////////////////////////////////////////////////////////////////////////////////////////
	//����PORV//PORV = DX*DY*DZ*PORO*NTG
	//���õ�ǰʱ�䣬��������ֵʱʹ�ó�ʼʱ��
	COleDateTime curTime = m_pReciveData->m_SimTimes[0];
	CreateGridPropData(*m_pReciveData, curTime ,m_strPropName);
	//�õ�������
	GridFunction dzFunc = m_pReciveData->GetGridFunction(_T("DZ"));
	GridFunction ntgFunc = m_pReciveData->GetGridFunction(_T("NTG"));
	GridFunction porvFunc = m_pReciveData->GetGridFunction(_T("PORV"));
	GridFunction dxFunc = m_pReciveData->GetGridFunction(_T("DX"));
	GridFunction dyFunc = m_pReciveData->GetGridFunction(_T("DY"));
	GridFunction poroFunc = m_pReciveData->GetGridFunction(_T("PORO"));

	//Ҫ�õ��ı���������Ƶ������
	double dzVal = UNACTVALUE;
	double ntgVal = UNACTVALUE;
	double dxVal  = UNACTVALUE;
	double dyVal = UNACTVALUE;
	double poroVal = UNACTVALUE;
	GridNo gridNo(0 ,0 ,0 );
	// �����ģ
	long nI, nJ, nK;
	m_pReciveData->GetGridSize(nI, nJ, nK);

	//�ɼ���PORV
	for (long kIndex = 0;kIndex < nK ;++kIndex)
	{
		for (long iIndex = 0;iIndex < nI ;++iIndex)
		{
			for (long jIndex = 0;jIndex < nJ ;++jIndex)
			{
				gridNo.noI = iIndex + 1;
				gridNo.noJ = jIndex + 1;
				gridNo.noK = kIndex + 1;
				if (!m_pReciveData->IsGridAct(gridNo))
				{
					//��Ч����ֱ�Ӹ���Чֵ
					continue;
				}
				gridNo.noI = iIndex;
				gridNo.noJ = jIndex;
				gridNo.noK = kIndex;
				//ȡ�ø�����ֵ
				dzVal = dzFunc.getValue(*m_pReciveData , curTime ,gridNo);
				ntgVal = ntgFunc.getValue(*m_pReciveData , curTime ,gridNo) ;
				dxVal = dxFunc.getValue(*m_pReciveData , curTime ,gridNo) ;
				dyVal = dyFunc.getValue(*m_pReciveData , curTime ,gridNo) ;
				poroVal = poroFunc.getValue(*m_pReciveData , curTime ,gridNo) ;
				//PORV = DX*DY*DZ*PORO*NTG
				if (dxVal == UNACTVALUE || dyVal == UNACTVALUE || poroVal == UNACTVALUE ||
					dzVal == UNACTVALUE || ntgVal == UNACTVALUE)
				{
					continue;
				}
				porvFunc.setValue(*m_pReciveData , curTime ,gridNo, dxVal * dyVal * dzVal * poroVal * ntgVal);
			}
		}	
		CProgressControl::getSingletonPtr()->StepProgress(_T("��ǰ���ԣ�PORV"));
	}
	dzFunc.clearData();
	ntgFunc.clearData();
	porvFunc.clearData();
	dxFunc.clearData();
	dyFunc.clearData();
	poroFunc.clearData();
	//////////////////////////////////////////////////////////////////////////
	//������������ʾ
	CProgressControl::getSingletonPtr()->StepProgress(100 , _T("������ݼ��㣡"),_T("��ǰ���ԣ�PORV") );
	return TRUE;
}

#include <time.h>
#include <sstream>
//����SOIL
BOOL CGridPropUnitPo::SOILdata()
{
	//��ʾ������
	CProgressControl::getSingletonPtr()->StepProgress(0 , _T("���ڼ������ݣ�"),_T("��ǰ���ԣ�SOIL") );

	//�����Իص�����
	GridFunction soilFunc = m_pReciveData->GetGridFunction(_T("SOIL"));
	GridFunction swatFunc = m_pReciveData->GetGridFunction(_T("SWAT"));

	GridFunction sgasFunc;
	if (m_pReciveData->IsExistGridFunction("SGAS"))
	{
		sgasFunc = m_pReciveData->GetGridFunction(_T("SGAS"));
	}
	
	COleDateTime curTime;

	double sgasVal = UNACTVALUE;
	double swatVal = UNACTVALUE;
	double soilVal = UNACTVALUE;

	GridNo gridNo(0, 0, 0);

	//�����ģ
	long nI, nJ, nK;
	m_pReciveData->GetGridSize(nI, nJ, nK);

	time_t rawtime;
	time(&rawtime);

	struct tm* timeinfo;
	timeinfo = localtime(&rawtime);
	stringstream stream;
	stream << "��ʼʱ��" << timeinfo->tm_hour<<":"<<timeinfo->tm_min<<":"<<timeinfo->tm_sec;
	::OutputDebugString(stream.str().c_str());

	for (size_t timeNo = 0;timeNo < m_pReciveData->m_SimTimes.size();++timeNo)
	{
		curTime = m_pReciveData->m_SimTimes[timeNo];
		//����һ��ʱ�䲽��������
		CreateGridPropData(*m_pReciveData , curTime ,m_strPropName);

		//��������
		for (long kIndex = 0;kIndex < nK ;++kIndex)
		{
			for (long iIndex = 0;iIndex < nI ;++iIndex)
			{
				for (long jIndex = 0;jIndex < nJ ;++jIndex)
				{
					gridNo.noI = iIndex + 1;
					gridNo.noJ = jIndex + 1;
					gridNo.noK = kIndex + 1;

					if (!m_pReciveData->IsGridAct(gridNo))
					{
						//��Ч����ֱ�Ӹ���Чֵ
						continue;
					}

					gridNo.noI = iIndex;
					gridNo.noJ = jIndex;
					gridNo.noK = kIndex;

					//����Soil
					if (m_pReciveData->IsExistGridFunction("SGAS"))
					{
						sgasVal = sgasFunc.getValue(*m_pReciveData , curTime ,gridNo);
						swatVal = swatFunc.getValue(*m_pReciveData , curTime ,gridNo);

						if (sgasVal != UNACTVALUE && swatVal != UNACTVALUE )
						{
							soilFunc.setValue(*m_pReciveData ,curTime ,gridNo, 1.0 - sgasVal - swatVal);
						}
					}
					else
					{
						swatVal = swatFunc.getValue(*m_pReciveData , curTime ,gridNo);

						if (swatVal != UNACTVALUE )
						{
							soilFunc.setValue(*m_pReciveData ,curTime ,gridNo, 1.0 - swatVal);
						}
					}
				}
			}
		}

		CProgressControl::getSingletonPtr()->StepProgress(_T("��ǰ���ԣ�SOIL"));
	}

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	stream << "��ʼʱ��" << timeinfo->tm_hour<<":"<<timeinfo->tm_min<<":"<<timeinfo->tm_sec;
	::OutputDebugString(stream.str().c_str());
	

	//�����ʱ����
	soilFunc.clearData();
	if (m_pReciveData->IsExistGridFunction("SGAS"))
	{
		sgasFunc.clearData();
	}
	swatFunc.clearData();
	
	//������������ʾ
	CProgressControl::getSingletonPtr()->StepProgress(100 , _T("������ݼ��㣡"),_T("��ǰ���ԣ�SOIL") );

	return TRUE;
}

BOOL CGridPropUnitPo::OGIPdata()
{
	//��ʾ������
	CProgressControl::getSingletonPtr()->StepProgress(0 , _T("���ڼ������ݣ�"),_T("��ǰ���ԣ�OGIP") );
	///////////////////////////////////////////////////////////////////////////////////////////
	//����OGIP
	////OGIP = PORV*SGAS
	//�����Իص�����
	GridFunction ogipFunc = m_pReciveData->GetGridFunction(_T("OGIP"));
	GridFunction sgasFunc = m_pReciveData->GetGridFunction(_T("SGAS"));
	GridFunction porvFunc = m_pReciveData->GetGridFunction(_T("PORV"));
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	COleDateTime curTime;
	//Ҫ�õ��ı���������Ƶ������
	double porvVal = UNACTVALUE ;
	double sgasVal = UNACTVALUE ;
	GridNo gridNo(0  , 0 , 0 );
	// �����ģ
	long nI, nJ, nK;
	m_pReciveData->GetGridSize(nI, nJ, nK);

	for (size_t timeNo = 0;timeNo < m_pReciveData->m_SimTimes.size();++timeNo)
	{
		curTime = m_pReciveData->m_SimTimes[timeNo];
		//����һ��ʱ�䲽��������
		CreateGridPropData(*m_pReciveData , curTime , m_strPropName);
		//����
		for (long kIndex = 0;kIndex < nK ;++kIndex)
		{
			for (long iIndex = 0;iIndex < nI ;++iIndex)
			{
				for (long jIndex = 0;jIndex < nJ ;++jIndex)
				{
					gridNo.noI = iIndex + 1;
					gridNo.noJ = jIndex + 1;
					gridNo.noK = kIndex + 1;
					if (!m_pReciveData->IsGridAct(gridNo))
					{
						//��Ч����ֱ�Ӹ���Чֵ
						continue;
					}
					gridNo.noI = iIndex;
					gridNo.noJ = jIndex;
					gridNo.noK = kIndex;
					porvVal = porvFunc.getValue(*m_pReciveData , curTime ,gridNo) ;
					if ( porvVal != UNACTVALUE )
					{
						//OGIP = PORV*SGAS
						sgasVal = sgasFunc.getValue(*m_pReciveData , curTime ,gridNo) ;	
						if (sgasVal != UNACTVALUE )
						{
							ogipFunc.setValue(*m_pReciveData ,curTime ,gridNo, sgasVal * porvVal);	
						}
					}
				}
			}
		}
		CProgressControl::getSingletonPtr()->StepProgress(_T("��ǰ���ԣ�OGIP"));
	}
	//�����ʱ����
	porvFunc.clearData();
	sgasFunc.clearData();
	ogipFunc.clearData();
	//////////////////////////////////////////////////////////////////////////
	//������������ʾ
	CProgressControl::getSingletonPtr()->StepProgress(100 , _T("������ݼ��㣡"),_T("��ǰ���ԣ�OGIP") );
	return TRUE;
}

BOOL CGridPropUnitPo::OWIPdata()
{
	//��ʾ������
	CProgressControl::getSingletonPtr()->StepProgress(0 , _T("���ڼ������ݣ�"),_T("��ǰ���ԣ�OWIP") );
	///////////////////////////////////////////////////////////////////////////////////////////
	//����OWIP
	//OWIP = PORV*SWAT	
	//�����Իص�����
	GridFunction owipFunc = m_pReciveData->GetGridFunction(_T("OWIP"));
	GridFunction swatFunc = m_pReciveData->GetGridFunction(_T("SWAT"));
	GridFunction porvFunc = m_pReciveData->GetGridFunction(_T("PORV"));	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	COleDateTime curTime;
	//Ҫ�õ��ı���������Ƶ������
	double porvVal = UNACTVALUE ;
	double swatVal = UNACTVALUE ;
	GridNo gridNo(0  , 0 , 0 );
	// �����ģ
	long nI, nJ, nK;
	m_pReciveData->GetGridSize(nI, nJ, nK);

	for (size_t timeNo = 0;timeNo < m_pReciveData->m_SimTimes.size();++timeNo)
	{
		curTime = m_pReciveData->m_SimTimes[timeNo];
		//����һ��ʱ�䲽��������
		CreateGridPropData(*m_pReciveData , curTime ,m_strPropName);
		//����
		for (long kIndex = 0;kIndex < nK ;++kIndex)
		{
			for (long iIndex = 0;iIndex < nI ;++iIndex)
			{
				for (long jIndex = 0;jIndex < nJ ;++jIndex)
				{
					gridNo.noI = iIndex + 1;
					gridNo.noJ = jIndex + 1;
					gridNo.noK = kIndex + 1;
					if (!m_pReciveData->IsGridAct(gridNo))
					{
						//��Ч����ֱ�Ӹ���Чֵ
						continue;
					}
					gridNo.noI = iIndex;
					gridNo.noJ = jIndex;
					gridNo.noK = kIndex;
					porvVal = porvFunc.getValue(*m_pReciveData , curTime ,gridNo) ;
					if ( porvVal != UNACTVALUE )
					{
						//OWIP = PORV*SWAT
						//����OWIP
						swatVal = swatFunc.getValue(*m_pReciveData , curTime ,gridNo) ;
						if (swatVal != UNACTVALUE )
						{
							owipFunc.setValue(*m_pReciveData , curTime , gridNo , swatVal * porvVal);	
						}
					}
				}
			}
		}
		CProgressControl::getSingletonPtr()->StepProgress(_T("��ǰ���ԣ�OWIP"));
	}
	//�����ʱ����
	porvFunc.clearData();
	swatFunc.clearData();
	owipFunc.clearData();
	//////////////////////////////////////////////////////////////////////////
	//������������ʾ
	CProgressControl::getSingletonPtr()->StepProgress(100 , _T("������ݼ��㣡"),_T("��ǰ���ԣ�OWIP") );
	return TRUE;
}

BOOL CGridPropUnitPo::OOIPdata()
{
	//��ʾ������
	CProgressControl::getSingletonPtr()->StepProgress(0 , _T("���ڼ������ݣ�"),_T("��ǰ���ԣ�OOIP") );
	///////////////////////////////////////////////////////////////////////////////////////////
	//����OOIP
	//OOIP = PORV*SOIL
	//�����Իص�����
	GridFunction soilFunc = m_pReciveData->GetGridFunction(_T("SOIL"));
	GridFunction ooipFunc = m_pReciveData->GetGridFunction(_T("OOIP"));
	GridFunction porvFunc = m_pReciveData->GetGridFunction(_T("PORV"));
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	COleDateTime curTime;
	//Ҫ�õ��ı���������Ƶ������
	double porvVal = UNACTVALUE ;
	double soilVal = UNACTVALUE ;
	GridNo gridNo(0  , 0 , 0 );
	// �����ģ
	long nI, nJ, nK;
	m_pReciveData->GetGridSize(nI, nJ, nK);

	for (size_t timeNo = 0;timeNo < m_pReciveData->m_SimTimes.size();++timeNo)
	{
		curTime = m_pReciveData->m_SimTimes[timeNo];
		//����һ��ʱ�䲽��������
		CreateGridPropData(*m_pReciveData , curTime ,m_strPropName);
		//����
		for (long kIndex = 0;kIndex < nK ;++kIndex)
		{
			for (long iIndex = 0;iIndex < nI ;++iIndex)
			{
				for (long jIndex = 0;jIndex < nJ ;++jIndex)
				{
					gridNo.noI = iIndex + 1;
					gridNo.noJ = jIndex + 1;
					gridNo.noK = kIndex + 1;
					if (!m_pReciveData->IsGridAct(gridNo))
					{
						//��Ч����ֱ�Ӹ���Чֵ
						continue;
					}
					gridNo.noI = iIndex;
					gridNo.noJ = jIndex;
					gridNo.noK = kIndex;
					porvVal = porvFunc.getValue(*m_pReciveData , curTime ,gridNo) ;
					soilVal = soilFunc.getValue(*m_pReciveData , curTime ,gridNo) ;
					if ( porvVal != UNACTVALUE && soilVal != UNACTVALUE )
					{
						ooipFunc.setValue(*m_pReciveData ,curTime ,gridNo, soilVal * porvVal);
					}
				}
			}
		}
		CProgressControl::getSingletonPtr()->StepProgress(_T("��ǰ���ԣ�OOIP") );
	}
	//�����ʱ����
	porvFunc.clearData();
	soilFunc.clearData();
	ooipFunc.clearData();
	//////////////////////////////////////////////////////////////////////////
	//������������ʾ
	CProgressControl::getSingletonPtr()->StepProgress(100 , _T("������ݼ��㣡"),_T("��ǰ���ԣ�OOIP") );
	return TRUE;
}
BOOL CGridPropUnitPo::TSATdata()
{
	//������ͼ�� TSAT = a * SWAT + b * SOIL + c * SGAS a,b,cΪ�������
	//��ʾ������
	CProgressControl::getSingletonPtr()->StepProgress(0 , _T("���ڼ������ݣ�"),_T("��ǰ���ԣ�TSAT") );
	///////////////////////////////////////////////////////////////////////////////////////////
	//����TSAT
	// TSAT = a * SWAT + b * SOIL + c * SGAS
	//�����Իص�����
	GridFunction tsatFunc = m_pReciveData->GetGridFunction(_T("TSAT"));
	GridFunction soilFunc = m_pReciveData->GetGridFunction(_T("SOIL"));	
	GridFunction swatFunc = m_pReciveData->GetGridFunction(_T("SWAT"));
	GridFunction sgasFunc = m_pReciveData->GetGridFunction(_T("SGAS"));
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	COleDateTime curTime;
	//Ҫ�õ��ı���������Ƶ������
	double swatVal = UNACTVALUE ;
	double soilVal = UNACTVALUE ;
	double sgasVal = UNACTVALUE ;
	Structure::CALC_PARAMSOPTION options;
	InitOption(options);
	double a = options.m_TSATaValue;
	double b = options.m_TSATbValue;
	double c = options.m_TSATcValue;
	GridNo gridNo(0  , 0 , 0 );
	// �����ģ
	long nI, nJ, nK;
	m_pReciveData->GetGridSize(nI, nJ, nK);

	for (size_t timeNo = 0;timeNo < m_pReciveData->m_SimTimes.size();++timeNo)
	{
		curTime = m_pReciveData->m_SimTimes[timeNo];
		//����һ��ʱ�䲽��������
		CreateGridPropData(*m_pReciveData , curTime ,m_strPropName);
		//����
		for (long kIndex = 0;kIndex < nK ;++kIndex)
		{
			for (long iIndex = 0;iIndex < nI ;++iIndex)
			{
				for (long jIndex = 0;jIndex < nJ ;++jIndex)
				{
					gridNo.noI = iIndex + 1;
					gridNo.noJ = jIndex + 1;
					gridNo.noK = kIndex + 1;
					if (!m_pReciveData->IsGridAct(gridNo))
					{
						//��Ч����ֱ�Ӹ���Чֵ
						continue;
					}
					gridNo.noI = iIndex;
					gridNo.noJ = jIndex;
					gridNo.noK = kIndex;
					swatVal = swatFunc.getValue(*m_pReciveData , curTime ,gridNo) ;
					soilVal = soilFunc.getValue(*m_pReciveData , curTime ,gridNo) ;
					sgasVal = sgasFunc.getValue(*m_pReciveData , curTime ,gridNo) ;
					if ( swatVal != UNACTVALUE && soilVal != UNACTVALUE && sgasVal != UNACTVALUE)
					{
						tsatFunc.setValue(*m_pReciveData ,curTime ,gridNo, a * swatVal + b * soilVal + c * sgasVal);
					}
				}
			}
		}
		CProgressControl::getSingletonPtr()->StepProgress(_T("��ǰ���ԣ�TSAT"));
	}
	//�����ʱ����
	swatFunc.clearData();
	soilFunc.clearData();
	sgasFunc.clearData();
	tsatFunc.clearData();
	//////////////////////////////////////////////////////////////////////////
	//������������ʾ
	CProgressControl::getSingletonPtr()->StepProgress(100 , _T("������ݼ��㣡"),_T("��ǰ���ԣ�TSAT") );
	return TRUE;
}

BOOL CGridPropUnitPo::FIPOIL1data()
{
	//FIPOIL1 ��ʣ���ͷ�ȣ� FIPOIL1 = FIPOIL / ������� ��λΪ ���/ƽ������ 
	//�����Իص�����
	GridFunction fipoil1Func = m_pReciveData->GetGridFunction(_T("FIPOIL1"));
	GridFunction fipoilFunc = m_pReciveData->GetGridFunction(_T("FIPOIL"));
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//Ҫ�õ��ı���������Ƶ������
	double fipoiltVal = UNACTVALUE ;
	double gridArea = 0;
	//��ʾ������
	CProgressControl::getSingletonPtr()->StepProgress(0 , _T("���ڼ������ݣ�"),_T("��ǰ���ԣ�FIPOIL1") );
	///////////////////////////////////////////////////////////////////////////////////////////
	//����	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	COleDateTime curTime;
	GridNo gridNo(0  , 0 , 0 );
	// �����ģ
	long nI, nJ, nK;
	m_pReciveData->GetGridSize(nI, nJ, nK);

	for (size_t timeNo = 0;timeNo < m_pReciveData->m_SimTimes.size();++timeNo)
	{
		curTime = m_pReciveData->m_SimTimes[timeNo];
		//����һ��ʱ�䲽��������
		CreateGridPropData(*m_pReciveData , curTime ,m_strPropName);
		//����
		for (long kIndex = 0;kIndex < nK ;++kIndex)
		{
			for (long iIndex = 0;iIndex < nI ;++iIndex)
			{
				for (long jIndex = 0;jIndex < nJ ;++jIndex)
				{
					gridNo.noI = iIndex + 1;
					gridNo.noJ = jIndex + 1;
					gridNo.noK = kIndex + 1;
					if (!m_pReciveData->IsGridAct(gridNo))
					{
						//��Ч����ֱ�Ӹ���Чֵ
						continue;
					}
					gridArea = CProjectManger::getSingletonPtr()->GetActiveCase()->GetGridData().GetGridArea(gridNo);
					gridNo.noI = iIndex;
					gridNo.noJ = jIndex;
					gridNo.noK = kIndex;
					fipoiltVal = fipoilFunc.getValue(*m_pReciveData , curTime ,gridNo) ;
					if ( fipoiltVal != UNACTVALUE && gridArea != 0)
					{
						fipoil1Func.setValue(*m_pReciveData ,curTime ,gridNo, fipoiltVal / gridArea);
					}
				}
			}
		}
		CProgressControl::getSingletonPtr()->StepProgress(_T("��ǰ���ԣ�FIPOIL1"));
	}
	//�����ʱ����
	fipoil1Func.clearData();
	fipoilFunc.clearData();
	//////////////////////////////////////////////////////////////////////////
	//������������ʾ
	CProgressControl::getSingletonPtr()->StepProgress(100 , _T("������ݼ��㣡"),_T("��ǰ���ԣ�FIPOIL1") );
	return TRUE;
}

BOOL CGridPropUnitPo::FIPOIL2data()
{
	//FIPOIL2 (ʣ��ɶ��ʹ���) FIPOIL2 = FIPOIL * ( ( SOIL - SOR) / SOIL )   SOR Ϊ�������(ʣ���ͱ��Ͷ�)
	//�����Իص�����
	GridFunction fipoil2Func = m_pReciveData->GetGridFunction(_T("FIPOIL2"));
	GridFunction fipoilFunc = m_pReciveData->GetGridFunction(_T("FIPOIL"));
	GridFunction soilFunc = m_pReciveData->GetGridFunction(_T("SOIL"));
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//Ҫ�õ��ı���������Ƶ������
	double fipoilVal = UNACTVALUE ;
	double soilVal = UNACTVALUE ;
	Structure::CALC_PARAMSOPTION options;
	InitOption(options);
	double sor = options.m_SORValue;
	//��ʾ������
	CProgressControl::getSingletonPtr()->StepProgress(0 , _T("���ڼ������ݣ�"),_T("��ǰ���ԣ�FIPOIL2") );
	///////////////////////////////////////////////////////////////////////////////////////////
	//����	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	COleDateTime curTime;
	GridNo gridNo(0  , 0 , 0 );
	// �����ģ
	long nI, nJ, nK;
	m_pReciveData->GetGridSize(nI, nJ, nK);

	for (size_t timeNo = 0;timeNo < m_pReciveData->m_SimTimes.size();++timeNo)
	{
		curTime = m_pReciveData->m_SimTimes[timeNo];
		//����һ��ʱ�䲽��������
		CreateGridPropData(*m_pReciveData , curTime ,m_strPropName);
		//����
		for (long kIndex = 0;kIndex < nK ;++kIndex)
		{
			for (long iIndex = 0;iIndex < nI ;++iIndex)
			{
				for (long jIndex = 0;jIndex < nJ ;++jIndex)
				{
					gridNo.noI = iIndex + 1;
					gridNo.noJ = jIndex + 1;
					gridNo.noK = kIndex + 1;
					if (!m_pReciveData->IsGridAct(gridNo))
					{
						//��Ч����ֱ�Ӹ���Чֵ
						continue;
					}
					gridNo.noI = iIndex;
					gridNo.noJ = jIndex;
					gridNo.noK = kIndex;
					fipoilVal = fipoilFunc.getValue(*m_pReciveData , curTime ,gridNo) ;
					soilVal = soilFunc.getValue(*m_pReciveData , curTime ,gridNo) ;
					if (  fipoilVal != UNACTVALUE && soilVal != 0 && soilVal != UNACTVALUE)
					{
						fipoil2Func.setValue(*m_pReciveData ,curTime ,gridNo, fipoilVal * (soilVal - sor) / soilVal);
					}
				}
			}
		}
		CProgressControl::getSingletonPtr()->StepProgress(_T("��ǰ���ԣ�FIPOIL2"));
	}
	//�����ʱ����
	fipoil2Func.clearData();
	fipoilFunc.clearData();
	soilFunc.clearData();
	//////////////////////////////////////////////////////////////////////////
	//������������ʾ
	CProgressControl::getSingletonPtr()->StepProgress(100 , _T("������ݼ��㣡"),_T("��ǰ���ԣ�FIPOIL2") );
	return TRUE;
}

//����fw
BOOL CGridPropUnitPo::fwdata()
{
	//��ʾ������

	GridFunction fw_Func = m_pReciveData->GetGridFunction(_T("fw"));

	GridFunction WATKR_Func = m_pReciveData->GetGridFunction(_T("WATKR"));
	GridFunction WAT_VISC_Func = m_pReciveData->GetGridFunction(_T("WAT_VISC"));
	GridFunction OILKR_Func = m_pReciveData->GetGridFunction(_T("OILKR"));
	GridFunction OIL_VISC_Func = m_pReciveData->GetGridFunction(_T("OIL_VISC"));

	double WATKR = UNACTVALUE;    //ˮ�������͸��
	double WAT_VISC = UNACTVALUE; //ˮճ��
	double OILKR = UNACTVALUE;    //���������͸��
	double OIL_VISC = UNACTVALUE; //��ճ��

	COleDateTime curTime;
	GridNo gridNo(0, 0, 0);
	
	long nI, nJ, nK;
	m_pReciveData->GetGridSize(nI, nJ, nK);

	for (size_t timeNo = 0; timeNo < m_pReciveData->m_SimTimes.size(); timeNo++)
	{
		curTime = m_pReciveData->m_SimTimes[timeNo];
		CreateGridPropData(*m_pReciveData, curTime, m_strPropName);

		for (long kIndex = 0; kIndex < nK; kIndex++)
		{
			for (long iIndex = 0; iIndex < nI; iIndex++)
			{
				for (long jIndex = 0; jIndex < nJ; jIndex++)
				{
					gridNo.noI = iIndex + 1;
					gridNo.noJ = jIndex + 1;
					gridNo.noK = kIndex + 1;

					if (!m_pReciveData->IsGridAct(gridNo))
					{					
						continue; //��Ч����
					}

					gridNo.noI = iIndex;
					gridNo.noJ = jIndex;
					gridNo.noK = kIndex;

					WATKR = WATKR_Func.getValue(*m_pReciveData, curTime, gridNo);
					WAT_VISC = WAT_VISC_Func.getValue(*m_pReciveData, curTime, gridNo);
					OILKR = OILKR_Func.getValue(*m_pReciveData, curTime, gridNo);
					OIL_VISC = OIL_VISC_Func.getValue(*m_pReciveData, curTime, gridNo);

					if (WATKR == UNACTVALUE || WAT_VISC == UNACTVALUE
					 || OILKR == UNACTVALUE || OIL_VISC == UNACTVALUE)
					{
						continue;
					}

					double resVal = 0;
					if (WATKR < 1e-3 && OILKR < 1e-3) //����ʦ
					{
						resVal = 0;
					}
					else
					{
						resVal = 100 * (WATKR / WAT_VISC) / (WATKR / WAT_VISC + OILKR / OIL_VISC);
					}

					fw_Func.setValue(*m_pReciveData, curTime, gridNo, resVal);
				}
			}

			CProgressControl::getSingletonPtr()->StepProgress(_T("��ǰ���ԣ�fw"));
		}
	}

	fw_Func.clearData();

	WATKR_Func.clearData();
	WAT_VISC_Func.clearData();
	OILKR_Func.clearData();
	OIL_VISC_Func.clearData();	

	//������������ʾ
	CProgressControl::getSingletonPtr()->StepProgress(100 , _T("������ݼ��㣡"), _T("��ǰ���ԣ�fw") );
	return TRUE;
}

//��鵱ǰ�����Ƿ�Ҫ����
BOOL CGridPropUnitPo::CheckCurPropData()
{
	if ( m_bFile)
	{
		return TRUE;
	}
	if ( !m_dataOffsets.empty() && !m_strFiles.empty() )
	{
		return TRUE;
	}
	double resVal;
	COleDateTime timetemp;
	CheckAndCalcProp( resVal , GridNo(0,0,0), timetemp ,TRUE );
	return FALSE;
}

void CGridPropUnitPo::CopyObj( CGridPropUnitPo& propUnit  ,CGridRecive* pReciveData)
{
	//�Ƿ�Ҫ���¼��������Сֵ
	propUnit.m_bRecal = m_bRecal;
	//��ǰ��¼��������
	propUnit.m_strPropName = m_strPropName;
	//���������Сֵ
	propUnit.m_dMaxValue = m_dMaxValue;
	propUnit.m_dMinValue = m_dMinValue;
	//TRUE Ϊ����FALSEΪǰ����
	propUnit.m_dataType = m_dataType;
	propUnit.m_dataRealType = m_dataRealType;
	//��ǰ������
	propUnit.m_strCurStoreDataProp = m_strCurStoreDataProp;
	//��ǰ������
	propUnit.m_strCurStoreDataCase = m_strCurStoreDataCase;
	//���������ļ���������
	propUnit.m_lgrName = m_lgrName;
	propUnit.m_namedGridProps = m_namedGridProps;

	//////////////////////////////////////////////////////////////////////////
	//�Ƿ�ˢ���ļ�����
	propUnit.m_bFlush = m_bFlush;
	//�Ƿ���д���ļ�
	propUnit.m_bFile = m_bFile;
	//�Ƿ�������
	propUnit.m_bNewProp = m_bNewProp;
	//�Ƿ��ڶ�������
	propUnit.m_bReadNewProp = m_bReadNewProp;
	//�������ݵ���ʼƫ��
	propUnit.m_dataOffsets = m_dataOffsets;
	//�������������ļ���
	propUnit.m_strFiles = m_strFiles;
	//��������
	propUnit.m_pReciveData = pReciveData;
	//��������
	propUnit.m_GridProps = m_GridProps;
	//��Ŀ��
	propUnit.m_objName = m_objName;
	//��Ŀ·��
	propUnit.m_objPath = m_objPath;
	//����ʵ��ƫ��
	propUnit.m_realOffset = m_realOffset;
	propUnit.m_bTotalGridData = m_bTotalGridData;
}

void CGridPropUnitPo::CloseFileHandle()
{
	if (m_dateFile.m_hFile != INVALID_HANDLE_VALUE)
	{
		//�򿪹��ļ�
		m_dateFile.Close();
	}
	if (m_file.m_hFile != INVALID_HANDLE_VALUE)
	{
		m_file.Flush();
		m_file.Close();
	}
	m_bFileOpen = FALSE;
}

void CGridPropUnitPo::ReadProp(const COleDateTime& time)
{
	TimedDataOffset::iterator it_dataIf = m_dataOffsets.begin();
	//////////////////////////////////////////////////////////////////////////	
	std::vector<float> sourceData ;
	GridValues  allPropvalues;
	//����Ϊ���ͻ�ʵ��;  ����Ϊ����	bIntOrReal = TRUE
	BOOL bIntOrReal = FALSE;
	//for (int nDate = 0; it_dataIf != m_dataOffsets.end() ;++it_dataIf , ++nDate)
	//COleDateTime time = CProjectManger::getSingletonPtr()->GetActiveCase()->GetGridData().GetCurTime();
	it_dataIf = m_dataOffsets.find(time);
	if (it_dataIf != m_dataOffsets.end())
	{
		//���ļ������������ļ��е���ʼλ����Ϣ����ȡ����
		//�����ݿ�COPY��vector			
		ReadPropData( m_strFiles[it_dataIf->first] ,  sourceData ,	it_dataIf->second , bIntOrReal);
		//ת������
		if (bIntOrReal)
		{
			DataIntread(sourceData,allPropvalues);
		}
		else
		{
			DataRealread(sourceData,allPropvalues);
		}
		//�����ʱ����
		sourceData.clear();
		//���һ��ʱ�䲽����
		m_bReadNewProp = TRUE;
		CreateGridPropData(*m_pReciveData , it_dataIf->first  ,m_strPropName);
		//��������
		SetTimePropDatas(*m_pReciveData , allPropvalues , it_dataIf->first );
		m_bReadNewProp = FALSE;
		//////////////////////////////////////////////////////////////////////////
	}
}

///////////////////////////////////////////////////////////
CString& CGridPropUnitPo::get_m_strCurStoreDataCase()
{
	return m_strCurStoreDataCase;
}

CString& CGridPropUnitPo::get_m_strCurStoreDataProp()
{
	return m_strCurStoreDataProp;
}

TimedGridProp& CGridPropUnitPo::get_m_GridProps()
{
	return m_GridProps;
}

std::map<long, long>& CGridPropUnitPo::get_m_realOffset()
{
	return m_realOffset;
}

std::map<long, long>& CGridPropUnitPo::get_m_totalOffset()
{
	return m_totalOffset;
}

BOOL& CGridPropUnitPo::get_m_bCalcState()
{
	return m_bCalcState;
}

BOOL& CGridPropUnitPo::get_m_bCalcAllProp()
{
	return m_bCalcAllProp;
}
///////////////////////////////////////////////////////////

/************************************************************************/
/* ����HiSimģ�����ݻص���ʽ�����ݶ�ȡ��ʽ                                */
/************************************************************************/

void CGridPropUnitPo::BindHSGridFunction( CGridRecive& gridRev )
{
	//�󶨻ص�����
	GridFunction gridFun;
	gridFun.createGridPropData = boost::bind(&CGridPropUnitPo::CreateHSGridPropData, this , _1,_2,_3);
	gridFun.getKMinMaxValue = boost::bind(&CGridPropUnitPo::GetHSKMinMaxValue, this , _1,_2,_3,_4,_5);
	gridFun.setValue = boost::bind(&CGridPropUnitPo::ModifyHSGridPropData, this , _1,_2,_3,_4);
	gridFun.getValue = boost::bind(&CGridPropUnitPo::GetHSPropValue, this , _1,_2,_3);
	gridFun.getMinMax = boost::bind(&CGridPropUnitPo::GetHSMinMaxValue, this , _1,_2);
	gridFun.clearData = boost::bind(&CGridPropUnitPo::ClearHSData, this );
	gridFun.getDataType = boost::bind(&CGridPropUnitPo::GetHSDataType, this );
	gridFun.isExistTime = boost::bind(&CGridPropUnitPo::IsExistHSTime, this ,_1);
	gridFun.checkCurPropData = boost::bind(&CGridPropUnitPo::CheckHSCurPropData, this );
//	gridFun.copyGridPropUnit = boost::bind(&CGridPropUnitPo::CopyObj, this , _1,_2);
	gridFun.closeFileHandle = boost::bind(&CGridPropUnitPo::CloseHSFileHandle, this );
	gridRev.SetGridFunction(m_strPropName , gridFun);
	//��������
	m_pReciveData = &gridRev;
	//���ɵ��ļ���
	//�ļ�������Ŀ��.������
	CString fileName;
	//�ļ���
	fileName.Format("%s\\%s.%s" , m_objPath , m_objName , m_strPropName);	
	//���ļ�
	if ( m_bFile )
	{
		// ���ļ��Ѵ����ȹر��ļ�
		if (m_bFileOpen)
		{
			m_file.Close();
		}

		//���ļ�
		if (m_file.Open(fileName , CFile::modeReadWrite | CFile::typeBinary ))
		{
			m_bFileOpen = TRUE;
		}
		else
		{
			//��ʧ��
			AfxMessageBox(fileName + "��ʧ�ܣ������¼���");
			m_bFile = FALSE;
			m_strFiles.clear();
			m_dataOffsets.clear();
		}
	}
}

void CGridPropUnitPo::CreateHSGridPropData( const CGridRecive& gridRev,const COleDateTime& time,
										   const CString& strPropName )
{
	if (m_strPropName.IsEmpty())
	{
		m_strPropName = strPropName;
	}
	ASSERT(!m_strPropName.IsEmpty());
	ASSERT(strPropName == m_strPropName);	
	//ֱ�Ӹ��������������ڴ�
	long lISize = 0;
	long lJSize = 0;
	long lKSize = 0;
	gridRev.GetGridSize(lISize ,lJSize ,lKSize);
	ASSERT(lISize * lJSize * lKSize != 0);

	if ( m_strCurStoreDataProp != m_strPropName )
	{
		//ֻ����ʱȡ������,����m_namedGridProps,��д���ļ�
		//ȷ��δ��ȡ����ʱ��
		ASSERT(m_namedGridProps.find(time) == m_namedGridProps.end());
		////����������С��
		//m_namedGridProps[time].resize(lISize * lJSize * lKSize,UNACTVALUE);
	}
	else
	{
		//ȷ��δ��ȡ����ʱ��
		ASSERT(m_GridProps.find(time) == m_GridProps.end());
		////����������С��
		//m_GridProps[time].resize(lISize * lJSize * lKSize,UNACTVALUE);
	}	
	if (m_dataOffsets.empty())
	{
		//�½�������
		m_bNewProp = TRUE;
	}
	if (m_bNewProp && !m_bReadNewProp )
	{
		//�½����ԣ��Ҳ��Ƕ�����ʱ����
		//�����½����Ե��ļ���Ϣ
		m_dataOffsets[time] = 0;
		m_strFiles[time] = _T("");
		WriteData();
	}
}

//�޸���������
void CGridPropUnitPo::ModifyHSGridPropData( CGridRecive& gridRev,const COleDateTime& time,
										   const GridNo& gridNo,const double& dValue )									  
{
	ASSERT(!m_strPropName.IsEmpty());	

	//��������Ƿ�Ҫ����
	double resVal;
	CheckAndCalcProp(resVal , gridNo , time ,TRUE);
	//��ȡ������
	long ISize = 0;
	long JSize = 0;
	long KSize = 0;
	gridRev.GetGridSize(ISize , JSize , KSize);
	//������������
	long gridIndex = gridNo.noK * JSize  * ISize  + gridNo.noJ * ISize + gridNo.noI;
	//����ָ�����������ֵ	
	COleDateTime  curtime = time;
	if (m_dataOffsets.find(time) == m_dataOffsets.end())
	{
		TimedDataOffset::iterator propIter = m_dataOffsets.end();
		--propIter;
		//ʱ����Ϊ���һ��ʱ��
		curtime = propIter->first;
	}

	if (!m_bTotalGridData)
	{
		gridIndex = gridRev.GetGridValueIndex(gridIndex);
	}

	if (gridIndex == -1) //��Ч����
	{
		return;
	}

	//�޸��ļ��е�����
	ModifyGridPropData( curtime, gridIndex, dValue );

	if ( m_strCurStoreDataProp != m_strPropName )
	{
		//ֻ����ʱ�޸ĵ�����,ֱ��д�ļ�
		if (m_bCalcState)
		{
			////����ʱ�޸�
			//if (m_namedGridProps.empty())
			//{
			//	ReadData();
			//}
			if (m_namedGridProps[curtime].size() <= gridIndex)
			{
				m_namedGridProps[curtime].resize(gridIndex+1, UNACTVALUE);
			}
			m_namedGridProps[curtime][gridIndex] = dValue; 
		}
		return;
	}

	//�޸��ڴ��е�����
	ASSERT(m_GridProps.find(curtime) != m_GridProps.end());
	if(m_GridProps[curtime].size() == 0)
	{
		m_GridProps[curtime].resize(ISize * JSize * KSize, UNACTVALUE);
	}

	m_GridProps[curtime][gridIndex] = dValue;

	//����Ҫ���¼������������Сֵ
	m_bRecal = TRUE;
}

double CGridPropUnitPo::GetHSPropValue( const CGridRecive& gridRev,const COleDateTime& time,const GridNo& gridNo )
{
	//��ѯ��������ʱ���Ȳ�ѯ����map�Ƿ�Ϊ��
	//���Ϊ�գ��ٲ�ѯ��������Ӧ���ļ���Ϣ�Ƿ�Ϊ��
	//���Ϊ��������������������ļ�
	//��ѯ������������
	double dbRes = UNACTVALUE;
	if (!m_bCalcState)
	{
		//���Ǽ���ʱȡֵ���ж��Ƿ���Ч����
		//����ʱ��ȡֵǰ���ж�
		if (!m_pReciveData->IsGridAct(GridNo(gridNo.noI+1 , gridNo.noJ + 1 ,gridNo.noK + 1)))
		{
			//��Ч����
			return dbRes;
		}
	}

	//����ֵʱ��	
	COleDateTime  curtime = time;

	COleDateTime originTime = static_cast<CDataEclipse*>(CProjectManger::getSingletonPtr()->GetActiveCase())->GetStartDate();

	/*std::vector<COleDateTime> allTimes = gridRev.GetAllTimes();
	COleDateTime originTime = allTimes[0];*/
	COleDateTime currentTime = curtime - originTime;
	//��������Ƿ�Ҫ����
	/*if (CheckAndCalcProp(dbRes , gridNo , curtime , m_bCalcAllProp))
	{
	return dbRes;
	}*/

	//������
	long ISize = 0;
	long JSize = 0;
	long KSize = 0;

	//��ȡ������
	gridRev.GetGridSize(ISize ,JSize ,KSize);

	//����ֵ���� ע����long long
	long long gridIndex = gridNo.noK * JSize  * ISize  + gridNo.noJ * ISize + gridNo.noI;

	/*if ( m_strCurStoreDataProp != m_strPropName )
	{*/
		//if (m_bCalcState)
		//{
		//	//����ʱȡֵ
		//	return GetCalcPropValue( curtime, gridIndex , TRUE ); 
		//}

		//ֻ����ʱȡ������,����m_namedGridProps,��д���ļ�
		//��ԭ�ļ���ȡ����
		if (curtime != m_pretime)
		{
			m_pretime = curtime;
		}
		KWMapper maper;
		CString propName = maper.getItem(m_strPropName);


		double propResult;
		bool getResult;
		PropTypes propType;
		HiSimHandle* hsHandle = HiSimHandle::Instance();

		if(propType.GetPropType(m_strPropName) == 0){
			//std::vector<double> propVec;
            propResult = hsHandle->getListAt<double>((LPSTR)(LPCTSTR)propName,gridIndex,&getResult);
				//propResult = propVec.at(gridIndex);
				//getResult = true;
			//}
		}
		else if(propType.GetPropType(m_strPropName) == 1){
			propResult = hsHandle->getlistAtTime<double>((LPSTR)(LPCTSTR)propName,gridIndex,currentTime.m_dt,&getResult);
		}
		return getResult ? propResult : dbRes;
	//}
	//if (m_bCalcState)
	//{
	//	//����ʱȡֵ
	//	return GetCalcPropValue( curtime, gridIndex , FALSE ); 
	//}

	////����д���ļ�
	//FlushFile();
	////��ȡָ����������ֵ�����ʱ����ֵ���򷵻����һ��ʱ���ֵ
	//return GetCalcPropValue( curtime, gridIndex , FALSE ); 
}

double CGridPropUnitPo::GetHSPropValue( COleDateTime curtime, long gridIndex )
{
	double dbRes = UNACTVALUE;
	////�����ļ��е�����
	////ȡ����
	//ASSERT(m_dataOffsets.find(curtime) != m_dataOffsets.end());
	////�����ļ�ָ�뵽����λ��
	//m_file.Seek(8 * (gridIndex + 1) + m_dataOffsets[curtime] , CFile::begin); //���ݺ�
	//m_file.Read( &dbRes , 8);
	return dbRes;
}

void CGridPropUnitPo::GetHSMinMaxValue( double& dMaxValue,double& dMinValue )
{
	if (m_strCurStoreDataProp != m_strPropName || m_strCurStoreDataCase != GetDataCaseName())
	{
		//�����л���
		m_GridProps.clear();
		//���õ�ǰ��ʾ��������
		m_strCurStoreDataProp = m_strPropName;
		m_strCurStoreDataCase = GetDataCaseName();
	}

	KWMapper kwmaper;
	CString propName = kwmaper.getItem(m_strCurStoreDataProp);
    PropTypes propType;
    HiSimHandle* hsHandle = HiSimHandle::Instance();
    bool success = false;
    if(propType.GetPropType(m_strPropName) == 0){
        hsHandle->getListRange<double>((LPSTR)(LPCTSTR)propName,&dMinValue,&dMaxValue,&success);
    }
    else if(propType.GetPropType(m_strPropName) == 1){
        hsHandle->getListSequenceRange<double>((LPSTR)(LPCTSTR)propName,&dMinValue,&dMaxValue,&success);
    }
	
}

void CGridPropUnitPo::ClearHSData()
{
	//�����ʱ����
	m_namedGridProps.clear();
}

BOOL CGridPropUnitPo::GetHSKMinMaxValue(CGridRecive& gridRecive , const COleDateTime& time,long layer,double& dMaxValue,double& dMinValue)
{
	//���õ�ǰ��ʾ��������
	m_strCurStoreDataProp = m_strPropName;

	long ISize = 0;
	long JSize = 0;
	long KSize = 0;
	gridRecive.GetGridSize(ISize ,JSize ,KSize);

	//��ȡ��ǰʱ�䵱ǰ�����������Сֵ
	BOOL bInit = FALSE;
	long nSkip = layer * JSize * ISize;
	long surSize = JSize * ISize;

	double curVal = UNACTVALUE;
	for (long nIndex = 0; nIndex < surSize; ++nIndex)
	{
		int gridnoI;
		int gridnoJ;
		if ((nIndex + 1) % ISize == 0)
		{
			gridnoI = ISize;
			gridnoJ = (nIndex + 1) / ISize;
		}
		else
		{
			gridnoI = (nIndex + 1) % ISize;
			gridnoJ = (nIndex + 1) / ISize + 1;
		}

		GridNo gridNo(gridnoI, gridnoJ, layer + 1);
		if (gridRecive.IsGridAct(gridNo) == false) //��Ч����
		{
			continue;
		}

		int newIndex;
		if (!m_bTotalGridData)
		{
			//���nSkip + nIndex=496, ǰ����4����Ч����
			newIndex = gridRecive.GetGridValueIndex(nSkip + nIndex); //ִ������һ���newIndex=492
		}
		else
		{
			newIndex = nSkip + nIndex;
		}

		if (m_GridProps.size() == 1)
		{
			//���ھ�̬����DZNET, �л�ʱ���ʱ��, m_GridProps����ʼ��ֻ��һ��ʱ�������
			curVal = m_GridProps.begin()->second[newIndex];
		}
		else
		{
			curVal = m_GridProps[time][newIndex];
		}

		if (curVal != UNACTVALUE)
		{
			if (!bInit)
			{
				//δ��ʼ�����ʼ��
				dMaxValue = dMinValue = curVal;
				bInit = TRUE;
			}
			else
			{
				dMaxValue = max(dMaxValue , curVal);
				dMinValue = min(dMinValue , curVal);
			}
		}
	}

	return TRUE;
}
BOOL CGridPropUnitPo::IsExistHSTime(const COleDateTime& time )
{
	if (m_dataOffsets.find( time ) == m_dataOffsets.end())
	{
		//��ʱ��û������
		if (m_bCalcState == TRUE)
		{
			double dbRes;
			CheckAndCalcProp(dbRes , GridNo(0 , 0 , 0) , time , TRUE);
		}
		if (m_dataOffsets.find( time ) == m_dataOffsets.end())
		{
			return FALSE;
		}
	}
	return TRUE;
}

//��鵱ǰ�����Ƿ�Ҫ����
BOOL CGridPropUnitPo::CheckHSCurPropData()
{
	/*if ( m_bFile)
	{
	return TRUE;
	}
	if ( !m_dataOffsets.empty() && !m_strFiles.empty() )
	{
	return TRUE;
	}
	double resVal;
	COleDateTime timetemp;
	CheckAndCalcProp( resVal , GridNo(0,0,0), timetemp ,TRUE )*/;
	return FALSE;
}


void CGridPropUnitPo::CloseHSFileHandle()
{
	if (m_dateFile.m_hFile != INVALID_HANDLE_VALUE)
	{
		//�򿪹��ļ�
		m_dateFile.Close();
	}
	if (m_file.m_hFile != INVALID_HANDLE_VALUE)
	{
		m_file.Flush();
		m_file.Close();
	}
	m_bFileOpen = FALSE;
}