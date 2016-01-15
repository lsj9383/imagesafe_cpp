#include "LogisticROTA.h"

LogROTAClass::LogROTAClass(char *fn, double key):EncryDecryClass(fn, key)
{
	this->cm = new LogisticClass(key);			//��ʼ��logistic���緽���������ó�ʼֵ
	this->em = new EncryROTA();					//��ʼ��xor���ܷ���
}

LogROTAClass::~LogROTAClass()
{
	delete cm;cm=NULL;									//�ͷ�
	delete em;em=NULL;									//
}