#ifndef __RANDOM_METHOD_H
#define __RANDOM_METHOD_H

#include "basic.h"

class ChaosMethod
{
public:
	virtual DWORD AutoGenerateBitData(BYTE bits)=0;
	virtual double GenerateOneDouble(void)=0;
	virtual void GenerateMap(DWORD *map, DWORD Len)=0;
};

#endif