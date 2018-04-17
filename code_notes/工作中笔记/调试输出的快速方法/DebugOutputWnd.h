#pragma once


// CDebugOutputWnd�����ڳ��򷢲���ʽ(����Release)��������ʱ��������
// ���ڴ�������ʱ��Debug�����Եú�����(̫����)

/* ʹ�÷���:

   *�����Ϣ��
		CString strInfo = "������Ϣ"
		CDebugOutputWnd::Output(strInfo);

   *�������ڳ����˳�ʱ����
		CDebugOutputWnd::DestoryDebugWindow();
*/

class CDebugOutputWnd : public CWnd
{
	DECLARE_DYNAMIC(CDebugOutputWnd)

public:
	static CDebugOutputWnd* ShowDebugWindow();
	static void CloseDebugWindow();
	static void Output(CString& strInfo);
	static void DestoryDebugWindow();
	virtual ~CDebugOutputWnd();

protected:
	CDebugOutputWnd();
	DECLARE_MESSAGE_MAP()

private:
	static CDebugOutputWnd* m_pDebugOutputWnd;
	static CRichEditCtrl* m_pRichEdit;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


