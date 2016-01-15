#ifndef __LOGISTIC_H
#define __LOGISTIC_H

#include "ChaosMethod.h"

#define MIU		3.9

class LogisticClass:public ChaosMethod
{
public:
	double ChaosSeries;						//����ϵͳ��ǰ�õ��Ļ���ֵ

private:
	BYTE Series2Bit(void);					//���ݵ�ǰ��ChaosSeries�õ���Ӧ��BIT
	double LogisticChaosSeries(void);		//���ݵ�ǰ��ChaosSeries�õ��´ε�ChaosSeries

public:
	LogisticClass(double x0);				//��ʼ�������ֵ
	DWORD AutoGenerateBitData(BYTE bits);
	double GenerateOneDouble(void);
	void GenerateMap(DWORD *map, DWORD Len);
};

#endif