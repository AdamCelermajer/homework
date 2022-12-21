#include <stdio.h>

int main()
{

    char ch;
    scanf("%c", &ch);

    while (1)
    {

        printf("%c\n", ch);

        scanf("%c", &ch);
        if (ch == '\n')
        {
            break;
        }
    }
    return 0;
}