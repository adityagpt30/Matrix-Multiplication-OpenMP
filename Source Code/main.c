#include <stdio.h>
#include "matrix.h"

int main( int argc, char **argv )
{
  int x, y, z, b, bb, bmin, bmax;
  int row, column, nth;
  double *A, *B, *C, *D, Alpha, Beta, time1, time2;
  char Status[10];

//Assigns value to scalars alpha and beta to compute resultant matrix C
   Alpha = (double) 1.0;	
   Beta  = (double) 2.0;

//Allocates the memory of the size of the matrices from heap.	
   A = (double *) malloc(sizeof(double) * MAX_D * MAX_D);
   B = (double *) malloc(sizeof(double) * MAX_D * MAX_D);
   C = (double *) malloc(sizeof(double) * MAX_D * MAX_D);
   D = (double *) malloc(sizeof(double) * MAX_D * MAX_D);
      if ((A == NULL) || (B == NULL) || (C == NULL) || (D == NULL))
       {
         printf("Memory Insufficient\n");
         exit(1); }

 //Initializes the arrays A, B and D using random function.
    for(row=0; row<MAX_D; row++)
     for(column=0; column<MAX_D; column++)
       A[row* MAX_D +column] = rand();

    for(row=0; row<MAX_D; row++)
     for(column=0; column<MAX_D; column++)
       B[row* MAX_D +column] = rand();

    for(row=0; row<MAX_D; row++)
     for(column=0; column<MAX_D; column++)
       D[row* MAX_D +column] = rand();

    for(x=MIN_D; x<=MAX_D; x+=128)
      {
       y = z = x ;
	    
 //Number of threads are 4 and block size is ranging from 4 to 64
    for(nth=1; nth<=4; nth*=2)
      {
       if(nth==4)
        {
         bmin = 4;
         bmax = 64; }
       else
         bmin = bmax = 16;
          for(bb=bmin; bb<=bmax; bb*=4)
		{
            for(row=0; row<x; row++)
              for(column=0; column<z; column++)
                C[row*z+column] = D[row*z+column];

           b = bb;
         if(b>x) b=x;
         if(b>y) b=y;
         if(b>z) b=z;

       omp_set_num_threads( nth );
          time1 = time(NULL);
       MatMul(x, y, z, b, Alpha, Beta, A, B, C);
          time2 = time(NULL);

 // Using Random function
  int success = 1, r;
    for(r=0; r<Trials; r++) {
       double minimum, maximum, error, answer;

       row = (rand()%x);
       column = (rand()%z);

       int k;
       answer = D[row*z+column] * Beta;
       for(k=0; k<y; k++)
         answer += Alpha * A[row*y+k]*B[k*z+column];

          if(answer > C[row*z+column])
             {
               minimum = C[row*z+column];
               maximum = answer;
            }
          else
            {
              minimum = answer;
              maximum = C[row*z+column];
            }
          error = (double) (maximum-minimum)/ (double) maximum;

      if((minimum > (double) 0.0001) && (error > (double) 0.01))
            success = 0;     }

      if(success == 0)
           strcpy (Status, "Failed");
      else
           strcpy (Status, "Passed");

     printf("{x=%d,y=%d,z=%d,nth=%d,b=%d,time=%g,Status=%s},  ", x, y, z, nth, b, (double) difftime(time2,time1), Status);
     fflush (stdout);
      }
    }
  }
return 0;
}
