#ifndef __INFOHIDE_H
#define __INFOHIDE_H

#include "Imgsf.h"

class InfoHideClass:public ImgsfClass
{
protected:
	DWORD maxEmbSize;						//最大的嵌入bit数
	DWORD eSize;							//嵌入/提取 文件大小
	HideMethod *hm;							//信息隐藏方法抽象类
	char efn[128];							// embedded/extract filename

protected:
	bool ReadyEmbFile(void);

public:
	InfoHideClass(char *fn, char *efn, double key);	//构造函数, 打开图像文件，读出像素，并且设置密钥.
	void process(BYTE flg, char *fn);				//图像处理
};

#endif