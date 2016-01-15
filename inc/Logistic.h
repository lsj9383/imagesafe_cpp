#ifndef __LOGISTIC_H
#define __LOGISTIC_H

#include "ChaosMethod.h"

#define MIU		3.9

class LogisticClass:public ChaosMethod
{
public:
	double ChaosSeries;						//混沌系统当前得到的混沌值

private:
	BYTE Series2Bit(void);					//根据当前的ChaosSeries得到对应的BIT
	double LogisticChaosSeries(void);		//根据当前的ChaosSeries得到下次的ChaosSeries

public:
	LogisticClass(double x0);				//初始化混沌初值
	DWORD AutoGenerateBitData(BYTE bits);
	double GenerateOneDouble(void);
	void GenerateMap(DWORD *map, DWORD Len);
};

#endif