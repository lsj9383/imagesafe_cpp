#include "rota.h"


/*************************************************************************
function	:equMatrix
param		:M1, M2, M, N
return		:none
description	:将矩阵M2的内容赋值给M1
**************************************************************************/
void equMatrix(DWORD **M1, DWORD **M2, int M, int N)
{
	for (int i=0; i<M; i++)
	{
		for (int j=0; j<N; j++)
		{
			M1[i][j] = M2[i][j];
		}
	}
}

/*************************************************************************
function	:disMatrix
param		:matrix, M, N
return		:none
description	:将矩阵matrix的内容显示
**************************************************************************/
void disMatrix(DWORD **matrix, int M, int N)
{
	for (int i=0; i<M; i++)
	{
		for (int j=0; j<N; j++)
		{
			printf("%4d", matrix[i][j]);
		}
		printf("\n");
	}
}

/*************************************************************************
function	:randInitMatrix
param		:matrix, M, N
return		:none
description	:将矩阵matrix的内容进行随机初始化
**************************************************************************/
void randInitMatrix(DWORD **matrix, int M, int N)
{
	srand(time(0));
	for (int i=0; i<M; i++)
	{
		for (int j=0; j<N; j++)
		{
			matrix[i][j] = rand()%100+1;
		}
	}
}

/*************************************************************************
function	:orderInitMatrix
param		:matrix, M, N
return		:none
description	:将矩阵matrix的内容进行顺序初始化
**************************************************************************/
void orderInitMatrix(DWORD **matrix, int M, int N)
{
	for (int i=0; i<M; i++)
	{
		for (int j=0; j<N; j++)
		{
			matrix[i][j] = i*N+j;
		}
	}
}

/*************************************************************************
function	:clearMatrix
param		:matrix, M, N
return		:none
description	:将矩阵matrix的内容进行清零
**************************************************************************/
void clearMatrix(DWORD **matrix, int M, int N)
{
	for (int i=0; i<M; i++)
	{
		for (int j=0; j<N; j++)
		{
			matrix[i][j] = 0;
		}
	}
}

/*************************************************************************
function	:RotaMatrix
param		:matrix, M, N, opr
return		:none
description	:将matrix矩阵的内容按指定的方式螺旋排列
**************************************************************************/
void RotaMatrix(DWORD **matrix, int M, int N, int opr)
{
	DWORD **rotaMatrix;
	rotaMatrix = (DWORD **)malloc(M * sizeof(DWORD *)); //为矩阵分配空间
	for (int i = 0; i<M; i++)
			rotaMatrix[i] = (DWORD *)malloc(N * sizeof(DWORD));

	switch (opr)
	{
		case 1: SetMatrix1(rotaMatrix, matrix, 0, 0, 0, M, N, M, N);		break;
		case 2:	SetMatrix2(rotaMatrix, matrix, N-1, 0, 0, M, N, M, N);		break;
		case 3:	SetMatrix3(rotaMatrix, matrix, N-1, M-1, 0, M, N, M, N);	break;
		case 4:	SetMatrix4(rotaMatrix, matrix, 0, M-1, 0, M, N, M, N);		break;
		default:	break;
	}

	//equ
	equMatrix(matrix, rotaMatrix, M, N);

	//release buffer
	for (int i = 0; i<M; i++)
			free(rotaMatrix[i]);
	free(rotaMatrix);
}

/*************************************************************************
function	:DeRotaMatrix
param		:matrix, M, N, opr
return		:none
description	:将matrix矩阵的内容按指定的方式解螺旋排列
**************************************************************************/
void DeRotaMatrix(DWORD **matrix, int M, int N, int opr)
{
	DWORD **deRotaMatrix;
	deRotaMatrix = (DWORD **)malloc(M * sizeof(DWORD *)); //为矩阵分配空间
	for (DWORD i = 0; i<M; i++)
			deRotaMatrix[i] = (DWORD *)malloc(N * sizeof(DWORD));

	switch (opr)
	{
		case 1: DeSetMatrix1(deRotaMatrix, matrix, 0, 0, 0, M, N, M, N);		break;
		case 2:	DeSetMatrix2(deRotaMatrix, matrix, N-1, 0, 0, M, N, M, N);		break;
		case 3:	DeSetMatrix3(deRotaMatrix, matrix, N-1, M-1, 0, M, N, M, N);	break;
		case 4:	DeSetMatrix4(deRotaMatrix, matrix, 0, M-1, 0, M, N, M, N);		break;
		default:	break;
	}

	equMatrix(matrix, deRotaMatrix, M, N);

	//release buffer
	for (int i = 0; i<M; i++)
			free(deRotaMatrix[i]);
	free(deRotaMatrix);
}

