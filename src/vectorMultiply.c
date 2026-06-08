#include <stdio.h>
#include "mpi.h"

int main(int argc , char * argv[]){
  int rank , size, n, x; 
  
  MPI_Init(&argc , &argv);
  MPI_Comm_rank(MPI_COMM_WORLD , &rank);
  MPI_Comm_size(MPI_COMM_WORLD , &size);
  
  if(rank == 0){
    x = 6; 
    n = 12; 
  }
  MPI_Bcast(&n , 1 , MPI_INT , 0 , MPI_COMM_WORLD); 
  MPI_Bcast(&x , 1 , MPI_INT , 0 , MPI_COMM_WORLD); 
  int array[n]; 
  int i;
  for(i = 0; i < n; i++) array[i] = i+1; 
  int recv[n/size]; 
  MPI_Scatter(&array , n/size , MPI_INT , &recv , n/size , MPI_INT , 0 , MPI_COMM_WORLD); 
  for(i = 0; i < n/size; i++)
    recv[i] *= x; 
  int result[n]; 
  MPI_Allgather(&recv , n/size, MPI_INT , &result , n/size , MPI_INT , MPI_COMM_WORLD); 
  
  printf("Result from process %d: " , rank);
  for(i = 0; i < n; i++) 
      printf("%d " , result[i]); 
  printf("\n"); 
    
  //if(rank == 0){
  //  int i; 
  //  for(i = 0; i < n; i++) 
  //    printf("%d " , result[i]); 
  //  printf("\n"); 
  //}
  MPI_Finalize(); 
  return 0;
}
