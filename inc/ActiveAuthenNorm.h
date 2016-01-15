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
	DWORD blockSize;		//块数量
	DWORD Height;			//图像高度
	DWORD Width;			//图像宽度
	DWORD *map;				//映射

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

	void GenerateAbBitsFromAllBlock(BYTE ***Lsb, BYTE ***bloc);		//从所有块中生成Authen Bits
	void GenerateRbBitsFromAllBlock(BYTE ***Lsb, BYTE ***bloc);		//从所有块中生成Reference Bits

	void AuthenBitsFromWaterMark(BYTE **Lsb, BYTE **bloc);			//根据水印从单个块中生成Authen Bits
	void AuthenBitsFromBlock(BYTE **Lsb, BYTE **bloc);				//从单个块中提取Authen Bits
	void ReferenceBitsFromWaterMark(BYTE **Lsb, BYTE **bloc);		//根据水印从单个块中生成Reference Bits
	void ReferenceBitsFromBlock(BYTE **Lsb, BYTE **bloc);			//从单个块中提取Reference Bits

	void MixedLsbAndImgBlock(BYTE ***Lsb, BYTE ***bloc);			//将Lsb和Block融合
	void RecoverBlockFromRbBlock(BYTE **bloc, BYTE **Lsb);			//利用lsb恢复block
};

#endif