//=========================================================================================================================================
//=========================================================================================================================================
//==============================================================       ====================================================================
//==============================================================C O R E====================================================================
//==============================================================       ====================================================================
//=========================================================================================================================================
//=========================================================================================================================================

/*************************************************************************
function	:SetMatrix1
description	:左上角为起始点的顺时针螺旋排列(递归型)
**************************************************************************/
void SetMatrix1(DWORD **rotaMatrix, DWORD **oriMatrix, int x, int y, DWORD index, int m, int n, int M, int N)
{
    int i, j;
    if (n<=0 || m<=0)	return;
    if ((n==1) && (m==1)) {
            rotaMatrix[x][y] = oriMatrix[index/N][index%N];
            return;
    }
	else if((m==1)&&(n!=1))
	{
		for (i = x; i < x + n; i++)				/* 上部 */
		{
            rotaMatrix[y][i] = oriMatrix[index/N][index%N];
			index++;
		}
		return ;
	}
	else if((m!=1)&&(n==1))
	{
		for (j = y; j < y + m; j++)				/* 右边 */
		{
            rotaMatrix[j][x] = oriMatrix[index/N][index%N];
			index++;
		}
		return ;
	}


    for (i = x; i < x + n-1; i++)				// 上部
	{
        rotaMatrix[y][i] = oriMatrix[index/N][index%N];
		index++;
	}
    for (j = y; j < y + m-1; j++)				// 右边
	{
        rotaMatrix[j][x+n-1] = oriMatrix[index/N][index%N];
		index++;
	}
    for (i = x+n-1; i > x; i--)					// 底部
	{
        rotaMatrix[y+m-1][i] = oriMatrix[index/N][index%N];
		index++;
	}
    for (j = y+m-1; j > y; j--)					// 左边
	{
        rotaMatrix[j][x] = oriMatrix[index/N][index%N];
		index++;
	}
    SetMatrix1(rotaMatrix, oriMatrix, x+1, y+1, index, m-2, n-2, M, N);     /* 递归 */
}

/*************************************************************************
function	:SetMatrix2
description	:右上角为起始点的顺时针螺旋排列(递归型)
**************************************************************************/
void SetMatrix2(DWORD **rotaMatrix, DWORD **oriMatrix, int x, int y, DWORD index, int m, int n, int M, int N)
{
    int i, j;
    if (n<=0 || m<=0)	return;
    if ((n==1) && (m==1)) {
            rotaMatrix[x][y] = oriMatrix[index/N][index%N];
            return;
    }
	else if((m==1)&&(n!=1))
	{
		for (i = x; i > (N-x-2); i--)					// 底部
		{
			rotaMatrix[y][i] = oriMatrix[index/N][index%N];
			index++;
		}
		return ;
	}
	else if((m!=1)&&(n==1))
	{
		 for (j = y; j < y + m; j++)					// 右边
		{
			rotaMatrix[j][x] = oriMatrix[index/N][index%N];
			index++;
		}
		return ;
	}

    for (j = y; j < y + m-1; j++)				// 右边
	{
        rotaMatrix[j][x] = oriMatrix[index/N][index%N];
		index++;
	}
    for (i = x; i > (N-x-1); i--)					// 底部
	{
        rotaMatrix[y+m-1][i] = oriMatrix[index/N][index%N];
		index++;
	}
    for (j = y+m-1; j > y; j--)					// 左边
	{
        rotaMatrix[j][x-n+1] = oriMatrix[index/N][index%N];
		index++;
	}
	 for (i = x-n+1; i < x ; i++)				// 上部
	{
        rotaMatrix[y][i] = oriMatrix[index/N][index%N];
		index++;
	}
	
//	printf("\n");
//	disMatrix(matrix, M, N);

    SetMatrix2(rotaMatrix, oriMatrix, x-1, y+1, index, m-2, n-2, M, N);     /* 递归 */
}

/*************************************************************************
function	:SetMatrix3
description	:右下角为起始点的顺时针螺旋排列(递归型)
**************************************************************************/
void SetMatrix3(DWORD **rotaMatrix, DWORD **oriMatrix, int x, int y, DWORD index, int m, int n, int M, int N)
{
    int i, j;
    if (n<=0 || m<=0)	return;
    if ((n==1) && (m==1)) {
            rotaMatrix[x][y] = oriMatrix[index/N][index%N];
            return;
    }
	else if((m==1)&&(n!=1))
	{
		for (i = x; i > (N-x-2); i--)					// 底部
		{
			rotaMatrix[y][i] = oriMatrix[index/N][index%N];
			index++;
		}
		return ;
	}
	else if((m!=1)&&(n==1))
	{
		for (j = y; j > (M-y-2); j--)					// 左边
		{
			rotaMatrix[j][x] = oriMatrix[index/N][index%N];
			index++;
		}
		return ;
	}

	for (i = x; i > (N-x-1); i--)					// 底部
	{
        rotaMatrix[y][i] = oriMatrix[index/N][index%N];
		index++;
	}
    for (j = y; j > (M-y-1); j--)					// 左边
	{
        rotaMatrix[j][x-n+1] = oriMatrix[index/N][index%N];
		index++;
	}
	for (i = x-n+1; i < x ; i++)				// 上部
	{
        rotaMatrix[y-m+1][i] = oriMatrix[index/N][index%N];
		index++;
	}
	for (j = y-m+1; j < y; j++)				// 右边
	{
        rotaMatrix[j][x] = oriMatrix[index/N][index%N];
		index++;
	}
//	printf("\n");
//	disMatrix(matrix, M, N);

    SetMatrix3(rotaMatrix, oriMatrix, x-1, y-1, index, m-2, n-2, M, N);     /* 递归 */
}

