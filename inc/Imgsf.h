#ifndef __IMGSF_H
#define __IMGSF_H

#include "basic.h"

/* 混沌方法头文件 */
#include "ChaosMethod.h"	//接口
#include "Logistic.h"		//接口对应的实例

#include "bmp.h"

/* 加密解密方法头文件 */
#include "EncryMethod.h"	//接口
#include "EncryXOR.h"		//接口对应的实例
#include "EncryROTA.h"

/* 信息隐藏方法头文件 */
#include "HideMethod.h"		//接口
#include "NormLSB.h"		//接口对应的实例

/* 主动认证方法头文件 */
#include "ActiveAuthenMethod.h"		//接口
#include "ActiveAuthenNorm.h"		//接口对应的实例




/*
   图像安全类，是图像加密解密，信息隐藏，图像认证等信息安全操作的抽象类。
*  主要职责是，	定义了混沌行为抽象类，以供所有子类赋予其具体混沌行为。
				定义了密钥，这是所有信息安全操作都需要的。
				定义了图像及其文件名，所有的图像安全操作都是基于某个图像文件进行的。
				定义了构造函数，打开了指定文件的图像, 设置了密钥key。
				定义了析构函数，释放了指定图像所占的内存。
				而混沌行为类的定义，与其释放，都交给子类完成。
*/

/* 图像安全类 */
class ImgsfClass
{
protected:
	ChaosMethod *cm;		//混沌行为类
	double key;				//密钥
	BmpClass *bf;			//操作的图像
	char *fn;				//图像名

public:
	ImgsfClass(char *fn, double key);
	virtual ~ImgsfClass();
	virtual void process(BYTE flg, char *fn)=0;
};

#endif