/******************************************************************************
* �ļ���: jcLock.hpp
* ����: �ٽ����������塢���������̰߳�ȫ����
* Copyright(c)2014-2016 JCDZ Co.,Ltd.
*
* �޸ļ�¼:
* --------------------
* v1.0   2014/03/19 11:2:3, lys �����ļ�
*
******************************************************************************/
#ifndef _JCLOCK_H_
#define _JCLOCK_H_

#include "jcnonecopy.h"

#if defined(__linux) || defined(__APPLE__) || defined(__CYGWIN__)
#include <pthread.h>
#define  CRITICAL_SECTION     pthread_mutex_t
#define  EnterCriticalSection pthread_mutex_lock  
#define  LeaveCriticalSection pthread_mutex_unlock 
#define  DeleteCriticalSection pthread_mutex_destroy
#else
#include <windows.h>
#endif

class JCCriticalSection
{
public:
    /******************************************************************************
    * ������:JCCriticalSection.JCCriticalSection
    * ����: Windows�û�̬�ٽ�η�װ.�̼߳以���ͬ����ѡ�û�̬��ʽ,�����û�̬�ں�̬
    *       �л�,Ч�ʸ�
    * ����:
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/03/21 10:29:1, lys ��������
    *
    ******************************************************************************/
	JCCriticalSection()
	{
#if defined(__linux) || defined(__APPLE__) || defined(__CYGWIN__)
		pthread_mutexattr_init(&m_tMutexAttr); 
		pthread_mutexattr_settype(&m_tMutexAttr , PTHREAD_MUTEX_RECURSIVE_NP);
        pthread_mutex_init(&m_tCriticalSection, &m_tMutexAttr);
#else
		InitializeCriticalSectionAndSpinCount(&m_tCriticalSection, 4000);/*���͵Ȳ�����Դ���߳��û�̬���ں�̬�л�����*/
#endif
	}

	~JCCriticalSection()
	{
		DeleteCriticalSection(&m_tCriticalSection);
	}

    /******************************************************************************
    * ������:JCCriticalSection.Lock
    * ����: �����ٽ���,����
    *
    * ����:
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/03/21 10:30:43, lys ��������
    *
    ******************************************************************************/
	void Lock()
	{
		EnterCriticalSection(&m_tCriticalSection);
	}

    /******************************************************************************
    * ������:JCCriticalSection.Unlock
    * ����: �뿪�ٽ���,����
    *
    * ����:
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/03/21 10:31:5, lys ��������
    *
    ******************************************************************************/
	void Unlock()
	{
		LeaveCriticalSection(&m_tCriticalSection);
	}

private:
	CRITICAL_SECTION m_tCriticalSection;
#if defined(__linux) || defined(__APPLE__) || defined(__CYGWIN__)
	pthread_mutexattr_t m_tMutexAttr;
#endif
};


template <class LockType>
class JCAutoLock : public JCNonecopy
{

public:
    /******************************************************************************
    * ������:JCAutoLock.JCAutoLock
    * ����: ʹ��������ʵ�����������Զ�����ģ��
    *       �����ʼ�����Զ�����,����ʱ�Զ�����,�������󲻽����ֶ�����(����Unlock),����
    *       ������Ǹ�������������������������
    * ����:
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/03/21 10:31:32, lys ��������
    *
    ******************************************************************************/
	JCAutoLock(LockType &tLock)
	:m_tLock(tLock)
	{
		m_tLock.Lock();
	}

    /******************************************************************************
    * ������:JCAutoLock.~JCAutoLock
    * ����: �����Զ�����
    *
    * ����:
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/03/21 10:35:6, lys ��������
    *
    ******************************************************************************/
	~JCAutoLock()
	{
		m_tLock.Unlock();
	}

    /******************************************************************************
    * ������:JCAutoLock.Lock
    * ����: �ֶ�����
    *
    * ����:
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/03/21 10:35:18, lys ��������
    *
    ******************************************************************************/
	void Lock()
	{
		m_tLock.Lock();
	}

    /******************************************************************************
    * ������:JCAutoLock.Unlock
    * ����: �ֶ�����
    *
    * ����:
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/03/21 10:35:33, lys ��������
    *
    ******************************************************************************/
	void Unlock()
	{
		m_tLock.Unlock();
	}

private:
	/*ע:��������,�ദʹ�ô�������ͬһ��Դʱ,���뱣֤������ʵ������������Ϊ
	ͬһ��, ��������Ӧһֱ���������һ�α�������*/
	LockType &m_tLock;
};

/*���ٽ��ʵ����������������*/
typedef JCAutoLock<JCCriticalSection> JCCSAutoLock;

#endif /* _JCLOCK_H_ */

