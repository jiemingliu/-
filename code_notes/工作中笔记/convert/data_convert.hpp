/********************************************************************
	created:	2016/06/29
	created:	29:6:2016   11:03
	file base:	data_convert
	file ext:	hpp
	author:		Huangl
	
	purpose:	����ת��
*********************************************************************/
#pragma once
#include <string>

namespace TGS {
namespace Convert {

/// <summary>
/// Author�� Huangl
/// ת����������
/// </summary>
/// <param name="srcDatas"></param>
/// <param name="tarDatas"></param>
/// <param name="count"></param>
/// <returns></returns>
template<typename _SrcType, typename _TarType>
inline void convertDatasToType(const _SrcType& srcDatas, _TarType& tarDatas, size_t count)
{
    for (size_t index = 0; index < count; ++index)
    {
        tarDatas[index] = srcDatas[index];
    }
}

/// <summary>
/// Author�� Huangl
/// ����ת����������
///    �����ڵ�srcDatas��tarDatas�ڴ��ַ��ͬ������Ҫ���ֽڽ�С������ת�����ֽ�
/// ��������ͣ�����short*ת����float*
/// </summary>
/// <param name="srcDatas"></param>
/// <param name="tarDatas"></param>
/// <param name="count"></param>
/// <returns></returns>
template<typename _SrcType, typename _TarType>
inline void reverseConvertType(const _SrcType& srcDatas, _TarType& tarDatas, size_t count)
{
    for (size_t index; count > 0; --count)
    {
        index = count - 1;
        tarDatas[index] = srcDatas[index];
    }
}

} // Convert
} // TGS