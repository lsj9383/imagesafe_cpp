#include "EncryDecry.h"

/*
 * ¹¹Ôìº¯Êý.
 */
EncryDecryClass::EncryDecryClass(char *fn, double key):ImgsfClass(fn, key)
{
	;
}


void EncryDecryClass::process(BYTE flg, char *fn)
{
	if (flg==ENCRY_FLG)		em->Encry(cm, bf);
	else if(flg==DECRY_FLG)	em->Decry(cm, bf);
	else{;}//none

	bf->WritePix2Bmp(fn);
}