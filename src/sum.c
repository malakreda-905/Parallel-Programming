#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <mpi.h>

int main(int argc , char * argv[]){
  int rank, size; 
  MPI_Status status;
  int tag = 0; 
  
  MPI_Init(&argc , &argv); 
  MPI_Comm_size(MPI_COMM_WORLD , &size); 
  MPI_Comm_rank(MPI_COMM_WORLD , &rank);
  
  int len = 12; 
  int chunck_size = len/(size-1); 
  
  if(rank == 0){
    int array[12] = {1,2,3,4,5,6,7,8,9,10,11,12}; 
    int dest; 
    for(dest = 1; dest < size; dest++){
      MPI_Send(&array[(dest-1)*chunck_size] , chunck_size, MPI_INT , dest, tag , MPI_COMM_WORLD);
    } 
    
    int global_sum = 0, local_sum; 
    
    for(dest = 1; dest < size; dest++){
      MPI_Recv(&local_sum , 1 , MPI_INT , dest , tag , MPI_COMM_WORLD , &status); 
      global_sum += local_sum;  
    }
    printf("Sum of the array is %d \n" , global_sum); 
  }
  else{
    int chunck[chunck_size]; 
    MPI_Recv(&chunck , chunck_size , MPI_INT , 0 , tag , MPI_COMM_WORLD , &status); 
    
    int local = 0; 
    int i; 
    for(i = 0; i < chunck_size; i++){
      local += chunck[i]; 
    }
    printf("Local sum of the array at process %d is %d \n", rank , local); 
    
    MPI_Send(&local , 1 , MPI_INT , 0 , tag , MPI_COMM_WORLD); 
  }
  
  MPI_Finalize(); 
  return 0; 
}
