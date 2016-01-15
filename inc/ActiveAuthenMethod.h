#ifndef __ACTIVE_AUTHEN_METHOD_H
#define __ACTIVE_AUTHEN_METHOD_H

#include "basic.h"
#include "bmp.h"
#include "ChaosMethod.h"

class ActiveAuthenMethod
{
public:
	virtual void protect(ChaosMethod *cm, BmpClass *bf)=0;
	virtual void authen(ChaosMethod *cm, BmpClass *bf)=0;
	virtual void recover(ChaosMethod *cm, BmpClass *bf)=0;
	virtual ~ActiveAuthenMethod(){;}
};

#endif