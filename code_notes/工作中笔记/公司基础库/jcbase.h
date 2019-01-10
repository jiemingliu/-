/******************************************************************************
* �ļ���: jcbase.h
* ����: �����⹫��ͷ�ļ�
* Copyright(c)2014-2016 JCDZ Co.,Ltd.
*
* �޸ļ�¼:
* --------------------
* v1.0   2014/03/14 12:1:8, lys �����ļ�
*
******************************************************************************/
#ifndef _JCBASE_H_
#define _JCBASE_H_

#if defined(__linux) || defined(__APPLE__) || defined(__CYGWIN__)
#include <linux/limits.h>
#define  DLL_EXPORT 
#define  WINAPI
#define  INVALID_HANDLE_VALUE -1
#define Sleep(time) usleep(time*1000)
#define MAX_PATH PATH_MAX
typedef void * HANDLE;
typedef unsigned short WORD;
typedef unsigned char  UINT8;
typedef unsigned short UINT16;
typedef unsigned int   UINT32;
typedef unsigned int   DWORD;
typedef unsigned int   UINT;
typedef unsigned char  BYTE;
typedef long long	   __int64;

#else

/*���θ澯*/
#pragma warning(disable: 4251 4275 4996)

#define  DLL_EXPORT __declspec( dllexport )
#endif

#define DEBUG_VERSION
#undef DEBUG_VERSION/*����Ӱ���Զ���Ԫ���������������,���ز���ʱ�Լ��򿪼���*/
#define DEBUG_TIMER
#undef DEBUG_TIMER

/*��������*/

#endif /* _JCBASE_H_ */


