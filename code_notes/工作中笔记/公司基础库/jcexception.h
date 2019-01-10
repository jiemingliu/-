/******************************************************************************
* �ļ���: jcexception.h
* ����: �쳣�������Ͷ���
* Copyright(c)2014-2016 JCDZ Co.,Ltd.
*
* �޸ļ�¼:
* --------------------
* v1.0   2014/03/18 11:54:34, lys �����ļ�
*
******************************************************************************/
#ifndef _JCEXCEPTION_H_
#define _JCEXCEPTION_H_

#include <string>
#include <exception>
#include "jcbase.h"

using namespace std;

class DLL_EXPORT JCException : public exception
{
public:

    /******************************************************************************
    * ������:JCException.JCException
    * ����: ���캯��
    *
    * ����: e �׳��쳣�����Ĵ������  s �׳��쳣�����Ĵ���������Ϣ
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/03/20 14:27:49, lys ��������
    *
    ******************************************************************************/
	explicit JCException(unsigned int nExcp, const string &strInfo);
	virtual ~JCException() throw();

    /******************************************************************************
    * ������:JCException.ErrMsg
    * ����: ��ȡ������Ϣ
    *
    * ����:
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/03/20 14:22:34, lys ��������
    *
    ******************************************************************************/
	virtual const string &ErrMsg() const;

    /******************************************************************************
    * ������:JCException.SetErrMsg
    * ����: ���ô�����Ϣ�ִ�
    *
    * ����:
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/03/20 14:23:30, lys ��������
    *
    ******************************************************************************/
	virtual void SetErrMsg(const string &strInfo);

    /******************************************************************************
    * ������:JCException.ErrCode
    * ����: ��ȡ�������
    *
    * ����:
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/03/20 14:24:1, lys ��������
    *
    ******************************************************************************/
	virtual unsigned int ErrCode() const;

    /******************************************************************************
    * ������:JCException.SetErrCode
    * ����: ���ô������
    *
    * ����:
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/03/20 14:27:31, lys ��������
    *
    ******************************************************************************/
	virtual void SetErrCode(unsigned int e);

protected:
	unsigned int m_nErrorCode;
	string m_strWhat;
};


class DLL_EXPORT JCWinErrException : public JCException
{
public:

    /******************************************************************************
    * ������:JCWinErrException.JCWinErrException
    * ����: Windows�����쳣���캯��, �Ե�ǰλ��GetLastError����ֵ��ʼ���쳣������,
    *       ���Ӧ����������ʼ���쳣��Ϣ
    * ����:
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/03/20 14:28:41, lys ��������
    *
    ******************************************************************************/
	explicit JCWinErrException();

	virtual ~JCWinErrException() throw();
	void CleanError();

protected:
    /*Windows�����쳣��������Ϊ�Ķ������뼰����*/
	virtual void SetErrMsg(const string &strInfo);
	virtual void SetErrCode(unsigned int nExcp);

private:
	string FormatError(unsigned long nErrorCode);
};

#endif /* _JCEXCEPTION_H_ */


