#ifndef __ERR_H
#define __ERR_H

#include <stdio.h>
#include <stdlib.h>
//�������
enum
{
NO_ERR,
NO_FILE,
ERR_BMP_TYPE,
ERR_RANGE_KEY,		//��Կ����Χ
HIDE_OVERLOAD,
HIDE_ERR_KEY,		//��Կ������Ϊ��������bit�������˿��ܵ�������
AA_IMAGE_TYPE,		//������֤�У�ʹ�õ�ͼ����Ҫ�к�����8�ı��������򱨴�
PARAMETER_ERR,		//ϵͳ��������
ELSE_ERR
};

void printError(int errCode);		//��ӡ�������

#endif
