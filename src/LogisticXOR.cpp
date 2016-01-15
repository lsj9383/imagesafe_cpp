#include "LogisticXOR.h"

LogXORClass::LogXORClass(char *fn, double key):EncryDecryClass(fn, key)
{
	this->cm = new LogisticClass(key);			//��ʼ��logistic���緽���������ó�ʼֵ
	this->em = new EncryXOR();					//��ʼ��xor���ܷ���
}

LogXORClass::~LogXORClass()
{
	delete cm;cm=NULL;									//�ͷ�
	delete em;em=NULL;									//
}