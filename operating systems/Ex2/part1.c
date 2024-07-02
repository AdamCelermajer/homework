// adam celermajer 332638592
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

void write_file(char *filename, char *buffer, int times)
{
    int fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0666);
    if (fd == -1)
    {
        perror("Error opening file");
        exit(1);
    }
    for (int i = 0; i < times; i++)
    {
        if (write(fd, buffer, strlen(buffer)) == -1)
        {
            perror("Error writing to file");
            close(fd);
            exit(1);
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        fprintf(stderr, "Usage: %s <parent_message> <child1_message> <child2_message> <count>", argv[0]);
        return 1;
    }
    char *parent_message = argv[1];
    char *first_message = argv[2];
    char *second_message = argv[3];
    int count = atoi(argv[4]);

    // Create a child process
    pid_t pid1 = fork();
    if (pid1 < 0)
    {
        perror("Fork failed");
        return 1;
    }
    else if (pid1 == 0)
    {
        // First child process
        write_file("output.txt", first_message, count);
        return 0;
    }

    pid_t pid2 = fork();
    if (pid2 < 0)
    {
        perror("Fork failed");
        return 1;
    }
    else if (pid2 == 0)
    {
        // First child process
        write_file("output.txt", second_message, count);
        return 0;
    }
    wait(NULL);
    wait(NULL);
    write_file("output.txt", parent_message, count);
    return 0;
}