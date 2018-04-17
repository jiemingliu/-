#pragma once

/**
* ����:	��ȡÿ������
* ȫ��:	GetDayAtMonth
* ����:	public 
* 
* @date	2008/08/14
* @author	flf
* @param	const COleDateTime & time
* @return	int
*/
inline int GetDayAtMonth(const COleDateTime* time )
{
	static COleDateTime newTime;
	ASSERT(time->GetStatus() == COleDateTime::valid);

	if (time->GetMonth() < 12)
	{
		//��Ϊ���µ�һ��
		newTime.SetDate(time->GetYear(),time->GetMonth()+1,1);
	}
	else
	{
		//��Ϊ���µ�һ��
		newTime.SetDate(time->GetYear()+1,1,1);
	}

	//��һ��
	COleDateTimeSpan span;
	span.SetDateTimeSpan(1,0,0,0);
	newTime -= span;

	return newTime.GetDay();
}

inline int GetDayAtSeason(const COleDateTime* time )
{
	static COleDateTime newTime;
	static int nMonthDay = 0;
	nMonthDay = GetDayAtMonth(time);

	int nMonth = time->GetMonth() % 3;
	switch(nMonth)
	{
	case 0://3,6,9,12
		{
			//����
			newTime.SetDate(time->GetYear(),time->GetMonth()-1,1);
			nMonthDay += GetDayAtMonth(&newTime);
			
			//������
			newTime.SetDate(time->GetYear(),time->GetMonth()-2,1);
			nMonthDay += GetDayAtMonth(&newTime);
			break;
		}
	case 1://1,4,7,10
		{
			//����
			newTime.SetDate(time->GetYear(),time->GetMonth()+1,1);
			nMonthDay += GetDayAtMonth(&newTime);

			//������
			newTime.SetDate(time->GetYear(),time->GetMonth()+2,1);
			nMonthDay += GetDayAtMonth(&newTime);
			break;
		}
	default://2,5,8,11
		{
			//����
			newTime.SetDate(time->GetYear(),time->GetMonth()+1,1);
			nMonthDay += GetDayAtMonth(&newTime);
			
			//����
			newTime.SetDate(time->GetYear(),time->GetMonth()-1,1);
			nMonthDay += GetDayAtMonth(&newTime);
			break;
		}
	}

	return nMonthDay;
}

inline int ConvertMonth(const CString&strMonth)
{
	if (strMonth == "JAN")
	{
		return 1;
	}
	if (strMonth == "FEB")
	{
		return 2;
	}

	if (strMonth == "MAR")
	{
		return 3;
	}

	if (strMonth == "APR")
	{
		return 4;
	}

	if (strMonth == "MAY")
	{
		return 5;
	}

	if (strMonth == "JUN")
	{
		return 6;
	}

	if (strMonth == "JUL" || strMonth == "JLY")
	{
		return 7;
	}

	if (strMonth == "AUG")
	{
		return 8;
	}

	if (strMonth == "SEP")
	{
		return 9;
	}

	if (strMonth == "COT" || strMonth == "OCT")
	{
		return 10;
	}

	if (strMonth == "NOV")
	{
		return 11;
	}

	if (strMonth == "DEC")
	{
		return 12;
	}

	return -1;
}
/**
 * ����:	�ַ���תʱ�䣨Y-m-d��ʽ��1992-8-07��
 * ȫ��:	StringCastTime
 * ����:	public 
 * 
 * @date	2008/08/14
 * @author	flf
 * @param	const CString & strDateTime
 * @param	COleDateTime * time
 * @return	BOOL
 */
inline BOOL StringCastTime(const CString& strDateTime,COleDateTime* time )
{
	try
	{
		//��
		CString strYear = strDateTime.SpanExcluding("-./");
		int nYear = atoi(strYear);
		if (nYear < 1900)
		{
			nYear+= 1900;
		}

		//��
		int nTemp = strDateTime.GetLength() - strYear.GetLength() - 1;
		CString strMonth = strDateTime.Right(nTemp).SpanExcluding("-./");
		strMonth.MakeUpper();
		int nMonth = ConvertMonth(strMonth);
		if (nMonth == -1)
		{
			nMonth = atoi(strMonth);
		}

		//��
		nTemp = nTemp - strMonth.GetLength() - 1;
		CString strDay = strDateTime.Right(nTemp);
		int nDay = atoi(strDay);

		time->SetDate(nYear,nMonth,nDay);
		if (time->GetStatus() != COleDateTime::valid)
		{
			return FALSE;
		}
	}
	catch (CException* )
	{
		time->SetDate(1900,1,1);
		return FALSE;
	}
	return TRUE;
}