/*************************************************************************
function	:SetMatrix4
description	:左下角为起始点的顺时针螺旋排列(递归型)
**************************************************************************/
void SetMatrix4(DWORD **rotaMatrix, DWORD **oriMatrix, int x, int y, DWORD index, int m, int n, int M, int N)
{
    int i, j;
    if (n<=0 || m<=0)	return;
    if ((n==1) && (m==1)) {
            rotaMatrix[x][y] = oriMatrix[index/N][index%N];
            return;
    }
	else if((m==1)&&(n!=1))
	{
		for (i = x; i < x + n; i++)					// 上部
		{
			rotaMatrix[y][i] = oriMatrix[index/N][index%N];
			index++;
		}
		return ;
	}
	else if((m!=1)&&(n==1))
	{
		for (j = y; j > (M-y-2); j--)					// 左边
		{
			rotaMatrix[j][x] = oriMatrix[index/N][index%N];
			index++;
		}
		return ;
	}

	for (j = y; j > (M-y-1); j--)					// 左边
	{
        rotaMatrix[j][x] = oriMatrix[index/N][index%N];
		index++;
	}
	for (i = x; i < x + n-1; i++)					// 上部
	{
        rotaMatrix[y-m+1][i] = oriMatrix[index/N][index%N];
		index++;
	}
	for (j = y-m+1; j < y; j++)						// 右边
	{
        rotaMatrix[j][x+n-1] = oriMatrix[index/N][index%N];
		index++;
	}
	for (i = x+n-1; i > x; i--)					// 底部
	{
        rotaMatrix[y][i] = oriMatrix[index/N][index%N];
		index++;
	}

//	printf("\n");
//	disMatrix(matrix, M, N);

    SetMatrix4(rotaMatrix, oriMatrix, x+1, y-1, index, m-2, n-2, M, N);     /* 递归 */
}


void DeSetMatrix1(DWORD **deRotaMatrix, DWORD **rotaMatrix, int x, int y, DWORD index, int m, int n, int M, int N)
{
    int i, j;
    if (n<=0 || m<=0)	return;
    if ((n==1) && (m==1)) 
	{
            deRotaMatrix[index/N][index%N] = rotaMatrix[x][y];
            return;
    }
	else if((m==1)&&(n!=1))
	{
		for (i = x; i < x + n; i++)				/* 上部 */
		{
            deRotaMatrix[index/N][index%N] = rotaMatrix[y][i];
			index++;
		}
		return ;
	}
	else if((m!=1)&&(n==1))
	{
		for (j = y; j < y + m; j++)				/* 右边 */
		{
            deRotaMatrix[index/N][index%N] = rotaMatrix[j][x];
			index++;
		}
		return ;
	}


    for (i = x; i < x + n-1; i++)				// 上部
	{
        deRotaMatrix[index/N][index%N] = rotaMatrix[y][i];
		index++;
	}
    for (j = y; j < y + m-1; j++)				// 右边
	{
        deRotaMatrix[index/N][index%N] = rotaMatrix[j][x+n-1];
		index++;
	}
	for (i = x+n-1; i > x; i--)					// 底部
	{
		deRotaMatrix[index/N][index%N] = rotaMatrix[y+m-1][i];
		index++;
	}
    for (j = y+m-1; j > y; j--)					// 左边
	{
        deRotaMatrix[index/N][index%N] = rotaMatrix[j][x];
		index++;
	}
    DeSetMatrix1(deRotaMatrix, rotaMatrix, x+1, y+1, index, m-2, n-2, M, N);     /* 递归 */
}

