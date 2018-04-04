#include "StdAfx.h"
#include ".\dataobjfactory.h"
#include "DataObjFactory_Inline.h"
#include "DataAqufetp.h"
#include "DataAquancon.h"
#include "DataAquct.h"
#include "DataEquil.h"
#include ".\Ado\KeywordAdo.h"
#include "DataEdit\CDataSPECGRID.h"
#include "DataEdit\CDataRSVD.h"
#include "DataEdit\CDATAMINPORV.h"
#include "DataEdit\CDataWRFTPLT.h"
#include "DataEdit\CDataMINPV.h"

//////////////////////////////////////////////////////////////////////////
MapDataBlock CDataObjFactory::m_mapDataBlocks;
MapKeyWord CDataObjFactory::m_mapKeyWords;
MapPoClass CDataObjFactory::m_mapPoClass;
MapPoEntity CDataObjFactory::m_mapPoEntity;

CDataObjFactory::CDataObjFactory(void)
{
}

CDataObjFactory::~CDataObjFactory(void)
{
}

CDataBlock* CDataObjFactory::CreateDataBlock(const CString& strBlockName)
{
	//����ص�����
	typedef CDataBlock* (* ApllyCreate_FUN)(void);
	ApllyCreate_FUN  ApllyCreate = (ApllyCreate_FUN)m_mapDataBlocks[strBlockName];

	ASSERT(ApllyCreate !=NULL);
	//��������
	return ApllyCreate();
}

CDataKeyWord* CDataObjFactory::CreateDataKeyWord(const KeyInfo& keyInfo)
{
	ASSERT(!keyInfo.strDataKey.IsEmpty());

	//����ص�����
	typedef CDataKeyWord* (* ApllyCreate_FUN)(void);
	ApllyCreate_FUN  ApllyCreate = (ApllyCreate_FUN)m_mapKeyWords[keyInfo.strDataKey];

	//��ǰ�����ҵ������������򴴽���֪�ؼ���
	if (ApllyCreate != NULL)
	{
		CDataKeyWord* pKeyWord = ApllyCreate();
		ASSERT(pKeyWord != NULL);
		pKeyWord->SetTittle(keyInfo.strDataKey);
		//��������
		return pKeyWord;
	}

	////��ǰΪʱ���޹����ݣ���Ϊ��������
	//if (!keyInfo.bIsGridData)
	//{
	//	return new CDataText(keyInfo.strDataKey);
	//}
	//else
	//{
	//	return new CDataAngleGrid(keyInfo.strDataKey);
	//}

	//ASSERT(FALSE);
	return new CDataText(keyInfo.strDataKey);
}

CDataPoClass* CDataObjFactory::CreateDataPoClass(const CString& strClassName)
{
	//����ص�����
	typedef CDataPoClass* (* ApllyCreate_FUN)(void);
	ApllyCreate_FUN  ApllyCreate = (ApllyCreate_FUN)m_mapPoClass[strClassName];

	ASSERT(ApllyCreate !=NULL);
	//��������
	return ApllyCreate();
}

CDataPoEntity* CDataObjFactory::CreateDataPoEntity(const CString& strEntityName)
{
	//����ص�����
	typedef CDataPoEntity* (* ApllyCreate_FUN)(void);
	ApllyCreate_FUN  ApllyCreate = (ApllyCreate_FUN)m_mapPoEntity[strEntityName];

	if (ApllyCreate !=NULL)
	{
		CDataPoEntity* pEntity = ApllyCreate();
		pEntity->SetTitle(strEntityName);
		//��������
		return pEntity;
	}

	return NULL;
}

void CDataObjFactory::RegisterType()
{
	//ע��SUMMARY�и��ؼ���
	RegisterSummaryKeyWord();

	//ע��DataBlock����
	RegisterDataBlockType();
	//ע��KeyWord����
	RegisterDataKeyWordType();
	//ע��PoClass����
	RegisterPoClassType();
	//ע��PoEntity����
	RegisterPoEntityType();
}

