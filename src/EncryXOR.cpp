#include "EncryXOR.h"

void EncryXOR::Encry(ChaosMethod *cm, BmpClass *bf)
{
	//0).����ǰGIVENUP��ϵ��
	for (int i=0; i<GIVENUP; i++)	cm->GenerateOneDouble();

	//1).��������
	BYTE len=BASIC_XOR_CNT+cm->AutoGenerateBitData(4);		//����������������ָ����������

	//2).encry
	for (DWORD c=0; c<len; c++)
	{
		for (DWORD i=0; i<bf->GetHeight(); i++)
		{
			for (DWORD j=0; j<bf->GetWidth(); j++)
			{
				DWORD xxx=0;
				xxx = cm->AutoGenerateBitData(24);				//����24bit����
				bf->pix[i][j] = (bf->pix[i][j])^xxx;
			}
		}
	}

	//3)done!
}

void EncryXOR::Decry(ChaosMethod *cm, BmpClass *bf)
{
	//0).����ǰGIVENUP��ϵ��
	for (int i=0; i<GIVENUP; i++)	cm->GenerateOneDouble();

	//1).��������
	BYTE len=BASIC_XOR_CNT+cm->AutoGenerateBitData(4);		//����������������ָ����������

	//2).encry
	for (DWORD c=0; c<len; c++)
	{
		for (DWORD i=0; i<bf->GetHeight(); i++)
		{
			for (DWORD j=0; j<bf->GetWidth(); j++)
			{
				DWORD xxx=0;
				xxx = cm->AutoGenerateBitData(24);				//����24bit����
				bf->pix[i][j] = (bf->pix[i][j])^xxx;
			}
		}
	}

	//3)done!
}
