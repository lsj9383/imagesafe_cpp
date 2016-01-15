#ifndef __ENCRY_XOR_H
#define __ENCRY_XOR_H

#include "EncryMethod.h"

#define BASIC_XOR_CNT 5

class EncryXOR:public EncryMethod
{
public:
	void Encry(ChaosMethod *cm, BmpClass *bf);
	void Decry(ChaosMethod *cm, BmpClass *bf);
};

#endif