#include <stdio.h>
#include <stdlib.h>
#include <mpi.h> 

int main(int argc , char * argv[]){
  int rank,size;
  int x ,res; 
  
  MPI_Init(&argc , &argv); 
  MPI_Comm_rank(MPI_COMM_WORLD , &rank); 
  MPI_Comm_size(MPI_COMM_WORLD , &size);
  
  if(rank == 0){
    x = 2; 
  }
  
  MPI_Bcast(&x , 1 , MPI_INT , 0 , MPI_COMM_WORLD);  
  x *= (rank+1); 
  
  MPI_Allreduce(&x , &res , 1 , MPI_INT , MPI_PROD , MPI_COMM_WORLD); 
  
  printf("Product from process %d is %d \n" , rank , res); 
  MPI_Finalize();
  return 0; 
}

