/*------------------------------------------------------------------------------------------------------
* �ļ�����						LoadLib.h
* ���ܣ�						����DLL,�Էº�����ʽ����DLL��ĺ���,���֧��10����
* ���ߣ�						---
* ע��:							ʹ�ø������DLLʱһ��Ҫʹ��try...catch(runtime_error)....��䲶׽�쳣
* ��������:					---
* ����޸����ڣ�			---
* ʹ��˵��:						
*								try
*								{
*									CLoadLib lib("DLL·��");
*									// ��CLoadLib lib;
*									// lib.LoadLib("DLL·��");
*									lib.call<����ֵ����, ����Լ��>("���ú�������", �����б�(0��10��));
*								}
*								catch(runtime_error e)
*								{
*									AfxMessageBox(e.what());
*								}
*								catch(...)
*								{
*								}
*								// ����Լ����ö��call_convention_e��call_convention_e_
* ʹ�ð�����
	CLoadLib eclDlgLib;
	std::map<CString,KeyInfo>  mapKeys;
	std::map<CString,std::set<CString>> allKeys;
	try
	{
		eclDlgLib.LoadLib("DataEclipseDlg.dll");
		//��ȡ���йؼ�����Ϣ
		eclDlgLib.call<void,_std_>(_T("GetMapKeys"),&mapKeys,&allKeys);
	}
	catch(std::runtime_error e)
	{
		AfxMessageBox(e.what());
		return FALSE;
	}
-----------------------------------------------------------------------------------------------------*/

#pragma once

#include <iostream>
#include <string>

template<class String>
String get_app_path()
{
	char chPath[MAX_PATH];
	//CString strPath;
	int nCount;

	GetModuleFileName(NULL,chPath,MAX_PATH);	//�õ�ִ���ļ�����ȫ·��
	strPath = chPath;
	nCount = strPath.ReverseFind('\\');
	strPath = strPath.Mid(0, nCount + 1);
	return strPath;
}

enum call_convention_e_ { _std_ = 0, _cd_ = 1, _fast_ = 2 };
enum call_convention_e  { _stdcall_ = _std_, _cdecl_ = _cd_, _fastcall_ = _fast_ };

class CLoadLib
{
public:
	//////////////////////////////////////////////////////////////////////////
	// ������,��һ������ӳ�䵽һ���ͱ�
	template<int index> struct type {};

public:
	CLoadLib()
	{
		m_bDetach = false;
		m_hInst = NULL;
	}

	CLoadLib(LPCTSTR lpLibFileName)				// ���캯��,����HLoadLibrary����DLL
	{
		m_bDetach = false;
		m_hInst = LoadLib(lpLibFileName);
	}

	~CLoadLib(void)
	{
		if(!m_bDetach)
			FreeLibrary(m_hInst);
		m_hInst = NULL;
	}

	HINSTANCE Detach(void)
	{
		m_bDetach = true;
		return m_hInst;
	}

	HINSTANCE LoadLib(LPCTSTR lpLibFileName)	// ����DLL
	{
		if(m_hInst != NULL)
		{
			m_bDetach = false;
			FreeLibrary(m_hInst);
			m_hInst = NULL;
		}

		m_hInst = ::LoadLibrary(lpLibFileName);
		if(m_hInst == NULL)
		{
			throw std::runtime_error(std::string(lpLibFileName) + "\n����DLLʧ�ܣ���ȷ���Ƿ��ڵ�ǰĿ¼��");
		}

		return m_hInst;
	}

