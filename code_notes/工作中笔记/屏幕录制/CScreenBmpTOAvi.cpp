/*************************************************
 ��ScreenBmpTOAvi��ʵ���ļ�
 ��/***��ʼ��ע�����Ҹ��˾��ñȽ������ĵط�
************x-ke***********************************/

#include "StdAfx.h"
#include "CScreenBmpTOAvi.h"

CScreenBmpTOAvi::CScreenBmpTOAvi()
{
	InitMemVariable();

}
void CScreenBmpTOAvi::InitMemVariable()                         //��Ҫ�ֶ��ͷŵı���ȫ����ΪNULL
{
	m_hScrDC=NULL;
	m_hMemDC=NULL;
	m_lpData=NULL;
	m_pStreamCompressed=NULL;
	m_pAviStream=NULL;
	m_pAviFile=NULL;
	m_hBitmap=NULL;
}
void CScreenBmpTOAvi::ReleaseResourse()                         //�ͷ���Դ��Ҫ��ȫ�治�ѱ�����ΪNULL�Ļ������ܻ�����쳣
{
	if(m_hScrDC)
	{
		DeleteDC(m_hScrDC);
		m_hScrDC=NULL;
	}
	if(m_hMemDC)
	{
		DeleteDC(m_hMemDC);
		m_hMemDC=NULL;
	}
	if (m_lpData) 
	{
		GlobalFree(m_lpData);
		m_lpData=NULL;
	}
	if (m_pStreamCompressed)
	{
		AVIStreamRelease(m_pStreamCompressed);
		m_pStreamCompressed=NULL;
	}
	if (m_pAviStream) 
	{
		AVIStreamRelease(m_pAviStream);
		m_pAviStream=NULL;
	}
	if (m_pAviFile) 
	{
        AVIFileRelease(m_pAviFile);
		m_pAviFile=NULL;
	}
	if (m_hBitmap) {
		DeleteObject(m_hBitmap);
		m_hBitmap=NULL;
	}

}

