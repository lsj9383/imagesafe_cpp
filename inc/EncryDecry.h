#ifndef __ENCRY_DECRY_H
#define __ENCRY_DECRY_H

#include "Imgsf.h"

/*
   ���ܽ����࣬�̳���ͼ��ȫ�࣬���ڵ��ȸ��ּ��ܽ��ܲ���
 * ��Ҫְ���ǣ�	�����˼��ܽ�����Ϊ�࣬�Թ���������ƶ���
				�����˴���������������em�Ĳ��ԡ�
				�����˹��캯������Ҫ�ǹ�����ImgsfClass��ʼ��
 */

class EncryDecryClass:public ImgsfClass
{
protected:
	EncryMethod *em;		//���ܽ�����Ϊ��

public:
	EncryDecryClass(char *fn, double key);
	void process(BYTE flg, char *fn);
};

#endif