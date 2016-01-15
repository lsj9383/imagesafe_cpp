#ifndef __IMGSF_H
#define __IMGSF_H

#include "basic.h"

/* ���緽��ͷ�ļ� */
#include "ChaosMethod.h"	//�ӿ�
#include "Logistic.h"		//�ӿڶ�Ӧ��ʵ��

#include "bmp.h"

/* ���ܽ��ܷ���ͷ�ļ� */
#include "EncryMethod.h"	//�ӿ�
#include "EncryXOR.h"		//�ӿڶ�Ӧ��ʵ��
#include "EncryROTA.h"

/* ��Ϣ���ط���ͷ�ļ� */
#include "HideMethod.h"		//�ӿ�
#include "NormLSB.h"		//�ӿڶ�Ӧ��ʵ��

/* ������֤����ͷ�ļ� */
#include "ActiveAuthenMethod.h"		//�ӿ�
#include "ActiveAuthenNorm.h"		//�ӿڶ�Ӧ��ʵ��




/*
   ͼ��ȫ�࣬��ͼ����ܽ��ܣ���Ϣ���أ�ͼ����֤����Ϣ��ȫ�����ĳ����ࡣ
*  ��Ҫְ���ǣ�	�����˻�����Ϊ�����࣬�Թ��������ำ������������Ϊ��
				��������Կ������������Ϣ��ȫ��������Ҫ�ġ�
				������ͼ�����ļ��������е�ͼ��ȫ�������ǻ���ĳ��ͼ���ļ����еġ�
				�����˹��캯��������ָ���ļ���ͼ��, ��������Կkey��
				�����������������ͷ���ָ��ͼ����ռ���ڴ档
				��������Ϊ��Ķ��壬�����ͷţ�������������ɡ�
*/

/* ͼ��ȫ�� */
class ImgsfClass
{
protected:
	ChaosMethod *cm;		//������Ϊ��
	double key;				//��Կ
	BmpClass *bf;			//������ͼ��
	char *fn;				//ͼ����

public:
	ImgsfClass(char *fn, double key);
	virtual ~ImgsfClass();
	virtual void process(BYTE flg, char *fn)=0;
};

#endif