#ifndef __ACTIVE_AUTHEN_H
#define __ACTIVE_AUTHEN_H

#include "Imgsf.h"

class ActiveAuthenClass:public ImgsfClass
{
protected:
	ActiveAuthenMethod *aam;						//�������淽��

public:
	ActiveAuthenClass(char *fn, double key);		//���캯��, ��ͼ���ļ����������أ�����������Կ.
	void process(BYTE flg, char *fn);				//ͼ����
};

#endif