CScreenBmpTOAvi::CScreenBmpTOAvi(LPCSTR outPutPath,CRect region)                //���캯����Ŀ���ǻ�ò�����
{
	  InitMemVariable();
	  AVIFileInit();
      m_nFreamCount=0;
	  m_strPath=outPutPath;
	  int  nX,nY,nX2,nY2;
	  nX=region.left;
	  nY=region.top;
      nX2=region.right;
	  nY2=region.bottom;
	  m_hScrDC  =     CreateDC("DISPLAY",   NULL,   NULL,   NULL);//��������õ���DCΪ����DC 
	  int xScrn   =   GetDeviceCaps(m_hScrDC,   HORZRES);//���������ĻX��Y    
      int yScrn   =   GetDeviceCaps(m_hScrDC,   VERTRES);

	  //////////////////��һ���if��Ϊ�������ǵ��������ܵ���Ļ��ȥ��///////////////
	  if   (nX<0)   
                nX=0;    
      if   (nY<0)   
                nY=0;   
      if   (nX2>xScrn)   
                nX2= xScrn;   
      if   (nY2>yScrn)   
                nY2=yScrn; 
	  m_nTop=nY;
	  m_nLeft=nX;
      this->m_nWidth=nX2-nX;   
      this->m_nHeight=nY2-nY;

}
CScreenBmpTOAvi::CScreenBmpTOAvi(LPCSTR outPutPath,CPoint lefttop,CPoint rightbottom) //���캯����Ŀ���ǻ�ò�����
{
	  InitMemVariable();
	  AVIFileInit();
      m_nFreamCount=0;
	  m_strPath=outPutPath;
	  int  nX,nY,nX2,nY2;
	  nX=lefttop.x;
	  nY=lefttop.y;
      nX2=rightbottom.x;
	  nY2=rightbottom.y;
	  m_hScrDC  =     CreateDC("DISPLAY",   NULL,   NULL,   NULL);//��������õ���DCΪ����DC 
	  int xScrn   =   GetDeviceCaps(m_hScrDC,   HORZRES);//���������ĻX��Y    
      int yScrn   =   GetDeviceCaps(m_hScrDC,   VERTRES);

	  //////////////////��һ���if��Ϊ�������ǵ��������ܵ���Ļ��ȥ��///////////////
	  if   (nX<0)   
                nX=0;    
      if   (nY<0)   
                nY=0;   
      if   (nX2>xScrn)   
                nX2= xScrn;   
      if   (nY2>yScrn)   
                nY2=yScrn; 
	  m_nTop=nY;
	  m_nLeft=nX;
      this->m_nWidth=nX2-nX;   
      this->m_nHeight=nY2-nY;
	
}
CScreenBmpTOAvi::CScreenBmpTOAvi(LPCSTR outPutPath,int left,int top,int right,int bottom )//���캯����Ŀ���ǻ�ò�����
{
	  InitMemVariable();
	  AVIFileInit();
      m_nFreamCount=0;
	  m_strPath=outPutPath;
	  int  nX,nY,nX2,nY2;
	  nX=left;
	  nY=top;
      nX2=right;
	  nY2=bottom;
	  m_hScrDC  =     CreateDC("DISPLAY",   NULL,   NULL,   NULL); //��������õ���DCΪ����DC
	  int xScrn   =   GetDeviceCaps(m_hScrDC,   HORZRES);//���������ĻX��Y    
      int yScrn   =   GetDeviceCaps(m_hScrDC,   VERTRES);

	  //////////////////��һ���if��Ϊ�������ǵ��������ܵ���Ļ��ȥ��///////////////
	  if   (nX<0)   
                nX=0;    
      if   (nY<0)   
                nY=0;   
      if   (nX2>xScrn)   
                nX2= xScrn;   
      if   (nY2>yScrn)   
                nY2=yScrn; 
	  m_nTop=nY;
	  m_nLeft=nX;
      m_nWidth=nX2-nX;   
      m_nHeight=nY2-nY;

	    /* COMPVARS m_CV;
           memset(&m_CV,0,sizeof(COMPVARS));
           //����COMPVARS�ṹ
           m_CV.dwFlags=AVICOMPRESSF_KEYFRAMES|ICMF_COMPVARS_VALID;
           //COMPVARS�ṹ��С
           m_CV.cbSize=sizeof(m_CV);
           //ʹ��divx������
           m_CV.fccHandler=mmioFOURCC('d','i','v','x');
           //����������
           m_CV.fccType=ICTYPE_VIDEO;
           //�򿪱�����,hicΪ���������
           //m_CV.hic=ICOpen(ICTYPE_VIDEO,mmioFOURCC('d','i','v','x'),ICMODE_COMPRESS);
           //��������ܷ���0.
           ICCompressorChoose((AfxGetApp()->m_pMainWnd)->GetSafeHwnd(),
			   ICMF_CHOOSE_DATARATE|ICMF_CHOOSE_KEYFRAME,
			   NULL,
			   NULL,
			   &m_CV,
			   "��ѡ��ѹ����ʽ.."); 

				ZeroMemory(&m_AviCompressOptions,sizeof(AVICOMPRESSOPTIONS));
	            m_AviCompressOptions.fccType=m_CV.fccType;                       //��ʾ��Ƶ                      
	            m_AviCompressOptions.fccHandler=m_CV.fccHandler;                               //ѹ������
	            m_AviCompressOptions.dwFlags=m_CV.dwFlags;//|AVICOMPRESSF_DATARATE;
	            m_AviCompressOptions.dwKeyFrameEvery=1;                                //ÿ����֡����1���ؼ�֡������ȫ�ǹؼ�֡
	            m_AviCompressOptions.dwBytesPerSecond=1000/8;                          
	            m_AviCompressOptions.dwQuality=7500; */                                  //ѹ������


}
CScreenBmpTOAvi::CScreenBmpTOAvi(LPCSTR outPutPath)//���캯����Ŀ���ǻ�ò�����
{
	  InitMemVariable();
	  AVIFileInit();
	  m_nFreamCount=0;
	  m_strPath=outPutPath;
	  m_hScrDC  =     CreateDC("DISPLAY",   NULL,   NULL,   NULL); //��������õ���DCΪ����DC
	  int xScrn   =   GetDeviceCaps(m_hScrDC,   HORZRES);//���������ĻX��Y    
      int yScrn   =   GetDeviceCaps(m_hScrDC,   VERTRES);
      m_nHeight=yScrn;
	  m_nWidth=xScrn;
	  m_nTop=0;
	  m_nLeft=0;

}
CScreenBmpTOAvi::CScreenBmpTOAvi(LPCSTR outPutPath, CWnd* pWnd)//���캯����Ŀ���ǻ�ò�����
{
	InitMemVariable();
	AVIFileInit();
	m_nFreamCount=0;
	m_strPath=outPutPath;
	//m_hScrDC  =     CreateDC("DISPLAY",   NULL,   NULL,   NULL); //��������õ���DCΪ����DC
	m_hScrDC = pWnd->GetDC()->GetSafeHdc();
	int xScrn   =   GetDeviceCaps(m_hScrDC,   HORZRES);//���������ĻX��Y    
	int yScrn   =   GetDeviceCaps(m_hScrDC,   VERTRES);
	m_nHeight=yScrn;
	m_nWidth=xScrn;
	m_nTop=0;
	m_nLeft=0;

}
LRESULT CScreenBmpTOAvi::CreateBmpInfo(BOOL bCursor)      //�ӻ�õĴ����л��λͼ��Ϣ
{
	   

          m_hMemDC  =   CreateCompatibleDC(m_hScrDC);//Ϊ��Ļ�豸�����������ݵ��ڴ��豸������
	      
          //   ����һ������Ļ�豸��������ݵ�λͼ   
          m_hBitmap   =   CreateCompatibleBitmap(m_hScrDC,   m_nWidth,   m_nHeight);   
          //   ����λͼѡ���ڴ��豸��������   
  
          HBITMAP hOldBitmap;
	      hOldBitmap = (HBITMAP)SelectObject(m_hMemDC,   m_hBitmap);
		  //   ����Ļ�豸�����������ڴ��豸��������
          BitBlt(m_hMemDC, 0, 0,m_nWidth, m_nHeight,m_hScrDC,m_nLeft,m_nTop,SRCCOPY);
		  //***�����������˼�ǰ�m_hScrDC�ϵ���m_nLeft��m_nTopΪ���Ͻǿ�Ϊm_nWidth����Ϊm_nHeight
		  //***�������ڴ�DC����0��0Ϊ���Ͻǣ���͸�Ϊm_nWidth��m_nHeight��������ȥ


		  /////////////////////////�õ������Ϣ/////////////////////////////////////
		   if (TRUE==bCursor) {
			 HCURSOR hCursor=GetCursor();//��ȡ��ǰ��꼰��λ��
             POINT ptCursor;
             GetCursorPos(&ptCursor);
             ICONINFO IconInfo; //��ȡ����ͼ������ 

             if (GetIconInfo(hCursor, &IconInfo))
			 {
                 ptCursor.x -= ((int) IconInfo.xHotspot);
                 ptCursor.y -= ((int) IconInfo.yHotspot);
                 if (IconInfo.hbmMask != NULL)
                  DeleteObject(IconInfo.hbmMask);
                 if (IconInfo.hbmColor != NULL)
                  DeleteObject(IconInfo.hbmColor);
			 }
          /////////////////�ڼ����豸�������ϻ����ù��////////////////////////
            DrawIconEx(
                 m_hMemDC, // �豸�����ľ�� 
                 ptCursor.x-m_nLeft,
				 ptCursor.y-m_nTop,//λ��
                 hCursor, // Ҫ���Ĺ����
                 0,
				 0, // width of the icon 
                 0, // index of frame in animated cursor 
                 NULL, // handle to background brush 
                 DI_NORMAL|DI_MASK|DI_IMAGE // icon-drawing flags 
                 );
		///////////////////////////////////////////////////////////////////////
			DWORD dw=GetLastError();

	     } 
	  //�õ���Ļλͼ�ľ��   
       m_hBitmap   = (HBITMAP)  SelectObject(m_hMemDC,   hOldBitmap);       
	  ///////////////////////
       DeleteObject(hOldBitmap);
       hOldBitmap=NULL;
//////////������δ����Ŀ���ǵõ�һ��BITMAP�ṹ������CBitmap��ֱ����HBITMAP����Ҳ����////
	   CBitmap   bm;
	   bm.Attach(m_hBitmap);
       BITMAP   btm;   
       bm.GetBitmap(&btm);
/////////////////////////////////////
	   DWORD   size=btm.bmWidthBytes*btm.bmHeight;     //bmp ���ݴ�С�������ڿ����ռ���ֽ�������λͼ��
       if (0==m_nFreamCount) {
       
	   m_lpData=(LPSTR)GlobalAlloc(GPTR,size);         //***�����ڴ�ռ䣬������C��ALLOC
	   }
//////////////////////////���λͼ�ṹ/////
	   if (0==m_nFreamCount) {
	   ZeroMemory(&m_bmpInfo,sizeof(BITMAPINFO));                    //*****ZeroMemory��������Ƚϳ��������ǰ�һ�γ���Ϊsizeof(..)�ڴ�����ʼ�����е����ָ���������ռ� 
	                                                                 //BITMAPINFO����ṹ��BITMAPINFOHEADER ��RGBQUAD  2��������ɾ�����Ϣ�뿴MSDN 
	   m_bmpInfo.bmiHeader.biPlanes		= 1;                         //����Ϊ1               
	   m_bmpInfo.bmiHeader.biWidth		= btm.bmWidth;               //λͼ��         
	   m_bmpInfo.bmiHeader.biHeight		= btm.bmHeight;              //λͼ��
	   m_bmpInfo.bmiHeader.biCompression	= BI_RGB;                //λͼѹ����ʽ BI_RGBΪ��ѹ����Ҳ��֪���ܲ��ܰ�ѹ���˵�λͼд��ȥ����λ���û�¿���ʽʽ
	   m_bmpInfo.bmiHeader.biBitCount	= btm.bmBitsPixel;           //�趨ÿ������ռ���ٸ�λ
	   m_bmpInfo.bmiHeader.biSize		= sizeof(BITMAPINFOHEADER);  //���ֵ��ʾλͼͷռ�˺ö��ֽ�
	   m_bmpInfo.bmiHeader.biSizeImage= m_bmpInfo.bmiHeader.biWidth
		                              *m_bmpInfo.bmiHeader.biHeight
									  *m_bmpInfo.bmiHeader.biBitCount
									  /8;                             //ͼ���С����Ҳ������Ϊɶ��Ҫ�������ֵ
	   }
	   /////////////////////////////////////////////////////////////////////////
	   /****GetDIBits������������������ض��ܸ�ʽ����λͼ�����һ������ȡ��һ���������� 
///////////////////////////////////////////////////////////////////////*/
	   /*GetDIBits(m_hMemDC,                                   //λͼ���ڵ�DC
		         m_hBitmap,                                  //λͼ���
				 0,                                          //
				 m_bmpInfo.bmiHeader.biHeight,
				 NULL,                      //��������������������Ϊʲô��NULL�һ������
				 (BITMAPINFO*)&m_bmpInfo,
				 DIB_RGB_COLORS
				 );*/                        
	   GetDIBits(m_hMemDC,
		         m_hBitmap,
				 0,
				 m_bmpInfo.bmiHeader.biHeight,
				 (LPVOID)m_lpData,
				 &m_bmpInfo,
				 DIB_RGB_COLORS);//��λͼ����ȡ��m_lpdata��
	   DeleteDC(m_hMemDC);
	   m_hMemDC=NULL;
	   return S_OK;
}

