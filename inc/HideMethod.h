#ifndef __HIDE_METHOD_H
#define __HIDE_METHOD_H

#include "ChaosMethod.h"
#include "basic.h"
#include "bmp.h"

class HideMethod
{
public:
	virtual void Embedded(ChaosMethod *cm, BmpClass *bf, char *efn, DWORD maxEmbSize, DWORD embSize)=0;
	virtual DWORD Extract(ChaosMethod *cm, BmpClass *bf, char *efn, DWORD maxEmbSize)=0;
};


#endif