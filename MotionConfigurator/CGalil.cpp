#include "stdafx.h"
#include "CGalil.h"

CGalil::CGalil()
{
	m_hConnection = NULL;
}


CGalil::~CGalil()
{
	DisConnect();
}

// Public Method to connect to Galil motion controler
int CGalil::Connect( void )
{
	GReturn ret = G_NOT_IMPLEMENTED;

	if ( m_hConnection == NULL )
	{
		// --direct -s MG -t 500
		ret = GOpen("192.168.1.8 --subscribe ALL", &m_hConnection);
	}
	else
	{
		ret = G_NO_ERROR;
	}

	return ret;
}


// When you no longer need to connect to the motion controller, you need to disconnect
int CGalil::DisConnect(void)
{
	GReturn ret = G_NOT_IMPLEMENTED;

	if (m_hConnection != NULL)
	{
		ret = GClose(m_hConnection);
		m_hConnection = NULL;
	}
	else
	{
		ret = G_NO_ERROR;
	}

	return ret;
}


// Get information of Galil motion controller
//GReturn CGalil::GetInfo(char *pBuf, unsigned int bufSize)
//{
//	GReturn ret = G_NOT_IMPLEMENTED;
//	GCStringOut strInfo = (GCStringOut)pBuf;
//
//	if (m_hConnection != NULL)
//	{
//		ret = GInfo(m_hConnection, strInfo, (GSize)bufSize);
//	}
//
//	return ret;
//}
//
//
//GReturn CGalil::GetData(char *pBuf, unsigned int bufSize)
//{
//	GReturn ret = G_NOT_IMPLEMENTED;
//
//	return ret;
//}
//
//
//GReturn CGalil::SetData(char *pBuf, unsigned int bufSize)
//{
//	GReturn ret = G_NOT_IMPLEMENTED;
//
//	GCStringOut strInfo = (GCStringOut)pBuf;
//	GBufOut outBuf = (GBufOut)pBuf;
//	GSize retSize = 0;
//	if (m_hConnection != NULL)
//	{
//		ret = GCommand(m_hConnection, "DP", outBuf, (GSize)bufSize, &retSize);
//	}
//
//	return ret;
//}


// Send commands to Galil controller
int CGalil::Command(const char * pStrCmd)
{
	GReturn ret = G_NOT_IMPLEMENTED;

	//GCStringOut strInfo = (GCStringOut)pBuf;
	//GBufOut outBuf = (GBufOut)pBuf;
	//GSize retSize = 0;
	if (m_hConnection != NULL)
	{
		ret = GCommand(m_hConnection, pStrCmd, NULL, 0, NULL );// outBuf, (GSize)bufSize, &retSize);
	}

	return ret;
}
