/******************************************************************************
* �ļ���: jcnonecopy.h
* ����: -
* Copyright(c)2014-2016 JCDZ Co.,Ltd.
*
* �޸ļ�¼:
* --------------------
* v1.0   2014/03/14 10:36:8, gaopeng �����ļ�
*
******************************************************************************/

#ifndef _JCNONECOPY_H
#define _JCNONECOPY_H

#include "jcbase.h"

class DLL_EXPORT JCNonecopy
{
protected:
	JCNonecopy();
	~JCNonecopy();

private:
	JCNonecopy(const JCNonecopy&);
	const JCNonecopy& operator=(const JCNonecopy&);
};

#endif /* _JCNONECOPY_H */

