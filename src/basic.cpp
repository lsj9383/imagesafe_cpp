#include "basic.h"
/***********************************************************************
function	: getFileSize
param		: fn--文件路径
return		: 文件大小
description	: 返回指定文件的大小
************************************************************************/
DWORD getFileSize(char *fn)
{
	FILE *pFile;
	DWORD size=0;

	pFile = fopen (fn,"rb");
	if (pFile != NULL)
	{
		fseek (pFile, 0, SEEK_END);   ///将文件指针移动文件结尾
		size=ftell (pFile); ///求出当前文件指针距离文件开始的字节数
		fclose(pFile);
		return size;
	}
	else
	{
		return 0;	
	}
}

/***********************************************************************
function	: char2num
param		: byteVal--是16进制符号形状的ascii码
return		: 对应的十进制数值
description	: 将byteVal转换为对应的十进制数值
************************************************************************/
BYTE char2num(char byteVal)
{
	switch(byteVal)
	{
		case '0':	return 0;
		case '1':	return 1;
		case '2':	return 2;
		case '3':	return 3;
		case '4':	return 4;
		case '5':	return 5;
		case '6':	return 6;
		case '7':	return 7;
		case '8':	return 8;
		case '9':	return 9;
		case 'A':	return 10;
		case 'B':	return 11;
		case 'C':	return 12;
		case 'D':	return 13;
		case 'E':	return 14;
		case 'F':	return 15;
		case 'a':	return 10;
		case 'b':	return 11;
		case 'c':	return 12;
		case 'd':	return 13;
		case 'e':	return 14;
		case 'f':	return 15;
		default:	return 255;
	}
}

/***********************************************************************
function	: MatrixChop
param		: matA--矩阵A, matB--矩阵B, rowRange--行范围, colRange--列范围
return		: no
description	: 矩阵剪裁，将matB中指定范围位置的元素，赋值给matA
************************************************************************/
void MatrixChop(BYTE **matA, BYTE **matB, DWORD *rowRange, DWORD *colRange)
{
	DWORD m=0, n=0;

	for (DWORD i=rowRange[0]; i<=rowRange[1]; i++)
	{
		n=0;
		for (DWORD j=colRange[0]; j<=colRange[1]; j++)
		{
			matA[m][n] = matB[i][j];
			n++;
		}
		m++;
	}
}

/***********************************************************************
function	: MatrixIchop
param		: matA--矩阵A, matB--矩阵B, rowRange--行范围, colRange--列范围
return		: no
description	: 矩阵逆剪裁，是剪裁的反响操作.将matB的元素，赋值给matA中指定的位置
************************************************************************/
void MatrixIchop(BYTE **matA, BYTE **matB, DWORD *rowRange, DWORD *colRange)
{
	DWORD m=0, n=0;

	for (DWORD i=rowRange[0]; i<=rowRange[1]; i++)
	{
		n=0;
		for (DWORD j=colRange[0]; j<=colRange[1]; j++)
		{
			matA[i][j] = matB[m][n];
			n++;
		}
		m++;
	}
}

/***********************************************************************
function	: MatrixEqu
param		: matA--矩阵A, matB--矩阵B, (M,N)两矩阵大小
return		: no
description	: 将matB的值赋给相同行列的matA
************************************************************************/
void MatrixEqu(BYTE **matA, BYTE **matB, int M, int N)
{
	for (int i=0; i<M; i++)
	{
		for (int j=0; j<N; j++)
		{
			matA[i][j] = matB[i][j];
		}
	}
}


/***********************************************************************
function	: MatrixCompare
param		: matA--矩阵A, matB--矩阵B, (M,N)两矩阵大小
return		: 0 or 1, 是否相同
description	: 将矩阵A和矩阵B进行比较，只要有1个元素不相同，就返回错误
************************************************************************/
BYTE MatrixCompare(BYTE **matA, BYTE **matB, int M, int N)
{
	for (int i=0; i<M; i++)
	{
		for (int j=0; j<N; j++)
		{
			if(matA[i][j] != matB[i][j])
			{
				return 0;
			}
		}
	}
	return 1;
}

/***********************************************************************
function	: MatrixQ
param		: matA--量化矩阵, matB--待量化矩阵, matC--量化步长矩阵, (M,N)--M行N列
return		: no
description	: 将double型二维矩阵根据量化步长量化为char型矩阵
************************************************************************/
void MatrixQ(char **matA, double **matB, WORD matC[][8], int M, int N)			//矩阵除
{
	for (int i=0; i<M; i++)
	{
		for (int j=0; j<N; j++)
		{
			//四舍五入
			if (matB[i][j]>=0)
				matA[i][j] = (char)(matB[i][j]/matC[i][j]+0.5);
			else
				matA[i][j] = (char)(matB[i][j]/matC[i][j]-0.5);
		}
	}
}