	template<class FunType>
		FunType addr(LPCTSTR lpProcName)		// �õ�ָ���������͵ĵ�ַ
	{
		FunType funaddr = (FunType)NULL;

		if(m_hInst == NULL)
		{
			throw std::runtime_error("����û�м���DLL");
		}
		else
		{
			funaddr = (FunType)::GetProcAddress(m_hInst, lpProcName);
			if(funaddr == (FunType)NULL)
			{
				throw std::runtime_error("���ú���ʧ�ܣ���ȷ���д˺���");
			}
		}

		return funaddr;
	}

public:
	//////////////////////////////////////////////////////////////////////////
	// ����ӿ�
	template<class RetType, int CallCon>
		RetType call(LPCTSTR lpProcName)
	{
		return call<RetType>(lpProcName, type<CallCon>());
	}

	// һ������
	template<class RetType, int CallCon, class T1>
		RetType call(LPCTSTR lpProcName, T1 t1)
	{
		return call<RetType>(lpProcName, t1, type<CallCon>());
	}

	// ��������
	template<class RetType, int CallCon, class T1, class T2>
		RetType call(LPCTSTR lpProcName, T1 t1, T2 t2)
	{
		return call<RetType>(lpProcName, t1, t2, type<CallCon>());
	}

	// ��������
	template<class RetType, int CallCon, class T1, class T2, class T3>
		RetType call(LPCTSTR lpProcName, T1 t1, T2 t2, T3 t3)
	{
		return call<RetType>(lpProcName, t1, t2, t3, type<CallCon>());
	}

	// �ĸ�����
	template<class RetType, int CallCon, class T1, class T2, class T3, class T4>
		RetType call(LPCTSTR lpProcName, T1 t1, T2 t2, T3 t3, T4 t4)
	{
		return call<RetType>(lpProcName, t1, t2, t3, t4, type<CallCon>());
	}

