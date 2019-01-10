/******************************************************************************
* 文件名: jctypetrans.h
* 描述: 字符等基础类型转换、判断等
* Copyright(c)2014-2016 JCDZ Co.,Ltd.
*
* 修改记录:
* --------------------
* v1.0   2014/03/12 16:40:6, lys 创建文件
*
******************************************************************************/

#ifndef _JCTYPETRANS_H_
#define _JCTYPETRANS_H_

#include <string>
#include <vector>
#include "jcbase.h"

namespace JCAssist
{
	using namespace std;

	const unsigned int ALL_LINK = 0xFFFFFFFF;

    /******************************************************************************
    * 函数名:JCAssist.IsDecDigit
    * 描述:
    *
    * 输入: 字符或ASCII码值, 输入多字符时结果未定义
    * 输出:
    * 返回值: true/false 是否十进制数字字符
    *
    * 修改记录:
    * --------------------
    *    2014/03/13 15:37:14, lys 创建函数
    *
    ******************************************************************************/
    bool DLL_EXPORT IsDecDigit(char ch);

    /******************************************************************************
    * 函数名:JCAssist.IsHexDigit
    * 描述:
    *
    * 输入: 字符或ASCII码值, 输入多字符时结果未定义
    * 输出:
    * 返回值: true/false 是否十六进制数字字符
    *
    * 修改记录:
    * --------------------
    *    2014/03/13 15:39:32, lys 创建函数
    *
    ******************************************************************************/
	bool DLL_EXPORT IsHexDigit(char ch);

    /******************************************************************************
    * 函数名:JCAssist.IsAlpha
    * 描述:
    *
    * 输入: 字符或ASCII码值, 输入多字符时结果未定义
    * 输出:
    * 返回值: true/false 是否a-z, A-Z字母字符
    *
    * 修改记录:
    * --------------------
    *    2014/03/13 15:41:12, lys 创建函数
    *
    ******************************************************************************/
	bool DLL_EXPORT IsAlpha(char ch);

    /******************************************************************************
    * 函数名:JCAssist.IsUpperAlpha
    * 描述:
    *
    * 输入: 字符或ASCII码值, 输入多字符时结果未定义
    * 输出:
    * 返回值: true/false 是否A-Z字母字符
    *
    * 修改记录:
    * --------------------
    *    2014/03/13 15:44:8, lys 创建函数
    *
    ******************************************************************************/
	bool DLL_EXPORT IsUpperAlpha(char ch);

    /******************************************************************************
    * 函数名:JCAssist.IsLowerAlpha
    * 描述:
    *
    * 输入: 字符或ASCII码值, 输入多字符时结果未定义
    * 输出:
    * 返回值: true/false 是否a-z字母字符
    *
    * 修改记录:
    * --------------------
    *    2014/03/13 15:44:51, lys 创建函数
    *
    ******************************************************************************/
	bool DLL_EXPORT IsLowerAlpha(char ch);

    /******************************************************************************
    * 函数名:JCAssist.IsAlnum
    * 描述: -
    *
    * 输入:字符或ASCII码值, 输入多字符时结果未定义
    * 输出:
    * 返回值: true/false 是否a-z/A-Z字母字符或者0-9数字
    *
    * 修改记录:
    * --------------------
    *    2014/03/15 0:45:20, lys 创建函数
    *
    ******************************************************************************/
	bool DLL_EXPORT IsAlnum(char ch);

    /******************************************************************************
    * 函数名:JCAssist.IsSpace
    * 描述:
    *
    * 输入: 字符或ASCII码值, 输入多字符时结果未定义
    * 输出:
    * 返回值: true/false 是否空格字符
    *
    * 修改记录:
    * --------------------
    *    2014/03/13 15:45:41, lys 创建函数
    *
    ******************************************************************************/
	bool DLL_EXPORT IsSpace(char ch);

