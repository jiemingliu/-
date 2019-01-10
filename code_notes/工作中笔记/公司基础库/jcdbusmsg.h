/******************************************************************************
* �ļ���: jcdbusmsg.h
* ����: JC-DBUS��Ϣ����
* Copyright(c)2014-2016 JCDZ Co.,Ltd.
*
* �޸ļ�¼:
* --------------------
* v1.0   2014/03/31 20:13:23, lys �����ļ�
*
******************************************************************************/
#ifndef _JCDBUSMSG_H_
#define _JCDBUSMSG_H_

#include "jcbase.h"
#include "jclink.h"
#include "jcdbusmsgdata.h"

using namespace SNACC;

/******************************************************************************
* ������:JCDbusMsgRoute
* ����: ��Ϣ·����Ϣ,���ڶ�λ��Ϣ�շ�����
*
* ����:
* ���:
* ����ֵ:
*
* �޸ļ�¼:
* --------------------
*    2014/04/03 20:0:56, lys ��������
*
******************************************************************************/
#define  INVALID_ID   0xFFFFFFFF
class DLL_EXPORT JCDbusMsgRoute
{
public:
	JCDbusMsgRoute();
	JCDbusMsgRoute(unsigned int nDaemonId, unsigned int nModuleId);
	JCDbusMsgRoute(const JCDbusMsgRoute &tInfo);
	JCDbusMsgRoute &operator = (const JCDbusMsgRoute &tInfo);
	friend bool DLL_EXPORT operator == (const JCDbusMsgRoute &lhs, const JCDbusMsgRoute &rhs);
	friend bool DLL_EXPORT operator != (const JCDbusMsgRoute &lhs, const JCDbusMsgRoute &rhs);

	virtual ~JCDbusMsgRoute();
	unsigned int m_nDaemonId;/*ͨ�ſ��daemon ID*/
	unsigned int m_nModuleId;/*daemonͬһ����ڵ�ģ��ID*/
};

/******************************************************************************
* ������:JCDbusMsgInfo
* ����: JCDbus��Ϣͷ�ṹ
*
* ����:
* ���:
* ����ֵ:
*
* �޸ļ�¼:
* --------------------
*    2014/04/02 16:49:39, lys ��������
*
******************************************************************************/
class DLL_EXPORT JCDbusMsgInfo
{
public:
	JCDbusMsgInfo();

    /******************************************************************************
    * ������:JCDbusMsgInfo.JCDbusMsgInfo
    * ����:���캯��
    *
    * ����:
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/04/03 20:1:49, lys ��������
    *
    ******************************************************************************/
	JCDbusMsgInfo(unsigned int nSendDaemonId, unsigned int nSendModuleId, unsigned int nReceDaemonId
		, unsigned int nReceModuleId, unsigned int nMessageId, unsigned int nClientId, unsigned int nExecCode = 0);
    /******************************************************************************
    * ������:JCDbusMsgInfo.JCDbusMsgInfo
    * ����: ���캯��
    *
    * ����: ����ģ����Ϣ,����ģ����Ϣ,��Ϣ����,��Ϣ����
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/04/02 16:52:15, lys ��������
    *
    ******************************************************************************/
	JCDbusMsgInfo(const JCDbusMsgRoute &tSenderId, const JCDbusMsgRoute &tReceiverId
		, unsigned int nMessageId, unsigned int nClientId, unsigned int nExecCode = 0);

    /******************************************************************************
    * ������:JCDbusMsgInfo.JCDbusMsgInfo
    * ����: ���ƹ��캯��
    *
    * ����:
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/04/02 16:53:16, lys ��������
    *
    ******************************************************************************/
    JCDbusMsgInfo(const JCDbusMsgInfo &tInfo);

    /******************************************************************************
    * ������:JCDbusMsgInfo.operator=
    * ����: ��ֵ����
    *
    * ����:
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/04/02 16:53:40, lys ��������
    *
    ******************************************************************************/
	JCDbusMsgInfo &operator = (const JCDbusMsgInfo &tInfo);
	friend bool DLL_EXPORT operator == (const JCDbusMsgInfo &lhs, const JCDbusMsgInfo &rhs);
	friend bool DLL_EXPORT operator != (const JCDbusMsgInfo &lhs, const JCDbusMsgInfo &rhs);
	virtual~JCDbusMsgInfo();
	JCDbusMsgInfo &SwapMsgRoute();

	JCDbusMsgRoute m_tSenderId;
	JCDbusMsgRoute m_tReceiverId;
	unsigned int m_nMessageId;
	unsigned int m_nClientId;
	unsigned int m_nExecCode;/*ִ�н�����벻����Ƚϲ���*/
};

class JCDbusQueue;
/******************************************************************************
* ������:JCDbusMsg
* ����: JCDbus��Ϣ�ṹ
*
* ����:
* ���:
* ����ֵ:
*
* �޸ļ�¼:
* --------------------
*    2014/04/02 16:54:33, lys ��������
*
******************************************************************************/
class DLL_EXPORT JCDbusMsg
{
	friend class JCDbusQueue;
public:
	JCDbusMsg();

