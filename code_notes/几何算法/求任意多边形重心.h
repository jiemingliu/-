/*   ������򵥶����polygon������   
  ��Ҫ�������漸��������   
  void   AddPosPart();       �����ұ���������   
  void   AddNegPart();       ���������������   
  void   AddRegion();         �����������   
  ��ʹ�øó���ʱ�������xtr,ytr,wtr,xtl,ytl,wtl���ȫ�ֱ����Ϳ���ʹ��Щ��������ʽ�õ�����,��Ҫע�⺯���������͵���Ҫ����Ӧ�仯                                             
  */   
  void   AddPosPart(double   x,   double   y,   double   w,   double   &xtr,   double   &ytr,   double   &wtr)   
  {   
        if   (abs(wtr   +   w)<1e-10   )     
        	return;       //   detect   zero   regions     
        xtr   =   (   wtr*xtr   +   w*x   )   /   (   wtr   +   w   );   
        ytr   =   (   wtr*ytr   +   w*y   )   /   (   wtr   +   w   );   
        wtr   =   w   +   wtr;   
        return;   
  }  
 
  void   AddNegPart(double   x,   ouble   y,   double   w,   double   &xtl,   double   &ytl,   double   &wtl)   
  {   
        if   (   abs(wtl   +   w)<1e-10   )       
  				return;       //   detect   zero   regions     
    
        xtl   =   (   wtl*xtl   +   w*x   )   /   (   wtl   +   w   );   
        ytl   =   (   wtl*ytl   +   w*y   )   /   (   wtl   +   w   );   
        wtl   =   w   +   wtl;   
        return;   
  }   
    

  void   AddRegion   (   double   x1,   double   y1,   double   x2,   double   y2,   double   &xtr,   double   &ytr,     
  double   &wtr,   double   &xtl,   double   &ytl,   double   &wtl   )   
  {   
        if   (   abs   (x1   -   x2)<   1e-10   )     
  				return;   
    
        if   (   x2   >   x1   )  
 
        {   
  				AddPosPart   ((x2+x1)/2,   y1/2,   (x2-x1)   *   y1,xtr,ytr,wtr); /*   rectangle   ȫ��   
  �����仯��   */   
  				AddPosPart   ((x1+x2+x2)/3,   (y1+y1+y2)/3,   (x2-x1)*(y2-y1)/2,xtr,ytr,wtr);       
    //   triangle   ȫ�ֱ����仯��   
        }   
        else   
        {   
  				AddNegPart   ((x2+x1)/2,   y1/2,   (x2-x1)   *   y1,xtl,ytl,wtl);     
  //   rectangle   ȫ�ֱ����仯��   
  				AddNegPart   ((x1+x2+x2)/3,   (y1+y1+y2)/3,   (x2-x1)*(y2-y1)/2,xtl,ytl,wtl);     
  //   triangle     ȫ�ֱ����仯��   
        }   
  }   
    
  POINT   cg_simple(int   vcount,POINT   polygon[])   
  {   
        double   xtr,ytr,wtr,xtl,ytl,wtl;                 
    //ע�⣺   �����xtr,ytr,wtr,xtl,ytl,wtl�ĳ�ȫ�ֱ���������Ҫɾȥ   
        POINT   p1,p2,tp;   
        xtr   =   ytr   =   wtr   =   0.0;   
        xtl   =   ytl   =   wtl   =   0.0;   
        for(int   i=0;i<vcount;i++)   
              {   
                    p1=polygon;   
                    p2=polygon[(i+1)%vcount];   
                    AddRegion(p1.x,p1.y,p2.x,p2.y,xtr,ytr,wtr,xtl,ytl,wtl);         //ȫ�ֱ����仯��   
              }   
        tp.x   =   (wtr*xtr   +   wtl*xtl)   /   (wtr   +   wtl);   
        tp.y   =   (wtr*ytr   +   wtl*ytl)   /   (wtr   +   wtl);   
        return   tp;   
  }