	// �������
	template<class RetType, int CallCon, class T1, class T2, class T3, class T4, class T5>
		RetType call(LPCTSTR lpProcName, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
	{
		return call<RetType>(lpProcName, t1, t2, t3, t4, t5, type<CallCon>());
	}

	// ��������
	template<class RetType, int CallCon, class T1, class T2, class T3, class T4, class T5, class T6>
		RetType call(LPCTSTR lpProcName, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6)
	{
		return call<RetType>(lpProcName, t1, t2, t3, t4, t5, t6, type<CallCon>());
	}

	// �߸�����
	template<class RetType, int CallCon, class T1, class T2, class T3, class T4, class T5, class T6, class T7>
		RetType call(LPCTSTR lpProcName, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7)
	{
		return call<RetType>(lpProcName, t1, t2, t3, t4, t5, t6, t7, type<CallCon>());
	}	

	// �˸�����
	template<class RetType, int CallCon, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
		RetType call(LPCTSTR lpProcName, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8)
	{
		return call<RetType>(lpProcName, t1, t2, t3, t4, t5, t6, t7, t8, type<CallCon>());
	}

	// �Ÿ�����
	template<class RetType, int CallCon, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
		RetType call(LPCTSTR lpProcName, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8, T9 t9)
	{
		return call<RetType>(lpProcName, t1, t2, t3, t4, t5, t6, t7, t8, t9, type<CallCon>());
	}

	// ʮ������
	template<class RetType, int CallCon, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10>
		RetType call(LPCTSTR lpProcName, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8, T9 t9, T10 t10)
	{
		return call<RetType>(lpProcName, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, type<CallCon>());
	}

private:
	//////////////////////////////////////////////////////////////////////////
	// ��__stdcall����Լ����ʵ��
	template<class RetType>
		RetType call(LPCTSTR lpProcName, type<_stdcall_>)
	{
		typedef RetType (__stdcall* LPProcName)();
		return addr<LPProcName>(lpProcName)();
	}

	// һ������
	template<class RetType, class T1>
		RetType call(LPCTSTR lpProcName, T1& t1, type<_stdcall_>)
	{
		typedef RetType (__stdcall* LPProcName)(T1);
		return addr<LPProcName>(lpProcName)(t1);
	}	

	// ��������
	template<class RetType, class T1, class T2>
		RetType call(LPCTSTR lpProcName, T1& t1, T2& t2, type<_stdcall_>)
	{
		typedef RetType (__stdcall* LPProcName)(T1, T2);
		return addr<LPProcName>(lpProcName)(t1, t2);
	}

	// ��������
	template<class RetType, class T1, class T2, class T3>
		RetType call(LPCTSTR lpProcName, T1& t1, T2& t2, T3& t3, type<_stdcall_>)
	{
		typedef RetType (__stdcall* LPProcName)(T1, T2, T3);
		return addr<LPProcName>(lpProcName)(t1, t2, t3);
	}

	// �ĸ�����
	template<class RetType, class T1, class T2, class T3, class T4>
		RetType call(LPCTSTR lpProcName, T1& t1, T2& t2, T3& t3, T4& t4, type<_stdcall_>)
	{
		typedef RetType (__stdcall* LPProcName)(T1, T2, T3, T4);
		return addr<LPProcName>(lpProcName)(t1, t2, t3, t4);
	}

	// �������
	template<class RetType, class T1, class T2, class T3, class T4, class T5>
		RetType call(LPCTSTR lpProcName, T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, type<_stdcall_>)
	{
		typedef RetType (__stdcall* LPProcName)(T1, T2, T3, T4, T5);
		return addr<LPProcName>(lpProcName)(t1, t2, t3, t4, t5);
	}

	// ��������
	template<class RetType, class T1, class T2, class T3, class T4, class T5, class T6>
		RetType call(LPCTSTR lpProcName, T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, T6& t6, type<_stdcall_>)
	{
		typedef RetType (__stdcall* LPProcName)(T1, T2, T3, T4, T5, T6);
		return addr<LPProcName>(lpProcName)(t1, t2, t3, t4, t5, t6);
	}

	// �߸�����
	template<class RetType, class T1, class T2, class T3, class T4, class T5, class T6, class T7>
		RetType call(LPCTSTR lpProcName, T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, T6& t6, T7& t7, type<_stdcall_>)
	{
		typedef RetType (__stdcall* LPProcName)(T1, T2, T3, T4, T5, T6, T7);
		return addr<LPProcName>(lpProcName)(t1, t2, t3, t4, t5, t6, t7);
	}	

	// �˸�����
	template<class RetType, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
		RetType call(LPCTSTR lpProcName, T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, T6& t6, T7& t7, T8& t8, type<_stdcall_>)
	{
		typedef RetType (__stdcall* LPProcName)(T1, T2, T3, T4, T5, T6, T7, T8);
		return addr<LPProcName>(lpProcName)(t1, t2, t3, t4, t5, t6, t7, t8);
	}

	// �Ÿ�����
	template<class RetType, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
		RetType call(LPCTSTR lpProcName, T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, T6& t6, T7& t7, T8& t8, T9& t9, type<_stdcall_>)
	{
		typedef RetType (__stdcall* LPProcName)(T1, T2, T3, T4, T5, T6, T7, T8, T9);
		return addr<LPProcName>(lpProcName)(t1, t2, t3, t4, t5, t6, t7, t8, t9);
	}

	// ʮ������
	template<class RetType, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10>
		RetType call(LPCTSTR lpProcName, T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, T6& t6, T7& t7, T8& t8, T9& t9, T10& t10, type<_stdcall_>)
	{
		typedef RetType (__stdcall* LPProcName)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10);
		return addr<LPProcName>(lpProcName)(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10);
	}

	//////////////////////////////////////////////////////////////////////////
	// ��__cdecl����Լ����ʵ��
	template<class RetType>
		RetType call(LPCTSTR lpProcName, type<_cdecl_>)
	{
		typedef RetType (__cdecl* LPProcName)();
		return addr<LPProcName>(lpProcName)();
	}

	// һ������
	template<class RetType, class T1>
		RetType call(LPCTSTR lpProcName, T1& t1, type<_cdecl_>)
	{
		typedef RetType (__cdecl* LPProcName)(T1);
		return addr<LPProcName>(lpProcName)(t1);
	}	

