/******************************************************************************
* �ļ���: jcftpclient.h
* ����: FTP�ͻ���
* Copyright(c)2014-2016 JCDZ Co.,Ltd.
*
* �޸ļ�¼:
* --------------------
* v1.0   2014/12/19 9:30:20, lys �����ļ�
*
******************************************************************************/
#ifndef _JCFTPCLIENT_H_
#define _JCFTPCLIENT_H_

#include <string>
#include <vector>
#include "jcbase.h"
#include "jcnonecopy.h"


using namespace std;

typedef int (*FtpClientCallbackFunc)(unsigned int nTransferedBytes, void *pVoid);

struct NetBuf;

/******************************************************************************
* ������:JCFtpClient.JCFtpClient
* ����: FTP�ͻ���
*
* ����:
* ���:
* ����ֵ:
*
* �޸ļ�¼:
* --------------------
*    2014/12/26 18:51:54, lys ��������
*
******************************************************************************/
class DLL_EXPORT JCFtpClient : public JCNonecopy
{
public:
	enum ConnectMode
	{
		PASSIVE_MODE,
		PORT_MODE
	};

	enum TransMode
	{
		ASCII_MODE,
		BINARY_MODE
	};

	JCFtpClient();
	JCFtpClient(const string &strFtpIp, const string &strFtpPort = "21");
	virtual ~JCFtpClient();

	/******************************************************************************
    * ������:JCFtpClient.Connect
    * ����: ����FTP������
    *
    * ����: IP�Ͷ˿�
    * ���: strResponse����˷��ص�Ӧ����Ϣ
    * ����ֵ: true �ɹ� false ʧ��
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/12/26 18:52:33, lys ��������
    *
    ******************************************************************************/
	bool Connect(const string &strFtpIp, const string &strFtpPort, string &strResponse);

    /******************************************************************************
    * ������:JCFtpClient.Connect
    * ����: ����FTP������
    *
    * ����:
    * ���: strResponse����˷��ص�Ӧ����Ϣ
    * ����ֵ: true �ɹ� false ʧ��
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/12/26 18:52:33, lys ��������
    *
    ******************************************************************************/
	bool Connect(string &strResponse);

    /******************************************************************************
    * ������:JCFtpClient.Disconnect
    * ����: -
    *
    * ����:
    * ���:strResponse����˷��ص�Ӧ����Ϣ
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/12/26 18:53:38, lys ��������
    *
    ******************************************************************************/
	void Disconnect(string &strResponse);

    /******************************************************************************
    * ������:JCFtpClient.Login
    * ����: ��¼
    *
    * ����:
    * ���:strResponse����˷��ص�Ӧ����Ϣ
    * ����ֵ:true �ɹ� false ʧ��
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/12/26 18:53:38, lys ��������
    *
    ******************************************************************************/
	bool Login(const string &strUser, const string &strPsw, string &strResponse);

    /******************************************************************************
    * ������:JCFtpClient.SetConnectMode
    * ����: ����FTP����ģʽ(Ĭ�ϱ���ģʽ)
    *
    * ����:
    * ���:
    * ����ֵ:true �ɹ� false ʧ��
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/12/26 18:53:38, lys ��������
    *
    ******************************************************************************/
	bool SetConnectMode(ConnectMode eMode);

    /******************************************************************************
    * ������:JCFtpClient.RemoteSysType
    * ����: ��ȡFTP���������ڵ�ϵͳ����
    *
    * ����:
    * ���: strSysType��ϵͳ���͵������ֶ� strResponse����˷��ص�Ӧ����Ϣ
    * ����ֵ:true �ɹ� false ʧ��
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/12/26 18:53:38, lys ��������
    *
    ******************************************************************************/
	bool RemoteSysType(string &strSysType, string &strResponse);

    /******************************************************************************
    * ������:JCFtpClient.Changedir
    * ����: ��ת��ָ��Ŀ¼
    *
    * ����:
    * ���: strResponse����˷��ص�Ӧ����Ϣ
    * ����ֵ:true �ɹ� false ʧ��
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/12/26 18:53:38, lys ��������
    *
    ******************************************************************************/
	bool Changedir(const string &strDestPath, string &strResponse);

    /******************************************************************************
    * ������:JCFtpClient.ChangeDirUp
    * ����: ��ת����ǰĿ¼����һ��Ŀ¼
    *
    * ����:
    * ���: strResponse����˷��ص�Ӧ����Ϣ
    * ����ֵ:true �ɹ� false ʧ��
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/12/26 18:53:38, lys ��������
    *
    ******************************************************************************/
	bool ChangeDirUp(string &strResponse);

