#include "basic.h"
/***********************************************************************
function	: getFileSize
param		: fn--�ļ�·��
return		: �ļ���С
description	: ����ָ���ļ��Ĵ�С
************************************************************************/
DWORD getFileSize(char *fn)
{
	FILE *pFile;
	DWORD size=0;

	pFile = fopen (fn,"rb");
	if (pFile != NULL)
	{
		fseek (pFile, 0, SEEK_END);   ///���ļ�ָ���ƶ��ļ���β
		size=ftell (pFile); ///�����ǰ�ļ�ָ������ļ���ʼ���ֽ���
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
param		: byteVal--��16���Ʒ�����״��ascii��
return		: ��Ӧ��ʮ������ֵ
description	: ��byteValת��Ϊ��Ӧ��ʮ������ֵ
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
param		: matA--����A, matB--����B, rowRange--�з�Χ, colRange--�з�Χ
return		: no
description	: ������ã���matB��ָ����Χλ�õ�Ԫ�أ���ֵ��matA
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
param		: matA--����A, matB--����B, rowRange--�з�Χ, colRange--�з�Χ
return		: no
description	: ��������ã��Ǽ��õķ������.��matB��Ԫ�أ���ֵ��matA��ָ����λ��
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
param		: matA--����A, matB--����B, (M,N)�������С
return		: no
description	: ��matB��ֵ������ͬ���е�matA
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
param		: matA--����A, matB--����B, (M,N)�������С
return		: 0 or 1, �Ƿ���ͬ
description	: ������A�;���B���бȽϣ�ֻҪ��1��Ԫ�ز���ͬ���ͷ��ش���
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
param		: matA--��������, matB--����������, matC--������������, (M,N)--M��N��
return		: no
description	: ��double�Ͷ�ά�������������������Ϊchar�;���
************************************************************************/
void MatrixQ(char **matA, double **matB, WORD matC[][8], int M, int N)			//�����
{
	for (int i=0; i<M; i++)
	{
		for (int j=0; j<N; j++)
		{
			//��������
			if (matB[i][j]>=0)
				matA[i][j] = (char)(matB[i][j]/matC[i][j]+0.5);
			else
				matA[i][j] = (char)(matB[i][j]/matC[i][j]-0.5);
		}
	}
}