    /******************************************************************************
    * ������:JCDbusMsg.JCDbusMsg
    * ����: ���캯��
    *
    * ����:
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/04/03 20:3:42, lys ��������
    *
    ******************************************************************************/
	JCDbusMsg(unsigned int nSendDaemonId, unsigned int nSendModuleId, unsigned int nReceDaemonId
		, unsigned int nReceModuleId, unsigned int nMessageId, unsigned int nClientId, unsigned int nExecCode = 0);

    /******************************************************************************
    * ������:JCDbusMsg.JCDbusMsg
    * ����: ���캯��
    *
    * ����:����ģ��ID,����ģ��ID,��Ϣ����,��Ϣ����
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/04/02 16:55:7, lys ��������
    *
    ******************************************************************************/
	JCDbusMsg(const JCDbusMsgRoute &tSenderId, const JCDbusMsgRoute &tReceiverId
		, unsigned int nMessageId, unsigned int nClientId, unsigned int nExecCode = 0);

    /******************************************************************************
    * ������:JCDbusMsg.JCDbusMsg
    * ����: ��Ϣͷ����������Ĺ��캯��
    *
    * ����:
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/04/02 16:55:56, lys ��������
    *
    ******************************************************************************/
    JCDbusMsg(const JCDbusMsgInfo &tInfo);

    /******************************************************************************
    * ������:JCDbusMsg.JCDbusMsg
    * ����: ���ƹ��캯��
    *
    * ����:
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/04/02 16:56:43, lys ��������
    *
    ******************************************************************************/
	JCDbusMsg(const JCDbusMsg &tMsg);
	JCDbusMsg &operator = (const JCDbusMsg &tMsg);
	virtual ~JCDbusMsg();

    /******************************************************************************
    * ������:JCDbusMsg.LinkToHead
    * ����: ����Ϣ���ӵ�ָ����ϢΪ����ͷ�������ͷ��(��ָ����Ϣ֮��)
    *
    * ����:
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/04/02 16:57:25, lys ��������
    *
    ******************************************************************************/
	void LinkToHead(JCDbusMsg &tMsg);

    /******************************************************************************
    * ������:JCDbusMsg.LinkToHead
    * ����: ͨ����Ϣ�ṹ�����ӽڵ�����,����ͬ��
    *
    * ����:
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/04/02 16:58:39, lys ��������
    *
    ******************************************************************************/
	void LinkToHead(JCDoubleLinkNode &tNode);

    /******************************************************************************
    * ������:JCDbusMsg.LinkToTail
    * ����: ����Ϣ���ӵ�ָ����ϢΪ����ͷ�������ͷ��(��ָ����Ϣ֮ǰ)
    *
    * ����:
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/04/02 16:59:24, lys ��������
    *
    ******************************************************************************/
	void LinkToTail(JCDbusMsg &tMsg);

    /******************************************************************************
    * ������:JCDbusMsg.LinkToTail
    * ����: ͨ����Ϣ�ṹ�����ӽڵ�����,����ͬ��
    *
    * ����:
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/04/02 17:0:13, lys ��������
    *
    ******************************************************************************/
	void LinkToTail(JCDoubleLinkNode &tNode);

    /******************************************************************************
    * ������:JCDbusMsg.BreakLink
    * ����: �Ͽ���Ϣ����,����Ϣ������ȡ��
    *
    * ����:
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/04/02 17:0:41, lys ��������
    *
    ******************************************************************************/
	void BreakLink();

    /******************************************************************************
    * ������:JCDbusMsg.SetMsgInfo
    * ����: ������Ϣͷ
    *
    * ����:
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/04/02 17:1:26, lys ��������
    *
    ******************************************************************************/
	void SetMsgInfo(const JCDbusMsgInfo &tInfo);

    /******************************************************************************
    * ������:JCDbusMsg.MsgInfo
    * ����: ��ȡ��Ϣͷ�ṹ
    *
    * ����:
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/04/02 17:1:50, lys ��������
    *
    ******************************************************************************/
	JCDbusMsgInfo &MsgInfo();

    /******************************************************************************
    * ������:JCDbusMsg.SetMsgData
    * ����: ������Ϣ����
    *
    * ����:
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/04/02 17:2:12, lys ��������
    *
    ******************************************************************************/
	void SetMsgData(const JCDbusMsgData &tData);

    /******************************************************************************
    * ������:JCDbusMsg.MsgData
    * ����: ��ȡ��Ϣ����
    *
    * ����:
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/04/02 17:2:32, lys ��������
    *
    ******************************************************************************/
	JCDbusMsgData &MsgData();

	unsigned int GetRecvDaemonId();
	unsigned int GetSendDaemonId();
	unsigned int GetRecvModuleId();
	unsigned int GetSendModuleId();
	unsigned int GetMessageId();
	unsigned int GetClientId();

    /******************************************************************************
    * ������:JCDbusMsg.ShowMassage
    * ����: ��ʾ��Ϣ��Ϣ,��������
    *
    * ����:
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/04/02 17:2:55, lys ��������
    *
    ******************************************************************************/
	void ShowMassage();

	JCDoubleLinkNode m_tLinkNode;
	JCDbusMsgInfo m_tMsgInfo;
	JCDbusMsgData m_tMsgData;
};

#endif /* _JCDBUSMSG_H_ */

