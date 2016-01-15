#include "EncryXOR.h"

void EncryXOR::Encry(ChaosMethod *cm, BmpClass *bf)
{
	//0).放弃前GIVENUP个系数
	for (int i=0; i<GIVENUP; i++)	cm->GenerateOneDouble();

	//1).迭代次数
	BYTE len=BASIC_XOR_CNT+cm->AutoGenerateBitData(4);		//基础异或次数，加上指定的异或次数

	//2).encry
	for (DWORD c=0; c<len; c++)
	{
		for (DWORD i=0; i<bf->GetHeight(); i++)
		{
			for (DWORD j=0; j<bf->GetWidth(); j++)
			{
				DWORD xxx=0;
				xxx = cm->AutoGenerateBitData(24);				//生成24bit数据
				bf->pix[i][j] = (bf->pix[i][j])^xxx;
			}
		}
	}

	//3)done!
}

void EncryXOR::Decry(ChaosMethod *cm, BmpClass *bf)
{
	//0).放弃前GIVENUP个系数
	for (int i=0; i<GIVENUP; i++)	cm->GenerateOneDouble();

	//1).迭代次数
	BYTE len=BASIC_XOR_CNT+cm->AutoGenerateBitData(4);		//基础异或次数，加上指定的异或次数

	//2).encry
	for (DWORD c=0; c<len; c++)
	{
		for (DWORD i=0; i<bf->GetHeight(); i++)
		{
			for (DWORD j=0; j<bf->GetWidth(); j++)
			{
				DWORD xxx=0;
				xxx = cm->AutoGenerateBitData(24);				//生成24bit数据
				bf->pix[i][j] = (bf->pix[i][j])^xxx;
			}
		}
	}

	//3)done!
}
