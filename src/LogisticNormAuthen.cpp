#include "LogisticNormAuthen.h"


LogisticNormAuthenClass::LogisticNormAuthenClass(char *fn, double key):ActiveAuthenClass(fn, key)
{
	this->cm = new LogisticClass(key);			//��ʼ��logistic���緽���������ó�ʼֵ
	this->aam = new ActiveAuthenNorm(bf);		//��ʼ��������֤����, ������ʼ��һЩ��Ҫ���ڴ�
}

LogisticNormAuthenClass::~LogisticNormAuthenClass()
{
	delete aam;aam=NULL;						//
	delete cm; cm=NULL;
}
