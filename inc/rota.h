#ifndef __ROTA_H
#define __ROTA_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bmp.h"

//rota and derota
void RotaMatrix(DWORD **matrix, int M, int N, int opr);
void DeRotaMatrix(DWORD **matrix, int M, int N, int opr);

//basic process
void disMatrix(DWORD **matrix, int M, int N);
void clearMatrix(DWORD **matrix, int M, int N);
void randInitMatrix(DWORD **matrix, int M, int N);
void orderInitMatrix(DWORD **matrix, int M, int N);
void equMatrix(DWORD **M1, DWORD **M2, int M, int N);

//rota algorithm
void SetMatrix1(DWORD **matrix, DWORD **oriMatrix, int x, int y, DWORD index, int m, int n, int M, int N);		//���Ͻ�Ϊ��ʼ��
void SetMatrix2(DWORD **matrix, DWORD **oriMatrix, int x, int y, DWORD index, int m, int n, int M, int N);		//���Ͻ�Ϊ��ʼ��
void SetMatrix3(DWORD **matrix, DWORD **oriMatrix, int x, int y, DWORD index, int m, int n, int M, int N);		//���½�Ϊ��ʼ��
void SetMatrix4(DWORD **matrix, DWORD **oriMatrix, int x, int y, DWORD index, int m, int n, int M, int N);		//���½�Ϊ��ʼ��

//derota algorithm
void DeSetMatrix1(DWORD **deRotaMatrix, DWORD **rotaMatrix, int x, int y, DWORD index, int m, int n, int M, int N);
void DeSetMatrix2(DWORD **deRotaMatrix, DWORD **rotaMatrix, int x, int y, DWORD index, int m, int n, int M, int N);
void DeSetMatrix3(DWORD **deRotaMatrix, DWORD **rotaMatrix, int x, int y, DWORD index, int m, int n, int M, int N);
void DeSetMatrix4(DWORD **deRotaMatrix, DWORD **rotaMatrix, int x, int y, DWORD index, int m, int n, int M, int N);

#endif