    /******************************************************************************
    * ������:JCFtpClient.MakeDir
    * ����: ����Ŀ¼, ������·��ʱ�ڵ�ǰĿ¼�´���(Ŀ¼��ʽ/a/b/c)
    *
    * ����:
    * ���: strResponse����˷��ص�Ӧ����Ϣ
    * ����ֵ:true �ɹ� false ʧ��
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/12/26 18:53:38, lys ��������
    *
    ******************************************************************************/
	bool MakeDir(const string &strMakePath, string &strResponse);

    /******************************************************************************
    * ������:JCFtpClient.RemoveDir
    * ����: �Ƴ�Ŀ¼, ������·��ʱ�ڵ�ǰĿ¼���Ƴ�(Ŀ¼��ʽ/a/b/c)
    *
    * ����:
    * ���: strResponse����˷��ص�Ӧ����Ϣ
    * ����ֵ:true �ɹ� false ʧ��
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/12/26 18:53:38, lys ��������
    *
    ******************************************************************************/
	bool RemoveDir(const string &strRmPath, string &strResponse);

    /******************************************************************************
    * ������:JCFtpClient.RemoveDir
    * ����: ��ȡ��ǰ·��
    *
    * ����:
    * ���: strResponse����˷��ص�Ӧ����Ϣ
    * ����ֵ:true �ɹ� false ʧ��
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/12/26 18:53:38, lys ��������
    *
    ******************************************************************************/
	bool CurrentDir(string &strCurrentPath, string &strResponse);

    /******************************************************************************
    * ������:JCFtpClient.ListDir
    * ����: ��ȡָ��·���µ�Ŀ¼�б�(ֻ����Ŀ¼,�������ļ�,ʹ��FTP NLST����,�еķ�������֧�ָ�����)
    *       , ��ָ��Ŀ¼������оٵ�ǰĿ¼
    * ����:
    * ���: strResponse����˷��ص�Ӧ����Ϣ
    * ����ֵ:true �ɹ� false ʧ��
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/12/26 18:53:38, lys ��������
    *
    ******************************************************************************/
	bool ListDir(const string &strRemotePath, vector<string> &tDirSet, string &strResponse);

    /******************************************************************************
    * ������:JCFtpClient.ListDirDetail
    * ����: ��ȡָ��·���µ�Ŀ¼���ļ��б�(ʹ��FTP LIST��MLSD����), ��ָ��Ŀ¼
    *       ʱ�оٵ�ǰĿ¼�µ�Ŀ¼(��ָ��Ŀ¼��Ŀ¼���ַ���Ϊ���ַ���)
    * ����:
    * ���: strResponse����˷��ص�Ӧ����Ϣ
    * ����ֵ:true �ɹ� false ʧ��
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/12/26 18:53:38, lys ��������
    *
    ******************************************************************************/
	bool ListDirDetail(const string &strRemotePath, vector<string> &tDirSet, string &strResponse);
	//bool ListFile(const string &strRemotePath, vector<string> &tFileSet, string &strResponse);

    /******************************************************************************
    * ������:JCFtpClient.GetFile
    * ����: ���ط��������ļ�������
    *
    * ����:eMode ����ģʽ, �ַ�ģʽ��������ģʽ
    * ���: strResponse����˷��ص�Ӧ����Ϣ
    * ����ֵ:true �ɹ� false ʧ��
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/12/26 18:53:38, lys ��������
    *
    ******************************************************************************/
	bool GetFile(const string &strLocalFile, const string &strRemoteFile, TransMode eMode, string &strResponse);

    /******************************************************************************
    * ������:JCFtpClient.PutFile
    * ����: �ϴ������ļ���������
    *
    * ����:eMode ����ģʽ, �ַ�ģʽ��������ģʽ
    * ���: strResponse����˷��ص�Ӧ����Ϣ
    * ����ֵ:true �ɹ� false ʧ��
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/12/26 18:53:38, lys ��������
    *
    ******************************************************************************/
    bool PutFile(const string &strLocalFile, const string &strRemoteFile, TransMode eMode, string &strResponse);

    /******************************************************************************
    * ������:JCFtpClient.DeleteFile
    * ����: ɾ�����������ļ�
    *
    * ����:
    * ���: strResponse����˷��ص�Ӧ����Ϣ
    * ����ֵ:true �ɹ� false ʧ��
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/12/26 18:53:38, lys ��������
    *
    ******************************************************************************/
    bool DelFile(const string &strRemoteFile, string &strResponse);

    /******************************************************************************
    * ������:JCFtpClient.RenameFile
    * ����: ��������������ָ���ļ�
    *
    * ����:
    * ���: strResponse����˷��ص�Ӧ����Ϣ
    * ����ֵ:true �ɹ� false ʧ��
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/12/26 18:53:38, lys ��������
    *
    ******************************************************************************/
    bool RenameFile(const string &strCurrentName, const string &strDesireName, string &strResponse);

