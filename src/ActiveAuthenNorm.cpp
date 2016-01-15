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

	/* *****************************����ͼ��ͬ��ɫ�������ڴ����********************************** */
	ImgChannel = (BYTE ***)malloc( 3*sizeof(BYTE **) );
	for (DWORD i=0; i<3; i++)
	{
		ImgChannel[i]=(BYTE **)malloc( Height*sizeof(BYTE *) );
		for (DWORD j=0; j<Height; j++)
		{
			ImgChannel[i][j] = (BYTE *)malloc( Width*sizeof(BYTE) );
			memset(ImgChannel[i][j], 0, sizeof(BYTE)*Width);			//��ʼ��
		}
	}

	/* *****************************����ͼ��ͬ��ɫ�������ڴ����********************************** */
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
				memset(Block[i][j][k], 0, sizeof(BYTE)*8);			//��ʼ��
			}
		}
	}

	/* *****************************����ͨ����LSB������ڴ����********************************** */

	OneChannelLsb = (BYTE ***)malloc( blockSize*sizeof(BYTE **) );
	for (DWORD i=0; i<blockSize; i++)
	{
		OneChannelLsb[i] = (BYTE **)malloc( 8*sizeof(BYTE *) );
		for (int m=0; m<8; m++)
		{
			OneChannelLsb[i][m] = (BYTE *)malloc( 8*sizeof(BYTE) );
			memset(OneChannelLsb[i][m], 0, sizeof(BYTE)*8);			//��ʼ��
		}
	}

	/* *****************************���ӳ��������ڴ����********************************** */
	map = (DWORD *)malloc( blockSize*sizeof(DWORD) );
	memset(map, 0, sizeof(DWORD)*blockSize);			//��ʼ��
}

