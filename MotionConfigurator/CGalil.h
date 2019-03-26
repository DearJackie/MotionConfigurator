#pragma once

#include "gclibo.h"
#include "gclib.h"

#define G_NOT_IMPLEMENTED   (-100)

class CGalil
{
public:
	CGalil();
	~CGalil();

private:
	GCon m_hConnection;

public:
	// Public Method to connect to Galil motion controler
	int Connect(void);
	// When you no longer need to connect to the motion controller, you need to disconnect
	int DisConnect(void);
	// Get information of Galil motion controller
	//GReturn GetInfo(char *pBuf, unsigned int bufSize);
	//GReturn GetData(char *pBuf, unsigned int bufSize);
	//GReturn SetData(char *pBuf, unsigned int bufSize);
	// Send commands to Galil controller
	int Command(const char * pStrCmd);
};

