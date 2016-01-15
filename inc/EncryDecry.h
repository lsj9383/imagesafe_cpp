#ifndef __ENCRY_DECRY_H
#define __ENCRY_DECRY_H

#include "Imgsf.h"

/*
   加密解密类，继承了图像安全类，用于调度各种加密解密策略
 * 主要职责是：	定义了加密解密行为类，以供子类策略制定。
				定义了处理函数，这利用了em的策略。
				定义了构造函数，主要是供超类ImgsfClass初始化
 */

class EncryDecryClass:public ImgsfClass
{
protected:
	EncryMethod *em;		//加密解密行为类

public:
	EncryDecryClass(char *fn, double key);
	void process(BYTE flg, char *fn);
};

#endif