void ActiveAuthenNorm::Channel2Img(BmpClass *bf)
{
	for (DWORD i=0; i<Height; i++)
	{
		for (DWORD j=0; j<Width; j++)
		{

			DWORD colorPix=0;

			//���ɫ������0, ��ɫ������1, ��ɫ������2
			colorPix =	(ImgChannel[0][i][j]<<16)+
						(ImgChannel[1][i][j]<<8)+
						(ImgChannel[2][i][j]<<0);

			//ע�⣬��������˷�ת
			//��Ϊbmpͼ�������ϵ�͸��㷨��ͼ���������ݵ�����ϵ�����ڲ����ݵ����
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
				//ע�⣬��������˷�ת
				//��Ϊbmpͼ�������ϵ�ͺ�����ͼ���������ݵ�����ϵ�����ڲ����ݵ����
				DWORD colorPix=bf->pix[Height-1-i][j];

				//���ɫ������0, ��ɫ������1, ��ɫ������2
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
			//����8���ˣ�������
			if((i&0x07)==0)
			{
				for (DWORD j=1; j<=Width; j++)
				{
					//��Ҳ��8���ˣ���¼һ��
					if ((j&0x07)==0)
					{
						DWORD rowRange[2];
						DWORD colRange[2];

						rowRange[0]=i-8;rowRange[1]=i-1;
						colRange[0]=j-8;colRange[1]=j-1;
						//ѡ��ת������
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

	//1).��ȡ320bit����hash������
	for (int i=0; i<8; i++)
	{
		for (int j=0; j<8; j++)
		{
			BYTE pixByte = bloc[i][j];
			for (int k=0; k<5; k++)
			{
				msbBits[c++] = pixByte>>7;	//��ȡ���λ
				pixByte<<=1;				//�������λ
			}
		}
	}

	//2).��������ȡ��320bitת��Ϊ320���ȵ�stirng
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
	for (int i=0; i<16; i++)			//ǰ64bit
	{
		BYTE val = char2num(charBuf[i]);
		for (int j=0; j<4; j++)
		{
			Lsb[c%8][c/8] = val>>3;		//ȡ���bit
			val=(val<<1)&0x0F;			//�������bit
			c++;
		}
	}
}

void ActiveAuthenNorm::ReferenceBitsFromBlock(BYTE **Lsb, BYTE **bloc)
{
	//��ʼ����صľ���
	WORD Q[8][8]={	{ 30,  11,  10,  16, 260, 260, 260, 260},
					{ 12,  12,  14, 260, 260, 260, 260, 260},
					{ 14,  13, 260, 260, 260, 260, 260, 260},
					{ 14, 260, 260, 260, 260, 260, 260, 260},
					{ 18, 260, 260, 260, 260, 260, 260, 260},
					{260, 260, 260, 260, 260, 260, 260, 260},
					{260, 260, 260, 260, 260, 260, 260, 260},
					{260, 260, 260, 260, 260, 260, 260, 260}};
	BYTE L[11] = {7, 7, 7, 6, 6, 7, 5, 5, 5, 5, 4};						//ǰ11���������õ���bit��
	BYTE zig_zag_scan[11] = {0, 8, 1, 2, 9, 16, 24, 17, 10, 3, 4};		//zigzagɨ��˳��
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

	//dct������
	Block8x8_Dct2(bloc, dctBlock);
	MatrixQ(qDctBlock, dctBlock, Q, 8, 8);
	for (int i=0; i<11; i++)
	{
		qDctSeries[i] = qDctBlock[zig_zag_scan[i]%8][zig_zag_scan[i]/8];

		char refByte = qDctSeries[i];
		//װ�ط���λ
		if (refByte>=0)
		{
			allBits[count++] = 0;

		}
		else
		{
			allBits[count++] = 1;
		}
		//�޷�
		refByte = abs(refByte);
		if (refByte>= pow(2, (double)(L[i]-1))-1 )
			refByte = (BYTE)pow(2, (double)(L[i]-1))-1;
		//��ȡÿ���ֽڶ�Ӧ��bit
		for (int j=0; j<(L[i]-1); j++)
		{
			allBits[count++]=refByte>>(L[i]-2);
			refByte=(refByte<<1)&((BYTE)( pow(2, (double)(L[i]-1))-1 ));
		}

	}

	//������Lsb
	for (int j=0; j<8; j++)
	{
		for (int i=0; i<8; i++)
		{
			Lsb[i][j] = allBits[j*8+i]*2+Lsb[i][j];				//ע������ķ���λ��
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
		AuthenBitsFromBlock(Lsb[blockNum], bloc[blockNum]);		//�õ���Ӧ���lsb
	}
}

//Reference Bits All Blocks
void ActiveAuthenNorm::GenerateRbBitsFromAllBlock(BYTE ***Lsb, BYTE ***bloc)
{
	for (DWORD blockNum=0; blockNum<blockSize; blockNum++)
	{
		ReferenceBitsFromBlock(Lsb[map[blockNum]], bloc[blockNum]);		//�õ���Ӧ���lsb
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
	//��ʼ����صľ���
	WORD Q[8][8]={	{ 30,  11,  10,  16, 260, 260, 260, 260},
					{ 12,  12,  14, 260, 260, 260, 260, 260},
					{ 14,  13, 260, 260, 260, 260, 260, 260},
					{ 14, 260, 260, 260, 260, 260, 260, 260},
					{ 18, 260, 260, 260, 260, 260, 260, 260},
					{260, 260, 260, 260, 260, 260, 260, 260},
					{260, 260, 260, 260, 260, 260, 260, 260},
					{260, 260, 260, 260, 260, 260, 260, 260}};
	BYTE L[11] = {7, 7, 7, 6, 6, 7, 5, 5, 5, 5, 4};						//ǰ11���������õ���bit��
	BYTE zig_zag_scan[11] = {0, 8, 1, 2, 9, 16, 24, 17, 10, 3, 4};		//zigzagɨ��˳��
	BYTE allBits[64], count=0;
	char allBytes[11];
	double **dctBlock;
	dctBlock = (double **)malloc( 8*sizeof(double *) );
	for (int i=0; i<8; i++)
	{
		dctBlock[i] = (double *)malloc( 8*sizeof(double) );
		memset(dctBlock[i], 0, sizeof(double)*8);
	}

	//�ָ�
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
		//��allByteת��ΪdctBlock(������ͷ�����)
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
			Lsb[i][j] = bloc[i][j]&0x01;			//ȡLSB
		}
	}
}

void ActiveAuthenNorm::ReferenceBitsFromWaterMark(BYTE **Lsb, BYTE **bloc)
{
	for (int i=0; i<8; i++)
	{
		for (int j=0; j<8; j++)
		{
			Lsb[i][j] = (bloc[i][j]>>1)&0x01;			//ȡLSB
		}
	}
}

void ActiveAuthenNorm::protect(ChaosMethod *cm, BmpClass *bf)
{
	Img2Channel(bf);					//תrgb��3ͨ��(��������ϵ�任Ϊ����ͼ��������ϵ,��matlab����ľ�����ʽ)
	ChannelBlockSwap(0);				//rgb3��ͼ��ת��Ϊ��Ӧ��ͼ���
	cm->GenerateMap(map, blockSize);	//�������ӳ��
	for (int i=0; i<3; i++)
	{
		//!!!!Ab��Rb������˳���ܽ���!!!!
		GenerateAbBitsFromAllBlock(OneChannelLsb, Block[i]);//�õ���Ӧ��ɫͨ����Authen Lsb
		GenerateRbBitsFromAllBlock(OneChannelLsb, Block[i]);//�õ���Ӧ��ɫͨ����Refer&Authen Lsb
		MixedLsbAndImgBlock(OneChannelLsb, Block[i]);		//����Ӧͨ����LSB����ɫ�������ں�
	}

	ChannelBlockSwap(1);
	Channel2Img(bf);		//ת��bmpͼ��(��������ϵ�任��bmp��ʽ)
}

void ActiveAuthenNorm::authen(ChaosMethod *cm, BmpClass *bf)
{
	//���ڱ�ʶ�Ŀ�
	BYTE **blockTrue, **blockFalse;
	blockTrue = (BYTE **)malloc( 8*sizeof(BYTE *));
	blockFalse = (BYTE **)malloc( 8*sizeof(BYTE *));
	for (int i=0; i<8; i++)
	{
		blockTrue[i] = (BYTE *)malloc( 8*sizeof(BYTE) );
		blockFalse[i] = (BYTE *)malloc( 8*sizeof(BYTE) );
		memset(blockTrue[i], 255, 8);		//��ȷ���ʼ��Ϊ��
		memset(blockFalse[i], 0, 8);		//������ʼ��Ϊ��
	}

	//һЩ����(rgb�ķ�ͨ���������Լ�8x8���ת��)�ĳ�ʼ������
	Img2Channel(bf);		//תrgb��3ͨ��(��������ϵ�任Ϊ����ͼ��������ϵ,��matlab����ľ�����ʽ)
	ChannelBlockSwap(0);	//rgb3��ͼ��ת��Ϊ��Ӧ��ͼ���

	BYTE **lsbBuf;
	lsbBuf = (BYTE **)malloc( 8*sizeof(BYTE*) );
	for (int i=0; i<8; i++)
	{
		lsbBuf[i] = (BYTE *)malloc( 8*sizeof(BYTE) );
	}

	//�����ú�ɫͨ��
	for (DWORD blockNum=0; blockNum<blockSize; blockNum++)
	{
		AuthenBitsFromBlock(OneChannelLsb[blockNum], Block[0][blockNum]);		//�õ���Ӧ���lsb
		AuthenBitsFromWaterMark(lsbBuf, Block[0][blockNum]);
		if (MatrixCompare(lsbBuf, OneChannelLsb[blockNum], 8, 8))
		{
			//����ͼ���Ϊ��ȷ��
			MatrixEqu(Block[0][blockNum], blockTrue, 8, 8);
			MatrixEqu(Block[1][blockNum], blockTrue, 8, 8);
			MatrixEqu(Block[2][blockNum], blockTrue, 8, 8);
		}
		else
		{
			//����ͼ���Ϊ�����
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

	//ת����bmp
	ChannelBlockSwap(1);
	Channel2Img(bf);		//ת��bmpͼ��(��������ϵ�任��bmp��ʽ)
}

void ActiveAuthenNorm::recover(ChaosMethod *cm, BmpClass *bf)
{
	//���ڱ�ʶ�Ŀ�
	BYTE **blockLost;
	blockLost = (BYTE **)malloc( 8*sizeof(BYTE *));
	for (int i=0; i<8; i++)
	{
		blockLost[i] = (BYTE *)malloc( 8*sizeof(BYTE) );
		memset(blockLost[i], 0, 8);		//��ʧ���ʼ��Ϊ��
	}

	//һЩ����(rgb�ķ�ͨ���������Լ�8x8���ת��)�ĳ�ʼ������
	Img2Channel(bf);		//תrgb��3ͨ��(��������ϵ�任Ϊ����ͼ��������ϵ,��matlab����ľ�����ʽ)
	ChannelBlockSwap(0);	//rgb3��ͼ��ת��Ϊ��Ӧ��ͼ���
	cm->GenerateMap(map, blockSize);	//�������ӳ��
	bool *isTrue;
	isTrue = (bool*)malloc( blockSize*sizeof(bool) );
	BYTE **lsbBuf;
	lsbBuf = (BYTE **)malloc( 8*sizeof(BYTE*) );
	for (int i=0; i<8; i++)
	{
		lsbBuf[i] = (BYTE *)malloc( 8*sizeof(BYTE) );
	}

	//��������Щ����������
	for (DWORD blockNum=0; blockNum<blockSize; blockNum++)
	{
		AuthenBitsFromBlock(OneChannelLsb[blockNum], Block[0][blockNum]);		//�õ���Ӧ���lsb
		AuthenBitsFromWaterMark(lsbBuf, Block[0][blockNum]);
		if (MatrixCompare(lsbBuf, OneChannelLsb[blockNum], 8, 8))
		{
			//����ͼ���Ϊ��ȷ��
			isTrue[blockNum]=true;
		}
		else
		{
			//����ͼ���Ϊ�����
			isTrue[blockNum]=false;
		}
	}

	//�ָ�
	DWORD countRec=0;
	for (DWORD blockNum=0; blockNum<blockSize; blockNum++)
	{
		if (!isTrue[blockNum])
		{
			DWORD mapi = map[blockNum];		//�ָ�blockNum����Ҫ��mapi���ˮӡ
			//����ʱ�����Խ���ͼ����޸�
			if (isTrue[mapi])
			{
				//mapi�Ŀ����ʹ�ã���ָ�
				ReferenceBitsFromWaterMark(lsbBuf, Block[0][mapi]);
				RecoverBlockFromRbBlock(Block[0][blockNum], lsbBuf);

				ReferenceBitsFromWaterMark(lsbBuf, Block[1][mapi]);
				RecoverBlockFromRbBlock(Block[1][blockNum], lsbBuf);

				ReferenceBitsFromWaterMark(lsbBuf, Block[2][mapi]);
				RecoverBlockFromRbBlock(Block[2][blockNum], lsbBuf);
			}
			else
			{
				//mapi�Ŀ鲻��ʹ�ã���ʧ
				MatrixEqu(Block[0][blockNum], blockLost, 8, 8);
				MatrixEqu(Block[1][blockNum], blockLost, 8, 8);
				MatrixEqu(Block[2][blockNum], blockLost, 8, 8);
			}
		}
	}

	//ת����bmp
	ChannelBlockSwap(1);
	Channel2Img(bf);		//ת��bmpͼ��(��������ϵ�任��bmp��ʽ)
}

ActiveAuthenNorm::~ActiveAuthenNorm(void)
{
	//�ͷ�����ͼ��ͬͨ����ͼ���ڴ�
	for (DWORD i=0; i<3; i++)
	{
		for (DWORD j=0; j<Height; j++)
		{
			free(ImgChannel[i][j]);ImgChannel[i][j]=NULL;
		}
		free(ImgChannel[i]);ImgChannel[i]=NULL;
	}
	free(ImgChannel);ImgChannel=NULL;

	//�ͷſ�ͼ��ͬͨ����ͼ���ڴ�
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

	//�ͷ�ͼ���LSB���ݾ����ڴ�
	for (DWORD i=0; i<blockSize; i++)
	{
		for (DWORD m=0; m<8; m++)
		{
			free(OneChannelLsb[i][m]);OneChannelLsb[i][m]=NULL;
		}
		free(OneChannelLsb[i]);OneChannelLsb[i]=NULL;
	}
	free(OneChannelLsb);OneChannelLsb=NULL;

	//�ͷ�ӳ���Ӧ���ڴ�
	free(map);
}