    /******************************************************************************
    * 函数名:JCAssist.IsPunctuation
    * 描述:
    *
    * 输入: 字符或ASCII码值, 输入多字符时结果未定义
    * 输出:
    * 返回值: true/false 是否为除空格外的标点字符,如,;:等
    *
    * 修改记录:
    * --------------------
    *    2014/03/13 15:46:16, lys 创建函数
    *
    ******************************************************************************/
	bool DLL_EXPORT IsPunctuation(char ch);

    /******************************************************************************
    * 函数名:JCAssist.IsStringAllDecDigit
    * 描述: 十进制字符串 如 "03948485"
    *
    * 输入:
    * 输出:
    * 返回值:
    *
    * 修改记录:
    * --------------------
    *    2014/03/14 9:57:26, lys 创建函数
    *
    ******************************************************************************/
	bool DLL_EXPORT IsStringAllDecDigit(const string str);

    /******************************************************************************
    * 函数名:JCAssist.IsStringAllHexDigit
    * 描述: 十六进制字符串 如: "FA093FE", "0aeb3dAf"
    *
    * 输入:
    * 输出:
    * 返回值:
    *
    * 修改记录:
    * --------------------
    *    2014/03/14 10:10:3, lys 创建函数
    *
    ******************************************************************************/
	bool DLL_EXPORT IsStringAllHexDigit(const string str);

    /******************************************************************************
    * 函数名:JCAssist.IsStringAllAlpha
    * 描述: 全字母字串 "ahdeHDKKe"
    *
    * 输入:
    * 输出:
    * 返回值:
    *
    * 修改记录:
    * --------------------
    *    2014/03/14 10:11:0, lys 创建函数
    *
    ******************************************************************************/
	bool DLL_EXPORT IsStringAllAlpha(const string str);

    /******************************************************************************
    * 函数名:JCAssist.IsStringAllUpperAlpha
    * 描述: 全大写字母字串
    *
    * 输入:
    * 输出:
    * 返回值:
    *
    * 修改记录:
    * --------------------
    *    2014/03/14 10:11:32, lys 创建函数
    *
    ******************************************************************************/
	bool DLL_EXPORT IsStringAllUpperAlpha(const string str);

    /******************************************************************************
    * 函数名:JCAssist.IsStringAllLowerAlpha
    * 描述: 全小写字母字串
    *
    * 输入:
    * 输出:
    * 返回值:
    *
    * 修改记录:
    * --------------------
    *    2014/03/14 10:11:55, lys 创建函数
    *
    ******************************************************************************/
	bool DLL_EXPORT IsStringAllLowerAlpha(const string str);

    /******************************************************************************
    * 函数名:JCAssist.IsStringAllAlnum
    * 描述: 数字和字母组成字串
    *
    * 输入:
    * 输出:
    * 返回值:
    *
    * 修改记录:
    * --------------------
    *    2014/03/15 0:43:35, lys 创建函数
    *
    ******************************************************************************/
	bool DLL_EXPORT IsStringAllAlnum(const string str);

    /******************************************************************************
    * 函数名:JCAssist.IsStringContainsChar
    * 描述:
    *
    * 输入: str 待检查字符串 ch 指定检查字符
    * 输出:
    * 返回值: true/false 是否包含指定字符
    *
    * 修改记录:
    * --------------------
    *    2014/03/13 15:48:31, lys 创建函数
    *
    ******************************************************************************/
	bool DLL_EXPORT IsStringContainsChar(const string str, char ch);

    /******************************************************************************
    * 函数名:JCAssist.DecStringToInt
    * 描述:
    *
    * 输入: 十进制字符串(不能越限) 如 "8392" -> 8392
    * 输出:
    * 返回值: 所表示的十进制数值
    *
    * 修改记录:
    * --------------------
    *    2014/03/13 15:50:14, lys 创建函数
    *
    ******************************************************************************/
	int DLL_EXPORT DecStringToInt(const string str);

    /******************************************************************************
    * 函数名:JCAssist.DecStringToU32
    * 描述:
    *
    * 输入: 十进制字符串(不能越限) 如 "8392" -> 8392
    * 输出:
    * 返回值: 所表示的无符号十进制数值
    *
    * 修改记录:
    * --------------------
    *    2014/03/13 15:50:14, lys 创建函数
    *
    ******************************************************************************/
	unsigned int DLL_EXPORT DecStringToU32(const string str);

