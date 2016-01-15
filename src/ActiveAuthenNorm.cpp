#include "ActiveAuthenNorm.h"

ActiveAuthenNorm::ActiveAuthenNorm(BmpClass *bf)
{
	Height = bf->GetHeight();
	Width  = bf->GetWidth();
	blockSize = Height*Width/64;

    ///////////////////////////////////////////////
    if (Height%8!=0 || Width%8!=0)
    {
        printError(AA_IMAGE_TYPE);
    }
    ///////////////////////////////////////////////

	/* *****************************整副图像不同颜色分量的内存分配********************************** */
	ImgChannel = (BYTE ***)malloc( 3*sizeof(BYTE **) );
	for (DWORD i=0; i<3; i++)
	{
		ImgChannel[i]=(BYTE **)malloc( Height*sizeof(BYTE *) );
		for (DWORD j=0; j<Height; j++)
		{
			ImgChannel[i][j] = (BYTE *)malloc( Width*sizeof(BYTE) );
			memset(ImgChannel[i][j], 0, sizeof(BYTE)*Width);			//初始化
		}
	}

	/* *****************************块型图像不同颜色分量的内存分配********************************** */
	Block = (BYTE ****)malloc( 3*sizeof(BYTE ***) );
	for (int i=0; i<3; i++  )
	{
		Block[i] = (BYTE ***)malloc( blockSize*sizeof(BYTE **) );
		for (DWORD j=0; j<blockSize; j++)
		{
			Block[i][j] = (BYTE **)malloc( 8*sizeof(BYTE *) );
			for (DWORD k=0; k<8; k++)
			{
				Block[i][j][k] = (BYTE *)malloc( 8*sizeof(BYTE) );
				memset(Block[i][j][k], 0, sizeof(BYTE)*8);			//初始化
			}
		}
	}

	/* *****************************单个通道的LSB矩阵的内存分配********************************** */

	OneChannelLsb = (BYTE ***)malloc( blockSize*sizeof(BYTE **) );
	for (DWORD i=0; i<blockSize; i++)
	{
		OneChannelLsb[i] = (BYTE **)malloc( 8*sizeof(BYTE *) );
		for (int m=0; m<8; m++)
		{
			OneChannelLsb[i][m] = (BYTE *)malloc( 8*sizeof(BYTE) );
			memset(OneChannelLsb[i][m], 0, sizeof(BYTE)*8);			//初始化
		}
	}

	/* *****************************随机映射数组的内存分配********************************** */
	map = (DWORD *)malloc( blockSize*sizeof(DWORD) );
	memset(map, 0, sizeof(DWORD)*blockSize);			//初始化
}

void ActiveAuthenNorm::Channel2Img(BmpClass *bf)
{
	for (DWORD i=0; i<Height; i++)
	{
		for (DWORD j=0; j<Width; j++)
		{

			DWORD colorPix=0;

			//嘛，红色分量是0, 蓝色分量是1, 绿色分量是2
			colorPix =	(ImgChannel[0][i][j]<<16)+
						(ImgChannel[1][i][j]<<8)+
						(ImgChannel[2][i][j]<<0);

			//注意，这里进行了翻转
			//因为bmp图像的坐标系和该算法的图像处理所依据的坐标系，存在不兼容的情况
			bf->pix[Height-1-i][j] = colorPix;
		}
	}
}

void ActiveAuthenNorm::Img2Channel(BmpClass *bf)
{
	for (int channel=0; channel<3; channel++)
	{
		for (DWORD i=0; i<Height; i++)
		{
			for (DWORD j=0; j<Width; j++)
			{
				//注意，这里进行了翻转
				//因为bmp图像的坐标系和后续的图像处理所依据的坐标系，存在不兼容的情况
				DWORD colorPix=bf->pix[Height-1-i][j];

				//嘛，红色分量是0, 蓝色分量是1, 绿色分量是2
				ImgChannel[channel][i][j] = (colorPix>>(8*(2-channel)))&0xFF;
			}
		}
	}
}

