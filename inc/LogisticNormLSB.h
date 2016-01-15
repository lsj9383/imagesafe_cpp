#ifndef __LOGISTIC_NORM_LSB_H
#define __LOGISTIC_NORM_LSB_H

#include "InfoHide.h"

class LogNormLSBClass:public InfoHideClass
{
public:
	LogNormLSBClass(char *fn, char *efn, double key);
	~LogNormLSBClass();
};

#endif