#ifndef __BASIC_H
#define __BASIC_H

#include "bmp.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "dct.h"
#include "hash.h"
using namespace std;

#define ENCRY_FLG	1
#define DECRY_FLG	0
#define EMBED_FLG	1
#define EXTRACT_FLG	0
#define PROTECT_FLG			2
#define ACTIVE_AUTHEN_FLG	1
#define RECOVER_FLG			0

enum method
{
LOGISTIC_XOR,
LOGISTIC_ROTA,
NORM_LSB,
LOGISTIC_ACTIVE_AUTHEN
};

//struct
typedef struct CMD_STRC
{
	char fileRecPath[128];
	char fileSavPath[128];
	char efilePath[128];
	char *syspath;
	char *remark;			//用于保存 嵌入数据 和 提取数据 的路径
	char *method;
	char opr;
	double key;
}CmdStrc;

//basic define
#define GIVENUP 100

//basic function
#define SIGN(x) (x<0 ? -1 : 1)				//符号函数
DWORD getFileSize(char *fn);
BYTE char2num(char byteVal);				//将0-F(f)的16进制字符，转换为对应的10进制字节数值
void MatrixChop(BYTE **matA, BYTE **matB, DWORD *rowRange, DWORD *colRange);	//矩阵剪裁
void MatrixIchop(BYTE **matA, BYTE **matB, DWORD *rowRange, DWORD *colRange);	//矩阵逆剪裁
void MatrixEqu(BYTE **matA, BYTE **matB, int M, int N);							//矩阵赋值
BYTE MatrixCompare(BYTE **matA, BYTE **matB, int M, int N);						//矩阵比较
void MatrixQ(char **matA, double **matB, WORD matC[][8], int M, int N);			//矩阵除

#endif
