/******************************************************************************
* �ļ���: jcsqlitedb.h
* ����: -
* Copyright(c)2014-2016 JCDZ Co.,Ltd.
*
* �޸ļ�¼:
* --------------------
* v1.0   2014/03/18 20:45:29, gaopeng �����ļ�
*
******************************************************************************/
#ifndef _JCSQLITEDB_H
#define _JCSQLITEDB_H

#include <string>
#include <vector>
#include <algorithm>
#include "jcbase.h"

/* ����tableʱ����ѯtableʱ��������vector */
typedef std::vector<std::string> StrVector;

typedef struct
{
	std::string    m_strKey ; 
	char          *m_szBuf ;
	unsigned int   m_nBufSize ; 
}TKeyBuff;
struct sqlite3_stmt;
struct sqlite3;
/* sqlite3_stmt��װ�࣬���ڰ��к�ֵ����ѯ������ */
class DLL_EXPORT JCSqlStmt
{
public:
    JCSqlStmt();
    ~JCSqlStmt();

public:
    /******************************************************************************
    * ������:JCSqlStmt
    * ����: -sql֧�ֲ������������

    * �޸ļ�¼:
    * --------------------
    *    2014/03/18 21:0:42, gaopeng ��������
    *
    ******************************************************************************/
    enum DATATYPE
    {
		/*
		#define SQLITE_INTEGER  1
		#define SQLITE_FLOAT    2
		#define SQLITE_BLOB     4
		#define SQLITE_NULL     5
		#ifdef SQLITE_TEXT
		# undef SQLITE_TEXT     3
		#else
		# define SQLITE_TEXT    3
		�����϶����Ӧ
		*/
        INT = 1,
        FLT = 2,
        TXT = 3,
        BLB = 4,
		NUL = 5,
    };
#define  MAX_MEM_BUF_LEN   1000
    /******************************************************************************
    * ������:JCSqlStmt.InitStmt
    * ����: -��ʼ��JCSqlStmt,ʹ��JCSqlStmt�������ݿ�ǰ�������ȳ�ʼ��
    *
    * ����:statement: Ҫִ�е�sql��䣬db:���ݿ�ָ�룬����Ϊ��
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/03/18 21:7:33, gaopeng ��������
    *
    ******************************************************************************/
    void InitStmt(std::string const& statement, sqlite3* db);

    /******************************************************************************
    * ������:JCSqlStmt.GetColumnType
    * ����: -����ָ���е���������
    *
    * ����:columnIndex:�����(***��1��ʼ***)
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/03/18 21:11:35, gaopeng ��������
    *
    ******************************************************************************/
    DATATYPE GetColumnType(int columnIndex);

    /******************************************************************************
    * ������:JCSqlStmt.ValueInt
    * ����: -����ָ���е���������,Ӧ���ж��Ƿ���Ϊ����
    *
    * ����:columnIndex:�����(***��1��ʼ***)
    * ���:
    * ����ֵ:���ͽ��
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/03/18 21:14:36, gaopeng ��������
    *
    ******************************************************************************/
    int         ValueInt   (int columnIndex);

    /******************************************************************************
    * ������:JCSqlStmt.ValueString
    * ����: -����ָ���е�string����,Ӧ���ж��Ƿ���Ϊstring����
    *
    * ����:columnIndex:�����(***��1��ʼ***)
    * ���:
    * ����ֵ:string���
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/03/18 21:16:36, gaopeng ��������
    *
    ******************************************************************************/
    std::string ValueString(int columnIndex);

	const void*     ValueBlob(int columnIndex,int &nSize);


    /******************************************************************************
    * ������:JCSqlStmt.Bind
    * ����: -�󶨲��뵽�����ֵ����Ӧ����(Ŀǰȫ��Ϊstring����)
    *
    * ����:columnIndex:�����(***��1��ʼ***), value:��Ӧֵ
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/03/18 21:17:43, gaopeng ��������
    *
    ******************************************************************************/
    bool Bind(int columnIndex, std::string const& value);
    bool Bind(int columnIndex, double value);
    bool Bind(int columnIndex, int value);
	bool Bind(int columnIndex,char *buf ,int nBufSize) ; 
    bool BindNull(int columnIndex);
	bool ClearBinds();


