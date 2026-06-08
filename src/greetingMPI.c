#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

int main(int argc , char* argv[]){
  int rank;
  int size; 
  char message[100]; 
  
  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);
  
  MPI_Status status; 
  if(rank != 0){
    sprintf(&message , "Hello from process %d" , rank); 
    
    MPI_Send(message , strlen(message)+1 , MPI_CHAR , 0 , 0 , MPI_COMM_WORLD); 
  }
  else{
    int i; 
    for(i = 1; i < size; i++){
      MPI_Recv(message , 100 , MPI_CHAR , i , 0 , MPI_COMM_WORLD , &status); 
      printf("%s\n" , message); 
    }
  }
  MPI_Finalize(); 
  return 0; 
}