	// ��������
	template<class RetType, class T1, class T2>
		RetType call(LPCTSTR lpProcName, T1& t1, T2& t2, type<_cdecl_>)
	{
		typedef RetType (__cdecl* LPProcName)(T1, T2);
		return addr<LPProcName>(lpProcName)(t1, t2);
	}

	// ��������
	template<class RetType, class T1, class T2, class T3>
		RetType call(LPCTSTR lpProcName, T1& t1, T2& t2, T3& t3, type<_cdecl_>)
	{
		typedef RetType (__cdecl* LPProcName)(T1, T2, T3);
		return addr<LPProcName>(lpProcName)(t1, t2, t3);
	}

	// �ĸ�����
	template<class RetType, class T1, class T2, class T3, class T4>
		RetType call(LPCTSTR lpProcName, T1& t1, T2& t2, T3& t3, T4& t4, type<_cdecl_>)
	{
		typedef RetType (__cdecl* LPProcName)(T1, T2, T3, T4);
		return addr<LPProcName>(lpProcName)(t1, t2, t3, t4);
	}

	// �������
	template<class RetType, class T1, class T2, class T3, class T4, class T5>
		RetType call(LPCTSTR lpProcName, T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, type<_cdecl_>)
	{
		typedef RetType (__cdecl* LPProcName)(T1, T2, T3, T4, T5);
		return addr<LPProcName>(lpProcName)(t1, t2, t3, t4, t5);
	}

	// ��������
	template<class RetType, class T1, class T2, class T3, class T4, class T5, class T6>
		RetType call(LPCTSTR lpProcName, T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, T6& t6, type<_cdecl_>)
	{
		typedef RetType (__cdecl* LPProcName)(T1, T2, T3, T4, T5, T6);
		return addr<LPProcName>(lpProcName)(t1, t2, t3, t4, t5, t6);
	}

	// �߸�����
	template<class RetType, class T1, class T2, class T3, class T4, class T5, class T6, class T7>
		RetType call(LPCTSTR lpProcName, T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, T6& t6, T7& t7, type<_cdecl_>)
	{
		typedef RetType (__cdecl* LPProcName)(T1, T2, T3, T4, T5, T6, T7);
		return addr<LPProcName>(lpProcName)(t1, t2, t3, t4, t5, t6, t7);
	}	

	// �˸�����
	template<class RetType, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
		RetType call(LPCTSTR lpProcName, T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, T6& t6, T7& t7, T8& t8, type<_cdecl_>)
	{
		typedef RetType (__cdecl* LPProcName)(T1, T2, T3, T4, T5, T6, T7, T8);
		return addr<LPProcName>(lpProcName)(t1, t2, t3, t4, t5, t6, t7, t8);
	}

	// �Ÿ�����
	template<class RetType, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
		RetType call(LPCTSTR lpProcName, T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, T6& t6, T7& t7, T8& t8, T9& t9, type<_cdecl_>)
	{
		typedef RetType (__cdecl* LPProcName)(T1, T2, T3, T4, T5, T6, T7, T8, T9);
		return addr<LPProcName>(lpProcName)(t1, t2, t3, t4, t5, t6, t7, t8, t9);
	}

