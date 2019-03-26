#include "stdafx.h"
#include "Log.h"
#include <iostream> //std::cout

using namespace std;
//USES_CONVERSION;

CLog::CLog()
{
	m_bLogControlEnable = true;
	m_bLogFileEnable = true;
	m_hLogFile = new CStdioFile();//CFile();
	m_bFileOpen = false;
}


CLog::~CLog()
{
	if ( m_hLogFile != NULL)
	{
		if (m_bFileOpen)
		{
			m_hLogFile->Close();
			m_bFileOpen = false;
		}
		delete m_hLogFile;
		m_hLogFile = NULL;
	}
}

bool CLog::LogWrite(const TCHAR *pBuf, TLOGTYPE enuType)
{
	bool ret = false;

	// Log to file
	if (m_hLogFile == NULL)
	{
		cout << "Log File NULL!\n";
	}
	else if (!m_bFileOpen)
	{
		cout << "Log file not opened!\n";
	}
	else
	{
		if (m_bLogFileEnable)
		{
//			char pBufTemp[1024];

//			strcpy_s(pBufTemp, pBuf);
//			strcat(pBufTemp, "\r\t");
			// Write one line
			// Enable the feature of appending the new texts into existing ones. 
			m_hLogFile->SeekToEnd();
//			m_hLogFile->WriteString((LPCTSTR)pBufTemp);// (LPCTSTR)(LPTSTR)pBufTemp);
//			TCHAR buf[] = _T("test4 \nstring4\n");

            // Write a NULl-terminated string ("\0"), "\0" will not be written, no "\n" added if
			// pBuf doesn't have "\n" inside.
//			LPCTSTR lpwstrVal = CA2T(pBuf); //I do not want to use the function CA2T..
			m_hLogFile->WriteString(pBuf);

			ret = true;
		}
	}

	// Log to control UI
	if (m_bLogControlEnable)
	{
		// http://blog.csdn.net/lonelyrains/article/details/8696962
		//UpdateData(TRUE);
		//m_log  += "操作演示开始";
		//m_log  += "\r\n";
		//m_logctrl.SetWindowText(m_log);
		////m_logctrl.SetScrollPos(SB_VERT,m_logctrl.GetLineCount(),TRUE);  
		//m_logctrl.LineScroll(m_logctrl.GetLineCount());
		//UpdateData(FALSE);
		ret = true;
	}

	return ret;
}

bool CLog::LogRead()
{
	bool ret = false;

	if (m_hLogFile != NULL)
	{
		if (m_bLogControlEnable)
		{
			ret = true;
		}

		if (m_bLogFileEnable)
		{
			ret = true;
		}
	}

	return ret;
}

bool CLog::LogStart()
{
	bool ret = false;

	if (m_hLogFile != NULL)
	{
		if (!m_bFileOpen)
		{
			if ( m_hLogFile->Open(_T(".\\Log.log"), 
                CFile::modeCreate | // Access mode options
                CFile::modeReadWrite | // Access mode options
                //CFile::typeText |  // Character mode options
                //CFile::shareDenyWrite |  // share mode options
                CFile::modeNoTruncate    //creation mode options
                                                     ))
			{
				m_bFileOpen = true;
			}
			else
			{
				m_bFileOpen = false;
			}
		}
	}

	return ret;
}


bool CLog::LogStop()
{
	if (m_hLogFile != NULL)
	{
		if (m_bFileOpen)
		{
			m_hLogFile->Close();
			m_bFileOpen = false;
		}
	}

	return true;
}

//void DebugAppend(const char *FileName, const char *str)
//{
//	FILE *fp;
////	fp = fopen(FileName, )
//	
//}