// adam celermajer 332638592
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
void write_message(const char *message, int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("%s\n", message);
        usleep((rand() % 100) * 1000); // Random delay between 0 and 99 milliseconds
    }
}
void try_writing(const char *message, int count)
{
    int fd;

    while (1)
    {
        fd = open("lockfile.lock", O_RDWR | O_CREAT | O_EXCL, 0600);
        if (fd < 0)
        {
            usleep(100000);
            continue;
        }
        break;
    }
    write_message(message, count);

    if (unlink("lockfile.lock") == -1)
    {
        perror("Error deleting lockfile.lock");
    }
    close(fd);
}
int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        fprintf(stderr, "Usage: %s <message1> <message2> ... <order> <count>", argv[0]);
        return 1;
    }
    char buffer[100];
    int count = atoi(argv[argc - 1]);

    pid_t pid;
    int status;

    for (int i = 1; i < argc - 1; i++)
    {
        // Create a child process
        pid = fork();
        if (pid < 0)
        {
            perror("Fork failed");
            return 1;
        }
        else if (pid == 0)
        {
            // First child process
            try_writing(argv[i], count);
            return 0;
        }
    }
    while ((pid = wait(&status)) > 0)
        ;
    return 0;
}