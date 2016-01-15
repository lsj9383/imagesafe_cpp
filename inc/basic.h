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
	char *remark;			//���ڱ��� Ƕ������ �� ��ȡ���� ��·��
	char *method;
	char opr;
	double key;
}CmdStrc;

//basic define
#define GIVENUP 100

//basic function
#define SIGN(x) (x<0 ? -1 : 1)				//���ź���
DWORD getFileSize(char *fn);
BYTE char2num(char byteVal);				//��0-F(f)��16�����ַ���ת��Ϊ��Ӧ��10�����ֽ���ֵ
void MatrixChop(BYTE **matA, BYTE **matB, DWORD *rowRange, DWORD *colRange);	//�������
void MatrixIchop(BYTE **matA, BYTE **matB, DWORD *rowRange, DWORD *colRange);	//���������
void MatrixEqu(BYTE **matA, BYTE **matB, int M, int N);							//����ֵ
BYTE MatrixCompare(BYTE **matA, BYTE **matB, int M, int N);						//����Ƚ�
void MatrixQ(char **matA, double **matB, WORD matC[][8], int M, int N);			//�����

#endif