void ActiveAuthenNorm::ChannelBlockSwap(BYTE swap)
{
	DWORD blockNum=0;

	for (int channel=0; channel<3; channel++)
	{
		blockNum=0;
		for (DWORD i=1; i<=Height; i++)
		{
			//行有8个了，看看列
			if((i&0x07)==0)
			{
				for (DWORD j=1; j<=Width; j++)
				{
					//列也有8个了，记录一发
					if ((j&0x07)==0)
					{
						DWORD rowRange[2];
						DWORD colRange[2];

						rowRange[0]=i-8;rowRange[1]=i-1;
						colRange[0]=j-8;colRange[1]=j-1;
						//选择转换方向
						if (swap==0)
							MatrixChop(Block[channel][blockNum], ImgChannel[channel], rowRange, colRange);
						else
							MatrixIchop(ImgChannel[channel], Block[channel][blockNum], rowRange, colRange);

						blockNum++;
					}
				}
			}
		}
	}
}

void ActiveAuthenNorm::AuthenBitsFromBlock(BYTE **Lsb, BYTE **bloc)
{
	BYTE msbBits[320];
	DWORD c=0;

	//1).提取320bit输入hash的数据
	for (int i=0; i<8; i++)
	{
		for (int j=0; j<8; j++)
		{
			BYTE pixByte = bloc[i][j];
			for (int k=0; k<5; k++)
			{
				msbBits[c++] = pixByte>>7;	//提取最高位
				pixByte<<=1;				//更替最高位
			}
		}
	}

	//2).哎，将提取的320bit转换为320长度的stirng
	c=0;
	string str="";
	for (int i=0; i<320; i++)
	{
		if (msbBits[c]==0)
			str = str+"0";
		else
			str = str+"1";
		c++;

	}

	//3).hash(MD5)
	string str_buf;
	BYTE *charBuf;
	str_buf = md5(str);
	charBuf = (BYTE *)str_buf.c_str();
	c=0;
	for (int i=0; i<16; i++)			//前64bit
	{
		BYTE val = char2num(charBuf[i]);
		for (int j=0; j<4; j++)
		{
			Lsb[c%8][c/8] = val>>3;		//取最高bit
			val=(val<<1)&0x0F;			//更替最高bit
			c++;
		}
	}
}

void ActiveAuthenNorm::ReferenceBitsFromBlock(BYTE **Lsb, BYTE **bloc)
{
	//初始化相关的矩阵
	WORD Q[8][8]={	{ 30,  11,  10,  16, 260, 260, 260, 260},
					{ 12,  12,  14, 260, 260, 260, 260, 260},
					{ 14,  13, 260, 260, 260, 260, 260, 260},
					{ 14, 260, 260, 260, 260, 260, 260, 260},
					{ 18, 260, 260, 260, 260, 260, 260, 260},
					{260, 260, 260, 260, 260, 260, 260, 260},
					{260, 260, 260, 260, 260, 260, 260, 260},
					{260, 260, 260, 260, 260, 260, 260, 260}};
	BYTE L[11] = {7, 7, 7, 6, 6, 7, 5, 5, 5, 5, 4};						//前11个像素所用到的bit数
	BYTE zig_zag_scan[11] = {0, 8, 1, 2, 9, 16, 24, 17, 10, 3, 4};		//zigzag扫描顺序
	BYTE allBits[64], count=0;
	double **dctBlock;
	char **qDctBlock;
	char qDctSeries[11];
	dctBlock = (double **)malloc(8*sizeof(double *));
	qDctBlock = (char **)malloc(8*sizeof(char *));
	for (int i=0; i<8; i++)
	{
		dctBlock[i] = (double *)malloc(8*sizeof(double));
		qDctBlock[i] = (char *)malloc(8*sizeof(char));
	}

	//dct和量化
	Block8x8_Dct2(bloc, dctBlock);
	MatrixQ(qDctBlock, dctBlock, Q, 8, 8);
	for (int i=0; i<11; i++)
	{
		qDctSeries[i] = qDctBlock[zig_zag_scan[i]%8][zig_zag_scan[i]/8];

		char refByte = qDctSeries[i];
		//装载符号位
		if (refByte>=0)
		{
			allBits[count++] = 0;

		}
		else
		{
			allBits[count++] = 1;
		}
		//限幅
		refByte = abs(refByte);
		if (refByte>= pow(2, (double)(L[i]-1))-1 )
			refByte = (BYTE)pow(2, (double)(L[i]-1))-1;
		//提取每个字节对应的bit
		for (int j=0; j<(L[i]-1); j++)
		{
			allBits[count++]=refByte>>(L[i]-2);
			refByte=(refByte<<1)&((BYTE)( pow(2, (double)(L[i]-1))-1 ));
		}

	}

	//加载至Lsb
	for (int j=0; j<8; j++)
	{
		for (int i=0; i<8; i++)
		{
			Lsb[i][j] = allBits[j*8+i]*2+Lsb[i][j];				//注意这里的放置位置
	//		Lsb[i][j] = allBits[j*8+i];
		}
	}
	//release memory
	for (int i=0; i<8; i++)
	{
		free(dctBlock[i]);dctBlock[i]=NULL;
		free(qDctBlock[i]);qDctBlock[i]=NULL;
	}
	free(dctBlock);dctBlock=NULL;
	free(qDctBlock);qDctBlock=NULL;
}

