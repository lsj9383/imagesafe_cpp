#include "dct.h"

void Block8x8_Dct2(BYTE **timeDomain, double **freDomain)
{
	double *timeSeries, *freSeries;		//一维的时域和频域信号
	int N=8;
	
	//1).将二维转一维(没办法，这个的函数用的是一维的，晕)
	timeSeries = (double *)malloc((N*N) * sizeof(double));
	freSeries = (double *)malloc((N*N) * sizeof(double));
	for (int i=0; i<N; i++)
	{
		for (int j=0; j<N; j++)
		{
			timeSeries[i*N+j] = timeDomain[i][j];
		}
	}

	//2).dct
	DCT(timeSeries, freSeries, N);

	//3).将结果赋值回去
	for (int i=0; i<N; i++)
	{
		for (int j=0; j<N; j++)
		{
			freDomain[i][j] = freSeries[i*N+j];
		}
	}
	free(timeSeries);
	free(freSeries);
}

void Block8x8_iDct2(BYTE **timeDomain, double **freDomain)
{
	double *timeSeries, *freSeries;		//一维的时域和频域信号
	int N=8;
	
	//1).将二维转一维(没办法，这个的函数用的是一维的，晕)
	timeSeries = (double *)malloc((N*N) * sizeof(double));
	freSeries = (double *)malloc((N*N) * sizeof(double));
	for (int i=0; i<N; i++)
	{
		for (int j=0; j<N; j++)
		{
			freSeries[i*N+j] = freDomain[i][j];
		}
	}

	//2).idct
	iDCT(freSeries, timeSeries, N);

	//3).将结果赋值回去
	for (int i=0; i<N; i++)
	{
		for (int j=0; j<N; j++)
		{
			if (timeSeries[i*N+j]>255)
				timeDomain[i][j]=255;
			else if(timeSeries[i*N+j]<0)
				timeDomain[i][j]=0;
			else
				timeDomain[i][j] = (BYTE)(timeSeries[i*N+j]+0.5);		//对整数四舍五入
		}
	}
	free(timeSeries);
	free(freSeries);
}

//f:空域
//F:频域
void DCT(double *f,double *F, int N)
{
	int n,m,x;
	double *dTemp=new double[N*N];		//中间矩阵
	double *coff=new double[N*N];		//变换系数

	//系数
	coff[0]=(double)1/sqrt((double)N);
	for(m=1;m<N;m++)
	{
		coff[m]=sqrt((double)2)/sqrt((double)N);
	}
	memset(dTemp,0,sizeof(double)*N*N);
	memset(F,0,sizeof(double)*N*N);

	//一维变换
	for(n=0;n<N;n++)
	{
		for(m=0;m<N;m++)
		{
			for(x=0;x<N;x++)
			{
				dTemp[m*N+n]+=coff[m]*f[x*N+n]*cos((2*x+1)*PI*m/(2*N));
			}
		}
	}

	//第二次一维变换
	for(m=0;m<N;m++)
	{
		for(n=0;n<N;n++)
		{
			for(x=0;x<N;x++)
			{
				F[m*N+n]+=coff[n]*dTemp[m*N+x]*cos((2*x+1)*PI*n/(2*N));
			}
		}
	}

	delete []dTemp;
	delete []coff;
}

//f:频域
//F:空域
void iDCT(double *f,double *F, int N)
{
	int m,y,x;
	double *dTemp=new double[N*N];//中间矩阵
	double *coff=new double[N*N];//变换系数

	//系数
	coff[0]=1/sqrt((double)N);
	for(m=1;m<N;m++)
	{
		coff[m]= sqrt((double)2) /  sqrt((double)N);
	}
	memset(dTemp,0,sizeof(double)*N*N);
	memset(F,0,sizeof(double)*N*N);

	//一维变换
	for(x=0;x<N;x++)
	{
		for(y=0;y<N;y++)
		{
			for(m=0;m<N;m++)
			{
				dTemp[x*N+y]+=coff[m]*f[x*N+m]*cos((2*y+1)*PI*m/(2*N));
			}
		}
	}
	//第二次一维变换
	for(y=0;y<N;y++)
	{
		for(x=0;x<N;x++)
		{
			for(m=0;m<N;m++)
			{
				F[x*N+y]+=coff[m]*dTemp[m*N+y]*cos((2*x+1)*PI*m/(2*N));
			}
		}
	}
	delete []dTemp;
	delete []coff;
}