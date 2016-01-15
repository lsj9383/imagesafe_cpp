#include "EncryROTA.h"

void EncryROTA::Encry(ChaosMethod *cm, BmpClass *bf)
{
	//0).����ǰGIVENUP��ϵ��
	for (int i=0; i<GIVENUP; i++)	cm->GenerateOneDouble();

	//1).��������
	BYTE len=10+cm->AutoGenerateBitData(4);						//����3bit����

	//2).��������
	for (int i=0; i<len; i++)
	{
		BYTE opr=cm->AutoGenerateBitData(2)+1;					//����2bit����
		RotaMatrix(bf->pix, bf->GetHeight(), bf->GetWidth(), opr);
	}
}

void EncryROTA::Decry(ChaosMethod *cm, BmpClass *bf)
{
	//0).����ǰGIVENUP��ϵ��
	for (int i=0; i<GIVENUP; i++)	cm->GenerateOneDouble();

	//1).��������
	BYTE len=10+cm->AutoGenerateBitData(4);						//����3bit����

	//2).��������
	BYTE *opr = (BYTE *)malloc(len*(sizeof(BYTE)));

	for (int i=0; i<len; i++)
	{
		opr[i]=cm->AutoGenerateBitData(2)+1;					//����2bit����
	}

	//3).�����ָ�
	for (int i=0; i<len; i++)
	{
		DeRotaMatrix(bf->pix, bf->GetHeight(), bf->GetWidth(), opr[len-1-i]);	//(��������)
	}
}