//Authen Bits All Blocks
void ActiveAuthenNorm::GenerateAbBitsFromAllBlock(BYTE ***Lsb, BYTE ***bloc)
{
	for (DWORD blockNum=0; blockNum<blockSize; blockNum++)
	{
		AuthenBitsFromBlock(Lsb[blockNum], bloc[blockNum]);		//得到对应块的lsb
	}
}

//Reference Bits All Blocks
void ActiveAuthenNorm::GenerateRbBitsFromAllBlock(BYTE ***Lsb, BYTE ***bloc)
{
	for (DWORD blockNum=0; blockNum<blockSize; blockNum++)
	{
		ReferenceBitsFromBlock(Lsb[map[blockNum]], bloc[blockNum]);		//得到对应块的lsb
	}
}

void ActiveAuthenNorm::MixedLsbAndImgBlock(BYTE ***Lsb, BYTE ***bloc)
{
	for (DWORD blockNum=0; blockNum<blockSize; blockNum++)
	{
		for (int i=0; i<8; i++)
		{
			for (int j=0; j<8; j++)
			{
				bloc[blockNum][i][j]=(bloc[blockNum][i][j]&0xFC)+Lsb[blockNum][i][j];
			}
		}
	}
}

void ActiveAuthenNorm::RecoverBlockFromRbBlock(BYTE **bloc, BYTE **Lsb)
{
	//初始化相关的矩阵
	WORD Q[8][8]={	{ 30,  11,  10,  16, 260, 260, 260, 260},
					{ 12,  12,  14, 260, 260, 260, 260, 260},
					{ 14,  13, 260, 260, 260, 260, 260, 260},
					{ 14, 260, 260, 260, 260, 260, 260, 260},
					{ 18, 260, 260, 260, 260, 260, 260, 260},
					{260, 260, 260, 260, 260, 260, 260, 260},
					{260, 260, 260, 260, 260, 260, 260, 260},
					{260, 260, 260, 260, 260, 260, 260, 260}};
	BYTE L[11] = {7, 7, 7, 6, 6, 7, 5, 5, 5, 5, 4};						//前11个像素所用到的bit数
	BYTE zig_zag_scan[11] = {0, 8, 1, 2, 9, 16, 24, 17, 10, 3, 4};		//zigzag扫描顺序
	BYTE allBits[64], count=0;
	char allBytes[11];
	double **dctBlock;
	dctBlock = (double **)malloc( 8*sizeof(double *) );
	for (int i=0; i<8; i++)
	{
		dctBlock[i] = (double *)malloc( 8*sizeof(double) );
		memset(dctBlock[i], 0, sizeof(double)*8);
	}

	//恢复
	for (int j=0; j<8; j++)
	{
		for (int i=0; i<8; i++)
		{
			allBits[j*8+i] = Lsb[i][j];
		}
	}

	for (int i=0; i<11; i++)
	{
		char isN;
		char RecByte=0;

		for (int j=0; j<L[i]; j++)
		{
			if (j==0)
			{
				isN = allBits[count++];
			}
			else
			{
				RecByte = RecByte*2 + allBits[count++];
			}
		}
		if (isN)
			RecByte*=-1;
		allBytes[i] = RecByte;
	}

	for (int i=0; i<11; i++)
	{
		//将allByte转换为dctBlock(重排序和反量化)
		dctBlock[zig_zag_scan[i]%8][zig_zag_scan[i]/8] =
			allBytes[i]*Q[zig_zag_scan[i]%8][zig_zag_scan[i]/8];
	}

	//idct
	Block8x8_iDct2(bloc, dctBlock);

	//release
	for (int i=0; i<8; i++)
	{
		free(dctBlock[i]);dctBlock[i]=NULL;
	}
	free(dctBlock);dctBlock=NULL;
}

void ActiveAuthenNorm::AuthenBitsFromWaterMark(BYTE **Lsb, BYTE **bloc)
{
	for (int i=0; i<8; i++)
	{
		for (int j=0; j<8; j++)
		{
			Lsb[i][j] = bloc[i][j]&0x01;			//取LSB
		}
	}
}

