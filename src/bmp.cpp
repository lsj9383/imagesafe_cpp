#include "bmp.h"

BmpClass::BmpClass(char* fn)
{
	file_name = fn;
	width = 0;
	height= 0;
	fopf=false;
}

BmpClass::~BmpClass()
{
	CloseFile();
}

void BmpClass::releaseMemory(void)
{
	//释放像素矩阵
	for (int i=0; i<bmpIh.biHeight; i++)
	{
		free(pix[i]);pix[i]=NULL;
	}
	free(pix);pix=NULL;

	//释放调色板
	free(quad);quad=NULL;
}

bool BmpClass::CloseFile(void)
{
	if(fopf==true)
	{
		fopf=false;
		releaseMemory();			//释放内存
		fclose(fp);
		return true;
	}
	return false;
}

bool BmpClass::OpenFile(void)
{
	fp = fopen(file_name, "rb");
	///////////////////////////
	if(fp == NULL)
    {
//        printf("open file failed\n");
        printError(NO_FILE);
        return false;
    }
    ////////////////////////////
	fopf=true;
	ReadHeaderQuad();
//	printf("open file success\n");
	return true;
}

void BmpClass::ReadHeaderQuad(void)
{
	fread(&bmpFh, 14, 1, fp);
	fread(&bmpIh, 40, 1, fp);
	////////////////////////////////////
	if (bmpIh.biBitCount != 24)
    {
        printError(ERR_BMP_TYPE);
    }
    ////////////////////////////////////
	quadSize = pow((long double)2, (int)bmpIh.biBitCount);
	quad = (RGBQUAD* )malloc(quadSize * 4);
	fread(quad,   4, quadSize, fp);

	//为颜色申请二维数组
	pix = (DWORD **)malloc(sizeof(DWORD)*bmpIh.biHeight);
	for (int i=0; i<bmpIh.biHeight; i++)
	{
		pix[i]=(DWORD*)malloc(sizeof(DWORD)*bmpIh.biWidth);
	}

}

void BmpClass::WirteBmpColor(DWORD color, FILE *wfp)
{
	if (fopf==true)
	{
		if (bmpIh.biBitCount==24)
		{
			BYTE rgb[3];

			rgb[2] = (color>>16)&0xFF;
			rgb[1] = (color>>8)&0xFF;
			rgb[0] = (color>>0)&0xFF;
			fwrite(rgb, 3, 1, wfp);
		}
	}
	else	return ;
}

DWORD BmpClass::LoadBmpPointColor(void)
{
	DWORD rval=0;
	static int count=0;

	if (fopf==true)
	{
		if (bmpIh.biBitCount==24)
		{
			BYTE rgb[3];
			fread(rgb, 3, 1, fp);
			rval = (rgb[2]<<16)|(rgb[1]<<8)|(rgb[0]<<0);
		}
		else
		{
			static BYTE bindex;
			BYTE index=0;

			if(count==0)
				fread(&bindex, 1, 1, fp);
			count = (count+1)%(8/bmpIh.biBitCount);
			index = bindex >> (8-bmpIh.biBitCount);
			bindex <<= bmpIh.biBitCount;
			rval = (quad[index].rgbRed<<16)|(quad[index].rgbGreen<<8)|(quad[index].rgbBlue<<0);
		}

		return rval;
	}
	else
		return 0;
}

void BmpClass::LoadBmp2Pix(void)
{
	if (fopf==true)
	{
		for (int i=0; i<bmpIh.biHeight; i++)
		{
			DWORD widthByte=bmpIh.biWidth*3;			//一行的字节数
			for (int j=0; j<bmpIh.biWidth; j++)
			{
				pix[i][j] = BmpClass::LoadBmpPointColor();
			}
			//行的字节数和4的余数不为零，则需要多读一些出来，嘿嘿
			if ((widthByte&0x03))
			{
				BYTE buf[4];
				fread(buf, 4-(widthByte&0x03), 1, this->fp);
			}

		}
	}
}

void BmpClass::WritePix2Bmp(char* fn)
{
	FILE* wfp;

	if (fopf==true)
	{
		wfp = fopen(fn, "wb");
		if (wfp==NULL)	return ;
		fwrite(&bmpFh, 14, 1, wfp);
		fwrite(&bmpIh, 40, 1, wfp);
		for (int i=0; i<bmpIh.biHeight; i++)
		{
			DWORD widthByte=bmpIh.biWidth*3;			//一行的字节数
			for (int j=0; j<bmpIh.biWidth; j++)
			{
				WirteBmpColor(pix[i][j], wfp);
			}
			//行的字节数和4的余数不为零，则需要多写一些进去补齐，嘿嘿
			if ((widthByte&0x03))
			{
				BYTE buf[4]={0, 0, 0, 0};
				fwrite(buf, 4-(widthByte&0x03), 1, wfp);
			}
		}
		fclose(wfp);
	}
	else	return ;
}

DWORD BmpClass::GetHeight(void)
{
	return bmpIh.biHeight;
}

DWORD BmpClass::GetWidth(void)
{
	return bmpIh.biWidth;
}
