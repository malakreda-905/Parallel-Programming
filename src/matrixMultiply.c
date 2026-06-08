#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include "omp.h"

#define SIZE 8

int main(int argc , char* argv[]){
  int rank , num_proc; 
  int provided; 
  MPI_Init_thread(&argc , &argv , MPI_THREAD_FUNNELED, &provided);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &num_proc);
  
  int rows_per_proc = SIZE/num_proc; 
  double *A = malloc(SIZE*SIZE*sizeof(double));
  double *B = malloc(SIZE*SIZE*sizeof(double));
  double *C = malloc(SIZE*SIZE*sizeof(double));
  
  double *localA = malloc(rows_per_proc * SIZE * sizeof(double));
  double *localC = malloc(rows_per_proc * SIZE * sizeof(double));
  
  for(int i = 0; i < rows_per_proc*SIZE; i++){
    localC[i] = 0.0;
  }
  
  if(rank == 0){
    for(int i = 0; i < SIZE*SIZE; i++){
      A[i] = 1.0;
      B[i] = 2.0;
      C[i] = 0.0; 
    }
  }
  
  MPI_Scatter(A , rows_per_proc*SIZE , MPI_DOUBLE , localA , rows_per_proc*SIZE , MPI_DOUBLE , 0 , MPI_COMM_WORLD); 
  MPI_Bcast(B , SIZE*SIZE , MPI_DOUBLE , 0 , MPI_COMM_WORLD); 
  
  #pragma omp parallel for schedule(static)
    for(int i = 0; i < rows_per_proc; i++){
      for(int k = 0; k < SIZE; k++){
        double tmp = localA[i*SIZE+k];
        for(int j = 0; j < SIZE; j++){
          localC[i*SIZE+j] += tmp*B[k*SIZE+j];
        }
      }
    }
  MPI_Gather(localC , rows_per_proc*SIZE , MPI_DOUBLE , C , rows_per_proc*SIZE , MPI_DOUBLE , 0 , MPI_COMM_WORLD);
  
  if(rank==0){
    printf("Matrix Multiplication\n");
    for(int i = 0; i < SIZE; i++){
      for(int j = 0; j < SIZE; j++){
        printf("%.1f " , C[i*SIZE+j]);
      }
      printf("\n");
    }
  }
  
  free(A);
  free(B);
  free(C);
  free(localA);
  free(localC);
  
  MPI_Finalize();
  
  return 0;
}
