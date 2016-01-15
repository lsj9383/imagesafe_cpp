#ifndef __ENCRY_METHOD_H
#define __ENCRY_METHOD_H

#include "basic.h"
#include "bmp.h"
#include "ChaosMethod.h"

class EncryMethod
{
public:
	virtual void Encry(ChaosMethod *cm, BmpClass *bf)=0;
	virtual void Decry(ChaosMethod *cm, BmpClass *bf)=0;
};

#endif