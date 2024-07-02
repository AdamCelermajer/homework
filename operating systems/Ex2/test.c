#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("Sleeping for 1 second...\n");
    usleep(2000000); // Sleep for 1 second (1,000,000 microseconds)
    printf("Awake!\n");
    return 0;
}