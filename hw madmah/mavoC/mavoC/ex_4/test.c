#include <stdio.h>

int main()
{

    printf("input number:\n");
    char input = 'g';

    while (1)
    {
        scanf("%c", &input);
        if (input == '\n')
            break;
        printf("output number: %c\n", input);
    }
}