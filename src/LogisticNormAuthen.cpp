#include "LogisticNormAuthen.h"


LogisticNormAuthenClass::LogisticNormAuthenClass(char *fn, double key):ActiveAuthenClass(fn, key)
{
	this->cm = new LogisticClass(key);			//初始化logistic混沌方法，并设置初始值
	this->aam = new ActiveAuthenNorm(bf);		//初始化主动认证方法, 这里会初始化一些必要的内存
}

LogisticNormAuthenClass::~LogisticNormAuthenClass()
{
	delete aam;aam=NULL;						//
	delete cm; cm=NULL;
}
