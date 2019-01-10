/******************************************************************************
* 文件名: jcalgorithm.h
* 描述: -
* Copyright(c)2014-2016 JCDZ Co.,Ltd.
*
* 修改记录:
* --------------------
* v1.0   2014/03/20 19:26:24, gaopeng 创建文件
*
******************************************************************************/
#ifndef _JCALGORITHM_H
#define _JCALGORITHM_H

#include <string>
#include <iostream>
#include <vector>
#include <io.h>

#include "jcbase.h"

#define READBUF_SIZE 512

/*md5类,计算md5,请直接调用CalcMd5全局函数*/
class DLL_EXPORT JCMd5
{
public:
    typedef unsigned int size_type; // must be 32bit

    JCMd5();
    JCMd5(const std::string& text);
    void Update(const unsigned char *buf, size_type length);
    void Update(const char *buf, size_type length);
    JCMd5& Finalize();
    std::string Hexdigest() const;
    friend std::ostream& operator<<(std::ostream&, JCMd5 md5);

private:
    void Init();
    typedef unsigned char uint1; //  8bit
    typedef unsigned int uint4;  // 32bit
    enum {blocksize = 64}; // VC6 won't eat a const static int here

    void Transform(const uint1 block[blocksize]);
    static void Decode(uint4 output[], const uint1 input[], size_type len);
    static void Encode(uint1 output[], const uint4 input[], size_type len);

    bool finalized;
    uint1 buffer[blocksize]; // bytes that didn't fit in last 64 byte chunk
    uint4 count[2];   // 64bit counter for number of bits (lo, hi)
    uint4 state[4];   // digest so far
    uint1 digest[16]; // the result