    /******************************************************************************
    * ������:JCFtpClient.RemoteFileSize
    * ����: ��ȡ��������ָ���ļ���С
    *
    * ����:
    * ���: strResponse����˷��ص�Ӧ����Ϣ
    * ����ֵ:true �ɹ� false ʧ��
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/12/26 18:53:38, lys ��������
    *
    ******************************************************************************/
    bool RemoteFileSize(const string &strRemoteFile, unsigned int &nSize, TransMode eMode, string &strResponse);

    /******************************************************************************
    * ������:JCFtpClient.RegisterCallBack
    * ����: ΪFTP����ע��ص�����,��ÿ����nTriggerBytes�ֽڻ�ÿ��nTriggerTimeʱ��ʱ��
    *       �����Դ���, ���ص���������0, �����ڵ����˳�(һ�����ڴ�����ļ���ʾ������)
    * ����:
    * ���:
    * ����ֵ:true �ɹ� false ʧ��
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/12/26 18:53:38, lys ��������
    *
    ******************************************************************************/
	bool RegisterCallBack(FtpClientCallbackFunc pCallBack, void *pVoid, unsigned int nTriggerBytes, unsigned int nTriggerTime);

	/******************************************************************************
    * ������:JCFtpClient.UnregisterCallBack
    * ����: ���ע��Ļص�����, �ص������ʧЧ
	*
    * ����:
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/12/26 18:53:38, lys ��������
    *
    ******************************************************************************/
	void UnregisterCallBack();

    /******************************************************************************
    * ������:JCFtpClient.FtpIp
    * ����: ��ȡFTP��������ַ
    *
    * ����:
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/12/26 19:8:49, lys ��������
    *
    ******************************************************************************/
	string &FtpIp();

    /******************************************************************************
    * ������:JCFtpClient.FtpPort
    * ����: ��ȡFTP�������˿ں�
    *
    * ����:
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/12/26 19:8:49, lys ��������
    *
    ******************************************************************************/
	string &FtpPort();

    /******************************************************************************
    * ������:JCFtpClient.FtpUser
    * ����: ��ȡFTP�������û���
    *
    * ����:
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/12/26 19:8:49, lys ��������
    *
    ******************************************************************************/
	string &FtpUser();

    /******************************************************************************
    * ������:JCFtpClient.FtpUser
    * ����: ��ȡFTP����������
    *
    * ����:
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/12/26 19:8:49, lys ��������
    *
    ******************************************************************************/
	string &FtpUserPsw();

	static int FtpClientCallBack(NetBuf *ctl, unsigned int xfered, void *arg);

private:
	bool IsFtpCtrlConnValid();
	char TransferMode(TransMode eMode);
	string LastFtpResponse();

private:
	string m_strFtpIp;
	string m_strFtpPort;
	string m_strUser;
	string m_strPsw;
	NetBuf *m_pFtpCtrlConn; /*�����������*/
	NetBuf *m_pFtpDataConn; /*���ݴ�������*/
	FtpClientCallbackFunc m_pCallBack;
	void *m_pCallBackArg;
};

class DLL_EXPORT JCFtpLineParse
{
	enum FILE_TYPE
	{
		eUnkonwn,
		eFile,
		eDIR,
	};
public:
	JCFtpLineParse();
	~JCFtpLineParse();
	bool ParseLine(const string &strLine);
	string GetFileDate();
	string GetFileType();
	unsigned int GetFileSize();
	string GetFileName();
	string GetFileAttr();
	vector<string> GetFileGroup();
protected: 
	void MapInit();
	void FilterLeftSpace(unsigned int &nPos,const string &strLine);
	/* linux */
	bool ParseLineForUnix(const string &strLine);
	bool ParseFileType(unsigned int &nPos,const string &strLine,string &strType);
	bool ParseFileAttr(unsigned int &nPos,const string &strLine,string &strAttr);
	bool ParseFileGroup(unsigned int &nPos,const string &strLine,vector<string> &strGroup);
	bool ParseFileSize(unsigned int &nPos,const string &strLine,unsigned int &nSize);
	bool ParseFileDate(unsigned int &nPos,const string &strLine,string &strDate);
	bool ParseFileName(unsigned int &nPos,const string &strLine,string &strName);
	
	/* windows */
	bool ParseLineForDos(const string &strLine);
	bool ParseFileDateForDos(unsigned int &nPos,const string &strLine,string &strDate);
	bool ParseFileSizeForDos(unsigned int &nPos,const string &strLine,unsigned int &nSize);
	bool ParseFileTypeForDos(unsigned int &nPos,const string &strLine,string &strType);
	int  GetTokenForDos(unsigned int nPos,const string &strLine);
private:
	string m_strFileDate;
	unsigned int m_nFileSize;
	string m_strFileType ;
	string m_strFileName ;
	string m_strFileAttr ;
	vector<string> m_strFileGroupVec ;
	map<string,int> m_MonthNamesMap ;
};
#endif /* _JCFTPCLIENT_H_ */



