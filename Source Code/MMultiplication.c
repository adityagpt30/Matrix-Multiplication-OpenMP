#include <stdio.h>
#include "matrix.h"

void MatMul( int x, int y, int z, int b, double Alpha, double Beta, double *A, double *B, double *C ){
int ii,jj,kk,i,j,k;
double* Ctemp = (double*)malloc(b*b* sizeof(double));

//Using #pragma omp parallel to parallelize the outermost for loop.
  #pragma omp parallel for collapse(2) private(i, j, k, ii, jj, kk) 
  for(i = 0;i < x;i += b)
    {
      for(j = 0;j < z;j += b)
      {
        for(ii = i;ii < i+b; ii++)
        {
          for(jj = j;jj < j+b;jj++)
          {
            Ctemp[(ii-i)*b + (jj-j)] = C[ii*z + jj];
            C[ii*z + jj] = 0;
          }
        }
        for(k = 0;k < y;k += b)
        {
  //Block Matrix Multiplication and passing the resultant matrix into the function as a reference.
          for(ii = i;ii < i+b;ii++)
          {
            for(jj = j;jj < j+b;jj++)
            {
              for(kk = k;kk < k+b;kk++)
              {
                C[ii*z+jj] += A[ii*y+kk] * B[kk*z+jj];
              }
            }
          }
        }
        for(ii=i;ii<i+b;ii++)
        {
          for(jj=j;jj<j+b;jj++)
          {
            C[ii*z+jj] = Alpha * C[ii*z + jj] + Beta * Ctemp[(ii-i)*b + (jj-j)]; /* Final C= Alpha * ( A * B) + Beta * C(temp variable)*/
          }
        }
      }
    }

}