#include <stdio.h>
#include <math.h>

int operation(int var1, char op, int var2)
{
    int diff = 'a' - 'A';
    int result = 0;
    if (var1 >= 'A' && var1 <= 'Z')
    {
        var1 = diff + var1;
    }
    if (var2 >= 'A' && var2 <= 'Z')
    {
        var2 = diff + var2;
    }
    switch (op)
    {
    case '>':
        result = (var1 > var2);
        break;
    case '<':
        result = (var1 < var2);
        break;
    case '=':
        result = (var1 == var2);
        break;

    default:
        break;
    }
    return result;
}

int loug(char x)
{
    int rst = 0, result;

    if (x == '~') // check the input of the first character.
    {
        rst = 1;
        scanf("%c", &x);
    }

    if (x != '(')
    {
        return 10;
    }

    int var1, var2;
    char op;
    int rst2 = 0, rst3 = 0;

    scanf("%c", &x);
    if (((x < 'a') || (x > 'z')) && ((x < 'A') || (x > 'Z')) && ((x > '9') || (x < '0')))
    // check if the input is true.
    {
        return 10;
    }

    if (x >= '0' && x <= '9')
    {
        while (x >= '0' && x <= '9')
        {
            rst2 = rst2 * 10 + (x - '0');
            scanf("%c", &x);
        }
        var1 = rst2;
    }
    else
    {
        var1 = x;
        scanf("%c", &x);
    }

    if (x != '<' && x != '>' && x != '=') // todo check is operator >=< return 10
    {
        return 10;
    }

    op = x;

    scanf("%c", &x);
    if (((x < 'a') || (x > 'z')) && ((x < 'A') || (x > 'Z')) && ((x > '9') || (x < '0')))
    // check if the input is true.
    {
        return 10;
    }

    if (x >= '0' && x <= '9')
    {
        while (x >= '0' && x <= '9')
        {
            rst3 = rst3 * 10 + (x - '0');
            scanf("%c", &x);
        }
        var2 = rst3;
    }
    else
    {
        var2 = x;
        scanf("%c", &x);
    } // TODO check behemet ze sograim
    result = operation(var1, op, var2);

    if (rst == 1)
    {
        result = !result;
    }
    return result;
}

int main()
{

    char op1, op2, x;
    int y = 0, rst2 = 0, rst3 = 0, rst4 = 0;
    printf("print stateme");
    scanf("%c", &x);
    rst2 = loug(x);
    //
    while (1)
    {
        scanf("%c", &x);
        op1 = x;
        if (x == ' ' || x == '\n')
        {
            break;
        }
        scanf("%c", &x);
        rst3 = loug(x);
        //

        switch (op1)
        {
        case '|':
            if (rst2 + rst3 > 0 && rst2 + rst3 <= 2)
            {
                rst4 = 1;
            }
            else if (rst2 + rst3 == 0)
            {
                rst4 = 0;
            }
            else
            {
                rst4 = 10;
            }
            break;
        case '&':
            if (rst2 + rst3 < 2 || rst2 + rst3 >= 0)
            {
                rst4 = 0;
            }
            else if (rst2 + rst3 == 2)
            {
                rst4 = 1;
            }
            else
            {
                rst4 = 10;
            }
            break;

        default:
            rst2 = 10; // 10 is wrong input
            break;
        }
        if (rst4 == 10)
        {
            rst2 = rst4;
            break;
        }
        rst2 = rst4;
    }

    if (rst2 == 1)
    {
        printf("The statement is true.\n");
    }
    else if (rst2 == 0)
    {
        printf("The statement is false.\n");
    }
    else
    {
        printf("You should stay positive, and so should your input.");
    }

    printf("\n");

    return 0;
}