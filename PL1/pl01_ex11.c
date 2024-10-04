#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define ARRAY_SIZE 1000
#define NFILHOS 5
int
main ()
{
  int numbers[ARRAY_SIZE];	/* array to lookup */
  int result[ARRAY_SIZE/2];
  int n;			/* the number to find */
  time_t t;			/* needed to initialize random number generator (RNG) */
  int i, j, max_value, status;
  pid_t p[NFILHOS];
  pid_t p2;

  /* intializes RNG (srand():stdlib.h; time(): time.h) */
  srand ((unsigned) time (&t));

  /* initialize array with random numbers (rand(): stdlib.h) */
  for (i = 0; i < ARRAY_SIZE; i++)
    numbers[i] = rand () % 1000;

  /* initialize n */
  n = rand () % 1000;

  for (i = 0; i< NFILHOS; i++){
    p[i] = fork();
    max_value = numbers[0];
    if (p[i] == 0){
      for (j = 0; j < ARRAY_SIZE/5; j++){
        if (numbers[j] > max_value){
          max_value = numbers[j];
          exit(max_value);
        } 
      }
    }
  }

  for(i = 0; i < NFILHOS; i++)
  {
        waitpid(p[i], &status, 0);

        max_value = WEXITSTATUS(status); // WEXITSTATUS(status) + i*200

        printf("Max value:%d\n",max_value);
  }
  p2 = fork();
  if (p2 == 0){
    for(i = 0; i < ARRAY_SIZE/2; i++){
        result[i]=((int) numbers[i]/max_value)*100;
        printf("Resultado[%d]: %d\n",i,result[i]);
    }
  }
  else {
    for(i = ARRAY_SIZE/2; i < ARRAY_SIZE; i++){
      waitpid(p2, &status, 0);
        result[i]=((int) numbers[i]/max_value)*100;
        printf("Resultado[%d]: %d\n",i,result[i]);
    }
  }
  exit(0);
    
}
