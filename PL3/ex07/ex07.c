#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#define STR_SIZE 50
#define NR_DISC 10

struct aluno
{
    int numero;
    char nome[STR_SIZE];
    int disciplinas[NR_DISC];
};

int main()
{
    int fd;
    struct aluno *shared_data;
    pid_t pid1, pid2;

    fd = shm_open("/EX07_Shared_File", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd == -1)
    {
        printf("Failed to create shared memory.\n");
        return 1;
    }

    ftruncate(fd, sizeof(struct aluno));

    shared_data = mmap(NULL, sizeof(struct aluno), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (shared_data == MAP_FAILED)
    {
        printf("Failed to map shared memory.\n");
        return 1;
    }

    printf("Enter student number: ");
    scanf("%d", &(shared_data->numero));
    printf("Enter student name: ");
    scanf("%s", shared_data->nome);
    printf("Enter grades of %d subjects:\n", NR_DISC);
    for (int i = 0; i < NR_DISC; i++)
    {
        scanf("%d", &(shared_data->disciplinas[i]));
    }

    int *sync = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *sync = 0;

    pid1 = fork();
    if (pid1 == 0)
    {

        int max_grade = shared_data->disciplinas[0], min_grade = shared_data->disciplinas[0];
        for (int i = 1; i < NR_DISC; i++)
        {
            if (shared_data->disciplinas[i] > max_grade)
            {
                max_grade = shared_data->disciplinas[i];
            }
            if (shared_data->disciplinas[i] < min_grade)
            {
                min_grade = shared_data->disciplinas[i];
            }
        }
        printf("Student number: %d\n", shared_data->numero);
        printf("Student name: %s\n", shared_data->nome);
        printf("Highest grade: %d\n", max_grade);
        printf("Lowest grade: %d\n", min_grade);

        *sync = 1;
    }
    else
    {
        pid2 = fork();
        if (pid2 == 0)
        {

            float avg_grade = 0;
            for (int i = 0; i < NR_DISC; i++)
            {
                avg_grade += shared_data->disciplinas[i];
            }
            avg_grade /= NR_DISC;
            printf("\nStudent number: %d\n", shared_data->numero);
            printf("Student name: %s\n", shared_data->nome);
            printf("Average grade: %.2f\n", avg_grade);

            *sync = 1;
        }
        else
        {

            waitpid(pid1, NULL, 0);
            waitpid(pid2, NULL, 0);

            munmap(shared_data, sizeof(struct aluno));
            shm_unlink("/EX07_Shared_File");

            munmap(sync, sizeof(int));
        }
    }

    return 0;
}