    /******************************************************************************
    * ������:JCSqlStmt.Execute
    * ����: -ִ�г�ʼ��JCSqlStmtʱ�������sql���
    *
    * ����:
    * ���:
    * ����ֵ:�ɹ���ʧ��
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/03/18 21:20:30, gaopeng ��������
    *
    ******************************************************************************/
    bool Execute();

    /******************************************************************************
    * ������:JCSqlStmt.NextRow
    * ����: -select����ֵ����һ�����ݣ���һ�������ݴ���ʱ���ã����ݷ���m_stmt
    *
    * ����:
    * ���:
    * ����ֵ:true:����һ���ɶ�����, false:�ѵ������һ������
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/03/18 21:21:33, gaopeng ��������
    *
    ******************************************************************************/
    bool NextRow();


    /******************************************************************************
    * ������:JCSqlStmt.Reset
    * ����: -   /*   Call Reset if not depending on the NextRow cleaning up.
        For example for select count(*) statements. (��NextRow����ʹ��)
    * ����:
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/03/18 21:31:21, gaopeng ��������
    *
    ******************************************************************************/
    bool Reset();

    /******************************************************************************
    * ������:JCSqlStmt.RestartSelect
    * ����: -����JCSqlStmt
    *
    * ����:
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/03/18 21:31:48, gaopeng ��������
    *
    ******************************************************************************/
    bool RestartSelect();

private:
    sqlite3_stmt* m_ptStmt;
};

/* select�������ؽ���� */

class DLL_EXPORT RecordField
{
public:
	std::string strKey;
	std::string strValue;
};

class DLL_EXPORT ResultRecord
{
public:
    std::vector<RecordField> m_tFields;
};

class DLL_EXPORT ResultTable
{
    friend class JCSqliteWrapper;
public:
    ResultTable() : m_nCurRecord(0) {}

    std::vector<ResultRecord> m_tRecords;

    ResultRecord* next()
    {
        if (m_nCurRecord < m_tRecords.size())
        {
            return &(m_tRecords[m_nCurRecord++]);
        }
        return 0;
    }

	ResultRecord* at(int nIndex)
	{
		if (nIndex < 0 || (size_t)nIndex >= m_tRecords.size())
			return 0;
		m_nCurRecord = nIndex;

		return &(m_tRecords[m_nCurRecord++]);
	}

	void Append(ResultTable table)
	{
		m_tRecords.insert(m_tRecords.end(), 
							table.m_tRecords.begin(),
							table.m_tRecords.end());
	}

	unsigned int TableSize()
	{
		return (unsigned int)m_tRecords.size();
	}

	void Reverse()
	{
		std::reverse(m_tRecords.begin(), m_tRecords.end());
	}

    void reset()
    {
        m_tRecords.clear();
        m_nCurRecord=0;
    }

private:
    unsigned int m_nCurRecord;
};

class DLL_EXPORT JCSqliteWrapper
{
public:
    JCSqliteWrapper();
    ~JCSqliteWrapper();

public:
    /******************************************************************************
    * ������:JCSqliteWrapper.OpenDb
    * ����: -���Ѵ��ڵ�db,���db�����ڣ�����false
    *
    * ����:db����
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/03/19 9:18:47, gaopeng ��������
    *
    ******************************************************************************/
    bool OpenDb(std::string const& dbPath);

    /******************************************************************************
    * ������:JCSqliteWrapper.CreateDb
    * ����: -����db
    *
    * ����:
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/03/19 9:20:7, gaopeng ��������
    *
    ******************************************************************************/
    bool CreateDb(std::string const& dbName, bool overWrite=false);

public:
    /******************************************************************************
    * ������:JCSqliteWrapper.CreateTable
    * ����: -����table,ֻ��Opendb��CreateDb�ɹ�����
    *
    * ����:tableName:������columns:��������
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/03/19 9:20:40, gaopeng ��������
    *
    ******************************************************************************/
    bool CreateTable(std::string tableName, StrVector& columns);
	bool CreateTable(std::string tableName,std::string strKeyName, std::string strValueName);

