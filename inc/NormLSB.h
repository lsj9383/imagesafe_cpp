#ifndef __NORM_LSB_H
#define __NORM_LSB_H


#include "HideMethod.h"

class NormLSBMethod:public HideMethod
{
private:
	DWORD *map;

private:
	BYTE ExtractOneByte(DWORD *a);

public:
	~NormLSBMethod();
	void Embedded(ChaosMethod *cm, BmpClass *bf, char *efn, DWORD maxEmbSize, DWORD embSize);
	DWORD Extract(ChaosMethod *cm, BmpClass *bf, char *efn, DWORD maxEmbSize);
};


#endif




