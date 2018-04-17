/********************************************************************
��������:	2008/10/15
�ļ�·��:	\CommonData\Data
�� �� ��:	GridPropUnit
�ļ���׺:	h
��    ��:	iuhiao	
˵��:	�������ݹ�����
*********************************************************************/
#pragma once

#include "GridPropUnit.h"
#include "..\Sim3DChart\Sim2D3DFlownLineStruct.h"
#include <boost\function.hpp>
class AFX_EXT_CLASS CGridPropUnitPo :
	public CGridPropUnit
{
	friend class CGridReciveEclipse;
	friend class CDataPoFloatTableValue;
public:
	CGridPropUnitPo( const CString& strPropName);
	CGridPropUnitPo(void);
	virtual ~CGridPropUnitPo(void);

public:
	//�ر��ļ�
	void CloseFileHandle();

	//��������
	void CopyObj(CGridPropUnitPo& propUnit ,CGridRecive* pReciveData);

	//ȡ����������TRUE Ϊ����(��ʱȡ����)��FALSEΪǰ����(������m_namedGridProps��)
	BOOL GetDataType() {return m_dataType;}; 

	//��鵱ǰ�����Ƿ�Ҫ����
	BOOL CheckCurPropData();

	//�������
	void ClearData();

	//����������������,������½���������д�ļ�
	void CreateGridPropData(const CGridRecive& gridRev,const COleDateTime& time,const CString& strPropName);

	//������������
	void AddGridPropData(const CGridRecive& gridRev,const COleDateTime& time,const GridNo& gridNo,const double& dValue);

	//�޸���������
	void ModifyGridPropData(CGridRecive& gridRev,const COleDateTime& time,const GridNo& gridNo,const double& dValue);

	//��ȡָ��ʱ���¶�Ӧ�������Ե�ֵ
	double GetPropValue(const CGridRecive& gridRev,const COleDateTime& time,const GridNo& gridNo);

	//��ȡָ��ʱ����������ֵ
	std::vector<double> getPropValues(const COleDateTime&,const std::vector<GridNo>&);

	//��ȡʵ����������
	void getGridIndexOffset();

	// ����:	��������ʱ�������Сֵ
	void ReCalcPropMaxmin();

	//��������ú���
	void BindGridFunction(CGridRecive& gridRev/* , int nDataType = 0*/);

	//��ȡ��ǰ���������Сֵ
	void GetMinMaxValue(double& dMaxValue,double& dMinValue);

	//��ȡ��ǰʱ�䵱ǰ�����������Сֵ
	BOOL GetKMinMaxValue(CGridRecive& gridRecive , const COleDateTime& time,long layer,	double& dMaxValue,double& dMinValue);

	//������������
	void SetTimePropDatas(CGridRecive& gridRecive ,GridValues& allPropvalues ,const COleDateTime& time);

	//�жϸ�ʱ�䲽�Ƿ��Ѷ�,�������ļ�ʱҪ�õ�
	BOOL IsExistTime(const COleDateTime& time);

	//����������Ϣ
	void SetDataInfo(CString strPropName , CGridRecive* gridRecive ,CString strFile,const COleDateTime& curTime ,__int64 dataOffset,__int64 dataCount);

	/************************************************************************/
	/* HiSim ģ������   ����������Ϣ                                          */
	/************************************************************************/
	void SetDataInfo(CString strPropName,CGridRecive* gridRecive ,const COleDateTime& curTime);

	//�������ݵĻص�����
	BOOL DZNETdata();
	BOOL PORVdata();
	BOOL SOILdata();
	BOOL OGIPdata();
	BOOL OWIPdata();
	BOOL OOIPdata();
	BOOL TSATdata();
	BOOL FIPOIL1data();
	BOOL FIPOIL2data();
	BOOL fwdata();

	// ���õ�ǰ���Լ�¼�����������Ƿ������Ч��������
	void SetTotalGridData(bool bGridTotalData) 
	{ 
		m_bTotalGridData = bGridTotalData; 
	}

public:
	/************************************************************************/
	/* ����HiSimģ�����ݻص������Ͷ�ȡ���ݷ�ʽ                                */
	/************************************************************************/
	void BindHSGridFunction(CGridRecive& gridRev);
	BOOL GetHSDataType() {return m_dataType;};
	void CGridPropUnitPo::CreateHSGridPropData( const CGridRecive& gridRev,const COleDateTime& time,
		const CString& strPropName );

	//�޸���������
	void CGridPropUnitPo::ModifyHSGridPropData( CGridRecive& gridRev,const COleDateTime& time,
		const GridNo& gridNo,const double& dValue );
	double CGridPropUnitPo::GetHSPropValue( const CGridRecive& gridRev,const COleDateTime& time,const GridNo& gridNo );

	double CGridPropUnitPo::GetHSPropValue( COleDateTime curtime, long gridIndex );

	void CGridPropUnitPo::GetHSMinMaxValue( double& dMaxValue,double& dMinValue );

	void CGridPropUnitPo::ClearHSData();

	//����:	��ȡ��ǰʱ�䵱ǰ�����������Сֵ
	BOOL CGridPropUnitPo::GetHSKMinMaxValue(CGridRecive& gridRecive , const COleDateTime& time,long layer,double& dMaxValue,double& dMinValue);
	BOOL CGridPropUnitPo::IsExistHSTime(const COleDateTime& time );

	//��鵱ǰ�����Ƿ�Ҫ����
	BOOL CGridPropUnitPo::CheckHSCurPropData();
	void CGridPropUnitPo::CloseHSFileHandle();
protected:
	//��ȡ����
	virtual void ReadProp(const COleDateTime& time);

	// ��ȡ��ǰ���Լ�¼������������ʱ���ļ��е�ƫ����
	long GetTotalGridValueOffset(long lGridIndex);
private:
	//��ʼ����ز���
	BOOL InitOption(Structure::CALC_PARAMSOPTION& options);
	//���ļ������������ļ��е���ʼλ����Ϣ����ȡ����
	void ReadData(const COleDateTime& time);

	//������д���ļ�
	void WriteData();

	//�޸��ļ��е�����
	void ModifyGridPropData(COleDateTime curtime, long gridIndex, const double& dValue);


	//��ȡʵ����������
	void CGridPropUnitPo::GetRealOffset( );


	//����OOIP
	void CalcData( boost::function<BOOL ()> readFunc );

protected:
	//���ļ���ȡ��������ֵ
	double GetPropValue(COleDateTime curtime, long gridIndex);

	//����ʱȡֵ
	double GetCalcPropValue(COleDateTime curtime, long gridIndex , BOOL btemp);

	//����Ƿ������ݣ�û�����������
	BOOL CheckAndCalcProp(double& resVal , GridNo gridNo, COleDateTime curTime ,BOOL bAllCalc = FALSE);

	//�ļ�����д�뵽�ļ�
	void FlushFile();

	//����Ӧ�ļ�
	BOOL MakeFileOpen(CString fileName);

protected:
	//�Ƿ�ˢ���ļ�����
	BOOL m_bFlush;
	//�Ƿ�������
	BOOL m_bNewProp;
	//�Ƿ��ڶ�������
	BOOL m_bReadNewProp;
	//��������
	CGridRecive* m_pReciveData;
	//����д����ļ�
	CFile m_file;
	//���������ļ�
	CFile m_dateFile;
	//m_dateFile����Ӧ��ʱ��
	COleDateTime  m_pretime;
	//////////////////////////////////////////////////////////////////////////
	//����CGridPropUnitPo
	//////////////////////////////////////////////////////////////////////////
	//�������ݵ���ʼƫ��
	typedef std::map<COleDateTime, __int64> TimedDataOffset;
	TimedDataOffset m_dataOffsets;
	//�������������ļ���
	std::map<COleDateTime , CString> m_strFiles;
	//��Ŀ��
	CString m_objName;
	//��Ŀ·��
	CString m_objPath;
	//�Ƿ���д���ļ�
	BOOL m_bFile;
	BOOL m_bFileOpen;

	// ��ǰ���������Ƿ��¼������������ֵ
	bool m_bTotalGridData;

protected:

	// ��ǰ���ݼ���¼�����������ķ���
	static CString m_strCurStoreDataCase;

	// ��ǰ���ݼ���¼������
	static CString m_strCurStoreDataProp;

	// ע��m_GridProps��static
	// ע���������һ��m_namedGridProps
	// ��ǰ���ݼ���¼����������
	static TimedGridProp m_GridProps;

	// ��ǰʱ�����ݵ�����ʵ��ƫ��
	static std::map<long, long> m_realOffset;

	// ��ǰʱ�����ݵ�����ʵ������
	static std::map<long,long> m_realGridIndexOffset;

	// ��¼������������ʱ��������ƫ����
	static std::map<long, long>	m_totalOffset;

	// �Ƿ�Ϊ��������
	static BOOL m_bCalcState;

	//�Ƿ����ȫ������
	static BOOL m_bCalcAllProp;

public:
	static CString& get_m_strCurStoreDataCase();
	static CString& get_m_strCurStoreDataProp();
	static TimedGridProp& get_m_GridProps();
	static std::map<long, long>& get_m_realOffset();
	static std::map<long, long>& get_m_totalOffset();
	static BOOL& get_m_bCalcState();
	static BOOL& get_m_bCalcAllProp();

private:
	//���л�����
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		//ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(CGridPropUnitPo);
		////����CGridPropUnitPo
		//ar & BOOST_SERIALIZATION_NVP(m_dataOffsets);
		//ar & BOOST_SERIALIZATION_NVP(m_strFiles);
		//ar & BOOST_SERIALIZATION_NVP(m_objName);
		//ar & BOOST_SERIALIZATION_NVP(m_objPath);
		//ar & BOOST_SERIALIZATION_NVP(m_bFile);
	}
};