    // low level logic operations
    static inline uint4 F(uint4 x, uint4 y, uint4 z);
    static inline uint4 G(uint4 x, uint4 y, uint4 z);
    static inline uint4 H(uint4 x, uint4 y, uint4 z);
    static inline uint4 I(uint4 x, uint4 y, uint4 z);
    static inline uint4 Rotate_left(uint4 x, int n);
    static inline void FF(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
    static inline void GG(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
    static inline void HH(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
    static inline void II(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
};


std::string DLL_EXPORT CalcMd5(const std::string str);

/* 标准crc校验 */
class DLL_EXPORT JCCrc
{
public:
    JCCrc()
    {
        const int tableLength = 256;

        unsigned short tempTable16[tableLength] =
        {
            0x0000, 0x1189, 0x2312, 0x329b, 0x4624, 0x57ad, 0x6536, 0x74bf,
            0x8c48, 0x9dc1, 0xaf5a, 0xbed3, 0xca6c, 0xdbe5, 0xe97e, 0xf8f7,
            0x1081, 0x0108, 0x3393, 0x221a, 0x56a5, 0x472c, 0x75b7, 0x643e,
            0x9cc9, 0x8d40, 0xbfdb, 0xae52, 0xdaed, 0xcb64, 0xf9ff, 0xe876,
            0x2102, 0x308b, 0x0210, 0x1399, 0x6726, 0x76af, 0x4434, 0x55bd,
            0xad4a, 0xbcc3, 0x8e58, 0x9fd1, 0xeb6e, 0xfae7, 0xc87c, 0xd9f5,
            0x3183, 0x200a, 0x1291, 0x0318, 0x77a7, 0x662e, 0x54b5, 0x453c,
            0xbdcb, 0xac42, 0x9ed9, 0x8f50, 0xfbef, 0xea66, 0xd8fd, 0xc974,
            0x4204, 0x538d, 0x6116, 0x709f, 0x0420, 0x15a9, 0x2732, 0x36bb,
            0xce4c, 0xdfc5, 0xed5e, 0xfcd7, 0x8868, 0x99e1, 0xab7a, 0xbaf3,
            0x5285, 0x430c, 0x7197, 0x601e, 0x14a1, 0x0528, 0x37b3, 0x263a,
            0xdecd, 0xcf44, 0xfddf, 0xec56, 0x98e9, 0x8960, 0xbbfb, 0xaa72,
            0x6306, 0x728f, 0x4014, 0x519d, 0x2522, 0x34ab, 0x0630, 0x17b9,
            0xef4e, 0xfec7, 0xcc5c, 0xddd5, 0xa96a, 0xb8e3, 0x8a78, 0x9bf1,
            0x7387, 0x620e, 0x5095, 0x411c, 0x35a3, 0x242a, 0x16b1, 0x0738,
            0xffcf, 0xee46, 0xdcdd, 0xcd54, 0xb9eb, 0xa862, 0x9af9, 0x8b70,
            0x8408, 0x9581, 0xa71a, 0xb693, 0xc22c, 0xd3a5, 0xe13e, 0xf0b7,
            0x0840, 0x19c9, 0x2b52, 0x3adb, 0x4e64, 0x5fed, 0x6d76, 0x7cff,
            0x9489, 0x8500, 0xb79b, 0xa612, 0xd2ad, 0xc324, 0xf1bf, 0xe036,
            0x18c1, 0x0948, 0x3bd3, 0x2a5a, 0x5ee5, 0x4f6c, 0x7df7, 0x6c7e,
            0xa50a, 0xb483, 0x8618, 0x9791, 0xe32e, 0xf2a7, 0xc03c, 0xd1b5,
            0x2942, 0x38cb, 0x0a50, 0x1bd9, 0x6f66, 0x7eef, 0x4c74, 0x5dfd,
            0xb58b, 0xa402, 0x9699, 0x8710, 0xf3af, 0xe226, 0xd0bd, 0xc134,
            0x39c3, 0x284a, 0x1ad1, 0x0b58, 0x7fe7, 0x6e6e, 0x5cf5, 0x4d7c,
            0xc60c, 0xd785, 0xe51e, 0xf497, 0x8028, 0x91a1, 0xa33a, 0xb2b3,
            0x4a44, 0x5bcd, 0x6956, 0x78df, 0x0c60, 0x1de9, 0x2f72, 0x3efb,
            0xd68d, 0xc704, 0xf59f, 0xe416, 0x90a9, 0x8120, 0xb3bb, 0xa232,
            0x5ac5, 0x4b4c, 0x79d7, 0x685e, 0x1ce1, 0x0d68, 0x3ff3, 0x2e7a,
            0xe70e, 0xf687, 0xc41c, 0xd595, 0xa12a, 0xb0a3, 0x8238, 0x93b1,
            0x6b46, 0x7acf, 0x4854, 0x59dd, 0x2d62, 0x3ceb, 0x0e70, 0x1ff9,
            0xf78f, 0xe606, 0xd49d, 0xc514, 0xb1ab, 0xa022, 0x92b9, 0x8330,
            0x7bc7, 0x6a4e, 0x58d5, 0x495c, 0x3de3, 0x2c6a, 0x1ef1, 0x0f78
        };
        unsigned int tempTable32[tableLength]=
        {
            0x00000000, 0x77073096, 0xEE0E612C, 0x990951BA, 0x076DC419, 0x706AF48F, 0xE963A535, 0x9E6495A3,
            0x0EDB8832, 0x79DCB8A4, 0xE0D5E91E, 0x97D2D988, 0x09B64C2B, 0x7EB17CBD, 0xE7B82D07, 0x90BF1D91,
            0x1DB71064, 0x6AB020F2, 0xF3B97148, 0x84BE41DE, 0x1ADAD47D, 0x6DDDE4EB, 0xF4D4B551, 0x83D385C7,
            0x136C9856, 0x646BA8C0, 0xFD62F97A, 0x8A65C9EC, 0x14015C4F, 0x63066CD9, 0xFA0F3D63, 0x8D080DF5,
            0x3B6E20C8, 0x4C69105E, 0xD56041E4, 0xA2677172, 0x3C03E4D1, 0x4B04D447, 0xD20D85FD, 0xA50AB56B,
            0x35B5A8FA, 0x42B2986C, 0xDBBBC9D6, 0xACBCF940, 0x32D86CE3, 0x45DF5C75, 0xDCD60DCF, 0xABD13D59,
            0x26D930AC, 0x51DE003A, 0xC8D75180, 0xBFD06116, 0x21B4F4B5, 0x56B3C423, 0xCFBA9599, 0xB8BDA50F,
            0x2802B89E, 0x5F058808, 0xC60CD9B2, 0xB10BE924, 0x2F6F7C87, 0x58684C11, 0xC1611DAB, 0xB6662D3D,
            0x76DC4190, 0x01DB7106, 0x98D220BC, 0xEFD5102A, 0x71B18589, 0x06B6B51F, 0x9FBFE4A5, 0xE8B8D433,
            0x7807C9A2, 0x0F00F934, 0x9609A88E, 0xE10E9818, 0x7F6A0DBB, 0x086D3D2D, 0x91646C97, 0xE6635C01,
            0x6B6B51F4, 0x1C6C6162, 0x856530D8, 0xF262004E, 0x6C0695ED, 0x1B01A57B, 0x8208F4C1, 0xF50FC457,
            0x65B0D9C6, 0x12B7E950, 0x8BBEB8EA, 0xFCB9887C, 0x62DD1DDF, 0x15DA2D49, 0x8CD37CF3, 0xFBD44C65,
            0x4DB26158, 0x3AB551CE, 0xA3BC0074, 0xD4BB30E2, 0x4ADFA541, 0x3DD895D7, 0xA4D1C46D, 0xD3D6F4FB,
            0x4369E96A, 0x346ED9FC, 0xAD678846, 0xDA60B8D0, 0x44042D73, 0x33031DE5, 0xAA0A4C5F, 0xDD0D7CC9,
            0x5005713C, 0x270241AA, 0xBE0B1010, 0xC90C2086, 0x5768B525, 0x206F85B3, 0xB966D409, 0xCE61E49F,
            0x5EDEF90E, 0x29D9C998, 0xB0D09822, 0xC7D7A8B4, 0x59B33D17, 0x2EB40D81, 0xB7BD5C3B, 0xC0BA6CAD,
            0xEDB88320, 0x9ABFB3B6, 0x03B6E20C, 0x74B1D29A, 0xEAD54739, 0x9DD277AF, 0x04DB2615, 0x73DC1683,
            0xE3630B12, 0x94643B84, 0x0D6D6A3E, 0x7A6A5AA8, 0xE40ECF0B, 0x9309FF9D, 0x0A00AE27, 0x7D079EB1,
            0xF00F9344, 0x8708A3D2, 0x1E01F268, 0x6906C2FE, 0xF762575D, 0x806567CB, 0x196C3671, 0x6E6B06E7,
            0xFED41B76, 0x89D32BE0, 0x10DA7A5A, 0x67DD4ACC, 0xF9B9DF6F, 0x8EBEEFF9, 0x17B7BE43, 0x60B08ED5,
            0xD6D6A3E8, 0xA1D1937E, 0x38D8C2C4, 0x4FDFF252, 0xD1BB67F1, 0xA6BC5767, 0x3FB506DD, 0x48B2364B,
            0xD80D2BDA, 0xAF0A1B4C, 0x36034AF6, 0x41047A60, 0xDF60EFC3, 0xA867DF55, 0x316E8EEF, 0x4669BE79,
            0xCB61B38C, 0xBC66831A, 0x256FD2A0, 0x5268E236, 0xCC0C7795, 0xBB0B4703, 0x220216B9, 0x5505262F,
            0xC5BA3BBE, 0xB2BD0B28, 0x2BB45A92, 0x5CB36A04, 0xC2D7FFA7, 0xB5D0CF31, 0x2CD99E8B, 0x5BDEAE1D,
            0x9B64C2B0, 0xEC63F226, 0x756AA39C, 0x026D930A, 0x9C0906A9, 0xEB0E363F, 0x72076785, 0x05005713,
            0x95BF4A82, 0xE2B87A14, 0x7BB12BAE, 0x0CB61B38, 0x92D28E9B, 0xE5D5BE0D, 0x7CDCEFB7, 0x0BDBDF21,
            0x86D3D2D4, 0xF1D4E242, 0x68DDB3F8, 0x1FDA836E, 0x81BE16CD, 0xF6B9265B, 0x6FB077E1, 0x18B74777,
            0x88085AE6, 0xFF0F6A70, 0x66063BCA, 0x11010B5C, 0x8F659EFF, 0xF862AE69, 0x616BFFD3, 0x166CCF45,
            0xA00AE278, 0xD70DD2EE, 0x4E048354, 0x3903B3C2, 0xA7672661, 0xD06016F7, 0x4969474D, 0x3E6E77DB,
            0xAED16A4A, 0xD9D65ADC, 0x40DF0B66, 0x37D83BF0, 0xA9BCAE53, 0xDEBB9EC5, 0x47B2CF7F, 0x30B5FFE9,
            0xBDBDF21C, 0xCABAC28A, 0x53B39330, 0x24B4A3A6, 0xBAD03605, 0xCDD70693, 0x54DE5729, 0x23D967BF,
            0xB3667A2E, 0xC4614AB8, 0x5D681B02, 0x2A6F2B94, 0xB40BBE37, 0xC30C8EA1, 0x5A05DF1B, 0x2D02EF8D,
        };

        //预留空间，减少resize
        table16.reserve(tableLength);
        table32.reserve(tableLength);
        for (int i = 0; i < tableLength; i++)
        {
            table16.push_back(tempTable16[i]);
            table32.push_back(tempTable32[i]);
        }
    }
    //////////////////////////////////////////////////////////////////////////
    //计算16位CRC校验码
    //@input    需要计算的字符串
    //@return   16位CRC校验码
    unsigned short Compute16(const std::string& input)
    {
        return Compute16((const unsigned char*)input.c_str(), (int) input.length());
    }

    //////////////////////////////////////////////////////////////////////////
    //计算16位CRC校验码
    //@input    需要计算的字符串
    //@inputLength 输入字符串长度
    //@return   16位CRC校验码
    unsigned short Compute16(const unsigned char* input, const int inputLength)
    {
        unsigned short fcs = 0xFFFF;
        if (input)
        {
            for(int i=0; i< inputLength; i++)
            {
                fcs = (fcs >> 8) ^ table16[(fcs ^ *input++) & 0xFF];
            }
        }
        return ~fcs;
    }

    //////////////////////////////////////////////////////////////////////////
    //计算32位CRC校验码
    //@input    需要计算的字符串
    //@return   32位CRC校验码
    unsigned int Compute32(const std::string& input)
    {
        return Compute32((const unsigned char*)input.c_str(), (int) input.length());
    }

    //////////////////////////////////////////////////////////////////////////
    //计算32位CRC校验码
    //@input    需要计算的字符串
    //@inputLength 输入字符串长度
    //@return   32位CRC校验码
    unsigned int Compute32(const unsigned char* input, const int inputLength)
    {
        unsigned int fcs = 0xFFFFFFFF;
        if(input)
        {
            for(int i=0; i< inputLength; ++i)
            {
                fcs = (fcs >> 8) ^ table32[(fcs ^ *input++) & 0xFF];
            }
        }
        return ~fcs;
    }

private:

    std::vector<unsigned short> table16;//16位编码表
    std::vector<unsigned int> table32;//32位编码表
};

/* 混沌加密算法 */
class DLL_EXPORT JCLogistic
{
public:
    /******************************************************************************
    * 函数名:JCLogistic.JCLogistic
    * 描述: -初始化类
    *
    * 输入:uValue:算法系数, initValue:算法初始值
    * 输出:
    * 返回值:
    *
    * 修改记录:
    * --------------------
    *    2014/03/20 19:34:44, gaopeng 创建函数
    *
    ******************************************************************************/
    JCLogistic(double uValue, double initValue);
    ~JCLogistic();

public:

    /******************************************************************************
    * 函数名:JCLogistic.ReadDEcodeFile
    * 描述: -读取密文，返回明文内容
    *
    * 输入:fileName:文件名
    * 输出:content:返回明文内容
    * 返回值:
    *
    * 修改记录:
    * --------------------
    *    2014/03/20 20:16:16, gaopeng 创建函数
    *
    ******************************************************************************/
    bool ReadDEcodeFile(const std::string& fileName, std::string& content);

    /******************************************************************************
    * 函数名:JCLogistic.WriteDEcodeFile
    * 描述: -明文加密后，写入文件
    *
    * 输入:fileName:文件名,  contnet:明文内容
    * 输出:
    * 返回值:
    *
    * 修改记录:
    * --------------------
    *    2014/03/20 20:18:1, gaopeng 创建函数
    *
    ******************************************************************************/
    bool WriteDEcodeFile(const std::string& fileName, const std::string& content);


    /******************************************************************************
    * 函数名:JCLogistic.ResetInitValue
    * 描述: -重置加密初始值，在加密，解密前，都要重置初始值，并且保证解密所用的系数，
    *        初始值与加密时用的一致。
    * 输入:
    * 输出:
    * 返回值:
    *
    * 修改记录:
    * --------------------
    *    2014/03/20 20:19:3, gaopeng 创建函数
    *
    ******************************************************************************/
    void ResetInitValue(double initValue);

private:

    /******************************************************************************
    * 函数名:JCLogistic.ChaosKeyCreate
    * 描述: -混沌序列产生函数
    *
    * 输入:
    * 输出:
    * 返回值:
    *
    * 修改记录:
    * --------------------
    *    2014/03/20 20:21:6, gaopeng 创建函数
    *
    ******************************************************************************/
    char ChaosKeyCreate();

    /******************************************************************************
    * 函数名:JCLogistic.DEcodeCharArry
    * 描述: -加密，解密字符串数组
    *
    * 输入:
    * 输出:
    * 返回值:
    *
    * 修改记录:
    * --------------------
    *    2014/03/20 20:21:41, gaopeng 创建函数
    *
    ******************************************************************************/
    void DEcodeCharArry(char* pInput, int len);

private:
    double m_uValue;
    double m_initValue;
};


/******************************************************************************
* 类名:JCAesRijndael
* 描述: -AES rijndael算法封装
* 修改记录:
* --------------------
*    2014/03/30 18:34:10, gaopeng 创建函数
*
******************************************************************************/

typedef std::vector<unsigned char> UCharVer;

class DLL_EXPORT JCAesRijndael
{
#define KEYBITS 256
#define KEYLENGTH(keybits) ((keybits)/8)
#define RKLENGTH(keybits)  ((keybits)/8+28)

public:
	JCAesRijndael();
	~JCAesRijndael();

public:
	UCharVer AESEncrypt(UCharVer strtext, std::string key="");
	UCharVer AESDecrypt(UCharVer strtext, std::string key="");

	std::string CalcEncryptText(const std::string &strPsw);
	std::string CalcDecryptText(const std::string &strEncText);

private:
	unsigned long m_rk[RKLENGTH(KEYBITS)];/*RKLENGTH(KEYBITS)*/
	unsigned char m_key[KEYLENGTH(KEYBITS)];/*KEYLENGTH(KEYBITS)*/
	std::string m_defaultKey;
};

#endif /* _JCALGORITHM_H */

