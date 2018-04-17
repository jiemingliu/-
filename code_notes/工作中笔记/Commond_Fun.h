#pragma once
#include <iomanip>
#include <iostream>
#include <fstream>
#include "Ini.h"
#include "Path.h"

//��ȡӦ�ó���·��
inline CString GetAppPath()
{
	char chPath[MAX_PATH];
	CString strPath;
	int nCount;
	GetModuleFileName(NULL,chPath,MAX_PATH);	//�õ�ִ���ļ�����ȫ·��
	strPath = chPath;
	nCount = strPath.ReverseFind('\\');
	strPath = strPath.Mid(0, nCount + 1);
	return strPath;
}

//ִ��ģ��������
inline void RunEclCalc(const CString& strFileName)
{
	//ȡ��ģ����·��
	CString eclExePath;
	//��ȡ�����ļ�
	CIni iniFile(GetAppPath()+ _T("\\Option.ini"));
	if ( iniFile.IsSectionExist("Option") == TRUE)
	{//�ж��Ƿ������Ϣ
		eclExePath = iniFile.GetString("Option", "EclipseexePath", "");
	}

	if (eclExePath.IsEmpty())
	{
		AfxMessageBox("�������� ECLIPSE ģ����·��!");
		return;
	}

	CFileFind   find;  
	if(!find.FindFile(eclExePath))  
	{
		CString strMsg;
		strMsg.Format("ECLIPSE ģ����·��: %s ������,����������!",eclExePath);
		AfxMessageBox(strMsg);
		find.Close();
		return;
	} 
	find.Close();

	CPath path(strFileName);
	//�ļ�·��
	CString strFilePath = path.GetLocation();
	//�ļ�����
	CString strFileTittle = path.GetFileTitle();
	//////////////////////////////////////////////////////////////////////////
	CString strTempPathFile;
	GetTempPath(MAX_PATH,strTempPathFile.GetBuffer(MAX_PATH));
	strTempPathFile.ReleaseBuffer();
	strTempPathFile = strTempPathFile + "Launcher.bat";
	//������ı�
	std::ofstream out(strTempPathFile.GetBuffer());
	//дע����Ϣ
	out << "@ECHO off" << std::endl;
	out << "echo -------------------------------------------------------------------------" << std::endl;
	//д�����ʱ��
	COleDateTime time = COleDateTime::GetCurrentTime();
	CString strTime = "echo " + time.Format("%Y-%m-%d %H:%M:%S");
	out << strTime.GetBuffer() << std::endl;
	//д��ִ����Ϣ
	CString strRunInfo = "echo Eclipse dataset " + strFilePath;
	out << strRunInfo.GetBuffer() << std::endl;
	out << "echo -------------------------------------------------------------------------" << std::endl;
	//дִ�����û�����Ϣ$eclrc.bat
	out << "call $eclrc.bat" << std::endl;
	//д�л�Ŀ¼��Ϣ
	out << "cd " << strFilePath.GetBuffer() << std::endl;
	//дִ������
	//ִ�����
	CString strRun;
	strRun.Format("%s %s",eclExePath,strFileTittle);
	out << strRun.GetBuffer() << std::endl;
	//д��ر�����
	out << "exit" << std::endl;
	//�ر��ļ�
	out.close();
	CString strParRun;
	strParRun = "/k " + strTempPathFile;	
	//ִ��������
	ShellExecute(NULL,"open","cmd.exe",strParRun.GetBuffer(),strFilePath.GetBuffer(), SW_SHOWNORMAL);
}

inline void StartTools(CString& strToolName)
{
	CString strToolPath;
	//��ȡ�����ļ�
	CIni iniFile(GetAppPath()+ _T("\\Option.ini"));
	if ( iniFile.IsSectionExist("Option") == TRUE)
	{//�ж��Ƿ������Ϣ
		strToolPath = iniFile.GetString("Option",strToolName);
	}
	if (strToolPath.IsEmpty())
	{
		AfxMessageBox("û�����ó���·��,�����ڹ���ѡ��������·��!");
		return;
	}
	//�жϸ�·���Ƿ����
	CFileFind   find;  
	if(!find.FindFile(strToolPath))  
	{
		CString strMsg;
		strMsg.Format("����·��:%s������,����������!",strToolName);
		AfxMessageBox(strMsg);
		find.Close();
		return;
	} 
	find.Close();

	if (strToolName == "EclipseRunPath")
	{
		//���ò���
		CString strTool = strToolPath;
		strTool += "\\macros\\geoquest.exe";
		CString	strFilePath = strToolPath;
		strFilePath += "\\macros\\RUNECLIPSE.exe";
		//��ʼ
		CString strdir = strToolPath;
		strdir += "\\home"; 
		//ִ�г���
		ShellExecute(NULL,"open",strTool, strFilePath ,strdir, SW_SHOWNORMAL);
	}
	else
	{
		//ִ�г���
		ShellExecute(NULL,"open",strToolPath,NULL,NULL, SW_SHOWNORMAL);
	}
}

// �ж��ļ��е������Ƿ���Ч
inline BOOL IsFolderNameValid( const CString& strFolderName )
{
	if (strFolderName.IsEmpty())
	{
		return FALSE;
	}

	CString strTemp = strFolderName;

	if (strTemp.Find('/') == -1 && 
		strTemp.Find('\\') == -1 && 
		strTemp.Find(':') == -1 && 
		strTemp.Find('*') == -1 && 
		strTemp.Find('?') == -1 && 

		strTemp.Find('"') == -1 && 
		strTemp.Find('>') == -1 && 
		strTemp.Find('<') == -1 && 
		strTemp.Find('|') == -1)
	{
		strTemp.TrimLeft();
		strTemp.TrimRight();
		if (strFolderName == strTemp)
		{
			return TRUE;
		}
	}
	return FALSE;
}

// �ж�һ���ַ����Ƿ�����Ч���ļ�Ŀ¼
inline BOOL IsValidDir(CString& strPath)
{
	CPath path(strPath, TRUE);
	if (path.IsRelativePath())		// ���·��
	{
		strPath = path.GetAbsolutePath(GetAppPath());
		path.SetPath(strPath);
	}

	// ��Ч��·��
	if (!path.IsLocalPath() || strPath.GetAt(2) != '\\')
	{
		AfxMessageBox(_T("��Ч�Ĵ洢·��"));
		return FALSE;
	}

	CString strTemp = strPath.Right(strPath.GetLength() - 3);
	int nPos = strTemp.Find('\\');
	while (nPos != -1)
	{
		CString strMid = strTemp.Left(nPos);
		if (!IsFolderNameValid(strMid))
		{
			AfxMessageBox(_T("��Ч�Ĵ洢·��"));
			return FALSE;
		}	
		strTemp = strTemp.Right(strTemp.GetLength() - nPos - 1);
		nPos = strTemp.Find('\\');
	}

	if (!strTemp.IsEmpty() && !IsFolderNameValid(strTemp))
	{
		AfxMessageBox(_T("��Ч�Ĵ洢·��"));
		return FALSE;
	}

	// ·������������ʾ����
	if (!path.ExistLocation())
	{
		if (IDNO == AfxMessageBox(_T("·�������ڣ��Ƿ񴴽�"), MB_YESNO | MB_ICONASTERISK))
		{
			return FALSE;
		}
		SHCreateDirectoryEx(NULL, strPath, NULL);
	}

	if (strPath.Right(1) != _T("\\"))
	{
		strPath.Append("\\");
	}
	return TRUE;
}