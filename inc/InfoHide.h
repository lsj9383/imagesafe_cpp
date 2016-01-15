#ifndef __INFOHIDE_H
#define __INFOHIDE_H

#include "Imgsf.h"

class InfoHideClass:public ImgsfClass
{
protected:
	DWORD maxEmbSize;						//����Ƕ��bit��
	DWORD eSize;							//Ƕ��/��ȡ �ļ���С
	HideMethod *hm;							//��Ϣ���ط���������
	char efn[128];							// embedded/extract filename

protected:
	bool ReadyEmbFile(void);

public:
	InfoHideClass(char *fn, char *efn, double key);	//���캯��, ��ͼ���ļ����������أ�����������Կ.
	void process(BYTE flg, char *fn);				//ͼ����
};

#endif