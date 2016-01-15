#include "ActiveAuthen.h"

/*
 * ¹¹Ôìº¯Êý.
 */
ActiveAuthenClass::ActiveAuthenClass(char *fn, double key):ImgsfClass(fn, key)
{
	;
}


void ActiveAuthenClass::process(BYTE flg, char *fn)
{
	if (flg==PROTECT_FLG)			aam->protect(cm, bf);
	else if(flg==ACTIVE_AUTHEN_FLG)	aam->authen(cm, bf);
	else if(flg==RECOVER_FLG)		aam->recover(cm, bf);
	else{;}//none

	bf->WritePix2Bmp(fn);
}