    /******************************************************************************
    * 函数名:JCAssist.DecStringToU32
    * 描述:
    *
    * 输入: 十进制字符串(不能越限) 如 "8392" -> 8392
    * 输出:
    * 返回值: 所表示的无符号十进制数值
    *
    * 修改记录:
    * --------------------
    *    2014/03/13 15:50:14, lys 创建函数
    *
    ******************************************************************************/
	long long DLL_EXPORT DecStringToI64(const string str);

    /******************************************************************************
    * 函数名:JCAssist.DecStringToU32
    * 描述:
    *
    * 输入: 十进制字符串(不能越限) 如 "8392" -> 8392
    * 输出:
    * 返回值: 所表示的无符号十进制数值
    *
    * 修改记录:
    * --------------------
    *    2014/03/13 15:50:14, lys 创建函数
    *
    ******************************************************************************/
	unsigned long long DLL_EXPORT DecStringToU64(const string str);
	
    /******************************************************************************
    * 函数名:JCAssist.IntToDecString
    * 描述: 十进制数值转换为字符串  如:8392->"8392"
    *
    * 输入:
    * 输出:
    * 返回值:
    *
    * 修改记录:
    * --------------------
    *    2014/03/14 10:12:39, lys 创建函数
    *
    ******************************************************************************/
	string DLL_EXPORT IntToDecString(int nValue);

	
    /******************************************************************************
    * 函数名:JCAssist.U32ToDecString
    * 描述: 无符号十进制数值转换为字符串  如:8392->"8392"
    *
    * 输入:
    * 输出:
    * 返回值:
    *
    * 修改记录:
    * --------------------
    *    2014/03/14 10:12:39, lys 创建函数
    *
    ******************************************************************************/
	string DLL_EXPORT U32ToDecString(unsigned int nValue);

    /******************************************************************************
    * 函数名:JCAssist.I64ToDecString
    * 描述: 无符号十进制数值转换为字符串  如:8392->"8392"
    *
    * 输入:
    * 输出:
    * 返回值:
    *
    * 修改记录:
    * --------------------
    *    2014/03/14 10:12:39, lys 创建函数
    *
    ******************************************************************************/
	string DLL_EXPORT I64ToDecString(long long nValue);

	/******************************************************************************
    * 函数名:JCAssist.U64ToDecString
    * 描述: 无符号十进制数值转换为字符串  如:8392->"8392"
    *
    * 输入:
    * 输出:
    * 返回值:
    *
    * 修改记录:
    * --------------------
    *    2014/03/14 10:12:39, lys 创建函数
    *
    ******************************************************************************/
	string DLL_EXPORT U64ToDecString(unsigned long long nValue);

    /******************************************************************************
    * 函数名:JCAssist.DecStringToDouble
    * 描述:
    *
    * 输入: 十进制字符串或浮点表示形式字符串(不能越限) 如: "255"->255.000000 "2e-2"->2e-2
    * 输出:
    * 返回值: 所表示的十进制数值,浮点数表示
    *
    * 修改记录:
    * --------------------
    *    2014/03/13 15:51:3, lys 创建函数
    *
    ******************************************************************************/
	double DLL_EXPORT DecStringToDouble(const string str);

    /******************************************************************************
    * 函数名:JCAssist.DoubleToDecString
    * 描述: 浮点数转换为对应字符串 如: 2.32->"2.320000"
    *
    * 输入:
    * 输出:
    * 返回值:
    *
    * 修改记录:
    * --------------------
    *    2014/03/14 10:14:26, lys 创建函数
    *
    ******************************************************************************/
	string DLL_EXPORT DoubleToDecString(double dValue);
	
	/******************************************************************************
    * 函数名:JCAssist.DoubleToDecString
    * 描述: 浮点数转换为指定精度的对应字符串 如: 2.32->"2.32"(默认2位小数精度)
    *
    * 输入:
    * 输出:
    * 返回值:
    *
    * 修改记录:
    * --------------------
    *    2014/03/14 10:14:26, lys 创建函数
    *
    ******************************************************************************/
	string DLL_EXPORT DoubleToDecStringEx(double dValue,int nLen =2);