/**
* ����:	�ַ���תʱ�䣨d-m-Y��ʽ��07-8-1992��
* ȫ��:	StringCastTime1
* ����:	public 
* 
* @date	2008/08/14
* @author	flf
* @param	const CString & strDateTime
* @param	COleDateTime * time
* @return	BOOL
*/
inline BOOL StringCastTime1(const CString& strDateTime,COleDateTime* time )
{
	try
	{
		//��
		CString strDay = strDateTime.SpanExcluding(_T("-./"));
		int nDay = atoi(strDay);

		//��
		int nTemp = strDateTime.GetLength() - strDay.GetLength() - 1;
		CString strMonth = strDateTime.Right(nTemp).SpanExcluding(_T("-./"));
		strMonth.MakeUpper();
		int nMonth = ConvertMonth(strMonth);
		if (nMonth == -1)
		{
			nMonth = atoi(strMonth);
		}

		//��
		nTemp = nTemp - strMonth.GetLength() - 1;
		CString strYear = strDateTime.Right(nTemp);
		int nYear = atoi(strYear);
		if (nYear < 1900)
		{
			nYear+= 1900;
		}

		time->SetDate(nYear,nMonth,nDay);
		if (time->GetStatus() != COleDateTime::valid)
		{
			return FALSE;
		}
	}
	catch (CException* )
	{
		time->SetDate(1900,1,1);
		return FALSE;
	}
	return TRUE;
}

/**
* ����:	�ַ���תʱ�䣨Y-m��ʽ��1992-8��
* ȫ��:	StringCastTime
* ����:	public 
* 
* @date	2008/08/14
* @author	flf
* @param	const CString & strDateTime
* @param	COleDateTime * time
* @return	BOOL
*/
inline BOOL StringCastTime(const CString& strDateTime,COleDateTime* time ,int nDay)
{
	try
	{
		//��
		CString strYear = strDateTime.SpanExcluding("-./");
		int nYear = atoi(strYear);
		if (nYear < 1900)
		{
			nYear+= 1900;
		}

		//��
		int nTemp = strDateTime.GetLength() - strYear.GetLength() - 1;
		CString strMonth = strDateTime.Right(nTemp).SpanExcluding("-./");
		strMonth.MakeUpper();
		int nMonth = ConvertMonth(strMonth);
		if (nMonth == -1)
		{
			nMonth = atoi(strMonth);
		}

		if (nDay > 28)
		{
			time->SetDate(nYear,nMonth,1);
			nDay = GetDayAtMonth(time);
		}

		time->SetDate(nYear,nMonth,nDay);
		if (time->GetStatus() != COleDateTime::valid)
		{
			return FALSE;
		}
	}
	catch (CException* )
	{
		time->SetDate(1900,1,1);
		return FALSE;
	}
	return TRUE;
}

/**
* ����:	�ַ���תʱ�䣨m-Y��ʽ��8-1992��
* ȫ��:	StringCastTime2
* ����:	public 
* 
* @date	2008/08/14
* @author	flf
* @param	const CString & strDateTime
* @param	COleDateTime * time
* @return	BOOL
*/
inline BOOL StringCastTime1(const CString& strDateTime,COleDateTime* time,int nDay)
{
	try
	{
		//��
		CString strMonth = strDateTime.SpanExcluding(_T("-./"));
		strMonth.MakeUpper();
		int nMonth = ConvertMonth(strMonth);
		if (nMonth == -1)
		{
			nMonth = atoi(strMonth);
		}

		//��
		int nTemp = strDateTime.GetLength() - strMonth.GetLength() - 1;
		CString strYear = strDateTime.Right(nTemp);
		int nYear = atoi(strYear);
		if (nYear < 1900)
		{
			nYear+= 1900;
		}

		if (nDay > 28)
		{
			time->SetDate(nYear,nMonth,1);
			nDay = GetDayAtMonth(time);
		}

		time->SetDate(nYear,nMonth,nDay);
		if (time->GetStatus() != COleDateTime::valid)
		{
			return FALSE;
		}
	}
	catch (CException* )
	{
		time->SetDate(1900,1,1);
		return FALSE;
	}
	return TRUE;
}

/**
 * ����:	�ַ����Ƿ�����
 * ȫ��:	IsNumeric
 * ����:	public 
 * 
 * @date	2008/08/14
 * @author	flf
 * @param	LPCTSTR lpszStr
 * @return	BOOL
 */
inline BOOL IsNumeric(LPCTSTR lpszStr) 
{ 
	char szTmp[MAX_PATH]=""; 
	const char *pTmp=lpszStr; 
	if(!*lpszStr) 
		return FALSE; 
	*pTmp=='-'?pTmp++:pTmp; 
	sscanf(pTmp," %[.,0-9]",szTmp); 
	if(strcmp(pTmp,szTmp) || !strcmp(pTmp,".")) 
		return FALSE; 
	if(pTmp=strstr(szTmp,".")) 
		if(pTmp=strstr(pTmp+1 , ".")) 
			return FALSE; 
	return TRUE; 
}