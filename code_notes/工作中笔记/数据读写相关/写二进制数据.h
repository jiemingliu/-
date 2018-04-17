	/**
	 * ����:	�����ֽڸߵ�λ˳��
	 * ȫ��:	WriteEclBinaryFile::SwitchByteOrder
	 * ����:	public 
	 * 
	 * @date	2010/08/24
	 * @author	HUANGL
	 * @param	char * in
	 * @param	char * out
	 * @param	int nSize
	 * @return	void
	 */
	inline void SwitchByteOrder(char* in, char* out, int nSize)
	{
		for (int i = 0; i < nSize; ++i)
		{
			*(out + i) = *(in + nSize - 1 - i);
		}
	}

	/**
	 * ����:	�����ֵ������
	 * ȫ��:	WriteEclBinaryFile::writeNumValue
	 * ����:	public 
	 * 
	 * @date	2010/08/24
	 * @author	HUANGL
	 * @param	char * pData
	 * @param	int nSize
	 * @param	CFile * pFile
	 * @return	void
	 */
	inline void writeNumValue(char* pData, int nSize, CFile* pFile)
	{
		for (int i = nSize - 1; i >= 0; i--)
		{		
			pFile->Write(pData+i, 1);
		}
	}

	/**
	 * ����:	���һ����ֵ������
	 * ȫ��:	WriteEclBinaryFile<_Ty>::writeDataArray
	 * ����:	public 
	 * 
	 * @date	2010/08/24
	 * @author	HUANGL
	 * @param	const std::vector<_Ty> & arrData
	 * @param	CFile * pFile
	 * @return	void
	 */
	template<typename _Ty>
	inline void writeDataArray(const std::vector<_Ty>& arrData, CFile* pFile)
	{
		int nTypeSize = sizeof(_Ty);
		int nTotalSize = (int)arrData.size();
		{
			int nSize;
			int nCount = 0;
			for (int i = 0; i < nTotalSize; ++i)
			{
				if (nCount == 0)
				{
					int nLeftSize = nTotalSize - i;
					if (nLeftSize > MAX_SEG_DATA_NUM)
					{
						nLeftSize = MAX_SEG_DATA_NUM;
					}

					nSize = nLeftSize * nTypeSize;
					writeNumValue((char*)&nSize, 4, pFile);
				}

				writeNumValue((char*)&arrData[i], nTypeSize, pFile);

				if (++nCount == MAX_SEG_DATA_NUM || i == nTotalSize-1)
				{
					writeNumValue((char*)&nSize, 4, pFile);
					nCount = 0;
				}
			}
		}
	}

	/**
	 * ����:	����ַ�������
	 * ȫ��:	WriteEclBinaryFile::stringwrite
	 * ����:	public 
	 * 
	 * @date	2010/08/24
	 * @author	HUANGL
	 * @param	char * chars
	 * @param	int nLength
	 * @param	CFile * pFile
	 * @return	void
	 */
	inline void charswrite(char* chars, int nLength, CFile* pFile)
	{
		pFile->Write(chars, nLength);
	}

	/**
	 * ����:	����ַ�������
	 * ȫ��:	WriteEclBinaryFile::stringwrite
	 * ����:	public 
	 * 
	 * @date	2010/08/24
	 * @author	HUANGL
	 * @param	CString str
	 * @param	CFile * pFile
	 * @return	void
	 */
	inline void stringwrite(const CString& str, CFile* pFile)
	{
		charswrite((char*)(LPCTSTR)str, str.GetLength(), pFile);
	}

	/**
	 * ����:	��8���ַ��������ַ�����,����8λʹ�ÿո���
	 * ȫ��:	WriteEclBinaryFile::charStringwrite
	 * ����:	public 
	 * 
	 * @date	2010/08/24
	 * @author	HUANGL
	 * @param	CString str
	 * @param	CFile * pFile
	 * @return	void
	 */
	inline void charStringwrite(CString str, CFile* pFile)
	{
		int nLength = str.GetLength();
		ASSERT(nLength <= 8);
		if (nLength > 8)
		{
			nLength = 8;
		}

		if (nLength == 8)
		{
			stringwrite(str, pFile);
		}
		else 
		{
			char chars[8];
			memset(chars, SPACE_HEX, 8);
			char* oriChars= str.GetBuffer();
			memcpy(chars, oriChars, nLength);
			charswrite(chars, 8, pFile);
			str.ReleaseBuffer();
		}

	}

	/**
	 * ����:	�������ͷ��ʶ
	 * ȫ��:	WriteEclBinaryFile::writeEVerNum
	 * ����:	public 
	 * 
	 * @date	2010/08/24
	 * @author	HUANGL
	 * @param	CFile * pFile
	 * @return	void
	 */
	inline void writeEVerNum(CFile* pFile)
	{
		writeNumValue((char*)&INT_KEY_HEAD_NUM, 4, pFile);
	}

	/**
	 * ����:	�����������
	 * ȫ��:	WriteEclBinaryFile::writeDataType
	 * ����:	public 
	 * 
	 * @date	2010/08/24
	 * @author	HUANGL
	 * @param	CString sType
	 * @param	CFile * pFile
	 * @return	void
	 */
	inline void writeDataType(CString sType, CFile* pFile)
	{
		char* chars = sType.GetBuffer();
		pFile->Write(chars, sType.GetLength());
		sType.ReleaseBuffer();
	}

	/**
	 * ����:	���һ���ַ�����
	 * ȫ��:	WriteEclBinaryFile::writeCharArray
	 * ����:	public 
	 * 
	 * @date	2010/08/24
	 * @author	HUANGL
	 * @param	std::vector<CString> datas
	 * @param	CFile * pFile
	 * @param	int nMaxSegNum
	 * @return	void
	 */
	inline void writeCharArray(std::vector<CString> datas, CFile* pFile, int nMaxSegNum)
	{
		int nTypeSize = 8;
		int nTotalSize = (int)datas.size();
		{
			int nSize;
			int nCount = 0;
			for (int i = 0; i < nTotalSize; ++i)
			{
				if (nCount == 0)
				{
					int nLeftSize = nTotalSize - i;
					if (nLeftSize > nMaxSegNum)
					{
						nLeftSize = nMaxSegNum;
					}

					nSize = nLeftSize * nTypeSize;
					writeNumValue((char*)&nSize, 4, pFile);
				}

				charStringwrite(datas[i], pFile);

				if (++nCount == nMaxSegNum || i == nTotalSize-1)
				{
					writeNumValue((char*)&nSize, 4, pFile);
					nCount = 0;
				}
			}
		}
	}