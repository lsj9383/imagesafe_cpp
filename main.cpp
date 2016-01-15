#include "LogisticXOR.h"
#include "LogisticROTA.h"
#include "LogisticNormLSB.h"
#include "LogisticNormAuthen.h"

/*****************************************************
指令形式:
imagesafe_module.exe username filename method opr key remark
0.exe		程序名称
1.username	用户名称
2.filename	文件名
3.method	方法
4.opr		操作
5.key		密钥
6.remark	备注(最少要写个NULL)
*******************************************************/

ImgsfClass *Factory(CmdStrc cs)
{
	if (!strcmp(cs.method, "logistic_xor"))
	{
		printf("执行logistic_xor\n");
		return (new LogXORClass(cs.fileRecPath, cs.key));
	}
	else if(!strcmp(cs.method, "logistic_rota"))
	{
		printf("执行logistic_rota\n");
		return (new LogROTAClass(cs.fileRecPath, cs.key));
	}
	else if(!strcmp(cs.method, "logistic_norm_lsb"))
	{
		printf("执行logistic_norm_lsb\n");
		return (new LogNormLSBClass(cs.fileRecPath, cs.efilePath, cs.key));
	}
	else if(!strcmp(cs.method, "logistic_norm_authen"))
	{
		printf("执行logistic_norm_authen\n");
		return (new LogisticNormAuthenClass(cs.fileRecPath, cs.key));
	}
	else
	{
		return NULL;
	}

}

//imagesafe_module.exe username filename method opr key remark
void ReadyCommand(CmdStrc* cs, char *argv[])
{
	//图像名
	sprintf(cs->fileRecPath, "%s/Public/users_pic/%s/rec/%s", cs->syspath, argv[1], argv[2]);		//操作的原始图像文件
	sprintf(cs->fileSavPath, "%s/Public/users_pic/%s/sav/r_%s", cs->syspath, argv[1], argv[2]);	//操作的结果图像文件
	//具体方法、操作、密钥
	cs->method = argv[3];			//方法
	cs->opr = atoi(argv[4]);		//操作
	cs->key = atof(argv[5])/65535.0;//密钥
	//备注
	cs->remark = argv[6];
	if (strcmp(cs->remark, "NULL"))	//remark不为NULL，就加入efile路径
	{
		if (cs->opr == EMBED_FLG)
			sprintf(cs->efilePath, "%s/Public/users_pic/%s/rec/%s", cs->syspath, argv[1], argv[6]);
		else if (cs->opr == EXTRACT_FLG)
			sprintf(cs->efilePath, "%s", cs->fileSavPath);
		else
			sprintf(cs->efilePath, "NULL");
	}
	else
	{
		sprintf(cs->efilePath, "NULL");
	}
}

void DisCommand(CmdStrc cs)
{
	printf("\n/////////////////////////////////////\n");
	printf("fileRecPath: %s\n", cs.fileRecPath);
	printf("fileSavPath: %s\n", cs.fileSavPath);
	printf("method: %s \n", cs.method);
	printf("operation: %d \n", cs.opr);
	printf("key: %f \n", cs.key);
	printf("remark: %s \n", cs.remark);
	printf("efilePath: %s \n", cs.efilePath);
	printf("/////////////////////////////////////\n");
}

void LoadArg(int *argc, char *argv[])
{
	*argc = 7;							//参数数量
	argv[1] = (char *)"lsj";					//用户名
	argv[2] = (char *)"emb_test.bmp";			//操作图片
	argv[3] = (char *)"logistic_norm_lsb";		//操作的类
	argv[4] = (char *)"0";						//类具体执行的操作
	argv[5] = (char *)"0.4";					//密钥
	argv[6] = (char *)"test.txt";				//标注嵌入和提取文件的文件名
//	argv[6] = "NULL";
}

int main(int argc, char *argv[])
{
	CmdStrc cs;
	ImgsfClass *isc;

	char chpath[256];
	getcwd(chpath, 256);

	cs.syspath = chpath;
//	LoadArg(&argc, argv);

	if (argc == 7)
	{
		ReadyCommand(&cs, argv);
		DisCommand(cs);
		isc = Factory(cs);
		isc->process(cs.opr, cs.fileSavPath);
		delete isc;
		printError(NO_ERR);
	}
	else
	{
		printError(PARAMETER_ERR);
	}

	return 0;
}
