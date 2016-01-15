#include "EncryROTA.h"

void EncryROTA::Encry(ChaosMethod *cm, BmpClass *bf)
{
	//0).放弃前GIVENUP个系数
	for (int i=0; i<GIVENUP; i++)	cm->GenerateOneDouble();

	//1).螺旋次数
	BYTE len=10+cm->AutoGenerateBitData(4);						//生成3bit数据

	//2).螺旋置乱
	for (int i=0; i<len; i++)
	{
		BYTE opr=cm->AutoGenerateBitData(2)+1;					//生成2bit数据
		RotaMatrix(bf->pix, bf->GetHeight(), bf->GetWidth(), opr);
	}
}

void EncryROTA::Decry(ChaosMethod *cm, BmpClass *bf)
{
	//0).放弃前GIVENUP个系数
	for (int i=0; i<GIVENUP; i++)	cm->GenerateOneDouble();

	//1).螺旋次数
	BYTE len=10+cm->AutoGenerateBitData(4);						//生成3bit数据

	//2).螺旋参数
	BYTE *opr = (BYTE *)malloc(len*(sizeof(BYTE)));

	for (int i=0; i<len; i++)
	{
		opr[i]=cm->AutoGenerateBitData(2)+1;					//生成2bit数据
	}

	//3).螺旋恢复
	for (int i=0; i<len; i++)
	{
		DeRotaMatrix(bf->pix, bf->GetHeight(), bf->GetWidth(), opr[len-1-i]);	//(参数倒置)
	}
}
