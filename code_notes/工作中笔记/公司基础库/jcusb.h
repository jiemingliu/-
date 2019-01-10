/******************************************************************************
* �ļ���: jcusb.h
* ����: -
* Copyright(c)2014-2016 JCDZ Co.,Ltd.
*
* �޸ļ�¼:
* --------------------
* v1.0   2014/12/11 09:09:33, gaopeng �����ļ�
*
******************************************************************************/
#ifndef _JCUSB_H
#define _JCUSB_H

#include <map>
#include <string>

#include <list>
#include "jcbase.h"
#include "..\..\..\JCbase\thirdparty\libusb\inc\lusb0_usb.h"
#include "jcnonecopy.h"
#include "jcLock.hpp"


typedef struct _CmdMap_
{
    int m_nCmdValue;
    std::string m_strCmdName;
    int m_nCmdMoudle;
} CmdMap, *pCmdMap;

typedef std::map<std::string, std::string> AttrMap;

typedef std::map<int , int> LibUsbListMap;

struct usb_dev_handle;

class DLL_EXPORT JCUsbWrapper : public JCNonecopy
{
public:
    JCUsbWrapper();
    ~JCUsbWrapper();

public:
    /******************************************************************************
    * ������:JCUsbWrapper.UsbInit
    * ����: -ʹ��ǰ����Usb�ĳ�ʼ��
    *
    * ����:
    * ���:
    * ����ֵ:false:��ʼ��ʧ�ܣ� true:��ʼ���ɹ�
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/12/11 09:09:33, gaopeng ��������
    *
    ******************************************************************************/
    bool UsbInit();

	/******************************************************************************
    * ������:JCUsbWrapper.UsbExit
    * ����: -ʹ���꣬����Usb
    *
    * ����:
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/12/11 09:09:33, gaopeng ��������
    *
    ******************************************************************************/
    void UsbExit();

	/******************************************************************************
    * ������:JCUsbWrapper.OpenDevice
    * ����: -��ָ��vid,pid��usb�豸
    *
    * ����:
    * ���:
    * ����ֵ:false:��ʧ�ܣ� true:�򿪳ɹ�
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/12/11 09:09:33, gaopeng ��������
    *
    ******************************************************************************/
    bool OpenDevice(int nVid, int nPid,int nDevNum);

	/******************************************************************************
    * ������:JCUsbWrapper.CloseDevice
    * ����: -�رմ򿪵��豸
    *
    * ����:
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/12/11 09:09:33, gaopeng ��������
    *
    ******************************************************************************/
    void CloseDevice();

	//�жϽӿ�,�շ�, ֧��CA310 USB�ڶ�д
	int InterruptWrite(int nEp, char* buff, int nLen, int nTimeOut = 1000);

	int InterruptRead(int nEp, char* buff, int nLen, int nTimeOut = 1000);

	//��ȡ���е�usb����Ϣ
	int GetAllUsbInformation(LibUsbListMap* m_tLibUsbListMap, int nVid, int nPid);

	//void OutputLog(std::string strFmt, ...);

	/****************************ͬ���ӿ�******************************************
	/******************************************************************************
    * ������:JCUsbWrapper.SyncControlTransfer
    * ����: -usb Control Transactions
    *
    * ����:
	*	bmRequestType	the request type field for the setup packet
	*	bRequest		the request field for the setup packet
	*	wValue			the value field for the setup packet
	*	wIndex			the index field for the setup packet
	*	data			a suitably-sized data buffer for either input or output (depending on direction bits within bmRequestType)
	*	wLength			the length field for the setup packet. The data buffer should be at least this size.
	*	timeout			timeout (in millseconds) that this function should wait before giving up due to no response being received. For an unlimited timeout, use value 0.
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/12/17 09:09:33, gaopeng ��������
    *
    ******************************************************************************/
    int SyncControlTransfer(unsigned char bmRequestType, 
							unsigned char bRequest, 
							unsigned short wValue, 
							unsigned short wIndex, 
							unsigned char *data, 
							unsigned short wLength, 
							unsigned int timeout);

	/****************************ͬ���ӿ�******************************************
	/******************************************************************************
    * ������:JCUsbWrapper.SyncBulkTransfer
    * ����: -usb Bulk Transactions
    *
    * ����:
	*	endpoint	the address of a valid endpoint to communicate with
	*	data		a suitably-sized data buffer for either input or output (depending on endpoint)
	*	length		for bulk writes, the number of bytes from data to be sent. for bulk reads, the maximum number of bytes to receive into the data buffer.
	*	transferred	output location for the number of bytes actually transferred.
	*	timeout		timeout (in millseconds) that this function should wait before giving up due to no response being received. For an unlimited timeout, use value 0.
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/12/17 09:09:33, gaopeng ��������
    *
    ******************************************************************************/
//     int SyncBulkTransfer(unsigned char endpoint, 
// 						unsigned char *data, 
// 						int length, 
// 						int *transferred, 
// 						unsigned int timeout);

	/****************************ͬ���ӿ�******************************************
	/******************************************************************************
    * ������:JCUsbWrapper.SyncInterruptTransfer
    * ����: -usb Interrupt Transactions
    *
    * ����:
	*	endpoint	the address of a valid endpoint to communicate with
	*	data		a suitably-sized data buffer for either input or output (depending on endpoint)
	*	length		for bulk writes, the number of bytes from data to be sent. for bulk reads, the maximum number of bytes to receive into the data buffer.
	*	transferred	output location for the number of bytes actually transferred.
	*	timeout		timeout (in millseconds) that this function should wait before giving up due to no response being received. For an unlimited timeout, use value 0.
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/12/17 09:09:33, gaopeng ��������
    *
    ******************************************************************************/
// 	int SyncInterruptTransfer(unsigned char endpoint, 
// 							unsigned char *data, 
// 							int length, 
// 							int *transferred, 
// 							unsigned int timeout);

private:
	usb_dev_handle *m_tHandle;
	JCCriticalSection m_tCsUsbPort;
};

#endif /* _JCUSB_H */

