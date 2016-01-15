#ifndef __ENCRY_ROTA_H
#define __ENCRY_ROTA_H

#include "EncryMethod.h"
#include "rota.h"

class EncryROTA:public EncryMethod
{
public:
	void Encry(ChaosMethod *cm, BmpClass *bf);
	void Decry(ChaosMethod *cm, BmpClass *bf);
};

#endif