#ifndef HEADER
#define HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <time.h>


#define Trials 10
#define MIN_D  960
#define MAX_D  1472


  void MatMul( int x, int y, int z, int b, double Alpha, double Beta, double *A, double *B, double *C );

#endif