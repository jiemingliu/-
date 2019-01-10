/******************************************************************************
* �ļ���: jcconfigdatabase.h
* ����: �������ͻ���, �ɷ��������Ա������, ���뵼������
* Copyright(c)2014-2016 JCDZ Co.,Ltd.
*
* �޸ļ�¼:
* --------------------
* v1.0   2014/10/17 17:7:19, lys �����ļ�
*
******************************************************************************/

#ifndef _JCCONFIGDATABASE_H_
#define _JCCONFIGDATABASE_H_

#include <sstream>
#include <string>
#include "jcbase.h"

using namespace std;

class JCLogWrapper;
class JCXMLparser;

enum InfoType
{
	MEMBTYPE,
	MEMBNAME,
	MEMBVALUE
};

/**************************************************************
  �������Ա�����ĺ궨��, Ŀǰ��֧�ָ������ͳ�Աʹ�ô˺�

  ��Ϊÿ����Ա����һ��λ������, һ����ȡ��Ϣ�ӿں�һ�����ýӿ�
**************************************************************/
#define DECLARE_MEMBER_ORDER(MembName, MembIndex) \
	static const unsigned char const##MembName = MembIndex;

#define MEMBER_ORDER(MembName) const##MembName

#define END_DECLARE_MEMBER(MembCount)\
	static const unsigned char constMaxMembCount = MembCount

#define MEMBER_COUNT constMaxMembCount

 /*��ȡ��Ա��������, ȥ����Ա������m_ǰ׺*/
#define DECFUNC_MEMBER_NAME(MembName)\
	string Get##MembName##Name(void)\
	{\
		string strName = #MembName;\
		return strName.substr(2);\
	}

#define DECFUNC_MEMBER_VALUE(MembName)\
	string Get##MembName##Value(void)\
	{\
		stringstream& stream = CustomizedStream();\
		stream << MembName;\
		return stream.str();\
	}

#define DECFUNC_SET_MEMBER_VALUE(MembName)\
	void Set##MembName##Value(const string &strValue)\
	{\
		stringstream& stream = CustomizedStream();\
		stream << strValue;\
		stream >> MembName;\
	}

#define DECFUNC_MEMBER_TYPE(MembType, MembName)\
	string Get##MembName##Type()\
	{\
		return #MembType;\
	}

#define MEMBER_GETFUNC_DISPATCH(MembInfoType, MembName) \
	case MEMBER_ORDER(MembName): \
	{\
		if (MembInfoType == MEMBTYPE)  return Get##MembName##Type(); \
		if (MembInfoType == MEMBNAME)  return Get##MembName##Name(); \
		if (MembInfoType == MEMBVALUE) return Get##MembName##Value(); \
		break;\
	}

#define MEMBER_SETFUNC_DISPATCH(MembName, SetValue) \
	case MEMBER_ORDER(MembName): \
	{\
		return Set##MembName##Value(SetValue); \
	}

#define DECLARE_MEMBER(MembType, MembName, MembIndex)\
		DECFUNC_MEMBER_TYPE(MembType, MembName)\
		DECFUNC_MEMBER_NAME(MembName)\
		DECFUNC_MEMBER_VALUE(MembName)\
		DECFUNC_SET_MEMBER_VALUE(MembName)\
		DECLARE_MEMBER_ORDER(MembName, MembIndex)\
		MembType MembName


/******************************************************************************
* ������:JCParaBase
* ����: �������ͻ�����, Ϊ�����ṩ�����Ա������ֵ����, ֵ���ü���ӡ�ӿ�
*       ע��: ����DECFUNC_MEMBER_NAME�Գ�Ա���Ĵ������, ���Ա������m_Ϊǰ׺
*       , �ҳ�Ա����ӦΪC++֧�����ݸ�ʽ�����ڽ�����
* ����:
* ���:
* ����ֵ:
*
* �޸ļ�¼:
* --------------------
*    2014/10/20 16:4:16, lys ��������
*
******************************************************************************/
class DLL_EXPORT JCParaBase
{
public:
	JCParaBase();
	virtual ~JCParaBase();

