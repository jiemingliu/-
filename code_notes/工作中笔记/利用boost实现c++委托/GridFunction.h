#pragma once
#include <boost/function.hpp>
#include "GridStruct.h"

class CGridRecive;
//#include "GridPropUnit.h"
//#include "GridPropUnitPre.h"
//ͨ������ȡ��ָ��������ִ��ʱ���µ�ֵ
typedef boost::function<double(const CGridRecive& ,const COleDateTime& ,const GridNo& )> fun_GetGridValue;
//ͨ�����Ժ�ʱ���ȡ������������
typedef boost::function<std::vector<double>(const COleDateTime&,const std::vector<GridNo>&)> fun_GetGridValues;
//����ָ��������ִ��ʱ���µ�ֵ
typedef boost::function<void(CGridRecive& ,const COleDateTime& ,const GridNo& ,const double& )> fun_SetGridValue;
//ͨ������ȡ������ʱ���¸����Ե������Сֵ
typedef boost::function<void(double& ,double& )> fun_GetMinMaxValue;
//��ȡ��ǰʱ�䵱ǰ�����������Сֵ
typedef boost::function<BOOL(CGridRecive&, const COleDateTime& ,long ,double& ,double& )> fun_GetKMinMaxValue;
//����һ��ʱ�䲽��������
typedef boost::function<void(const CGridRecive& ,const COleDateTime& ,const CString& )> fun_createGridPropData;
//�������
typedef boost::function<void()> fun_ClearData;
//��ȡ�������͡�TRUE Ϊ����FALSEΪǰ����
typedef boost::function<BOOL()> fun_DataType;
//���Դ�ʱ���Ƿ�������
typedef boost::function<BOOL(const COleDateTime&)> fun_IsExistTime;
////����ǰ��������
//typedef boost::function<void(CGridPropUnitPre&)> fun_CopyGridPropUnitPre;
////������������
//typedef boost::function<void(CGridPropUnit& , CGridRecive*)> fun_CopyGridPropUnit;
//�رմ򿪵��ļ��������ִ��ECL
typedef boost::function<void()> fun_CloseFileHandle;

//�������Ի�ȡ����
struct GridFunction
{
	//ͨ������ȡ��ָ��������ִ��ʱ���µ�ֵ
	fun_GetGridValue getValue;
	//ͨ�����Ժ�ʱ���ȡ������������
	fun_GetGridValues getValues;
	//����ָ��������ִ��ʱ���µ�ֵ
	fun_SetGridValue setValue;
	//ͨ������ȡ������ʱ���¸����Ե������Сֵ
	fun_GetMinMaxValue getMinMax;
	//��ȡ��ǰʱ�䵱ǰ�����������Сֵ
	fun_GetKMinMaxValue getKMinMaxValue;
	//����һ��ʱ�䲽��������
	fun_createGridPropData createGridPropData;
	//�������
	fun_ClearData clearData;
	fun_DataType getDataType;
	fun_IsExistTime isExistTime;
	//��鵱ǰ�����Ƿ�Ҫ����
	fun_DataType checkCurPropData;
	//fun_CopyGridPropUnitPre copyGridPropUnitPre;
	//fun_CopyGridPropUnit     copyGridPropUnit;
	fun_CloseFileHandle        closeFileHandle;
};
