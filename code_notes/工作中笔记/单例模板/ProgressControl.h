
#pragma once

#include "Tools/Singleton.h"
#include <boost/function.hpp>
//ˢ�»ص�����
typedef boost::function<void ()> fun_UpdateFunc;
class CLoadLib;
class CDataPoProgressDlg;
class AFX_EXT_CLASS CProgressControl:
	public Singleton<CProgressControl>
{
public:
	CProgressControl();
	~CProgressControl();

public:
	/**
	* ����:	�������Ƿ��Ѵ���
	* ȫ��:	CProgressControl::IsProgressRun
	* ����:	public 
	* @���� 	2008-12-30
	* @����  iuhiao
	* @�������� 	BOOL
	*/
	BOOL IsProgressRun();
	//************************************
	// Method:    ��ʼ������
	// FullName:  CProgressControl::BeginProgress
	// Access:    public 
	// Returns:   void
	// Qualifier:
	//************************************
	void BeginProgress();

	//************************************
	// Method:    ����������
	// FullName:  CProgressControl::EndProgress
	// Access:    public static 
	// Returns:   void
	// Qualifier:
	//************************************
	BOOL EndProgress();

	//************************************
	// Method:    �󶨶��ļ�����
	// FullName:  CProgressControl::BindReadFunc
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: fun_CaseReadFunc readFunc
	//************************************
	void BindReadFunc(boost::function<BOOL ()> readFunc);

	//************************************
	// Method:    ��ˢ�º���
	// FullName:  CProgressControl::BindUpdateFunc
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: fun_UpdateFunc updateFunc
	//************************************
	void BindUpdateFunc(fun_UpdateFunc updateFunc);

	//************************************
	// Method:    ��ʼ������
	// FullName:  CProgressControl::BeginReadCase
	// Access:    public 
	// Returns:   void
	// Qualifier:
	//************************************
	void BeginReadCase();

	/************************************
	* ��������:    ���ý�����
	* ȫ������:    CProgressControl::StepProgress
	* ����Ȩ��:    public 
	* ��������:    void

	* �Ρ�����:    int pos
	* �Ρ�����:    const CString titleInfo
	* ��������:    iuhiao
	************************************/
	void StepProgress(int pos , const CString fileInfo , const CString titleInfo);
	void StepProgress(const CString titleInfo);
	void StepProgress();

	/**
	* ����:	��Ӵ�����Ϣ
	* ȫ��:	CProgressControl::AddErrorInfo
	* ����:	public 
	* @����  iuhiao
	* @���� 	CString strError
	* @�������� 	void
	*/
	void AddErrorInfo(CString strError);

	/**
	* ����:	�������Զ�����
	* ȫ��:	CProgressControl::AutoRunProgress
	* ����:	public 
	* @���� 	2008-12-22
	* @����  iuhiao
	* @�������� 	void
	*/
	void AutoRunProgress();

	/**
	* ����:	��ֹ�Զ�����
	* ȫ��:	CDataPoProgressDlg::StopAutoProgress
	* ����:	public 
	* @���� 	2008-12-22
	* @����  iuhiao
	* @�������� 	void
	*/
	void StopAutoProgress();

private:
	//�������߳�
	HANDLE m_pThread;
	//�������Ի���
	CDataPoProgressDlg* m_progress;
	HWND m_hProgressWnd;
	//�������Ƿ��Ѵ���
	BOOL m_isProgressRun;
	//�Ƿ�������ˢ�º���
	BOOL m_bsetUpdateFunc;
};