	static stringstream& CustomizedStream();

    /******************************************************************************
    * ������:JCParaBase.PrintPara
    * ����: ��ӡ���г�Ա��Ϣ(�����ʽ:  ��Ա������: ��Ա����ֵ)
    *
    * ����: tLog��־���Ͷ���, nMemberCnt����ӦΪ�����͵ķǸ��Ͻṹ��Ա��Ŀ, ����ʹ�� ����::MEMBER_COUNT
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/10/20 16:0:24, lys ��������
    *
    ******************************************************************************/
	virtual void PrintPara(JCLogWrapper &tLog, unsigned int nMemberCnt);

	/******************************************************************************
    * ������:JCParaBase.DumpParaToXml
    * ����: �����Ա��Ϣд��XML�ļ�(�����ʽ:  <��Ա������>��Ա����ֵ</��Ա������>)
    *
    * ����: tXml XML�ļ�������� strPath ���Աд���XML���ڵ�, ��aaa/bbb/ccc·����ʽ��ʾ
	*        nMemberCnt ͬ��
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/10/20 16:0:24, lys ��������
    *
    ******************************************************************************/
	virtual void DumpParaToXml(JCXMLparser &tXml, const string &strPath, unsigned int nMemberCnt);

	/******************************************************************************
    * ������:JCParaBase.LoadParaFromXml
    * ����: ��XML�ļ���ֵ�����Ӧ���Ա
    *
    * ����: tXml XML�ļ�������� strPath ���Աд���XML���ڵ�, ��aaa/bbb/ccc·����ʽ��ʾ
	*        nMemberCnt ͬ��
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/10/20 16:0:24, lys ��������
    *
    ******************************************************************************/
	virtual void LoadParaFromXml(JCXMLparser &tXml, const string &strPath, unsigned int nMemberCnt);

    /******************************************************************************
    * ������:JCParaBase.MemberInfo
    * ����: ��ȡ���Ա�����Ϣ
    *
    * ����: nMemberIndex ���Ա���ڲ���� eInfoType ��ȡ��Ϣ����(���Ա������, ���Ա����, ���Աֵ)
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/10/20 16:16:49, lys ��������
    *
    ******************************************************************************/
	/************************************************************************/
	/* 
	�����·�ʽʵ�ֺ���, ����Ҫ����ʵ�����Ա����������ض��Ƹý�
	, ����Ҫ��ȡ��Ϣ�����Ա�ɲ��о�
	switch(nMemberIndex)
	{
		MEMBER_GETFUNC_DISPATCH(eInfoType, ��Ա1);      
		MEMBER_GETFUNC_DISPATCH(eInfoType, ��Ա2);
		...
	}
	return string();
	*/
	/************************************************************************/
	virtual string MemberInfo(unsigned int nMemberIndex, InfoType eInfoType);

    /******************************************************************************
    * ������:JCParaBase.SetMemberValue
    * ����: �������Աֵ
    *
    * ����:nMemberIndex���Ա���, strValue ��Ҫ���õ�ֵ
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/10/20 16:17:10, lys ��������
    *
    ******************************************************************************/
	/************************************************************************/
	/* 	�����·�ʽʵ�ֺ���, ����Ҫ����ʵ�����Ա����������ض��Ƹý�
		, ����Ҫ��ȡ��Ϣ�����Ա�ɲ��о�

	switch(nMemberIndex)
	{
		MEMBER_SETFUNC_DISPATCH(��Ա1, strValue);      
		MEMBER_SETFUNC_DISPATCH(��Ա2, strValue);
		...
	}
	*/
	/************************************************************************/
	virtual void SetMemberValue(unsigned int nMemberIndex, const string &strValue);

};

#endif /* _JCCONFIGDATABASE_H_ */