void CDataObjFactory::RegisterDataBlockType()
{
	//ע��CDataRunspec����
	AddDataBlockType<CDataRunspec>();
	//ע��CDataGrid����
	AddDataBlockType<CDataGrid>();
	//ע��CDataEdit����
	AddDataBlockType<CDataEdit>();
	//ע��CDataProps����
	AddDataBlockType<CDataProps>();
	//ע��CDataRegions����
	AddDataBlockType<CDataRegions>();
	//ע��CDataSolution����
	AddDataBlockType<CDataSolution>();
	//ע��CDataSummary����
	AddDataBlockType<CDataSummary>();
	//ע��CDataSchedule����
	AddDataBlockType<CDataSchedule>();
	//ע��CDataOptimize����
	AddDataBlockType<CDataOptimize>();
}

void CDataObjFactory::RegisterDataKeyWordType()
{
	//ע��CDataGefac����
	AddDataKeyWordType<CDataGefac>();

	//ע��CDataTstep����
	AddDataKeyWordType<CDataTstep>();
	//ע��CDataNumres����
	AddDataKeyWordType<CDataNumres>();
	//ע��CDataCoordsys����
	AddDataKeyWordType<CDataCoordsys>();
	//ע��CDataStart����
	AddDataKeyWordType<CDataStart>();
	//ע��CDataTitle����
	AddDataKeyWordType<CDataTitle>();
	//ע��CDataFaults����
	AddDataKeyWordType<CDataFaults>();
	//ע��CDataLGR����
	AddDataKeyWordType<CDataLGR>();
	//ע��CDataDimens����
	AddDataKeyWordType<CDataDimens>();
	//ע��CDataEqldims����
	AddDataKeyWordType<CDataEqldims>();
	//ע��CDataWellDims����
	AddDataKeyWordType<CDataWelldims>();
	//ע��CDataTabdims����
	AddDataKeyWordType<CDataTabdims>();
	//ע��CDataRegdims����
	AddDataKeyWordType<CDataRegdims>();
	//ע��CDataPvto����
	AddDataKeyWordType<CDataPvto>();
	//ע��CDataUnit����
	AddDataKeyWordType<CDataUnit>();	
	//ע��CDataSimulateState����
	AddDataKeyWordType<CDataSimulateState>();
	//ע��CDataPvdo����
	AddDataKeyWordType<CDataPvdo>();
	//ע��CDataPvtw����
	AddDataKeyWordType<CDataPvtw>();
	//ע��CDataPvtg����
	AddDataKeyWordType<CDataPvtg>();
	//ע��CDataPvdg����
	AddDataKeyWordType<CDataPvdg>();
	//ע��CDataSwof����
	AddDataKeyWordType<CDataSwof>();
	//ע��CDataSgof����
	AddDataKeyWordType<CDataSgof>();
	//ע��CDataSlgof����
	AddDataKeyWordType<CDataSlgof>();
	//ע��CDataSof3����
	AddDataKeyWordType<CDataSof3>();
	//ע��CDataSof2����
	AddDataKeyWordType<CDataSof2>();
	//ע��CDataSwfn����
	AddDataKeyWordType<CDataSwfn>();
	//ע��CDataSgfn����
	AddDataKeyWordType<CDataSgfn>();
	//ע��CDataPvco����
	AddDataKeyWordType<CDataPvco>();
	//ע��CDataPvzg����
	AddDataKeyWordType<CDataPvzg>();
	//ע��CDataWelspecs����
	AddDataKeyWordType<CDataWelspecs>();
	//ע��CDataWelspecl����
	AddDataKeyWordType<CDataWelspecl>();
	//ע��CDataCompdat����
	AddDataKeyWordType<CDataCompdat>();
	//ע��CDataCompdatl����
	AddDataKeyWordType<CDataCompdatl>();
	//ע��CDataWconhist����
	AddDataKeyWordType<CDataWconhist>();
	//ע��CDataWconinj����
	AddDataKeyWordType<CDataWconinj>();
	//ע��CDataDates����
	AddDataKeyWordType<CDataDates>();
	//ע��CDataCoord����
	AddDataKeyWordType<CDataCoord>();
	//ע��CDataZcorn����
	AddDataKeyWordType<CDataZcorn>();
	//ע��CDataAqufetp����
	AddDataKeyWordType<CDataAqufetp>();
	//ע��CDataAqufetp����
	AddDataKeyWordType<CDataAquct>();
	//ע��CDataAqufetp����
	AddDataKeyWordType<CDataAquancon>();
	//ע��CDataEquil����
	AddDataKeyWordType<CDataEquil>();
	//ע��CDataPoro����
	AddDataKeyWordType<CDataAngleGrid>(_T("PORO"));
	//ע��CDataDznet����
	AddDataKeyWordType<CDataAngleGrid>(_T("DZNET"));
	//ע��CDataNtg����
	AddDataKeyWordType<CDataAngleGrid>(_T("NTG"));
	//ע��CDataPermx����
	AddDataKeyWordType<CDataAngleGrid>(_T("PERMX"));
	//ע��CDataPermy����
	AddDataKeyWordType<CDataAngleGrid>(_T("PERMY"));
	//ע��CDataPermz����
	AddDataKeyWordType<CDataAngleGrid>(_T("PERMZ"));
	//ע��CDataGravity����
	AddDataKeyWordType<CDataGravity>();
	//ע��CDataPvds����
	AddDataKeyWordType<CDataPvds>();
	//ע��CDataSgwfn����
	AddDataKeyWordType<CDataSgwfn>();
	//ע��CDataWconinjh����
	AddDataKeyWordType<CDataWconinjh>();
	//ע��CDataWconinje����
	AddDataKeyWordType<CDataWconinje>();
	//ע��CDataWelopen����
	AddDataKeyWordType<CDataWelopen>();
	//ע��CDataWecon����
	AddDataKeyWordType<CDataWecon>();
	//ע��CDataWefac����
	AddDataKeyWordType<CDataWefac>();
	//ע��CDataWelpi����
	AddDataKeyWordType<CDataWelpi>();
	//ע��CDataWpimult����
	AddDataKeyWordType<CDataWpimult>();
	//ע��CDataCompve����
	AddDataKeyWordType<CDataCompve>();	
	//ע��CDataDx����
	AddDataKeyWordType<CDataBlockGrid>(_T("DX"));
	//ע��CDataDy����
	AddDataKeyWordType<CDataBlockGrid>(_T("DY"));
	//ע��CDataDz����
	AddDataKeyWordType<CDataBlockGrid>(_T("DZ"));
	//ע��CDataDx����
	AddDataKeyWordType<CDataBlockGrid>(_T("DXV"));
	//ע��CDataDy����
	AddDataKeyWordType<CDataBlockGrid>(_T("DYV"));
	//ע��CDataDz����
	AddDataKeyWordType<CDataBlockGrid>(_T("DZV"));
	//ע��CDataTops����
	AddDataKeyWordType<CDataBlockGrid>(_T("TOPS"));
	//ע��CDataPvcdo����
	AddDataKeyWordType<CDataPvcdo>();
	//ע��CDataPorv����
	AddDataKeyWordType<CDataAngleGrid>(_T("PORV"));
	//ע��CDataDepth����
	AddDataKeyWordType<CDataAngleGrid>(_T("DEPTH"));
	//ע��CDataPressure����
	AddDataKeyWordType<CDataAngleGrid>(_T("PRESSURE"));
	//ע��CDataSoil����
	AddDataKeyWordType<CDataAngleGrid>(_T("SOIL"));
	//ע��CDataSwat����
	AddDataKeyWordType<CDataAngleGrid>(_T("SWAT"));
	//ע��CDataSgas����
	AddDataKeyWordType<CDataAngleGrid>(_T("SGAS"));
	//ע��CDataGruptree����
	AddDataKeyWordType<CDataGruptree>();
	//ע��CDataWconprod����
	AddDataKeyWordType<CDataWconprod>();
	//ע��CDataMultflt����
	AddDataKeyWordType<CDataMultflt>();
	//ע��CDataCarfin����
	AddDataKeyWordType<CDataCarfin>();
	//ע��CDataBox����
	AddDataKeyWordType<CDataBox>(_T("BOX"));
	////ע��CDataBox����
	//AddDataKeyWordType<CDataBox>(_T("ENDBOX"));
	//ע��CDataField����
	AddDataKeyWordType<CDataField>();
	//ע��CDataMeter����
	AddDataKeyWordType<CDataMetric>();
	//ע��CDataCompsegs����
	AddDataKeyWordType<CDataCompsegs>();
	//ע��CDataWsegdims����
	AddDataKeyWordType<CDataWsegdims>();
	//ע��CDataWelsegs����
	AddDataKeyWordType<CDataWelsegs>();
	//
	AddDataKeyWordType<CDataMapaxes>();
	//
	AddDataKeyWordType<CDataRsconst>();
	//
	AddDataKeyWordType<CDataRsconstt>();
	//
	AddDataKeyWordType<CDataDensity>();
	//
	AddDataKeyWordType<DataEditNnc>();
	AddDataKeyWordType<CDataGridunit>();
	//ֱ�ӿ����Ĺؼ���
	AddDataKeyWordType<CDataSameCopy>(_T("ROCK"));
	AddDataKeyWordType<CDataSameCopy>(_T("RPTSCHED"));
	AddDataKeyWordType<CDataSameCopy>(_T("RPTRST"));
	AddDataKeyWordType<CDataSameCopy>(_T("NEXTSTEP"));
	AddDataKeyWordType<CDataSameCopy>(_T("WELTARG"));
	//AddDataKeyWordType<CDataSameCopy>(_T("WCONPROD"));
	AddDataKeyWordType<CDataSameCopy>(_T("RPTSOL"));
	AddDataKeyWordType<CDataSameCopy>(_T("PMAX"));
	AddDataKeyWordType<CDataSameCopy>(_T("AQUTAB"));
	AddDataKeyWordType<CDataSameCopy>(_T("TUNING"));
	AddDataKeyWordType<CDataSameCopy>(_T("AQUDIMS"));
	AddDataKeyWordType<CDataSameCopy>(_T("AQUALIST"));
	//AddDataKeyWordType<CDataSameCopy>(_T("GRIDUNIT"));
	AddDataKeyWordType<CDataSameCopy>(_T("MAPUNITS"));
	AddDataKeyWordType<CDataSameCopy>(_T("PBVD"));
	AddDataKeyWordType<CDataSameCopy>(_T("DATUM"));
	AddDataKeyWordType<CDataSameCopy>(_T("MSGFILE"));
	AddDataKeyWordType<CDataSameCopy>(_T("SMRYDIMS"));
	AddDataKeyWordType<CDataSameCopy>(_T("DISPDIMS"));
	AddDataKeyWordType<CDataSameCopy>(_T("SCDPDIMS"));
	AddDataKeyWordType<CDataSameCopy>(_T("VFPPDIMS"));
	AddDataKeyWordType<CDataSameCopy>(_T("MESSAGES"));
	AddDataKeyWordType<CDataSameCopy>(_T("NSTACK"));
	AddDataKeyWordType<CDataSameCopy>(_T("EQUIL"));
	AddDataKeyWordType<CDataSameCopy>(_T("PINCH"));
	AddDataKeyWordType<CDataSameCopy>(_T("RTEMP"));

	AddDataKeyWordType<CDataSPECGRID>(_T("SPECGRID")); //���ݺ�
	AddDataKeyWordType<CDataRSVD>(_T("RSVD"));         //���ݺ�
	AddDataKeyWordType<CDATAMINPORV>(_T("MINPORV"));   //���ݺ�
	AddDataKeyWordType<CDataWRFTPLT>(_T("WRFTPLT"));   //���ݺ�
	AddDataKeyWordType<CDataMINPV>(_T("MINPV"));       //���ݺ�

	//////////////////////////////////////////////////////////////////////////
	//ע��CDataModifyKey(ADD)����
	AddDataKeyWordType<CDataModifyKey>(_T("ADD"));//AddDataKeyWordType<CDataAdd>();
	//ע��CDataModifyKey(MULTIPLY)����
	AddDataKeyWordType<CDataModifyKey>(_T("MULTIPLY"));//AddDataKeyWordType<CDataMultiply>();
	//ע��CDataModifyKey(EQUALS)����
	AddDataKeyWordType<CDataModifyKey>(_T("EQUALS"));
	//ע��CDataModifyKey(COPY)����
	AddDataKeyWordType<CDataModifyKey>(_T("COPY"));
	//ע��CDataModifyKey(COPYBOX)����
	AddDataKeyWordType<CDataModifyKey>(_T("COPYBOX"));
	//ע��CDataModifyKey(ADDREG)����
	AddDataKeyWordType<CDataModifyKey>(_T("ADDREG"));
	//ע��CDataModifyKey(MULTIREG)����
	AddDataKeyWordType<CDataModifyKey>(_T("MULTIREG"));
	//ע��CDataModifyKey(MINVALUE)����
	AddDataKeyWordType<CDataModifyKey>(_T("MINVALUE"));
	//ע��CDataModifyKey(MAXVALUE)����
	AddDataKeyWordType<CDataModifyKey>(_T("MAXVALUE"));
	//ע��CDataModifyKey(EQUALREG)����
	AddDataKeyWordType<CDataModifyKey>(_T("EQUALREG"));
	//ע��CDataModifyKey(COPREG)����
	AddDataKeyWordType<CDataModifyKey>(_T("COPYREG"));
	////ע��CDataModifyKey(RPTSOL)����
	//AddDataKeyWordType<CDataModifyKey>(_T("RPTSOL"));
	//ע��CDataModifyKey(PRTSCHED)����
	AddDataKeyWordType<CDataModifyKey>(_T("PRTSCHED"));
	//ע��CDataModifyKey(PRTRST)����
	AddDataKeyWordType<CDataModifyKey>(_T("PRTRST"));
	//ע��CDataModifyKey(RPTREGS)����
	AddDataKeyWordType<CDataModifyKey>(_T("RPTREGS"));
	//ע��CDataModifyKey(RPTPOPS)����
	AddDataKeyWordType<CDataModifyKey>(_T("RPTPOPS"));
	//ע��CDataModifyKey(RPTOPT)����
	AddDataKeyWordType<CDataModifyKey>(_T("RPTOPT"));
	//ע��CDataModifyKey(RPTHMW)����
	AddDataKeyWordType<CDataModifyKey>(_T("RPTHMW"));
	//ע��CDataModifyKey(RPTHMG)����
	AddDataKeyWordType<CDataModifyKey>(_T("RPTHMG"));
	//ע��CDataModifyKey(RPTGRID)����
	AddDataKeyWordType<CDataSameCopy>(_T("RPTGRID")); //���ݺ�
	//////////////////////////////////////////////////////////////////////////
	//ע�᳣������ؼ���
	AddDataKeyWordType<CDataCommonGrid>(_T("EQLNUM"));
	AddDataKeyWordType<CDataCommonGrid>(_T("SATNUM"));
	AddDataKeyWordType<CDataCommonGrid>(_T("PVTNUM"));
	AddDataKeyWordType<CDataCommonGrid>(_T("FIPNUM"));
	AddDataKeyWordType<CDataCommonGrid>(_T("EOSNUM"));
	AddDataKeyWordType<CDataCommonGrid>(_T("ACTNUM"));	
	//////////////////////////////////////////////////////////////////////////
}

