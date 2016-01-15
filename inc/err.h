#ifndef __ERR_H
#define __ERR_H

#include <stdio.h>
#include <stdlib.h>
//错误代码
enum
{
NO_ERR,
NO_FILE,
ERR_BMP_TYPE,
ERR_RANGE_KEY,		//密钥超范围
HIDE_OVERLOAD,
HIDE_ERR_KEY,		//密钥错误，因为待读出的bit数大于了可能的隐藏数
AA_IMAGE_TYPE,		//主动认证中，使用的图像需要行和列是8的倍数，否则报错
PARAMETER_ERR,		//系统参数错误
ELSE_ERR
};

void printError(int errCode);		//打印错误代码

#endif
