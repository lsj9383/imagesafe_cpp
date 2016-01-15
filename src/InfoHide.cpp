#include "InfoHide.h"
/*
 * 构造函数.
 */
InfoHideClass::InfoHideClass(char *fn, char *efn, double key):ImgsfClass(fn, key)
{
	this->maxEmbSize = this->bf->GetHeight()*this->bf->GetHeight();
	sprintf(this->efn, "%s", efn);
}

bool InfoHideClass::ReadyEmbFile(void)
{
	DWORD EmbSize;

	EmbSize = (getFileSize(efn)+4)*8;		//换成bit,加4是因为要用4字节来隐藏嵌入数据的长度
	if (EmbSize>this->maxEmbSize)
	{
	    printError(HIDE_OVERLOAD);
		return false;
	}
	else
	{
		this->eSize = EmbSize;
	}
	return true;
}

void InfoHideClass::process(BYTE flg, char *fn)
{
	if (flg==EMBED_FLG)
	{
		this->ReadyEmbFile();
		hm->Embedded(cm, bf, efn, this->maxEmbSize, this->eSize);
		bf->WritePix2Bmp(fn);
	}
	else if(flg==EXTRACT_FLG)
	{
		this->eSize = hm->Extract(cm, bf, efn, this->maxEmbSize);
	}
	else{;}//none
}
