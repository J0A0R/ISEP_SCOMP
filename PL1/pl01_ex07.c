#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
 #include <sys/types.h>
       #include <sys/wait.h>

#define ARRAY_SIZE 1000
int
main ()
{
  int numbers[ARRAY_SIZE];	/* array to lookup */
  int n;			/* the number to find */
  time_t t;			/* needed to initialize random number generator (RNG) */
  int i, count1, count2, final, status;

  /* intializes RNG (srand():stdlib.h; time(): time.h) */
  srand ((unsigned) time (&t));

  /* initialize array with random numbers (rand(): stdlib.h) */
  for (i = 0; i < ARRAY_SIZE; i++)
    numbers[i] = rand () % 1000;

  /* initialize n */
  n = rand () % 1000;

  pid_t p = fork();

 if (p == 0){
    count1 = 0;
    for (i = 0; i < 500; i++){
        if (numbers[i] == n){
            count1++;
        }
    }
    exit(count1);
 }
else {
    count2 = 0;
    for (i = 501; i < ARRAY_SIZE; i++){
        if (numbers[i] == n){
            count2++;
        }
    }
    wait(&status);
    count1 = WEXITSTATUS(status);
    final = count1+ count2;
    printf("Count1=%d,\nCount2=%d,\nFinal=%d\n",count1,count2,final);
}

return 0;
}