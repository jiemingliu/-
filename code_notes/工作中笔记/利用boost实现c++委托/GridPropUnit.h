/********************************************************************
��������:	2008/10/15
�ļ�·��:	\CommonData\Data
�� �� ��:	GridPropUnitBase
�ļ���׺:	h
��    ��:	iuhiao	
˵��:	���ݹ�����Ļ���
*********************************************************************/
#pragma once
#include "GridStruct.h"
#include <boost/bind.hpp>
class CGridRecive;


class AFX_EXT_CLASS CGridPropUnit
{
public:
	CGridPropUnit( const CString& strPropName);
	CGridPropUnit(void);
	virtual  ~CGridPropUnit(void);

public:
	/**
	 * ����:	��鵱ǰ������ȷ��
	 * ȫ��:	CGridPropUnit::CheckData
	 * ����:	virtual public 
	 * 
	 * @date	2009/01/14
	 * @author	flf
	 * @param	long dataSize
	 * @return	BOOL
	 */
	virtual BOOL CheckData(long dataSize);
	/**
	* ����:	�������
	* ȫ��:	CGridPropUnit::ClearData
	* ����:	public 
	* 
	* @date	2008/08/21
	* @author	XX
	* @return	void
	*/
	virtual void ClearData() = 0;

	/**
	* ����:	����������������
	* ȫ��:	CGridPropUnit::CreateGridPropData
	* ����:	public 
	* 
	* @date	2008/08/18
	* @author	XX
	* @param	const CGridRecive & gridRev
	* @param	const COleDateTime & time
	* @param	const CString & strPropName
	* @return	void
	*/
	virtual void CreateGridPropData(const CGridRecive& gridRev,const COleDateTime& time,
		const CString& strPropName) = 0;

	/**
	* ����:	������������
	* ȫ��:	CGridPropUnit::AddGridPropData
	* ����:	public 
	* 
	* @date	2008/08/18
	* @author	XX
	* @param	const CGridRecive & gridRev
	* @param	const COleDateTime & time
	* @param	const GridNo & gridNo
	* @param	const double & dValue
	* @return	void
	*/
	virtual void AddGridPropData(const CGridRecive& gridRev,const COleDateTime& time,
		const GridNo& gridNo,const double& dValue) = 0;

	/**
	* ����:	�޸���������
	* ȫ��:	CGridPropUnit::ModifyGridPropData
	* ����:	public 
	* 
	* @date	2008/08/18
	* @author	XX
	* @param	const CGridRecive & gridRev
	* @param	const COleDateTime & time
	* @param	const GridNo & gridNo
	* @param	const double & dValue
	* @return	void
	*/
	virtual void ModifyGridPropData(CGridRecive& gridRev,const COleDateTime& time,
		const GridNo& gridNo,const double& dValue) = 0;

	/**
	* ����:	��ȡָ��ʱ���¶�Ӧ�������Ե�ֵ
	* ȫ��:	CGridPropUnit::GetPropValue
	* ����:	public 
	* 
	* @date	2008/08/18
	* @author	XX
	* @param	const CGridRecive & gridRev
	* @param	const COleDateTime & time
	* @param	const GridNo & gridNo
	* @return	double
	*/
	virtual double GetPropValue(const CGridRecive& gridRev,const COleDateTime& time,const GridNo& gridNo) = 0;

	/**
	* ����:	��������ʱ�������Сֵ
	* ȫ��:	CGridPropUnit::ReCalcPropMaxmin
	* ����:	public 
	* 
	* @���� 	2008/08/18
	* @����  iuhiao
	* @�������� 	void
	*/
	virtual void ReCalcPropMaxmin() = 0;

	/**
	* ����:	��������ú���
	* ȫ��:	CGridPropUnit::BindGridFunction
	* ����:	public 
	* 
	* @date	2008/08/18
	* @author	XX
	* @param	CGridRecive & gridRev
	* @return	void
	*/
	virtual void BindGridFunction(CGridRecive& gridRev /*, int nDataType = 0*/) = 0;

	/**
	* ����:	��ȡ��ǰ���������Сֵ
	* ȫ��:	CDataPoFloatTableValue::GetMinMaxValue
	* ����:	public 
	* 
	* @���� 	2008/08/12
	* @����  iuhiao
	* @���� 	double & dMaxValue
	* @���� 	double & dMinValue
	* @�������� 	void
	*/
	virtual void GetMinMaxValue(double& dMaxValue,double& dMinValue) = 0;

