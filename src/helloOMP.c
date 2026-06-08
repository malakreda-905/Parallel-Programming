#include <stdio.h>
#include "omp.h" 

#define THREADS 4

int main(){
  int id , total_threads; 
  
  printf("Serial Region! \n"); 
  int x = 2 , y = 10; 
  
  #pragma omp parallel num_threads(THREADS) firstprivate(x) shared(y)
  {
    total_threads = omp_get_num_threads(); 
    id = omp_get_thread_num(); 
    if(id == 0) 
      x = 20; 
    printf("X is %d and Y is %d from Process %d \n" , x , y , id); 
    //printf("Hello from Thread %d out of %d Threads! \n" , id , total_threads); 
  }
  printf("Serial Region Again!\n");
  return 0; 
}
