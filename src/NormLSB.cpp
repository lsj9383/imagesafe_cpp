#include "NormLSB.h"

NormLSBMethod::~NormLSBMethod()
{
	if(map!=NULL)
	{
		free(map);map=NULL;
	}
}

BYTE NormLSBMethod::ExtractOneByte(DWORD *a)
{
	BYTE c=0;

	for (int i=0; i<8; i++)
	{
		if ((a[i]&0x01)==0)
		{
			c<<=1;
		}
		else
		{
			c = (c<<1)|0x01;
		}
	}
	return c;
}


void NormLSBMethod::Embedded(ChaosMethod *cm, BmpClass *bf, char *efn, DWORD maxEmbSize, DWORD embSize)
{
	//1).选取嵌入文件
	FILE *efp=NULL;
	efp = fopen(efn, "rb");

	//given
	for (int i=0; i<GIVENUP; i++)	cm->GenerateOneDouble();

	//generate map
	map = (DWORD *)malloc(maxEmbSize*sizeof(DWORD));
	cm->GenerateMap(map, maxEmbSize);

	//2).Embedded
	DWORD width = bf->GetWidth();
	for (DWORD i=0; i<4; i++)
	{
		BYTE c=0;
		c = ((embSize)>>(8*(3-i))) &0xFF;
		//读取一个字节，嵌入8bit
		for (int j=0; j<8; j++)
		{
			DWORD index = this->map[i*8+j];									//当前位对应的嵌入位置

			if ((c&0x80)==0)
			{
				bf->pix[index/width][index%width] &= 0xFFFFFFFE;	//将最后1bit置0
			}
			else
			{
				bf->pix[index/width][index%width] |= 0x01;		//将最后1bit置1
			}
			c<<=1;
		}
	}
	for (DWORD i=0; i<(embSize/8-4); i++)
	{
		BYTE c=0;
		fread(&c, 1, 1, efp);
		//读取一个字节，嵌入8bit
		for (int j=0; j<8; j++)
		{
			DWORD index = map[32+i*8+j];								//当前位对应的嵌入位置

			if ((c&0x80)==0)
			{
				bf->pix[index/width][index%width] &= 0xFFFFFFFE;	//将最后1bit置0
			}
			else
			{
				bf->pix[index/width][index%width] |= 0x01;	//将最后1bit置1
			}
			c<<=1;
		}
	}

	//release
	free(map);map=NULL;
}

DWORD NormLSBMethod::Extract(ChaosMethod *cm, BmpClass *bf, char *efn, DWORD maxEmbSize)
{
	DWORD extSize=0;

	//1).选取嵌入文件
	FILE *efp=NULL;
	efp = fopen(efn, "wb");
	if (efp == NULL)
	{
		printError(ELSE_ERR);
		return 0;
	}
	//given
	for (int i=0; i<GIVENUP; i++)	cm->GenerateOneDouble();

	//generate map
	map = (DWORD *)malloc(maxEmbSize*sizeof(DWORD));
	cm->GenerateMap(map, maxEmbSize);


	//4).Embedded
	DWORD width = bf->GetWidth();
	for (DWORD i=0; i<4; i++)
	{
		BYTE c=0;
		DWORD a[8];
		for (int j=0; j<8; j++)
		{
			DWORD index = map[i*8+j];
			a[j] = bf->pix[index/width][index%width];
		}
		c = ExtractOneByte(a);
		extSize = (extSize<<8)|c;
	}

	///////////////////////////////////////////
	if ((maxEmbSize-32)<extSize)
    {
        printError(HIDE_ERR_KEY);
    }
	///////////////////////////////////////////

	for (DWORD i=0; i<(extSize/8-4); i++)
	{
		DWORD a[8];
		BYTE c=0;
		for (int j=0; j<8; j++)
		{
			DWORD index = map[32+i*8+j];
			a[j] = bf->pix[index/width][index%width];
		}
		c = ExtractOneByte(a);
		fwrite(&c, 1, 1, efp);
	}

	fclose(efp);

	//release
	free(map);map=NULL;
	return extSize;
}
