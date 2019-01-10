/******************************************************************************
* �ļ���: jcdynamiclog.h
* ����: ��̬��־���
* Copyright(c)2014-2016 JCDZ Co.,Ltd.
*
* �޸ļ�¼:
* --------------------
* v1.0   2014/03/27 22:31:31, lys �����ļ�
*
******************************************************************************/
#ifndef _JCDYNAMICLOG_H_
#define _JCDYNAMICLOG_H_

#include <string>
#include "jcbase.h"

#define LOG_MSG_HEAD_LEN     128
#define LOG_MSG_CONTENT_LEN  4096
#define MSG_LEN       (LOG_MSG_HEAD_LEN + LOG_MSG_CONTENT_LEN)

using namespace std;
class DLL_EXPORT JCDynamicLog
{
public:
	JCDynamicLog();
	~JCDynamicLog();

	void Logd(const string &strMsg);
};


#endif /* _JCDYNAMICLOG_H_ */

