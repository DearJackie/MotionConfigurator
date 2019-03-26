#pragma once

typedef enum tagLogType {
	LOG_TO_FILE = 0,
	LOG_TO_BUF,
	LOG_TO_BOTH
}TLOGTYPE;

class CLog //: public CFile
{
public:
	CLog();
	~CLog();

	bool LogWrite(const TCHAR *pBuf, TLOGTYPE enuType = TLOGTYPE::LOG_TO_BOTH);
	bool LogRead();

protected:
	CStdioFile *m_hLogFile;
	bool m_bLogFileEnable;

	CStatic m_controlLog;
	bool m_bLogControlEnable;

	bool m_bFileOpen;
public:
	bool LogStart();
	bool LogStop();
};

