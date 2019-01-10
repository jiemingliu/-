/******************************************************************************
* �ļ���: jcxmlparse.h
* ����: -
* Copyright(c)2014-2016 JCDZ Co.,Ltd.
*
* �޸ļ�¼:
* --------------------
* v1.0   2014/03/13 18:40:33, gaopeng �����ļ�
* v1.1	 2015/11/27 09:40:33, gaopeng ���Ʒ�װ�����ζ�tiXml��ͷ�ļ�����	
******************************************************************************/
#ifndef _JCXMLPARSE_H
#define _JCXMLPARSE_H

#include <map>
#include <string>

#include <list>
#include "jcbase.h"
#include "jcnonecopy.h"

using namespace std;

typedef std::map<std::string, std::string> AttrMap;

class TiXmlElement ;
class TiXmlNode;
class TiXmlAttribute;
class TiXmlText;
class TiXmlDocument;
class TiXmlDeclaration;

/************************************************************************/
/*��Ӧ��XML�е���������	                                                */
/************************************************************************/
class DLL_EXPORT JCXmlDeclaration 
{
public:
	JCXmlDeclaration(string strVersion, string strEncoding, string strStandalone)
	{
		m_strVersion = strVersion;
		m_strEncoding = strEncoding;
		m_strStandalone = strStandalone;
	}

public:
	string m_strVersion;
	string m_strEncoding;
	string m_strStandalone;
};

/************************************************************************/
/*��Ӧ��XML��Ԫ������	                                                */
/************************************************************************/
class DLL_EXPORT JCXmlAttribute
{ 
public:
	JCXmlAttribute(string strAttribute, string strValue)
	{
		m_strAttribute = strAttribute;
		m_strValue = strValue;
	}

public:
	string m_strAttribute;
	string m_strValue;
};

/************************************************************************/
/*��Ӧ��XML��Ԫ��		                                                */
/************************************************************************/
class DLL_EXPORT JCXmlElement
{
public:
	JCXmlElement():m_strValue(""), m_ptElem(NULL)
	{
	}

	JCXmlElement(string strValue):m_strValue(strValue), m_ptElem(NULL)
	{
	}

	typedef std::map<std::string, std::string> AttrMap;

public:
	bool GetNextElement(JCXmlElement& tElem);

	bool GetAttributeValue(string strAttrName, string& strAttrValueRet);

	bool GetAttributes(AttrMap& tAttrMap);

	bool FindAttribute(string strAttrName);

	bool InsertAttribute(string strAttrName, string strAttrValue);

	bool DelAttribute(string strAttrName);

public:
	string m_strValue;
	TiXmlElement* m_ptElem;
};

/************************************************************************/
/* ��Ӧ��DOM�ṹ�еĽڵ�                                                */
/************************************************************************/
class DLL_EXPORT JCXmlNode
{
public:
	JCXmlNode():m_ptNote(NULL)
	{}
	JCXmlNode(string strNodeName):m_strNodeName(strNodeName),m_ptNote(NULL)
	{}

public:
	bool InsertElement(JCXmlElement& tElement);
	bool GetFirstChildNode(JCXmlNode& tNode);
	bool GetNextNode(JCXmlNode& tNode);
	JCXmlElement ToElement();

public:
	string m_strNodeName;
	TiXmlNode* m_ptNote;
};

/************************************************************************/
/*XML�ĵ�����			                                                */
/************************************************************************/
class DLL_EXPORT JCXMLparser : public JCNonecopy
{
public:
    JCXMLparser();
    ~JCXMLparser();

public:
    /******************************************************************************
    * ������:JCXMLparser.CreateXmlFile
    * ����: -���������ļ�������xml�ļ���***��Ҫ����SaveXmlFile�ű��浽����***
    *
    * ����:fullName:�����ļ���������·����overWrite:�Ƿ񸲸��Ѵ����ļ�
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/03/13 18:39:27, gaopeng ��������
    *
    ******************************************************************************/
    bool CreateXmlFile(std::string fullName, bool overWrite=false);

    /******************************************************************************
    * ������:JCXMLparser.LoadXmlFile
    * ����: -�����ļ���������xml�ļ�
    *
    * ����:fileName:xml�����ļ���������·��
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/03/13 18:39:51, gaopeng ��������
    *
    ******************************************************************************/
    bool LoadXmlFile(std::string fileName);

    /******************************************************************************
    * ������:JCXMLparser.SaveXmlFile
    * ����: -���洴����xml�ļ���**������fileNameΪ��ʱ���Դ���ʱ������ļ������档**
    *
    * ����:fileName �ļ���
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/03/13 18:40:50, gaopeng ��������
    *
    ******************************************************************************/
    bool SaveXmlFile(std::string fileName="");

	/******************************************************************************
    * ������:JCXMLparser.GetRootNode
    * ����: -��ȡxml�ĵ����ڵ�
    *
    * ����:tNode���ؽڵ�
    * ���:
    * ����ֵ:�ɹ���True�� ʧ�ܣ�False
    *
    * �޸ļ�¼:
    * --------------------
    *    2015/11/27 10:40:59, gaopeng ��������
    *
    ******************************************************************************/
	bool GetRootNode(JCXmlNode& tNode);