	// ʮ������
	template<class RetType, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10>
		RetType call(LPCTSTR lpProcName, T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, T6& t6, T7& t7, T8& t8, T9& t9, T10& t10, type<_cdecl_>)
	{
		typedef RetType (__cdecl* LPProcName)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10);
		return addr<LPProcName>(lpProcName)(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10);
	}

	//////////////////////////////////////////////////////////////////////////
	// ��__fastcall����Լ����ʵ��
	template<class RetType>
		RetType call(LPCTSTR lpProcName, type<_fastcall_>)
	{
		typedef RetType (__fastcall* LPProcName)();
		return addr<LPProcName>(lpProcName)();
	}

	// һ������
	template<class RetType, class T1>
		RetType call(LPCTSTR lpProcName, T1& t1, type<_fastcall_>)
	{
		typedef RetType (__fastcall* LPProcName)(T1);
		return addr<LPProcName>(lpProcName)(t1);
	}	

	// ��������
	template<class RetType, class T1, class T2>
		RetType call(LPCTSTR lpProcName, T1& t1, T2& t2, type<_fastcall_>)
	{
		typedef RetType (__fastcall* LPProcName)(T1, T2);
		return addr<LPProcName>(lpProcName)(t1, t2);
	}

	// ��������
	template<class RetType, class T1, class T2, class T3>
		RetType call(LPCTSTR lpProcName, T1& t1, T2& t2, T3& t3, type<_fastcall_>)
	{
		typedef RetType (__fastcall* LPProcName)(T1, T2, T3);
		return addr<LPProcName>(lpProcName)(t1, t2, t3);
	}

	// �ĸ�����
	template<class RetType, class T1, class T2, class T3, class T4>
		RetType call(LPCTSTR lpProcName, T1& t1, T2& t2, T3& t3, T4& t4, type<_fastcall_>)
	{
		typedef RetType (__fastcall* LPProcName)(T1, T2, T3, T4);
		return addr<LPProcName>(lpProcName)(t1, t2, t3, t4);
	}

	// �������
	template<class RetType, class T1, class T2, class T3, class T4, class T5>
		RetType call(LPCTSTR lpProcName, T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, type<_fastcall_>)
	{
		typedef RetType (__fastcall* LPProcName)(T1, T2, T3, T4, T5);
		return addr<LPProcName>(lpProcName)(t1, t2, t3, t4, t5);
	}

	// ��������
	template<class RetType, class T1, class T2, class T3, class T4, class T5, class T6>
		RetType call(LPCTSTR lpProcName, T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, T6& t6, type<_fastcall_>)
	{
		typedef RetType (__fastcall* LPProcName)(T1, T2, T3, T4, T5, T6);
		return addr<LPProcName>(lpProcName)(t1, t2, t3, t4, t5, t6);
	}

	// �߸�����
	template<class RetType, class T1, class T2, class T3, class T4, class T5, class T6, class T7>
		RetType call(LPCTSTR lpProcName, T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, T6& t6, T7& t7, type<_fastcall_>)
	{
		typedef RetType (__fastcall* LPProcName)(T1, T2, T3, T4, T5, T6, T7);
		return addr<LPProcName>(lpProcName)(t1, t2, t3, t4, t5, t6, t7);
	}	

	// �˸�����
	template<class RetType, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
		RetType call(LPCTSTR lpProcName, T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, T6& t6, T7& t7, T8& t8, type<_fastcall_>)
	{
		typedef RetType (__fastcall* LPProcName)(T1, T2, T3, T4, T5, T6, T7, T8);
		return addr<LPProcName>(lpProcName)(t1, t2, t3, t4, t5, t6, t7, t8);
	}

	// �Ÿ�����
	template<class RetType, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
		RetType call(LPCTSTR lpProcName, T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, T6& t6, T7& t7, T8& t8, T9& t9, type<_fastcall_>)
	{
		typedef RetType (__fastcall* LPProcName)(T1, T2, T3, T4, T5, T6, T7, T8, T9);
		return addr<LPProcName>(lpProcName)(t1, t2, t3, t4, t5, t6, t7, t8, t9);
	}

	// ʮ������
	template<class RetType, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10>
		RetType call(LPCTSTR lpProcName, T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, T6& t6, T7& t7, T8& t8, T9& t9, T10& t10, type<_fastcall_>)
	{
		typedef RetType (__fastcall* LPProcName)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10);
		return addr<LPProcName>(lpProcName)(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10);
	}

public:
	HINSTANCE m_hInst;
private:
	bool	  m_bDetach;
};