    /******************************************************************************
    * 函数名:JCAssist.BufToHexString
    * 描述: buf转换成16进制串
    *
    * 输入:
    * 输出:
    * 返回值:
    *
    * 修改记录:
    * --------------------
    *    2014/03/14 10:14:26, lys 创建函数
    *
    ******************************************************************************/
	string DLL_EXPORT BufToHexString(const char* buf,int nLen);

    /******************************************************************************
    * 函数名:JCAssist.HexStringToInt
    * 描述: 转换十六进制字符串为数值 如: "0xFF"->255, "fE"->254
    *
    * 输入: 十六进制字符串(不能越限)
    * 输出:
    * 返回值: 对应十进制数值
    *
    * 修改记录:
    * --------------------
    *    2014/03/13 15:53:3, lys 创建函数
    *
    ******************************************************************************/
	int DLL_EXPORT HexStringToInt(const string str);

    /******************************************************************************
    * 函数名:JCAssist.IntToHexString
    * 描述: 十进制值转换为十六进制字符串 如: 255->"FF" 254->"FE"(字符串大写,且以两位表示)
    *
    * 输入:
    * 输出:
    * 返回值:
    *
    * 修改记录:
    * --------------------
    *    2014/03/14 10:17:5, lys 创建函数
    *
    ******************************************************************************/
	string DLL_EXPORT IntToHexString(int nValue);

    /******************************************************************************
    * 函数名:JCAssist.RemoveBlank
    * 描述: 移除字串中的所有空格并返回副本,不改变原字串
    *
    * 输入:
    * 输出:
    * 返回值:
    *
    * 修改记录:
    * --------------------
    *    2014/04/08 20:22:7, lys 创建函数
    *
    ******************************************************************************/
	string DLL_EXPORT RemoveBlank(const string &str);

    /******************************************************************************
    * 函数名:JCAssist.RemoveSpecChar
    * 描述: 不改变原字串情况下移除指定的所有字符
    *
    * 输入:
    * 输出:
    * 返回值:
    *
    * 修改记录:
    * --------------------
    *    2014/04/08 20:39:46, lys 创建函数
    *
    ******************************************************************************/
	string DLL_EXPORT RemoveSpecChar(const string &str, char ch);

    /******************************************************************************
    * 函数名:JCAssist.ReplaceSpecChar
    * 描述: 使用新字符替换字符串中的指定字符, 返回新字符串,不改变原字串
    *
    * 输入:
    * 输出:
    * 返回值:
    *
    * 修改记录:
    * --------------------
    *    2014/04/23 10:47:53, lys 创建函数
    *
    ******************************************************************************/
	string DLL_EXPORT ReplaceSpecChar(const string &str, char chold, char chnew);

    /******************************************************************************
    * 函数名:JCAssist.ReplaceSpecStr
    * 描述: 使用新子串替换字符串中的指定子串, 返回新字符串,不改变原字串
    *
    * 输入:
    * 输出:
    * 返回值:
    *
    * 修改记录:
    * --------------------
    *    2014/04/23 10:48:18, lys 创建函数
    *
    ******************************************************************************/
	string DLL_EXPORT ReplaceSpecStr(const string &str, const string &strOld, const string &strNew);

	/******************************************************************************
    * 函数名:JCAssist.SplitString
    * 描述: 将字符串以指定子串为分隔符分割
    *
    * 输入:
    * 输出:
    * 返回值:按顺序存储分割出的子串集合
    *
    * 修改记录:
    * --------------------
    *    2014/04/23 10:48:18, lys 创建函数
    *
    ******************************************************************************/
	vector<string> DLL_EXPORT SplitString(const string &str, string sep = ",", bool bKeepEmptyParts = true);