	/******************************************************************************
    * ������:JCXMLparser.InsertDeclaration
    * ����: -xml�ĵ��в�������
    *
    * ����:tDel ����
    * ���:
    * ����ֵ:�ɹ���True�� ʧ�ܣ�False
    *
    * �޸ļ�¼:
    * --------------------
    *    2015/11/27 10:40:59, gaopeng ��������
    *
    ******************************************************************************/
	bool InsertDeclaration(JCXmlDeclaration& tDel);

	/******************************************************************************
    * ������:JCXMLparser.FindTextNodeByPath
    * ����: -��·������ָ��text�ڵ㣬·����ʽ��level1/level2/destNode
    *
    * ����:path ·��
    * ���:
    * ����ֵ:�ɹ��������ļ����ݣ� ʧ�ܣ����ؿ��ַ���
    *
    * �޸ļ�¼:
    * --------------------
    *    2015/11/27 10:40:59, gaopeng ��������
    *
    ******************************************************************************/
    string FindTextNodeByPath(std::string path);

	/******************************************************************************
    * ������:JCXMLparser.InsertTextNodeByPath
    * ����: -ȫ·������text�ڵ㣬 ·����ʽ��level1/level2/destNode
    *		���·�������ڣ������δ����ڵ�·��
    * ����:path: ·��, strValue: destNodeֵ
    * ���:
    * ����ֵ:�ɹ������ؽڵ�ָ�룬 ʧ�ܣ�����NULL
    *
    * �޸ļ�¼:
    * --------------------
    *    2015/11/27 10:40:59, gaopeng ��������
    *
    ******************************************************************************/
	bool InsertTextNodeByPath(std::string path, std::string strValue);

	/******************************************************************************
    * ������:JCXMLparser.InsertCommentNodeByPath
    * ����: -ȫ·������text�ڵ㣬 ·����ʽ��level1/level2/destNode
    *		���·�������ڣ������δ����ڵ�·��
    * ����:path: ·��, strValue: destNodeֵ
    * ���:
    * ����ֵ:�ɹ������ؽڵ�ָ�룬 ʧ�ܣ�����NULL
    *
    * �޸ļ�¼:
    * --------------------
    *    2017/02/11 18:49:59, gaopeng ��������
    *
    ******************************************************************************/
	bool InsertCommentNodeByPath(std::string path, std::string strValue);

	/******************************************************************************
    * ������:JCXMLparser.FindXmlNodeByPath
    * ����: -��·������element�ڵ㣬 ·����ʽ��level1/level2/elementName
    *
    * ����:path: ·���� tNode���ؽ��
    * ���:
    * ����ֵ:�ɹ���True�� ʧ�ܣ�False
    *
    * �޸ļ�¼:
    * --------------------
    *   2015/11/27 10:40:59, gaopeng ��������
    *
    ******************************************************************************/
	bool FindXmlNodeByPath(std::string path, JCXmlNode& tNode);

	/******************************************************************************
    * ������:JCXMLparser.InsertXmlNodeByPath
    * ����: -ȫ·������ڵ㣬 ·����ʽ��level1/level2/elementName
    *		���·�������ڣ������δ����ڵ�·��
    * ����:path: ·��
    * ���:
    * ����ֵ:�ɹ���True�� ʧ�ܣ�False
    *
    * �޸ļ�¼:
    * --------------------
    *    2015/11/27 10:40:59, gaopeng ��������
    *
    ******************************************************************************/
	bool InsertXmlNodeByPath(std::string path);

	/******************************************************************************
    * ������:JCXMLparser.DeleteXmlNodeByPath
    * ����: -ɾ��ָ���ڵ㣬 ·����ʽ��level1/level2/elementName
    *		
    * ����:path: ·��
    * ���:
    * ����ֵ:�ɹ���True�� ʧ�ܣ�False
    *
    * �޸ļ�¼:
    * --------------------
    *    2015/11/27 10:40:59, gaopeng ��������
    *
    ******************************************************************************/
	bool DeleteXmlNodeByPath(std::string path);

private:
	/******************************************************************************
    * ������:JCXMLparser.FindNodeByPath
    * ����: -��·������element�ڵ㣬 ·����ʽ��level1/level2/elementName
    *
    * ����:path: ·��
    * ���:
    * ����ֵ:�ɹ������ؽڵ�ָ�룬 ʧ�ܣ�����NULL
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/03/13 18:42:39, gaopeng ��������
    *
    ******************************************************************************/
	TiXmlElement* FindNodeByPath(std::string path);

	/******************************************************************************
    * ������:JCXMLparser.InsertNodeByPath
    * ����: -ȫ·������ڵ㣬 ·����ʽ��level1/level2/elementName
    *		���·�������ڣ������δ����ڵ�·��
    * ����:path: ·��
    * ���:
    * ����ֵ:�ɹ������ؽڵ�ָ�룬 ʧ�ܣ�����NULL
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/03/13 18:42:39, gaopeng ��������
    *
    ******************************************************************************/
	TiXmlElement* InsertNodeByPath(std::string path);

	//���ó�Աָ��
    void ResetFilePorinter();

private:
    TiXmlDocument* m_ptDocument;
    std::string m_strFileName;
};

#endif /* _JCXMLPARSE_H */