	/**
	* ����:	��ȡ��ǰʱ�䵱ǰ�����������Сֵ
	* ȫ��:	CGridPropUnit::GetKMinMaxValue
	* ����:	virtual public 
	* 
	* @���� 	2008/10/15
	* @����  iuhiao
	* @���� 	CGridRecive & gridRecive
	* @���� 	const COleDateTime & time
	* @���� 	long layer
	* @���� 	double & dMaxValue
	* @���� 	double & dMinValue
	* @�������� 	BOOL
	*/
	virtual BOOL GetKMinMaxValue(CGridRecive& gridRecive , const COleDateTime& time,long layer,
		double& dMaxValue,double& dMinValue) = 0;

	/**
	* ����:	������������
	* ȫ��:	CGridPropUnit::SetTimePropDatas
	* ����:	public 
	* 
	* @���� 	2008/08/18
	* @����  iuhiao
	* @���� 	CGridRecive & gridRecive
	* @���� 	GridValues & allPropvalues
	* @���� 	COleDateTime & time
	* @�������� 	void
	*/
	virtual void SetTimePropDatas(CGridRecive& gridRecive ,GridValues& allPropvalues ,const COleDateTime& time) = 0;

	/**
	* ����:	�жϸ�ʱ�䲽�Ƿ��Ѷ�,�������ļ�ʱҪ�õ�
	* ȫ��:	CGridPropUnit::IsExistTime
	* ����:	public 
	* 
	* @���� 	2008/08/24
	* @����  iuhiao
	* @���� 	COleDateTime & time
	* @�������� 	BOOL  /TRUE����
	*/
	virtual BOOL IsExistTime(const COleDateTime& time) = 0;

	/**
	* ����:	��鵱ǰ�����Ƿ�Ҫ����
	* ȫ��:	CGridPropUnit::CheckCurPropData
	* ����:	public 
	* @���� 	2008-12-22
	* @����  iuhiao
	* @�������� 	BOOL
	*/
	virtual BOOL CheckCurPropData() = 0;

	/**
	 * ����:	�������������ļ���������
	 * ȫ��:	CGridPropUnit::SetLgrName
	 * ����:	virtual public 
	 * @���� 	2008-12-31
	 * @����  iuhiao
	 * @���� 	CString strName
	 * @�������� 	void
	 */
	virtual void SetLgrName(CString strName);

	/**
	 * ����:	���ö�ȡ�������ݵ����� "INTE" "CHAR"  "DOUB" "REAL"
	 * ȫ��:	CGridPropUnit::SetDataType
	 * ����:	virtual public 
	 * 
	 * @date	2010/06/30
	 * @author	Administrator
	 * @param	CString dataType
	 * @return	void
	 */
	virtual void SetDataType(CString dataType = _T("REAL")){m_dataRealType = dataType;};

protected:
	/**
	 * ����:	��ȡ��ǰѡ�е�������������
	 * ȫ��:	CGridPropUnit::GetCurGridProp
	 * ����:	protected 
	 * 
	 * @date	2010/06/30
	 * @author	Administrator
	 * @return	CString
	 */
	CString GetCurGridPropName();

	/**
	 * ����:	��ȡ��ǰ��������
	 * ȫ��:	CGridPropUnit::GetDataCaseName
	 * ����:	protected 
	 * 
	 * @date	2010/06/30
	 * @author	Administrator
	 * @return	CString
	 */
	CString GetDataCaseName();

protected:
	//�Ƿ�Ҫ���¼��������Сֵ
	BOOL m_bRecal;

	//���������Сֵ
	double  m_dMaxValue;
	double  m_dMinValue;
	//TRUE Ϊ����FALSEΪǰ����
	BOOL m_dataType;
	//���������ļ���������
	CString m_lgrName;

	//��ǰ��¼��������
	CString m_strPropName;

	//��������
	TimedGridProp m_namedGridProps;

	//��������
	CString m_dataRealType;

	//��Ч�������ݸ���
	__int64 m_dataCount;
private:
	//���л�����
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		//ar & BOOST_SERIALIZATION_NVP(m_namedGridProps);
		//ar & BOOST_SERIALIZATION_NVP(m_strPropName);
		//ar & BOOST_SERIALIZATION_NVP(m_dMaxValue);
		//ar & BOOST_SERIALIZATION_NVP(m_dMinValue);
		//ar & BOOST_SERIALIZATION_NVP(m_bRecal);
		//ar & BOOST_SERIALIZATION_NVP(m_dataType);
		//ar & BOOST_SERIALIZATION_NVP(m_dataRealType);
	}
};