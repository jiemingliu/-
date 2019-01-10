/******************************************************************************
* �ļ���: jcmacrotools.h
* ����: �궨�幤��
* Copyright(c)2014-2016 JCDZ Co.,Ltd.
*
* �޸ļ�¼:
* --------------------
* v1.0   2014/03/12 9:58:33, lys �����ļ�
*
******************************************************************************/
#ifndef _JCMACROTOOLS_H_
#define _JCMACROTOOLS_H_

#include <iostream>
#include "jcbase.h"

namespace JCAssist
{
	/*�Ƚ�*/
	#define MAX(a, b) ((a) > (b) ? (a) : (b))
	#define MIN(a, b) ((a) > (b) ? (b) : (a))

	/*λ����*/
	#define BIT0 	(1<<0)
	#define BIT1 	(1<<1)
	#define BIT2 	(1<<2)
	#define BIT3 	(1<<3)
	#define BIT4 	(1<<4)
	#define BIT5 	(1<<5)
	#define BIT6 	(1<<6)
	#define BIT7 	(1<<7)
	#define BIT8 	(1<<8)
	#define BIT9 	(1<<9)
	#define BIT10  (1<<10)
	#define BIT11  (1<<11)
	#define BIT12  (1<<12)
	#define BIT13  (1<<13)
	#define BIT14  (1<<14)
	#define BIT15  (1<<15)

	/*n��bit0��ʼ*/
	#define SET_BIT(x,n) ((x)|=(0x01<<(n))) 
	#define SET_BIT64(x,n) ((x)|=((__int64)0x01<<(n))) 
	#define CLEAR_BIT(x,n) ((x)&= ~(0x01<<(n)))
	#define CLEAR_BIT64(x,n) ((x)&= ~((__int64)0x01<<(n)))
	#define TEST_BIT(x,n) (0!=((x)&(0x01<<(n))))
	#define TEST_BIT64(x,n) (0!=((x)&((__int64)0x01<<(n))))
	#define EXTRACT_BITS(x, hbit, lbit)  (((x)&(((1<<((hbit)+1))-1)&(~((1<<(lbit))-1))))>>(lbit))


	/*��������Ԫ�ظ���*/
	#define ARRAY_SIZE(a) (sizeof(a)/sizeof((a)[0]))

	/*���������г�Աƫ��,PUBLIC��Ա����ʹ��,�����ֽڶ����й�*/
	#define MEMBER_OFFSET(type, member) ((size_t) &((type *)0)->member)

	/*����ĳ�����г�Ա����ָ���ȡ���Ͷ���ָ��*/
	#define MEMBER_CONTAINER(memberptr, type, member) ((type *)(((char *)memberptr) - MEMBER_OFFSET(type, member)))

#ifdef DEBUG_VERSION
	/*������ֵ�����У��*/
	#define VALRET_ASSERT(condition, ret)\
		do \
		{\
			if (!(condition))\
			{\
			std::cout<<"Error condition: "<< __FILE__<<", line: "<<__LINE__<<std::endl;\
				return (ret);\
			}\
		} while (0)

	/*��������ֵ�����У��*/
	#define VOIDRET_ASSERT(condition)\
		do \
		{\
			if (!(condition))\
			{\
				std::cout<<"Error condition: "<<__FILE__<<", line: "<<__LINE__<<std::endl;\
				return;\
			}\
		} while (0)
#else
	/*������ֵ�����У��*/
	#define VALRET_ASSERT(condition, ret)\
		do \
		{\
			if (!(condition))\
			{\
				return (ret);\
			}\
		} while (0)

	/*��������ֵ�����У��*/
	#define VOIDRET_ASSERT(condition)\
		do \
		{\
			if (!(condition))\
			{\
				return;\
			}\
		} while (0)
#endif
	
	/*�ͷŷ����������ڴ漰����ָ��*/
	#define FREE_POINT(p)\
	{\
		if (NULL != (p))\
		{\
			delete (p);\
			p = NULL;\
		}\
	}	

	/*�ͷ����������ڴ漰����ָ��*/
	#define FREE_ARRAYPOINT(p)\
			{\
				if (NULL != (p))\
				{\
					delete[] (p);\
					p = NULL;\
				}\
			}
	
	/*16λ�ߵ��ֽڽ���, ��֧�ָ�������, ���ı�a��ֵ*/
	#define SWAP16(a) \
			(unsigned short)(((((unsigned short)(a)) & 0xFF) << 8) \
			| ((((unsigned short)(a)) & 0xFF00) >> 8))

	/*32λ�ߵ��ֽڽ���, ��֧�ָ�������, ���ı�a��ֵ*/
	#define SWAP32(a) \
			(unsigned int)(((((unsigned int)(a)) & 0xFF000000) >> 24)\
			| ((((unsigned int)(a)) & 0x00FF0000 ) >> 8 )\
			| ((((unsigned int)(a)) & 0x0000FF00 ) << 8 )\
			| ((((unsigned int)(a)) & 0x000000FF ) << 24))

}

#endif /* _JCMACROTOOLS_H_ */
