#ifndef __LOGISTIC_ROTA_H
#define __LOGISTIC_ROTA_H

#include "EncryDecry.h"
#include "rota.h"

class LogROTAClass:public EncryDecryClass
{
public:
	LogROTAClass(char *fn, double key);
	~LogROTAClass();
};

#endif