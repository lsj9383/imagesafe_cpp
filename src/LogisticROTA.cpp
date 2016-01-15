#include "LogisticROTA.h"

LogROTAClass::LogROTAClass(char *fn, double key):EncryDecryClass(fn, key)
{
	this->cm = new LogisticClass(key);			//初始化logistic混沌方法，并设置初始值
	this->em = new EncryROTA();					//初始化xor加密方法
}

LogROTAClass::~LogROTAClass()
{
	delete cm;cm=NULL;									//释放
	delete em;em=NULL;									//
}