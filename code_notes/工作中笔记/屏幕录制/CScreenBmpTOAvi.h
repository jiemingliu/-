/*****************************************************
�������ɵ��ǻ�ȡ��Ļһ������BMP��Ȼ������BMPд�뵽 
һ��AVI�ļ���ȥ
��Ҫ�ڹ���������vfw32.lib����ҪMFC

||||****ע��*********************||||
1��ScreenToAviStream()�����������ʹ��һ��Ҫ�ж����Ƿ��Ѿ��ɹ�����Ȼ���е����ˣ�
   ���ɹ���Ҫֱ��ֹͣ¼�ƣ���
2����Ҫͬʱ¼��2������Ŷ��С��������������
3������һ��Ҫ�ǵ�ReleaseResourse()Ŷ;��Ȼ��¼��AVI���Ǵ򲻿���ɶ�Ӷ�û�У�
||||*****************************||||
����˵����
    CScreenBmpTOAvi bmp(300,300,600,600);
    //CScreenBmpTOAvi bmp1(CRect(200,400,500,700));
	//CScreenBmpTOAvi bmp2(CPoint(0,0),CPoint(500,500));
	//CScreenBmpTOAvi bmp3;
    for (int i=0;i<100;i++) {
		//bmp1.CreateBmpInfo(); 
		//bmp2.CreateBmpInfo();
		//bmp3.CreateBmpInfo();

		bmp.CreateBmpInfo();
		if(E_FAIL==bmp.ScreenToAviStream())
		{
			break;
		}

		//if(E_FAIL==bmp1.ScreenToAviStream(_T("outputrect.avi")))
	//	{
	//		break;
		//}
	//	if(E_FAIL==bmp2.ScreenToAviStream(_T("outputpoint.avi")))
		//{
		//	break;
		//}
		//if(E_FAIL==bmp3.ScreenToAviStream(_T("outputfullscreen.avi")))
		//{
		//	break;
		//}
    	Sleep(100);
    }
//	bmp1.ReleaseResourse();
//	bmp2.ReleaseResourse();
//	bmp3.ReleaseResourse();
	bmp.ReleaseResourse();
****************x-ke***07**4***27*********************/
#pragma comment(lib,"vfw32.lib") 

#include <vfw.h>
#ifndef __BMPTOAVI
#define __BMPTOAVI

class CScreenBmpTOAvi{
private:                                            //-------------------��Ա����------------------------||
	int  m_nxScrn,m_nyScrn;                         //��¼��ǰ��Ļ�ֱ���
	int  m_nLeft,m_nTop;                            //��2������ȷ��¼����������Ͻ�λ��         
	int  m_nWidth,m_nHeight;                        //����ĳ��͸ߣ����Ǻ�ǰ����������ϾͿ����ҵ�����Ҫ¼�Ƶ�����
	HDC  m_hScrDC;                                  //��ĻDC��DC�򵥵�˵���Ǵ����ϵ�һ������
	HDC  m_hMemDC;                                  //����ĻDC���Ӧ���ڴ�DC
	LPSTR   m_lpData;                               //һ������ָ�룬���������ڱ���ͼƬ�������
	LPCSTR  m_strPath;
	DWORD m_nFreamCount;                            //֡������
	HBITMAP m_hBitmap;                              //λͼ��������ڱ���ÿ�λ�õ�λͼ��Ϣ
	BITMAPINFO m_bmpInfo;                           //λͼ��Ϣ�ṹ
    PAVIFILE      m_pAviFile;                       //AVI�ļ�ָ�룬���൱��һ���ļ�����
    PAVISTREAM    m_pAviStream;                     //AVI��
	PAVISTREAM	  m_pStreamCompressed;              //AVIѹ����
	AVISTREAMINFO m_StreamInfo;                     //AVI��Ƶ���ṹ
    AVICOMPRESSOPTIONS	m_AviCompressOptions;       //ѹ������
                                                    //����������������������������������������������������||


	void InitMemVariable();                         //��Ҫ�����ڴ棬�������ֶ�ɾ���ĳ�Աȫ����ΪNULL���Ա��ں�������ȷ��ɾ����

public:
	CScreenBmpTOAvi();
	CScreenBmpTOAvi(LPCSTR outPutPath);                                               //������캯����ʾץȡ����������Ļ����    
	CScreenBmpTOAvi(LPCSTR outPutPath, CWnd* pWnd); 
	CScreenBmpTOAvi(LPCSTR outPutPath,CRect region);                                   //������캯������һ�������������
	CScreenBmpTOAvi(LPCSTR outPutPath,CPoint lefttop,CPoint rightbottom);	            //����2����
	CScreenBmpTOAvi(LPCSTR outPutPath,int left,int top,int right,int bottom);          //����4������	                                     
	LRESULT CreateBmpInfo(BOOL bCursor=FALSE);       //����BMP��Ϣ����ȡ����
	LRESULT ScreenToAviStream(                       //��������ǰ���һ��������õ�BMP��Ϣ������д��AVI��Ƶ��ȥ����һ֡�Ļ��ʹ���AVIͷ
		    COMPVARS &cmopVers,
			DWORD dwKeyFrameEvery=3,
			DWORD dwFrameRate =2,					// ֡����
			DWORD dwCodec= mmioFOURCC('M','S','V','C')             //ѹ����ʽ                    			
			);                                   
	void ReleaseResourse();                                          //�ͷ���Դ

	void SetScrHDC(HDC hdcScr){ m_hScrDC = hdcScr;}
};
#endif