void ActiveAuthenNorm::ReferenceBitsFromWaterMark(BYTE **Lsb, BYTE **bloc)
{
	for (int i=0; i<8; i++)
	{
		for (int j=0; j<8; j++)
		{
			Lsb[i][j] = (bloc[i][j]>>1)&0x01;			//取LSB
		}
	}
}

void ActiveAuthenNorm::protect(ChaosMethod *cm, BmpClass *bf)
{
	Img2Channel(bf);					//转rgb的3通道(包含坐标系变换为后续图像处理坐标系,即matlab里面的矩阵形式)
	ChannelBlockSwap(0);				//rgb3个图像，转换为对应的图像块
	cm->GenerateMap(map, blockSize);	//生成随机映射
	for (int i=0; i<3; i++)
	{
		//!!!!Ab和Rb的生成顺序不能交换!!!!
		GenerateAbBitsFromAllBlock(OneChannelLsb, Block[i]);//得到对应颜色通道的Authen Lsb
		GenerateRbBitsFromAllBlock(OneChannelLsb, Block[i]);//得到对应颜色通道的Refer&Authen Lsb
		MixedLsbAndImgBlock(OneChannelLsb, Block[i]);		//将对应通道的LSB和颜色块像素融合
	}

	ChannelBlockSwap(1);
	Channel2Img(bf);		//转回bmp图像(包含坐标系变换回bmp格式)
}

void ActiveAuthenNorm::authen(ChaosMethod *cm, BmpClass *bf)
{
	//用于标识的块
	BYTE **blockTrue, **blockFalse;
	blockTrue = (BYTE **)malloc( 8*sizeof(BYTE *));
	blockFalse = (BYTE **)malloc( 8*sizeof(BYTE *));
	for (int i=0; i<8; i++)
	{
		blockTrue[i] = (BYTE *)malloc( 8*sizeof(BYTE) );
		blockFalse[i] = (BYTE *)malloc( 8*sizeof(BYTE) );
		memset(blockTrue[i], 255, 8);		//正确块初始化为亮
		memset(blockFalse[i], 0, 8);		//错误块初始化为黑
	}

	//一些矩阵(rgb的分通道操作，以及8x8块的转换)的初始化设置
	Img2Channel(bf);		//转rgb的3通道(包含坐标系变换为后续图像处理坐标系,即matlab里面的矩阵形式)
	ChannelBlockSwap(0);	//rgb3个图像，转换为对应的图像块

	BYTE **lsbBuf;
	lsbBuf = (BYTE **)malloc( 8*sizeof(BYTE*) );
	for (int i=0; i<8; i++)
	{
		lsbBuf[i] = (BYTE *)malloc( 8*sizeof(BYTE) );
	}

	//仅适用红色通道
	for (DWORD blockNum=0; blockNum<blockSize; blockNum++)
	{
		AuthenBitsFromBlock(OneChannelLsb[blockNum], Block[0][blockNum]);		//得到对应块的lsb
		AuthenBitsFromWaterMark(lsbBuf, Block[0][blockNum]);
		if (MatrixCompare(lsbBuf, OneChannelLsb[blockNum], 8, 8))
		{
			//设置图像块为正确块
			MatrixEqu(Block[0][blockNum], blockTrue, 8, 8);
			MatrixEqu(Block[1][blockNum], blockTrue, 8, 8);
			MatrixEqu(Block[2][blockNum], blockTrue, 8, 8);
		}
		else
		{
			//设置图像块为错误块
			MatrixEqu(Block[0][blockNum], blockFalse, 8, 8);
			MatrixEqu(Block[1][blockNum], blockFalse, 8, 8);
			MatrixEqu(Block[2][blockNum], blockFalse, 8, 8);
		}
	}

	//release
	for (int i=0; i<8; i++)
	{
		free(blockTrue[i]);blockTrue[i]=NULL;
		free(blockFalse[i]);blockFalse[i]=NULL;
		free(lsbBuf[i]);lsbBuf[i]=NULL;
	}
	free(blockTrue);blockTrue=NULL;
	free(blockFalse);blockFalse=NULL;
	free(lsbBuf);lsbBuf=NULL;

	//转换回bmp
	ChannelBlockSwap(1);
	Channel2Img(bf);		//转回bmp图像(包含坐标系变换回bmp格式)
}