    /******************************************************************************
    * ������:JCSqliteWrapper.InsertItems
    * ����: -ָ�����У���������
    *
    * ����:tableName:������columns:��ֵ����(***��ֵ֤���������ݱ�������ͬ***)
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/03/19 9:22:33, gaopeng ��������
    *
    ******************************************************************************/
    bool InsertItems(std::string tableName, StrVector& columns);
	
    /******************************************************************************
    * ������:JCSqliteWrapper.InsertItems
    * ����: -ָ�����У���������
    *
    * ����:tableName:������keyBuf: key��buf������Ҫ�����洢�ļ�����
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/03/19 9:22:33, gaopeng ��������
    *
    ******************************************************************************/
    bool InsertItems(std::string tableName, TKeyBuff& keyBuf);

    /******************************************************************************
    * ������:JCSqliteWrapper.DeleteItems
    * ����: -ָ�����У���������
    *
    * ����:tableName:������ɾ��items ���� keyBuf �е�m_strKey
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/03/19 9:22:33, gaopeng ��������
    *
    ******************************************************************************/
	bool DeleteItems(std::string tableName,const std::string &strKeyName,const TKeyBuff& keyBuf);

	bool DeleteItemsByCondition(std::string tableName, std::string strCondition);

	/******************************************************************************
    * ������:JCSqliteWrapper.SelectFromTable
    * ����: -��ѯָ����ָ��������
    *
    * ����:tableName:������columns:��������(***��Ϊ�գ�Ĭ�Ϸ���������***), res:���ؽ����
    * ���:
    * ����ֵ: true: ��ѯ�ɹ���false:��ѯʧ��
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/06/19 10:24:38, gaopeng ��������
    *
    ******************************************************************************/
	bool SelectCountFromTable(std::string tableName, ResultTable& res, std::string condition, std::string& errMsg);

    /******************************************************************************
    * ������:JCSqliteWrapper.SelectFromTable
    * ����: -��ѯָ����ָ��������
    *
    * ����:tableName:������columns:��������(***��Ϊ�գ�Ĭ�Ϸ���������***), res:���ؽ����
    * ���:
    * ����ֵ: true: ��ѯ�ɹ���false:��ѯʧ��
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/03/19 9:24:38, gaopeng ��������
    *
    ******************************************************************************/
	bool SelectFromTable(std::string tableName, 
		StrVector columns, 
		ResultTable& res, 
		std::string condition, 
		std::string& errMsg);

	bool SelectFromTable(std::string tableName,
		std::string  keyName,
		std::string  valueName,
		std::string  keyValue ,
		const void * &pBuf,
		int  &nLen,
		std::string& errMsg);
	bool UpdateTable(std::string tableName,
		std::string  keyName,
		std::string  valueName,
		TKeyBuff& keyBuf,
		std::string& errMsg
		);
	void BuildUpCondition(std::string& sql, std::string condition);

	bool SelectStmt(std::string const& stmt, ResultTable& res, std::string& errMsg);

	/******************************************************************************
    * ������:JCSqliteWrapper.ResetDbPointer
    * ����: -����dbָ�룬������������db�ļ���
    *
    * ����:
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/05/16 18:24:38, gaopeng ��������
    *
    ******************************************************************************/
	bool ResetDbPointer();

    /******************************************************************************
    * ������:JCSqliteWrapper.CreateIndex
    * ����: -����ָ���е�����
    *
    * ����:tableName:������columnName:������indexName:������
    * ���:
    * ����ֵ:
    *
    * �޸ļ�¼:
    * --------------------
    *    2014/12/06 15:20:40, gaopeng ��������
    *
    ******************************************************************************/
	bool CreateIndex(std::string tableName, std::string columnName, std::string indexName);

    bool ExecSql(std::string const& stmt);
    std::string LastError();

    //���ݿ��������
    bool Begin   ();
    bool Commit  ();
    bool Rollback();

	//���ݿ�locked�������
	bool ResolveDatabaseLocked(std::string strFile);

private:
    static int SelectCallback(void *p_data, int num_fields, char **p_fields, char **p_col_names);

    sqlite3* m_ptDb;
    JCSqlStmt m_tJCSqlStmt;
	std::string m_strTableName;
	int	m_nValueSize;
	std::string m_strTempDbName;
};

#endif /* _JCSQLITEDB_H */

