/*#pragma once

#include "ICodeurManager.h"


#define CMD_RESET -3

class SerialCodeurManager : public ICodeurManager
{
public:

	SerialCodeurManager(int init);

	virtual void Initialisation();
	virtual void CloseS();
	
	virtual void readAndReset() override;
	virtual void reset() override;

private:
	int initCodeur;
};
*/
