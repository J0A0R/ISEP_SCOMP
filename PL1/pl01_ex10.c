#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define ARRAY_SIZE 2000
#define NFILHOS 10
int
main ()
{
  int numbers[ARRAY_SIZE];	/* array to lookup */
  int appear[10];
  int n;			/* the number to find */
  time_t t;			/* needed to initialize random number generator (RNG) */
  int i, count1, count2, final;
  pid_t p[NFILHOS];
  int status;

  /* intializes RNG (srand():stdlib.h; time(): time.h) */
  srand ((unsigned) time (&t));

  /* initialize array with random numbers (rand(): stdlib.h) */
  for (i = 0; i < ARRAY_SIZE; i++)
    numbers[i] = rand () % 1000;

  /* initialize n */
  n = rand () % 1000;
    

    for(i = 0; i < NFILHOS; i++) {
        p[i] = fork();
        
        if (p[i] == 0)
        {
            for(int j = i * 200; j <= (i + 1) * 200; j++)
            {
                if (numbers[j] == n) {
                    exit(j - (i*200));
                }
            }
            exit(255);
        }
    }

    for(i = 0; i < NFILHOS; i++)
    {
        waitpid(p[i], &status, 0);

        appear[i] = WEXITSTATUS(status); // WEXITSTATUS(status) + i*200

        printf("Filho %d : posiçao relativa %d\n", i, appear[i]);
    }

    // ------------------------------------
    
    exit(0);


}