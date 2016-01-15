#ifndef __DCT_H
#define __DCT_H

#include <memory.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "bmp.h"

#define PI 3.1415926
#define CLK_TCK CLOCKS_PER_SEC

void Block8x8_Dct2(BYTE **timeDomain, double **freDomain);
void Block8x8_iDct2(BYTE **timeDomain, double **freDomain);
void DCT(double *f,double *F, int N);
void iDCT(double *f,double *F, int N);

#endif
