#pragma once
#include "Singleton.h"
#include <vector>
#include "DataRoot.h"

//���巽�����ƽṹ
typedef std::vector<CString> CaseNames;
//���巽�����
typedef std::vector<unsigned int> CaseNos;

class CDataRoot;
class CDataOperation;

#ifdef COMMON_LIB
#define COMMON_EXPORT __declspec(dllexport)
#else
#define COMMON_EXPORT __declspec(dllimport)
#endif // COMMON_LIB


class COMMON_EXPORT CProjectManger:
	public Singleton<CProjectManger>
{
public:
	CProjectManger(void);
	~CProjectManger(void);

	enum SaveProjFlag
	{
		SaveActive,
		SaveAll
	};
public:
	/**
	 * ����:	��ȡ������Ϣ
	 * ȫ��:	CProjectManger::ReadProjectInfo
	 * ����:	public 
	 * 
	 * @date	2008/11/03
	 * @author	XX
	 * @return	BOOL
	 */
	BOOL ReadProjectInfo(CString& modelPath);

	/**
	 * ����:	д����Ŀ������Ϣ
	 * ȫ��:	CProjectManger::WriteProjectInfo
	 * ����:	public 
	 * 
	 * @date	2008/11/13
	 * @author	XX
	 * @return	BOOL
	 */
	BOOL WriteProjectInfo();

	/**
	 * ����:	�����µķ���
	 * ȫ��:	CProjectManger::CreateNewDataCase
	 * ����:	public 
	 * 
	 * @date	2008/11/14
	 * @author	XX
	 * @param	const CString & strCaseName
	 * @return	CDataRoot*
	 */
	CDataRoot* CreateNewDataCase(const CString& strCaseName);

	/**
	* ����:	����ģ�ͷ�������
	* ȫ��:	CProjectManger::CreateModeCase
	* ����:	protected 
	* 
	* @date	  2009/02/16
	* @author	Wangxh
	* @param	  const CString & strModeName
	* @return	CDataRoot*
	*/
	CDataRoot* CreateModeCase(const CString& strModeName);
	/**
	 * ����:	ɾ������
	 * ȫ��:	CProjectManger::DeleteDataCase
	 * ����:	public 
	 * 
	 * @date	2008/11/24
	 * @author	XX
	 * @param	const CString & strCaseName
	 * @param	BOOL bIsDeleteFile
	 * @return	BOOL
	 */
	BOOL DeleteDataCase(const CString& strCaseName,BOOL bIsDeleteFile);

	/**
	 * ����:	ɾ������
	 * ȫ��:	CProjectManger::DeleteDataCase
	 * ����:	public 
	 * 
	 * @date	2008/11/15
	 * @author	XX
	 * @param	CDataRoot * dataCase
	 * @param	BOOL bIsDeleteFile
	 * @return	BOOL
	 */
	BOOL DeleteDataCase(CDataRoot* dataCase,BOOL bIsDeleteFile);

	/**
	 * ����:  ��ոù�������е���������
	 * ȫ��:
	 * ����:
	 * 
	 * @date
	 * @author
	 * @return
	*/
	void ClearProjectMangerData();

public:
	/**
	 * ����:	��ȡ��������
	 * ȫ��:	CProjectManger::GetDataTypeParam
	 * ����:	public 
	 * 
	 * @date	2010/07/16
	 * @author	Administrator
	 * @return	CString
	 */
	CString GetDataTypeParam();

	/**
	 * ����:	������������
	 * ȫ��:	CProjectManger::SetDataTypeParam
	 * ����:	public 
	 * 
	 * @date	2010/07/16
	 * @author	Administrator
	 * @param	const CString & strType
	 * @return	void
	 */
	void SetDataTypeParam(const CString& strType);

	/**
	 * ����:	��ȡ��Ŀ·��
	 * ȫ��:	CProjectManger::GetPrjPath
	 * ����:	public 
	 * 
	 * @date	2008/11/07
	 * @author	XX
	 * @return	const CString&
	 */
	const CString& GetPrjPath();

	/**
	 * ����:	��ȡ��Ŀ����
	 * ȫ��:	CProjectManger::GetProjectName
	 * ����:	public 
	 * 
	 * @date	2008/10/30
	 * @author	XX
	 * @return	CString
	 */
	CString GetProjectName();

	/**
	 * ����:	��ȡ������
	 * ȫ��:	CProjectManger::GetMainDataCase
	 * ����:	public 
	 * 
	 * @date	2008/11/07
	 * @author	XX
	 * @return	CDataRoot*
	 */
	CDataRoot* GetMainDataCase();

	/**
	 * ����:	��ȡ����������
	 * ȫ��:	CProjectManger::GetMainCaseName
	 * ����:	public 
	 * 
	 * @date	2008/10/30
	 * @author	XX
	 * @return	CString
	 */
	CString GetMainCaseName();

	/**
	 * ����:	��ȡ���з�������
	 * ȫ��:	CProjectManger::GetCaseNames
	 * ����:	public 
	 * 
	 * @date	2008/10/30
	 * @author	XX
	 * @return	CaseNames
	 */
	CaseNames GetCaseNames();

	/**
	 * ����:	��ȡ��Ŀ���
	 * ȫ��:	CProjectManger::GetCaseNos
	 * ����:	public 
	 * 
	 * @date	2008/11/10
	 * @author	XX
	 * @return	CaseNos
	 */
	CaseNos GetCaseNos();

	/**
	 * ����:	ͨ������������ҷ�������
	 * ȫ��:	CProjectManger::GetCaseNameByNoID
	 * ����:	public 
	 * 
	 * @date	2008/11/10
	 * @author	XX
	 * @param	unsigned int nCaseID
	 * @return	CString
	 */
	CString GetCaseNameByNoID(unsigned int nCaseID);

	/**
	 * ����:	ͨ���������ƻ�ȡ����ID
	 * ȫ��:	CProjectManger::GetCaseNoByNoName
	 * ����:	public 
	 * 
	 * @date	2008/11/10
	 * @author	XX
	 * @param	const CString & strCaseName
	 * @return	unsigned int
	 */
	unsigned int GetCaseNoByNoName(const CString& strCaseName);

	/**
	 * ����:	��ȡ��ǰ������ݸ�����
	 * ȫ��:	CProjectManger::GetActiveCase
	 * ����:	public 
	 * 
	 * @date	2008/10/27
	 * @author	XX
	 * @return	CDataRoot*
	 */
	CDataRoot* GetActiveCase();

	/**
	 * ����:	ͨ�������Ż�ȡָ������
	 * ȫ��:	CProjectManger::GetDataCase
	 * ����:	public 
	 * 
	 * @date	2008/11/10
	 * @author	XX
	 * @param	unsigned int nCaseID
	 * @return	CDataRoot*
	 */
	CDataRoot* GetDataCase(unsigned int nCaseID);

	/**
	 * ����:	��ȡָ������
	 * ȫ��:	CProjectManger::GetDataCase
	 * ����:	public 
	 * 
	 * @date	2008/10/30
	 * @author	XX
	 * @param	const CString & strCaseName
	 * @return	CDataRoot*
	 */
	CDataRoot* GetDataCase(const CString& strCaseName);

	/**
	 * ����:	���û��������
	 * ȫ��:	CProjectManger::SetActiveCase
	 * ����:	public 
	 * 
	 * @date	2008/10/30
	 * @author	XX
	 * @param	const CString & strCaseName
	 * @return	void
	 */
	void SetActiveCase(const CString& strCaseName);

public:
	/**
	 * ����:	ע����������
	 * ȫ��:	CProjectManger::RegisterDataClass
	 * ����:	public 
	 * 
	 * @date	2010/07/07
	 * @author	Administrator
	 * @param	const CString & strClassName
	 * @param	void * fun_Create
	 * @return	void
	 */
	void RegisterDataClass(const CString& strClassName,void* fun_Create);

	/**
	 * ����:	ע�����ݲ�����
	 * ȫ��:	CProjectManger::RegisterDataOperation
	 * ����:	public 
	 * 
	 * @date	2010/08/20
	 * @author	Administrator
	 * @param	CDataOperation * pDataOperation
	 * @return	void
	 */
	void RegisterDataOperation(CDataOperation* pDataOperation);

	/**
	 * ����:	��ȡ���ݲ�������
	 * ȫ��:	CProjectManger::GetDataOperation
	 * ����:	protected 
	 * 
	 * @date	2010/08/20
	 * @author	Administrator
	 * @return	CDataOperation*
	 */
	CDataOperation* GetDataOperation();

protected:
	//���巽����������
	typedef std::map<unsigned int,CDataRoot*> DataRoots;
	//��������
	DataRoots m_dataRoots;
	//��ǰ�����
	CDataRoot* m_actDataRoot;
protected:
	//�������ݲ�����������
	typedef std::map<CString,CDataOperation*> DataOperations;
	//���ݲ�������
	DataOperations m_dataOperations;
protected:
	//��ǰ��������
	CString m_strDatatypeParam;
	//��ǰ��Ŀ����
	CString m_strProjectName;
	//����������
	CString m_strMainCase;
	//��ǰ��Ŀ·��
	CString m_strPrjPath;
};
