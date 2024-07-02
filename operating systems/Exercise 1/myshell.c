// name: adam celermajer
// taz: 332638592
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h> // Added for directory operations
#define MAX_HISTORY_SIZE 99
#define MAX_COMMAND_SIZE 100

typedef struct
{
    char *data[MAX_HISTORY_SIZE + 1];
    int top_element;
} History;

void add_to_history(History *history, const char *command)
{
    if (history->top_element == MAX_HISTORY_SIZE)
    {
        history->top_element = 0;
        exit(0);
        return;
    }
    history->top_element++;
    int len = strlen(command);
    history->data[history->top_element] = (char *)malloc((len + 1) * sizeof(char)); // Allocate memory
    strcpy(history->data[history->top_element], command);                           // Copy command
}

void print_to_history(History *history)
{
    for (int i = 0; i <= history->top_element; i++)
    {
        printf("%s\n", history->data[i]);
    }
}

int find_executable(const char *command, char *paths[], int path_count, char *full_path)
{
    for (int i = 0; i < path_count; i++)
    {
        struct dirent *entry;
        DIR *dp = opendir(paths[i]);
        if (dp == NULL)
        {
            continue;
        }
        while ((entry = readdir(dp)))
        {
            if (strcmp(entry->d_name, command) == 0)
            {
                snprintf(full_path, MAX_COMMAND_SIZE, "%s/%s", paths[i], command);
                closedir(dp);
                return 1;
            }
        }
        closedir(dp);
    }
    return 0;
}

int main(int argc, char *argv[])
{
    // Store the provided paths
    char *paths[MAX_COMMAND_SIZE];
    int path_count = 0;
    for (int i = 1; i < argc; i++)
    {
        paths[path_count++] = argv[i];
    }

    char *command = (char *)malloc(sizeof(char) * MAX_COMMAND_SIZE);
    char *args[MAX_COMMAND_SIZE / 2 + 1]; // Command line arguments
    char rsp[1024];                       // response to some command
    History history;
    history.top_element = -1;

    char *current_directory = (char *)malloc(sizeof(char) * MAX_COMMAND_SIZE);
    current_directory = argv[0];
    while (1)
    {
        printf("$ ");
        fflush(stdout);
        fgets(command, MAX_COMMAND_SIZE, stdin);
        // Remove the newline character if present
        size_t len = strlen(command);

        if (len == 1)
            continue;
        if (len > 0 && command[len - 1] == '\n')
        {
            command[len - 1] = '\0'; // Replace newline with null terminator
        }

        add_to_history(&history, command);

        if (strcmp(command, "exit") == 0)
        {
            break;
        }

        if (strcmp(command, "history") == 0)
        {
            print_to_history(&history);
            continue;
        }

        if (strcmp(command, "pwd") == 0)
        {
            if (getcwd(rsp, sizeof(rsp)) != NULL)
            {
                printf("Current working directory: %s\n", rsp);
            }
            else
            {
                perror("getcwd() error");
            }
            continue;
        }

        // Fork-exec command OR CD command
        // *****************************************************************
        // Split the command into arguments
        int argc = 0;
        char *token = strtok(command, " ");
        while (token != NULL)
        {
            args[argc++] = token;
            token = strtok(NULL, " ");
        }
        args[argc] = NULL;

        if (strcmp(args[0], "cd") == 0)
        {
            if (chdir(args[1]) == 0)
            {
            }
            else
            {
                perror("chdir failed");
            }
            continue;
        }

        pid_t pid = fork();
        if (pid < 0)
        {
            // Error occurred
            perror("fork failed");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            // Child process
            char full_path[MAX_COMMAND_SIZE];
            if (find_executable(args[0], paths, path_count, full_path))
            {
                execv(full_path, args);
            }
            else
            {
                execvp(args[0], args); // Try the default PATH if not found in provided paths
            }
            // If execvp returns, it must have failed
            perror("exec failed");
            exit(EXIT_FAILURE);
        }
        else
        {
            // Parent process
            int status;
            if (waitpid(pid, &status, 0) > 0)
            {
                if (WIFEXITED(status) && !WEXITSTATUS(status))
                {
                }
                else if (WIFEXITED(status) && WEXITSTATUS(status))
                {
                }
                else
                {
                }
            }
            else
            {
                // waitpid failed
                perror("waitpid failed");
                exit(EXIT_FAILURE);
            }
        }
    }

    // Free allocated memory
    for (int i = 0; i <= history.top_element; i++)
    {
        free(history.data[i]);
    }
    free(command);
    return 0;
}