void DeSetMatrix2(DWORD **deRotaMatrix, DWORD **rotaMatrix, int x, int y, DWORD index, int m, int n, int M, int N)
{
    int i, j;
    if (n<=0 || m<=0)	return;
    if ((n==1) && (m==1)) {
            deRotaMatrix[index/N][index%N] = rotaMatrix[x][y];
            return;
    }
	else if((m==1)&&(n!=1))
	{
		for (i = x; i > (N-x-2); i--)					// 底部
		{
			deRotaMatrix[index/N][index%N] = rotaMatrix[y][i];
			index++;
		}
		return ;
	}
	else if((m!=1)&&(n==1))
	{
		 for (j = y; j < y + m; j++)					// 右边
		{
			deRotaMatrix[index/N][index%N] = rotaMatrix[j][x];
			index++;
		}
		return ;
	}

    for (j = y; j < y + m-1; j++)				// 右边
	{
        deRotaMatrix[index/N][index%N] = rotaMatrix[j][x];
		index++;
	}
    for (i = x; i > (N-x-1); i--)					// 底部
	{
        deRotaMatrix[index/N][index%N] = rotaMatrix[y+m-1][i];
		index++;
	}
    for (j = y+m-1; j > y; j--)					// 左边
	{
        deRotaMatrix[index/N][index%N] = rotaMatrix[j][x-n+1];
		index++;
	}
	 for (i = x-n+1; i < x ; i++)				// 上部
	{
        deRotaMatrix[index/N][index%N] = rotaMatrix[y][i];
		index++;
	}

    DeSetMatrix2(deRotaMatrix, rotaMatrix, x-1, y+1, index, m-2, n-2, M, N);     /* 递归 */
}

void DeSetMatrix3(DWORD **deRotaMatrix, DWORD **rotaMatrix, int x, int y, DWORD index, int m, int n, int M, int N)
{
    int i, j;
    if (n<=0 || m<=0)	return;
    if ((n==1) && (m==1)) {
            deRotaMatrix[index/N][index%N] = rotaMatrix[x][y];
            return;
    }
	else if((m==1)&&(n!=1))
	{
		for (i = x; i > (N-x-2); i--)					// 底部
		{
			deRotaMatrix[index/N][index%N] = rotaMatrix[y][i];
			index++;
		}
		return ;
	}
	else if((m!=1)&&(n==1))
	{
		for (j = y; j > (M-y-2); j--)					// 左边
		{
			deRotaMatrix[index/N][index%N] = rotaMatrix[j][x];
			index++;
		}
		return ;
	}

	for (i = x; i > (N-x-1); i--)					// 底部
	{
        deRotaMatrix[index/N][index%N] = rotaMatrix[y][i];
		index++;
	}
    for (j = y; j > (M-y-1); j--)					// 左边
	{
        deRotaMatrix[index/N][index%N] = rotaMatrix[j][x-n+1];
		index++;
	}
	for (i = x-n+1; i < x ; i++)				// 上部
	{
        deRotaMatrix[index/N][index%N] = rotaMatrix[y-m+1][i];
		index++;
	}
	for (j = y-m+1; j < y; j++)				// 右边
	{
        deRotaMatrix[index/N][index%N] = rotaMatrix[j][x];
		index++;
	}
//	printf("\n");
//	disMatrix(matrix, M, N);

    DeSetMatrix3(deRotaMatrix, rotaMatrix, x-1, y-1, index, m-2, n-2, M, N);     /* 递归 */
}

void DeSetMatrix4(DWORD **deRotaMatrix, DWORD **rotaMatrix, int x, int y, DWORD index, int m, int n, int M, int N)
{
    int i, j;
    if (n<=0 || m<=0)	return;
    if ((n==1) && (m==1)) {
            deRotaMatrix[index/N][index%N] = rotaMatrix[x][y];
            return;
    }
	else if((m==1)&&(n!=1))
	{
		for (i = x; i < x + n; i++)					// 上部
		{
			deRotaMatrix[index/N][index%N] = rotaMatrix[y][i];
			index++;
		}
		return ;
	}
	else if((m!=1)&&(n==1))
	{
		for (j = y; j > (M-y-2); j--)					// 左边
		{
			deRotaMatrix[index/N][index%N] = rotaMatrix[j][x];
			index++;
		}
		return ;
	}

	for (j = y; j > (M-y-1); j--)					// 左边
	{
        deRotaMatrix[index/N][index%N] = rotaMatrix[j][x];
		index++;
	}
	for (i = x; i < x + n-1; i++)					// 上部
	{
        deRotaMatrix[index/N][index%N] = rotaMatrix[y-m+1][i];
		index++;
	}
	for (j = y-m+1; j < y; j++)						// 右边
	{
        deRotaMatrix[index/N][index%N] = rotaMatrix[j][x+n-1];
		index++;
	}
	for (i = x+n-1; i > x; i--)					// 底部
	{
        deRotaMatrix[index/N][index%N] = rotaMatrix[y][i];
		index++;
	}

//	printf("\n");
//	disMatrix(matrix, M, N);

    DeSetMatrix4(deRotaMatrix, rotaMatrix, x+1, y-1, index, m-2, n-2, M, N);     /* 递归 */
}
