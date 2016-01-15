#include "err.h"

void printError(int errCode)
{
    printf("\n");
	printf("errCode:%d\n", errCode);
	printf("err:");
	switch (errCode)
	{
		case NO_ERR:		printf("没有错误");					break;
		case NO_FILE:		printf("指定的文件不存在");			break;
		case ERR_BMP_TYPE:	printf("错误的bmp模式");				break;
		case ERR_RANGE_KEY:	printf("密钥超过范围");				break;
		case HIDE_OVERLOAD:	printf("要隐藏的数据量过大");			break;
		case HIDE_ERR_KEY:	printf("提取所用的密钥错误");			break;
		case AA_IMAGE_TYPE:	printf("主动认证用到的图像格式错误");	break;
		case PARAMETER_ERR:	printf("系统参数错误");				break;
		case ELSE_ERR     : printf("其他错误");
		default:break;
	}
	printf("\n");
	printf("done!\n");
	exit(0);
}
