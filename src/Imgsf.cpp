#include "Imgsf.h"

/*
 * ���캯��. ��ʼ��bmpͼ�񣬼�¼��Կ
 */
ImgsfClass::ImgsfClass(char *fn, double key)
{
	cm = NULL;
	bf = new BmpClass(fn);		//bmpͼ����
	this->fn = fn;				//��¼�ļ���
	bf->OpenFile();				//��ͼ��
	bf->LoadBmp2Pix();			//��������
	this->key = key;			//��Կ
}

/*
 * ��������. �ͷ�bmpͼ���ڴ�
 */
ImgsfClass::~ImgsfClass()
{
	delete bf;bf = NULL;
	if (cm!=NULL){delete cm;cm=NULL;}
}
