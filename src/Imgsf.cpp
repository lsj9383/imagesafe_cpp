#include "Imgsf.h"

/*
 * 构造函数. 初始化bmp图像，记录密钥
 */
ImgsfClass::ImgsfClass(char *fn, double key)
{
	cm = NULL;
	bf = new BmpClass(fn);		//bmp图像类
	this->fn = fn;				//记录文件名
	bf->OpenFile();				//打开图像
	bf->LoadBmp2Pix();			//载入像素
	this->key = key;			//密钥
}

/*
 * 析构函数. 释放bmp图像内存
 */
ImgsfClass::~ImgsfClass()
{
	delete bf;bf = NULL;
	if (cm!=NULL){delete cm;cm=NULL;}
}
