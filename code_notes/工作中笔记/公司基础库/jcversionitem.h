/******************************************************************************
* �ļ���: jcversionitem.h
* ����: �汾������(�ο�����汾����淶�ϲ��������)
* Copyright(c)2014-2016 JCDZ Co.,Ltd.
*
* �޸ļ�¼:
* --------------------
* v1.0   2014/04/08 23:37:12, lys �����ļ�
*
******************************************************************************/
#ifndef _JCVERSIONITEM_H_
#define _JCVERSIONITEM_H_

#include <string>
#include "jcbase.h"

using namespace std;
/******************************************************************************
* ������:JCVersionItem
* ����: �汾������
*
* ����:
* ���:
* ����ֵ:
*
* �޸ļ�¼:
* --------------------
*    2014/04/09 14:47:21, lys ��������
*
******************************************************************************/
class DLL_EXPORT JCVersionItem
{
public:
	JCVersionItem();

    /******************************************************************************
    * ������:JCVersionItem.JCVersionItem
    * ����: -
    *
    * ����:ƽ̨���/���Լ��ϱ��/���̻��豸���ͱ��/build���
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/04/09 14:47:46, lys ��������
    *
    ******************************************************************************/
	JCVersionItem(unsigned int nPlatForm, unsigned int nFeature, unsigned int nLabel, unsigned int nBuild);
	JCVersionItem(const JCVersionItem &tv);
	JCVersionItem &operator = (const JCVersionItem &tv);
	virtual ~JCVersionItem();

    /******************************************************************************
    * ������:JCVersionItem.Compare
    * ����: �汾�űȽϺ���,�ɼ̳���д,���ƱȽϹ���
    *
    * ����:
    * ���:
    * ����ֵ: ��� 0/ С�� -1/ ���� 1
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/04/09 14:49:16, lys ��������
    *
    ******************************************************************************/
	virtual unsigned int Compare(const JCVersionItem &tv);

    /******************************************************************************
    * ������:JCVersionItem.operator==
    * ����: �ȺŲ���������
    *
    * ����:
    * ���:
    * ����ֵ:���ֶ������Ϊ��
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/04/09 14:51:0, lys ��������
    *
    ******************************************************************************/
	friend bool DLL_EXPORT operator == (const JCVersionItem &lhs, const JCVersionItem &rhs);
	friend bool DLL_EXPORT operator != (const JCVersionItem &lhs, const JCVersionItem &rhs);

    /******************************************************************************
    * ������:JCVersionItem.operator<
    * ����: С�ڲ���������
    *
    * ����:
    * ���:
    * ����ֵ:���ֶ�Ȩ�رȽ�,m_nPlatFormȨ�����,���εݼ�
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/04/09 14:52:16, lys ��������
    *
    ******************************************************************************/
	friend bool DLL_EXPORT operator < (const JCVersionItem &lhs, const JCVersionItem &rhs);

    /******************************************************************************
    * ������:JCVersionItem.Version
    * ����: ��ȡ*.*.*.*��ʽ�汾��
    *
    * ����:
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/04/09 14:54:24, lys ��������
    *
    ******************************************************************************/
	string Version();

	unsigned int GetPlatForm();
	unsigned int GetFeature();
	unsigned int GetLabel();
	unsigned int GetBuild();

protected:
	unsigned int m_nPlatForm;
	unsigned int m_nFeature;
	unsigned int m_nLable;
	unsigned int m_nBuild;
};

#endif /* _JCVERSIONITEM_H_ */