//ע��PoClass����
void CDataObjFactory::RegisterPoClassType()
{
	//ע��CDataEGrid����
	AddPoClassType<CDataEGrid>();
	//ע��CDataINIT����
	AddPoClassType<CDataINIT>();
	//ע��CDataRsspec����
	AddPoClassType<CDataRsspec>();
	//ע��CDataSnnnn����
	AddPoClassType<CDataSnnnn>();
	//ע��CDataXnnnn����
	AddPoClassType<CDataXnnnn>();
	//ע��CDataSmspec����
	AddPoClassType<CDataSmspec>();
	//ע��CDataSLNSPEC����
	AddPoClassType<CDataSLNSPEC>();	
	//ע��CDataSLNnnnn����
	AddPoClassType<CDataSLNnnnn>();	
	//ע��HiSim Pro Plot Grd����
	AddPoClassType<CDataHiSimPro>();	
	AddPoClassType<CDataHiSimPlot>();	
	AddPoClassType<CDataHiSimGrd>();
}

//ע��PoEntity����
void CDataObjFactory::RegisterPoEntityType()
{
	//ע��CDataPoDIMENS����
	AddPoEntityType<CDataPoDIMENS>();
	//ע��CDataPoStartDat����
	AddPoEntityType<CDataPoStartDat>();
	//ע��CDataPoACTNUM����
	AddPoEntityType<CDataPoACTNUM>();
	//ע��CDataPoGRIDHEAD����	
	AddPoEntityType<CDataPoGRIDHEAD>();	
	//ע��CDataPoITIME����
	AddPoEntityType<CDataPoITIME>();
	//ע��CDataPoCOORDSYS����
	AddPoEntityType<CDataPoCOORDSYS>();
	//ע��CDataPoCOORD����
	AddPoEntityType<CDataPoCOORD>();
	//ע��CDataPoZCORN����
	AddPoEntityType<CDataPoZCORN>();	
	//////////////////////////////////////////////////////////////////////////
	//���켣���
	//////////////////////////////////////////////////////////////////////////
	//ע��CDataPoIWell����
	AddPoEntityType<CDataPoIWell>();
	//ע��CDataPoICon����
	AddPoEntityType<CDataPoICon>();
	//////////////////////////////////////////////////////////////////////////
	//�������
	//////////////////////////////////////////////////////////////////////////
	//ע��CDataPoParams����
	AddPoEntityType<CDataPoParams>();
	//ע��CDataPoKeywords����
	AddPoEntityType<CDataPoStringParams>( _T("KEYWORDS"));
	//ע��CDataPoWgnames����
	AddPoEntityType<CDataPoStringParams>( _T("WGNAMES"));
	//ע��CDataPoNums����
	AddPoEntityType<CDataPoNums>();
	//��λ
	AddPoEntityType<CDataPoStringParams>( _T("UNITS"));
	//���������뾮�켣��ص�ǰʱ�����еľ���
	AddPoEntityType<CDataPoStringParams>( _T("ZWEL"));
	//ע��CDataPoSEQHDR����
	AddPoEntityType<CDataPoSEQHDR>();
	
	//////////////////////////////////////////////////////////////////////////
	//�����������
	//////////////////////////////////////////////////////////////////////////
	//ע�᲻��ʱ��仯�Ĺؼ���
	AddPoEntityType<CDataPoFloatTableValue>( _T("DX"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("DY"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("DZ"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("TOPS"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("PORV"));	
	AddPoEntityType<CDataPoFloatTableValue>( _T("PERMX"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("PERMY"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("PERMZ"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("TRANX"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("TRANY"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("TRANZ"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("PORO"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("DZNET"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("NTG"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("DEPTH"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("SATNUM"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("PVTNUM"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("EQLNUM"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("FIPNUM"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("FLUXNUM"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("MULTNUM"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("ENDNUM"));


	AddPoEntityType<CDataPoFloatTableValue>( _T("DIFFX"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("DIFFY"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("DIFFZ"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("MULTX"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("MULTY"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("MULTZ"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("MULTX-"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("MULTY-"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("MULTZ-"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("MULTPV"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("MINPVV"));       //���ݺ�


	//ע����ʱ��仯�Ĺؼ���
	AddPoEntityType<CDataPoFloatTableValue>( _T("PRESSURE"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("FIPGAS"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("FIPWAT"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("FIPOIL"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("SWAT"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("SOIL"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("SGAS"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("OOIP"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("OWIP"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("OGIP"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("RS"));
	//ע����ʱ��仯�Ĺؼ�����չ
	AddPoEntityType<CDataPoFloatTableValue>( _T("SWCR"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("SGCR"));


	//��ȷ���Ƿ���õ�������
	AddPoEntityType<CDataPoFloatTableValue>( _T("SWL"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("SWU"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("SGL"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("SGU"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("KRW"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("KRO"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("KRG"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("PCG"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("PCW"));

	AddPoEntityType<CDataPoFloatTableValue>( _T("OILKR"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("OIL_VISC"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("WATKR"));
	AddPoEntityType<CDataPoFloatTableValue>( _T("WAT_VISC"));

	AddPoEntityType<CDataPoFloatTableValue>( _T("Facies")); //���س���΢��ֲ�����


	//ע���������
	//ע��CDataPoLGRPARNT����
	AddPoEntityType<CDataPoLGRPARNT>();
	//ע��CDataPoLGR����
	AddPoEntityType<CDataPoLGR>();
	//ע��CDataPoLGRSGRID����
	AddPoEntityType<CDataPoLGRSGRID>();
	//ע��CDataPoLGRNAME����
	AddPoEntityType<CDataPoLGRNAME>();
	//ע��CDataPoGRIDUNIT����
	AddPoEntityType<CDataPoGRIDUNIT>();
	//////////////////////////////////////////////////////////////////////////
	//�������
	//ע��CDataPoINTEHEAD����	
	AddPoEntityType<CDataPoINTEHEAD>();
	//ע��CDataPoNAMES����
	AddPoEntityType<CDataPoNAMES>();

	//���߷�������
	AddPoEntityType<CDataStreamLineBase>(_T("ID_BEG"));
	AddPoEntityType<CDataStreamLineBase>(_T("ID_END"));
	//������ͷֶ�����
	AddPoEntityType<CDataStreamLineBase>(_T("GEOMETRY"));
	AddPoEntityType<CDataStreamLineBase>(_T("GEOMINDX"));

	//ÿ����һ��ֵ������
	AddPoEntityType<CDataStreamLineBase>(_T("PFRACRES"));
	AddPoEntityType<CDataStreamLineBase>(_T("PFRACOIL"));
	AddPoEntityType<CDataStreamLineBase>(_T("PFRACWAT"));
	AddPoEntityType<CDataStreamLineBase>(_T("PFRACGAS"));

	AddPoEntityType<CDataStreamLineBase>(_T("IFRACRES"));
	AddPoEntityType<CDataStreamLineBase>(_T("IFRACOIL"));
	AddPoEntityType<CDataStreamLineBase>(_T("IFRACWAT"));
	AddPoEntityType<CDataStreamLineBase>(_T("IFRACGAS"));

	//ÿ���߶�(�����������)һ��ֵ������
	AddPoEntityType<CDataStreamLineBase>(_T("LINE_SWAT"));
	AddPoEntityType<CDataStreamLineBase>(_T("ID_CELL"));
	//ÿ����һ��ֵ������
	AddPoEntityType<CDataStreamLineBase>(_T("TIME_BEG"));	
}

void CDataObjFactory::RegisterSummaryKeyWord()
{
	CKeywordAdo ado;
	CADORecordset* dataset;

	try
	{
		dataset = ado.GetKeyword_SUMMARY();
	}
	catch(std::runtime_error e)
	{
		AfxMessageBox(e.what());
	}

	//������
	if (dataset == NULL)
	{
		return;
	}

	int nRowsCount = dataset->GetRecordCount();

	CString strValue;

	for (int nRow = 0; nRow < nRowsCount; nRow++)
	{
		//�ؼ�������
		dataset->GetFieldValue(0, strValue);

		if (strValue.Left(1) == "W")
		{
			AddDataKeyWordType<CDataSummaryW>(strValue);
		}
		else if (strValue.Left(1) == "C")
		{
			AddDataKeyWordType<CDataSummaryC>(strValue);
		}
		else
		{
			AddDataKeyWordType<CDataSameCopy>(strValue);
		}
		
		dataset->MoveNext();
	}
}