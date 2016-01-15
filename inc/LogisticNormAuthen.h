#ifndef __LOGISTIC_NORM_AUTHEN_H
#define __LOGISTIC_NORM_AUTHEN_H

#include "ActiveAuthen.h"

class LogisticNormAuthenClass:public ActiveAuthenClass
{
public:
	LogisticNormAuthenClass(char *fn, double key);
	~LogisticNormAuthenClass();
};

#endif
