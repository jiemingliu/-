Visual C++ 2012 ʹ���˸��Ӱ�ȫ�� run-time library routines ���µ�Security CRT functions��������Щ���С�_s����׺�ĺ�����
����һ����ԭ���ľɺ����滻���µ� Security CRT functions��

�������������·�������������棺

    1. ��Ԥ����ͷ�ļ�stdafx.h�ע�⣺һ��Ҫ��û��include�κ�ͷ�ļ�֮ǰ����������ĺ꣺

       #define _CRT_SECURE_NO_DEPRECATE

    2. ������ #pragma warning(disable:4996)

    3. ����Ԥ�����壺

        ��Ŀ->����->��������->C/C++ -> Ԥ������ -> Ԥ���������壬���ӣ�

            _CRT_SECURE_NO_DEPRECATE

��������������û��ʹ�ø��Ӱ�ȫ�� CRT ��������Ȼ����һ��ֵ���Ƽ��ĺ÷������������ֲ���һ��һ���ظĺ����������ﻹ��һ�������ķ�����

��Ԥ����ͷ�ļ� stdafx.h �ͬ��Ҫ��û��include�κ�ͷ�ļ�֮ǰ����������ĺ꣺

#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1

�����ӵ�ʱ�����Զ����ɺ����滻�� Security CRT functions ��

ע�⣺���������Ȼʹ�����µĺ��������ǲ�����������(ԭ�������)���㻹��ͬʱʹ�÷�����(-_-)����ʵ��Ӧ��Ԥ����ͷ�ļ� stdafx.h ������������䣺

#define _CRT_SECURE_NO_DEPRECATE

#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1