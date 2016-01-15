#include "LogisticXOR.h"
#include "LogisticROTA.h"
#include "LogisticNormLSB.h"
#include "LogisticNormAuthen.h"

/*****************************************************
ָ����ʽ:
imagesafe_module.exe username filename method opr key remark
0.exe		��������
1.username	�û�����
2.filename	�ļ���
3.method	����
4.opr		����
5.key		��Կ
6.remark	��ע(����Ҫд��NULL)
*******************************************************/

ImgsfClass *Factory(CmdStrc cs)
{
	if (!strcmp(cs.method, "logistic_xor"))
	{
		printf("ִ��logistic_xor\n");
		return (new LogXORClass(cs.fileRecPath, cs.key));
	}
	else if(!strcmp(cs.method, "logistic_rota"))
	{
		printf("ִ��logistic_rota\n");
		return (new LogROTAClass(cs.fileRecPath, cs.key));
	}
	else if(!strcmp(cs.method, "logistic_norm_lsb"))
	{
		printf("ִ��logistic_norm_lsb\n");
		return (new LogNormLSBClass(cs.fileRecPath, cs.efilePath, cs.key));
	}
	else if(!strcmp(cs.method, "logistic_norm_authen"))
	{
		printf("ִ��logistic_norm_authen\n");
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
	//ͼ����
	sprintf(cs->fileRecPath, "%s/Public/users_pic/%s/rec/%s", cs->syspath, argv[1], argv[2]);		//������ԭʼͼ���ļ�
	sprintf(cs->fileSavPath, "%s/Public/users_pic/%s/sav/r_%s", cs->syspath, argv[1], argv[2]);	//�����Ľ��ͼ���ļ�
	//���巽������������Կ
	cs->method = argv[3];			//����
	cs->opr = atoi(argv[4]);		//����
	cs->key = atof(argv[5])/65535.0;//��Կ
	//��ע
	cs->remark = argv[6];
	if (strcmp(cs->remark, "NULL"))	//remark��ΪNULL���ͼ���efile·��
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
	*argc = 7;							//��������
	argv[1] = (char *)"lsj";					//�û���
	argv[2] = (char *)"emb_test.bmp";			//����ͼƬ
	argv[3] = (char *)"logistic_norm_lsb";		//��������
	argv[4] = (char *)"0";						//�����ִ�еĲ���
	argv[5] = (char *)"0.4";					//��Կ
	argv[6] = (char *)"test.txt";				//��עǶ�����ȡ�ļ����ļ���
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
