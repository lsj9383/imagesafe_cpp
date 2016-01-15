#include "err.h"

void printError(int errCode)
{
    printf("\n");
	printf("errCode:%d\n", errCode);
	printf("err:");
	switch (errCode)
	{
		case NO_ERR:		printf("û�д���");					break;
		case NO_FILE:		printf("ָ�����ļ�������");			break;
		case ERR_BMP_TYPE:	printf("�����bmpģʽ");				break;
		case ERR_RANGE_KEY:	printf("��Կ������Χ");				break;
		case HIDE_OVERLOAD:	printf("Ҫ���ص�����������");			break;
		case HIDE_ERR_KEY:	printf("��ȡ���õ���Կ����");			break;
		case AA_IMAGE_TYPE:	printf("������֤�õ���ͼ���ʽ����");	break;
		case PARAMETER_ERR:	printf("ϵͳ��������");				break;
		case ELSE_ERR     : printf("��������");
		default:break;
	}
	printf("\n");
	printf("done!\n");
	exit(0);
}
