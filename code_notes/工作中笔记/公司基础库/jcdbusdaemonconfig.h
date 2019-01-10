/******************************************************************************
* �ļ���: jcdbusdaemonconfig.h
* ����: daemon���ý���
* Copyright(c)2014-2016 JCDZ Co.,Ltd.
*
* �޸ļ�¼:
* --------------------
* v1.0   2014/10/16 17:6:15, lys �����ļ�
*
******************************************************************************/
#ifndef _JCDBUSDAEMONCONFIG_H_
#define _JCDBUSDAEMONCONFIG_H_

#include <string>
#include <map>
#include "jcmacrotools.h"
#include "jcconfigdatabase.h"
#include "jcLock.hpp"

using namespace std;

class DLL_EXPORT JCDbusDaemonConfigItem : public JCParaBase
{
public:
	enum NetworkMode{CLIENT, SERVER, RENDEZVOUS};/*�ͻ���ģʽ �����ģʽ ���ģʽ(�Ե�)*/

	JCDbusDaemonConfigItem();
	JCDbusDaemonConfigItem(const string &strIp, unsigned int nPort
		, unsigned int nDaemonId, unsigned int nMode = RENDEZVOUS);
	JCDbusDaemonConfigItem(const JCDbusDaemonConfigItem &tItem);
	JCDbusDaemonConfigItem &operator=(const JCDbusDaemonConfigItem &tItem);
	virtual ~JCDbusDaemonConfigItem();

	DECLARE_MEMBER(string,       m_strDaemonIp,    0);
	DECLARE_MEMBER(unsigned int, m_nDaemonPort,    1);
	DECLARE_MEMBER(unsigned int, m_nDaemonMode,    2);
	DECLARE_MEMBER(unsigned int, m_nDaemonId,      3);/*daemonId��MacAddr������*/
	DECLARE_MEMBER(unsigned int, m_nUdtSocketId,   4);
	DECLARE_MEMBER(string,		 m_strMacAddr,     5);
	DECLARE_MEMBER(string,		 m_strSubnetMask,  6);
	DECLARE_MEMBER(string,		 m_strPCName,      7);
	END_DECLARE_MEMBER(8);

	unsigned long IntergeIp();

protected:
	string MemberInfo(unsigned int nMemberIndex, InfoType eInfoType);
	void SetMemberValue(unsigned int nMemberIndex, const string &strValue);
};


class DLL_EXPORT JCDbusDaemonConfig
{
public:
	JCDbusDaemonConfig();
	virtual ~JCDbusDaemonConfig();

    typedef map<unsigned int, JCDbusDaemonConfigItem> JCDbusDaemonMap;

	bool LoadDaemonConfig(const string &strFile);
	JCDbusDaemonConfigItem &LocalDaemon();
	void SetLocalDaemon(JCDbusDaemonConfigItem& configItem);
	unsigned int RemoteDaemonCount();
	bool GetRemoteDaemonByDaemonId(unsigned int nDaemonId, JCDbusDaemonConfigItem &tGetConfig);
	bool GetRemoteDaemonBySocketId(unsigned int nSocketId, JCDbusDaemonConfigItem &tGetConfig);
	bool GetFirstRemoteDaemon(JCDbusDaemonConfigItem &tGetConfig);/*���ݴ洢������Ż�ȡdaemon����, order��0��ʼ*/
	unsigned int AddDaemon(const JCDbusDaemonConfigItem &tGetConfig);
	unsigned int DeleteDaemon(unsigned int nDaemonId);
	unsigned int DeleteDaemonBySocketId(unsigned int nUdtSocketId);
	bool ClearRemoteDaemon();

private:
	JCDbusDaemonConfigItem m_tLocalDaemon;
	JCDbusDaemonMap m_tRemoteDaemons;
	JCCriticalSection m_tCs;
};



#endif /* _JCDBUSDAEMONCONFIG_H_ */

