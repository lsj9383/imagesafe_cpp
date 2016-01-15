#ifndef __ACTIVE_AUTHEN_NORM_H
#define __ACTIVE_AUTHEN_NORM_H

#include "ActiveAuthenMethod.h"

#define rChannel	0
#define gChannel	1
#define bChannel	2

class ActiveAuthenNorm:public ActiveAuthenMethod
{
private:
	BYTE ***ImgChannel, ****Block;
	BYTE ***OneChannelLsb;
	DWORD blockSize;		//������
	DWORD Height;			//ͼ��߶�
	DWORD Width;			//ͼ����
	DWORD *map;				//ӳ��

public:
	ActiveAuthenNorm(BmpClass *bf);
	~ActiveAuthenNorm(void);
	void protect(ChaosMethod *cm, BmpClass *bf);
	void authen(ChaosMethod *cm, BmpClass *bf);
	void recover(ChaosMethod *cm, BmpClass *bf);

private:
	void Img2Channel(BmpClass *bf);
	void Channel2Img(BmpClass *bf);
	void ChannelBlockSwap(BYTE swap);

	void GenerateAbBitsFromAllBlock(BYTE ***Lsb, BYTE ***bloc);		//�����п�������Authen Bits
	void GenerateRbBitsFromAllBlock(BYTE ***Lsb, BYTE ***bloc);		//�����п�������Reference Bits

	void AuthenBitsFromWaterMark(BYTE **Lsb, BYTE **bloc);			//����ˮӡ�ӵ�����������Authen Bits
	void AuthenBitsFromBlock(BYTE **Lsb, BYTE **bloc);				//�ӵ���������ȡAuthen Bits
	void ReferenceBitsFromWaterMark(BYTE **Lsb, BYTE **bloc);		//����ˮӡ�ӵ�����������Reference Bits
	void ReferenceBitsFromBlock(BYTE **Lsb, BYTE **bloc);			//�ӵ���������ȡReference Bits

	void MixedLsbAndImgBlock(BYTE ***Lsb, BYTE ***bloc);			//��Lsb��Block�ں�
	void RecoverBlockFromRbBlock(BYTE **bloc, BYTE **Lsb);			//����lsb�ָ�block
};

#endif