#include "LogisticNormLSB.h"

LogNormLSBClass::LogNormLSBClass(char *fn, char *efn, double key):InfoHideClass(fn, efn, key)
{
	this->cm = new LogisticClass(key);			//��ʼ��logistic���緽���������ó�ʼֵ
	this->hm = new NormLSBMethod();				//��ʼ��xor���ܷ���
}

LogNormLSBClass::~LogNormLSBClass()
{
	delete cm;cm=NULL;							//�ͷ�
	delete hm;hm=NULL;							//
}
