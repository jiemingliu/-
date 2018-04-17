#pragma once
#include <map>
#include "DataObjStruct.h"

class CDataBlock;
class CDataKeyWord;
class CDataPoClass;
class CDataPoEntity;

//���ݿ���������
typedef std::map<CString,void*> MapDataBlock;
//�ؼ�����������
typedef std::map<CString,void*> MapKeyWord;
//������������
typedef std::map<CString,void*> MapPoClass;
//��������ʵ������
typedef std::map<CString,void*> MapPoEntity;


class AFX_EXT_CLASS CDataObjFactory
{
public:
	CDataObjFactory(void);
	~CDataObjFactory(void);

public:
	/**
	 * ����:	ע���������
	 * ȫ��:	CDataObjFactory::RegisterType
	 * ����:	public static 
	 * 
	 * @date	2008/03/21
	 * @author	xx
	 * @return	void
	 */
	static void RegisterType();

	/**
	 * ����:	Regע��Chemical����������isterChemicalPropType
	 * ȫ��:	CDataObjFactory::RegisterChemicalPropType
	 * ����:	public 
	 * 
	 * @date	2010/08/19
	 * @author	HUANGL
	 * @return	void
	 */
	static void RegisterChemicalPropType();

	/**
	 * ����:	���л������Ʒ�ʽע��
	 * ȫ��:	CDataObjFactory::RegisterType_binary_iarchive
	 * ����:	public static 
	 * 
	 * @date	2008/07/02
	 * @author	XX
	 * @param	boost::archive::binary_iarchive & Archive
	 * @return	void
	 */
	void RegisterType_archive(boost::archive::binary_iarchive& Archive);

	/**
	 * ����:	���л������Ʒ�ʽע��
	 * ȫ��:	CDataObjFactory::RegisterType_binary_oarchive
	 * ����:	public static 
	 * 
	 * @date	2008/07/02
	 * @author	XX
	 * @param	boost::archive::binary_oarchive & Archive
	 * @return	void
	 */
	void RegisterType_archive(boost::archive::binary_oarchive& Archive);

	///**
	// * ����:	���л��ı���ʽע��
	// * ȫ��:	CDataObjFactory::RegisterType_text_iarchive
	// * ����:	public static 
	// * 
	// * @date	2008/07/02
	// * @author	XX
	// * @param	boost::archive::text_iarchive & Archive
	// * @return	void
	// */
	//void RegisterType_archive(boost::archive::xml_iarchive& Archive);

	///**
	// * ����:	���л��ı���ʽע��
	// * ȫ��:	CDataObjFactory::RegisterType_text_oarchive
	// * ����:	public static 
	// * 
	// * @date	2008/07/02
	// * @author	XX
	// * @param	boost::archive::text_oarchive & Archive
	// * @return	void
	// */
	//void RegisterType_archive(boost::archive::xml_oarchive& Archive);

public:
	/**
	 * ����:	����DataBlock
	 * ȫ��:	CDataObjFactory::CreateColByType
	 * ����:	public static 
	 * 
	 * @date	2008/03/21
	 * @author	xx
	 * @param	const CString & strBlockName
	 * @return	CDataBlock*
	 */
	static CDataBlock* CreateDataBlock(const CString& strBlockName);

	/**
	 * ����:	����DataKeyWord
	 * ȫ��:	CDataObjFactory::CreateDataKeyWord
	 * ����:	public 
	 * 
	 * @date	2008/03/27
	 * @author	xx
	 * @param	const KeyInfo & keyInfo
	 * @return	CDataKeyWord*
	 */
	static CDataKeyWord* CreateDataKeyWord(const KeyInfo& keyInfo);

	/**
	 * ����:	����DataPoClass��������
	 * ȫ��:	CDataObjFactory::CreateDataPoClass
	 * ����:	public static 
	 * 
	 * @date	2008/04/01
	 * @author	xx
	 * @param	const CString & strClassName
	 * @return	CDataPoClass*
	 */
	static CDataPoClass* CreateDataPoClass(const CString& strClassName);

