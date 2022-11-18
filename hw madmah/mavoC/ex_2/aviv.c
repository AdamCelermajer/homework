#include <stdio.h>

int main()
{

    int x = 1;
    while (x != 7)
    {

        printf("choose an option:\n");
        printf("1. octal to hex\n");
        printf("2. binary addition\n");
        printf("3. print HI\n");
        printf("4. count bits\n");
        printf("5. decimal to binary\n");
        printf("6. zig-zag bits\n");
        printf("7. exit\n");

        int y;
        scanf("%d", &y);

        switch (y)
        {
        case 1:
            /* code */
            break;

        case 2:
            /* code */
            break;

        case 3:
            /* code */
            break;

        case 4:

            printf("please enter a binary number: \n");
            long long int z;
            long long int s;
            int alert = 0;
            int k;
            scanf("%lld", &z);
            s = z;

            printf("please enter a binary number: \n");

            while (z != 0)
            {
                if (z % 10 > 1 || z % 10 < 0)
                {
                    alert = 1;
                }
                z = z / 10;
            }

            if (alert == 1)
            {
                printf("invaild input\n");
                break;
            }
            while (s > 0)
            {
                if (s % 10 == 1)
                {
                    k++;
                                }
                s = s / 10;
            }
            printf("%d", k);

            break;

        case 5:
            /* code */
            break;

        case 6:
            /* code */
            break;

        case 7:
            printf("Bye!\n");
            x = 7;
            break;
        default:
            printf("Invalid option!\n");
            break;
        }
    }

    return 0;
}