////////////////////////////�������׼��дAVI��/////////////////////////////////////

LRESULT  CScreenBmpTOAvi::ScreenToAviStream(
			COMPVARS &cmopVers,
			DWORD dwKeyFrameEvery,
			DWORD dwFrameRate,						   
			DWORD dwCodec
			)
{
	LRESULT hr=S_OK;
	if(0==m_nFreamCount)//�����һ֡�Ļ���ô�����ȴ��ļ�����дAVI�ļ�ͷ��
             {
			    __try
				{
                AVIFileOpen(&m_pAviFile,m_strPath,OF_WRITE | OF_CREATE,NULL);  //��·����ΪlpszFileNamAVI�ļ����Դ�����д�ķ�ʽ
			////////////////////�趨�ļ�����Ϣ��AVISTREAMINFO�ṹ///////////
                memset(&m_StreamInfo, 0, sizeof(AVISTREAMINFO));                     //���������ZEROMEMORYЧ��һ����
                m_StreamInfo.fccType                = streamtypeVIDEO;               //��ʾΪ��Ƶ
                m_StreamInfo.fccHandler             =dwCodec;                       //ѹ������
                m_StreamInfo.dwScale                = 1;
                m_StreamInfo.dwRate                 = dwFrameRate;                 //rate����scale����֡Ƶ
				m_StreamInfo.dwQuality=-1;                            
                m_StreamInfo.dwSuggestedBufferSize = m_bmpInfo.bmiHeader.biSizeImage ;//���뻺������һ����ΪͼƬ��С
                SetRect(&m_StreamInfo.rcFrame,
					    0,
						0,
						m_bmpInfo.bmiHeader.biWidth,
						m_bmpInfo.bmiHeader.biHeight
						);                                                            //����AVI��ͼƬ���ڵĴ����С

                _tcscpy(m_StreamInfo.szName,_T("Video Stream"));                      //���֣����ȡ
		  ////////////////////////������/////////////////////////////

                hr = AVIFileCreateStream(m_pAviFile,&m_pAviStream,&m_StreamInfo);   
				
		  ///////////////ѹ�����//////////////////////

    
//		///////////////////////////////////////////////////////
				ZeroMemory(&m_AviCompressOptions,sizeof(AVICOMPRESSOPTIONS));
	            m_AviCompressOptions.fccType=streamtypeVIDEO;                          //��ʾ��Ƶ                      
	            m_AviCompressOptions.fccHandler=dwCodec;                               //ѹ������
	            m_AviCompressOptions.dwFlags=AVICOMPRESSF_KEYFRAMES|AVICOMPRESSF_VALID;//|AVICOMPRESSF_DATARATE;
	            m_AviCompressOptions.dwKeyFrameEvery=dwKeyFrameEvery;                                //ÿ����֡����1���ؼ�֡������ȫ�ǹؼ�֡
	            m_AviCompressOptions.dwBytesPerSecond=1000/8;                          
	            m_AviCompressOptions.dwQuality=cmopVers.lQ;                                   //ѹ������
//           ///////////////////////////////////////////     
	             if(AVIERR_OK!=(AVIMakeCompressedStream(&m_pStreamCompressed,
					                                     m_pAviStream,
														 &m_AviCompressOptions,
														 NULL)))                        //����ѹ��AVI��                       
				 {
				   hr= E_FAIL;
		
				 }
		      AVIStreamSetFormat(
					        m_pStreamCompressed,
					        m_nFreamCount,
					        (LPVOID)&m_bmpInfo,
					        sizeof(BITMAPINFOHEADER));
				}
			__except(EXCEPTION_EXECUTE_HANDLER )
			{
				hr= E_FAIL;

			}
	}

///////////////д���ļ���////////////////////////
            __try
			{
			
                AVIStreamWrite(m_pStreamCompressed,                // stream pointer
			                   m_nFreamCount,                    // time of this frame
                               1,                                  // number to write
                               (LPVOID) m_lpData,
                               m_bmpInfo.bmiHeader.biSizeImage ,   // size of this frame
                               0,                                  // flags....
                               NULL,
							   NULL);
			}
			__except(EXCEPTION_EXECUTE_HANDLER )
			{
				hr= E_FAIL;
			}
			
	m_nFreamCount++;
	//GlobalFree(m_lpData);
	//m_lpData=NULL;
	return hr;
}