	/**
	 * ����:	����CDataPoEntity��������ʵ��
	 * ȫ��:	CDataObjFactory::CreateDataPoEntity
	 * ����:	public static 
	 * 
	 * @date	2008/04/03
	 * @author	xx
	 * @param	const CString & strEntityName
	 * @return	CDataPoEntity*
	 */
	static CDataPoEntity* CreateDataPoEntity(const CString& strEntityName);

	/**
	 * ����:	����Chemical����������
	 * ȫ��:	CDataObjFactory::FindChemicalProp
	 * ����:	public static 
	 * 
	 * @date	2010/08/20
	 * @author	HUANGL
	 * @param	long nFlag
	 * @param	CString & strProp
	 * @return	bool
	 */
	static bool FindChemicalProp(long nFlag, CString& strProp);

private:
	//ע��DataBlock����
	static void RegisterDataBlockType();
	//ע��KeyWord����
	static void RegisterDataKeyWordType();
	//ע��PoClass����
	static void RegisterPoClassType();
	//ע��PoEntity����
	static void RegisterPoEntityType();
	/// <summary>
	/// ע��summary�еĹؼ���
	/// </summary>
	static void RegisterSummaryKeyWord();
private:
	//�������ݿ�����
	template<class dataBlkType>
	static void AddDataBlockType()
	{
		ASSERT(m_mapDataBlocks.find(dataBlkType::typeBlockName) == m_mapDataBlocks.end());
		m_mapDataBlocks[dataBlkType::typeBlockName] = &(dataBlkType::CreateDataBlock);
	}

	//����ؼ�������
	template<class dataKeyWord>
	static void AddDataKeyWordType()
	{
		ASSERT(m_mapKeyWords.find(dataKeyWord::typeKeyWord) == m_mapKeyWords.end());
		m_mapKeyWords[dataKeyWord::typeKeyWord] = &(dataKeyWord::CreateDataKeyWord);
	}

	//����ؼ�������-�˷�����������������ͬ���͵�һ��ؼ��ʴ�������
	template<class dataKeyWord>
	static void AddDataKeyWordType(CString strKeyWord)
	{
		ASSERT(m_mapKeyWords.find(strKeyWord) == m_mapKeyWords.end());
		m_mapKeyWords[strKeyWord] = &(dataKeyWord::CreateDataKeyWord);
	}

	//����DataPoClass��������
	template<class dataPoClassType>
	static void AddPoClassType()
	{
		ASSERT(m_mapPoClass.find(dataPoClassType::typeClassName) == m_mapPoClass.end());
		m_mapPoClass[dataPoClassType::typeClassName] = &(dataPoClassType::CreateDataPoClass);
	}

	//����DataPoClass��������
	template<class dataPoEntityType>
	static void AddPoEntityType()
	{
		ASSERT(m_mapPoEntity.find(dataPoEntityType::typeEntityName) == m_mapPoEntity.end());
		m_mapPoEntity[dataPoEntityType::typeEntityName] = &(dataPoEntityType::CreateDataPoEntity);
	}
	template<class dataPoEntityType>
	static void AddPoEntityType(CString strKeyword)
	{
		ASSERT(m_mapPoEntity.find(strKeyword) == m_mapPoEntity.end());
		m_mapPoEntity[strKeyword] = &(dataPoEntityType::CreateDataPoEntity);
	}

private:
	//���洴��CDataBlock�ӿں���ָ��
	static MapDataBlock m_mapDataBlocks;
	//���洴��CDataKeyWord�ӿں���ָ��
	static MapKeyWord m_mapKeyWords;
	//���洴��CDataPoClass�ӿں���ָ��
	static MapPoClass m_mapPoClass;
	//��������ʵ������
	static MapPoEntity m_mapPoEntity;
};
