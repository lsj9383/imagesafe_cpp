#include "Logistic.h"

LogisticClass::LogisticClass(double x0)
{
    ///////////////////////////////////////
    if (x0>1 || x0<0)
    {
        printError(ERR_RANGE_KEY);
    }
    ///////////////////////////////////////
	this->ChaosSeries = x0;
}

double LogisticClass::LogisticChaosSeries(void)
{
	return MIU*ChaosSeries*(1-ChaosSeries);
}

BYTE LogisticClass::Series2Bit(void)
{
	return (SIGN( 2*(ChaosSeries-0.5) ) + 1)/2;
}

DWORD LogisticClass::AutoGenerateBitData(BYTE bits)
{
	DWORD rval=0;

	for (int q=0; q<bits; q++)
	{
		rval<<=1;
		ChaosSeries = LogisticChaosSeries();	//更新ChaoSeries
		rval = rval|Series2Bit();
	}

	return rval;
}

double LogisticClass::GenerateOneDouble(void)
{
	this->ChaosSeries = LogisticChaosSeries();
	return this->ChaosSeries;
}

void LogisticClass::GenerateMap(DWORD *map, DWORD Len)
{
	double *Series;
	double *SortSeries;
	//1).生成随机序列
	Series = (double*)malloc(sizeof(double)*Len);				//序列空间
	SortSeries = (double*)malloc(sizeof(double)*Len);			//序列空间
	for (DWORD i=0; i<Len; i++)
	{
		Series[i] = GenerateOneDouble();
		SortSeries[i] = Series[i];
	}

	//2).随机序列排序
	for (DWORD i=0; i<Len; i++)
	{
		double min = SortSeries[i];
		double buf = 0;
		DWORD col=i;
		for (DWORD j=i; j<Len; j++)
		{
			if (min>SortSeries[j])
			{
				min = SortSeries[j];
				col = j;
			}
		}
		buf = SortSeries[i];
		SortSeries[i] = SortSeries[col];
		SortSeries[col] = buf;
	}

	//3).生成映射
	for (DWORD i=0; i<Len; i++)
	{
		DWORD col=0;
		for (DWORD j=0; j<Len; j++)
		{
			if (SortSeries[i] == Series[j])
			{
				col = j;
				break;
			}
		}
		map[i]=col;
	}
	//4)done, release and
	free(Series);
	free(SortSeries);
}

