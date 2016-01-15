#include "LogisticNormLSB.h"

LogNormLSBClass::LogNormLSBClass(char *fn, char *efn, double key):InfoHideClass(fn, efn, key)
{
	this->cm = new LogisticClass(key);			//初始化logistic混沌方法，并设置初始值
	this->hm = new NormLSBMethod();				//初始化xor加密方法
}

LogNormLSBClass::~LogNormLSBClass()
{
	delete cm;cm=NULL;							//释放
	delete hm;hm=NULL;							//
}
