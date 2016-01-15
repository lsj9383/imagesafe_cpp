#ifndef __ACTIVE_AUTHEN_H
#define __ACTIVE_AUTHEN_H

#include "Imgsf.h"

class ActiveAuthenClass:public ImgsfClass
{
protected:
	ActiveAuthenMethod *aam;						//主动认真方法

public:
	ActiveAuthenClass(char *fn, double key);		//构造函数, 打开图像文件，读出像素，并且设置密钥.
	void process(BYTE flg, char *fn);				//图像处理
};

#endif