    /******************************************************************************
    * 函数名:JCAssist.DecDigitToByte
    * 描述: 十进制字符转换为对应值 如 '0'->0, '9'->9等, 支持(0->9)
    *
    * 输入:
    * 输出:
    * 返回值: 非法字符时返回255
    *
    * 修改记录:
    * --------------------
    *    2014/03/14 11:22:45, lys 创建函数
    *
    ******************************************************************************/
	unsigned char DLL_EXPORT DecDigitToByte(char ch);

    /******************************************************************************
    * 函数名:JCAssist.HexDigitToByte
    * 描述: 十六进制字符转换为对应值  如: '1'->1, 'f'->15, 'E'->14,支持(0->9,a->f,A-F)
    *
    * 输入:
    * 输出:
    * 返回值: 非法字符时返回255
    *
    * 修改记录:
    * --------------------
    *    2014/03/14 10:18:36, lys 创建函数
    *
    ******************************************************************************/
	unsigned char DLL_EXPORT HexDigitToByte(char ch);
	
    /******************************************************************************
    * 函数名:JCAssist.TransBitPos2Id
    * 描述: 
    *          根据计算二进制BIT 1所在的十进制BIT位置, 序号从1开始, 如0010 -> 2
    * 输入: 建议只有一个为1 BIT位, 若存在多个BIT位为1, 则计算最高位BIT 1的位置
    * 输出:
    * 返回值:  
    *
    * 修改记录:
    * --------------------
    *    2015/01/05 15:19:36, gaopeng 增加函数
    *
    ******************************************************************************/
	unsigned int DLL_EXPORT TransBitPos2Id(unsigned int nIndex);

	/******************************************************************************
    * 函数名:JCAssist.CountBit
    * 描述: 计算整数中为1的bit数
    *
    * 输入:
    * 输出:
    * 返回值:
    *
    * 修改记录:
    * --------------------
    *    2014/04/08 20:22:7, lys 创建函数
    *
    ******************************************************************************/
	unsigned int DLL_EXPORT CountBits(unsigned int nValue);
	
	/******************************************************************************
    * 函数名:JCAssist.StringTrimmed
    * 描述: 移除字串中首尾的空格并返回副本,不改变原字串
    *
    * 输入:
    * 输出:
    * 返回值:
    *
    * 修改记录:
    * --------------------
    *    2014/04/08 20:22:7, lys 创建函数
    *
    ******************************************************************************/
	string DLL_EXPORT StringTrimmed(const string& str);

	/******************************************************************************
    * 函数名:JCAssist.OutPutUpperLetterString
    * 描述: 返回大写字母字符串
    *
    * 输入:
    * 输出:
    * 返回值:
    *
    * 修改记录:
    * --------------------
    *    2015/09/28 14:22:7, gaopeng 创建函数
    *
    ******************************************************************************/
	string DLL_EXPORT OutPutUpperLetterString(const string& str);

	/******************************************************************************
    * 函数名:JCAssist.OutPutLowerLetterString
    * 描述: 返回小写字母字符串
    *
    * 输入:
    * 输出:
    * 返回值:
    *
    * 修改记录:
    * --------------------
    *    2015/09/28 14:22:7, gaopeng 创建函数
    *
    ******************************************************************************/
	string DLL_EXPORT OutPutLowerLetterString(const string& str);

	/******************************************************************************
    * 函数名:JCAssist.CalcBroadcastAddress
    * 描述: 返回广播地址
    *
    * 输入:
    * 输出:
    * 返回值:
    *
    * 修改记录:
    * --------------------
    *    2015/12/08 09:22:7, gaopeng 创建函数
    *
    ******************************************************************************/
	string DLL_EXPORT CalcBroadcastAddress(const string& strIp, const string& strSubnetMask);
	
		/******************************************************************************
    * 函数名:JCAssist.StringIP2IntIP
    * 描述: 返回DWORD类型IP值
    *
    * 输入:
    * 输出:
    * 返回值:
    *
    * 修改记录:
    * --------------------
    *    2016/08/15 10:18:7, jsy 创建函数
    *
    ******************************************************************************/
	unsigned int DLL_EXPORT StringIP2IntIP(const string& strIp);
}
#endif /* _JCTYPETRANS_H_ */