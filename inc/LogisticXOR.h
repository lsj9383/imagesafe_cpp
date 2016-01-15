#ifndef __LOGISTIC_XOR_H
#define __LOGISTIC_XOR_H

#include "EncryDecry.h"

class LogXORClass:public EncryDecryClass
{
public:
	LogXORClass(char *fn, double key);
	~LogXORClass();
};

#endif