/******************************************************************************
* �ļ���: jcsmartpointer.hpp
* ����: ����ָ��
* Copyright(c)2014-2016 JCDZ Co.,Ltd.
*
* �޸ļ�¼:
* --------------------
* v1.0   2014/03/19 16:16:41, lys �����ļ�
*
******************************************************************************/
#ifndef _JCSMARTPOINTER_H_
#define _JCSMARTPOINTER_H_

#include "jcnonecopy.h"

template <class T>
class JCBasicPointer : public JCNonecopy
{
public:
    /******************************************************************************
    * ������:JCBasicPointer.JCBasicPointer
    * ����: ����ָ���йܶ���
    *
    * ����:
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/03/21 10:45:6, lys ��������
    *
    ******************************************************************************/
	JCBasicPointer()
	: m_p(NULL)
	{

	}

    /******************************************************************************
    * ������:JCBasicPointer.~JCBasicPointer
    * ����: �����Զ��ͷ����йܵ��ڴ�����
    *
    * ����:
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/03/21 10:45:43, lys ��������
    *
    ******************************************************************************/
	~JCBasicPointer()
	{
		if (NULL != m_p)
		{
			delete m_p;
			m_p = NULL;
		}
	}

	T *m_p;
};


template <class T>
class JCMemberPointer : public JCNonecopy
{
public:
	/******************************************************************************
	* ������:JCMemberPointer.JCMemberPointer
	* ����: ָ���й���ģ����չ
	*
	* ����:
	* ���:
	* ����ֵ:
	*
	* �޸ļ�¼:
	* --------------------
	*    2014/03/21 10:48:20, lys ��������
	*
	******************************************************************************/
	explicit JCMemberPointer(T *p = NULL)
	: m_p(p)
	{

	}

	~JCMemberPointer()
	{
		Reset(NULL);
	}

	const T& operator*() const
	{
		return *m_p;
	}

	T& operator*()
	{
		return *m_p;
	}

	const T* operator->() const
	{
		return m_p;
	}

	T* operator->()
	{
		return m_p;
	}

	const T* Get() const
	{
		return m_p;
	}

	T* Get()
	{
		return m_p;
	}

	T* Release()
	{
		T *old_p = m_p;
		m_p = 0;
		return old_p;
	}

	void Reset(T *p = 0)
	{
		if (NULL != m_p)
		{
			delete m_p;
		}
		m_p = p;
	}

private:
	T *m_p;
};

#endif /* _JCSMARTPOINTER_H_ */