void ActiveAuthenNorm::recover(ChaosMethod *cm, BmpClass *bf)
{
	//用于标识的块
	BYTE **blockLost;
	blockLost = (BYTE **)malloc( 8*sizeof(BYTE *));
	for (int i=0; i<8; i++)
	{
		blockLost[i] = (BYTE *)malloc( 8*sizeof(BYTE) );
		memset(blockLost[i], 0, 8);		//丢失块初始化为黑
	}

	//一些矩阵(rgb的分通道操作，以及8x8块的转换)的初始化设置
	Img2Channel(bf);		//转rgb的3通道(包含坐标系变换为后续图像处理坐标系,即matlab里面的矩阵形式)
	ChannelBlockSwap(0);	//rgb3个图像，转换为对应的图像块
	cm->GenerateMap(map, blockSize);	//生成随机映射
	bool *isTrue;
	isTrue = (bool*)malloc( blockSize*sizeof(bool) );
	BYTE **lsbBuf;
	lsbBuf = (BYTE **)malloc( 8*sizeof(BYTE*) );
	for (int i=0; i<8; i++)
	{
		lsbBuf[i] = (BYTE *)malloc( 8*sizeof(BYTE) );
	}

	//先找下哪些块有问题嘛
	for (DWORD blockNum=0; blockNum<blockSize; blockNum++)
	{
		AuthenBitsFromBlock(OneChannelLsb[blockNum], Block[0][blockNum]);		//得到对应块的lsb
		AuthenBitsFromWaterMark(lsbBuf, Block[0][blockNum]);
		if (MatrixCompare(lsbBuf, OneChannelLsb[blockNum], 8, 8))
		{
			//设置图像块为正确块
			isTrue[blockNum]=true;
		}
		else
		{
			//设置图像块为错误块
			isTrue[blockNum]=false;
		}
	}

	//恢复
	DWORD countRec=0;
	for (DWORD blockNum=0; blockNum<blockSize; blockNum++)
	{
		if (!isTrue[blockNum])
		{
			DWORD mapi = map[blockNum];		//恢复blockNum块需要用mapi块的水印
			//错误时，可以进行图像块修复
			if (isTrue[mapi])
			{
				//mapi的块可以使用，则恢复
				ReferenceBitsFromWaterMark(lsbBuf, Block[0][mapi]);
				RecoverBlockFromRbBlock(Block[0][blockNum], lsbBuf);

				ReferenceBitsFromWaterMark(lsbBuf, Block[1][mapi]);
				RecoverBlockFromRbBlock(Block[1][blockNum], lsbBuf);

				ReferenceBitsFromWaterMark(lsbBuf, Block[2][mapi]);
				RecoverBlockFromRbBlock(Block[2][blockNum], lsbBuf);
			}
			else
			{
				//mapi的块不能使用，则丢失
				MatrixEqu(Block[0][blockNum], blockLost, 8, 8);
				MatrixEqu(Block[1][blockNum], blockLost, 8, 8);
				MatrixEqu(Block[2][blockNum], blockLost, 8, 8);
			}
		}
	}

	//转换回bmp
	ChannelBlockSwap(1);
	Channel2Img(bf);		//转回bmp图像(包含坐标系变换回bmp格式)
}

ActiveAuthenNorm::~ActiveAuthenNorm(void)
{
	//释放整副图像不同通道的图像内存
	for (DWORD i=0; i<3; i++)
	{
		for (DWORD j=0; j<Height; j++)
		{
			free(ImgChannel[i][j]);ImgChannel[i][j]=NULL;
		}
		free(ImgChannel[i]);ImgChannel[i]=NULL;
	}
	free(ImgChannel);ImgChannel=NULL;

	//释放块图像不同通道的图像内存
	for (int i=0; i<3; i++)
	{
		for (DWORD j=0; j<blockSize; j++)
		{
			for (DWORD k=0; k<8; k++)
			{
				free(Block[i][j][k]);Block[i][j][k]=NULL;
			}
			free(Block[i][j]);Block[i][j]=NULL;
		}
		free(Block[i]);Block[i]=NULL;
	}
	free(Block);Block=NULL;

	//释放图像的LSB数据矩阵内存
	for (DWORD i=0; i<blockSize; i++)
	{
		for (DWORD m=0; m<8; m++)
		{
			free(OneChannelLsb[i][m]);OneChannelLsb[i][m]=NULL;
		}
		free(OneChannelLsb[i]);OneChannelLsb[i]=NULL;
	}
	free(OneChannelLsb);OneChannelLsb=NULL;

	//释放映射对应的内存
	free(map);
}
