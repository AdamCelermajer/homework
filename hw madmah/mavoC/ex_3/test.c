#include <stdio.h>

char error = 0;

int final(int op1, int cmd, int op2)
{

    switch (cmd)
    {
    case '>':
        return op1 > op2;
        break;

    case '=':
        return (op1 == op2);
        break;

    case '<':

        return op1 < op2;
        break;

    case '&':

        return op1 && op2;
        break;

    case '|':

        return op1 || op2;
        break;

    default:
        return -1;
    }
}

int operator()
{
    char ch, op = 0;
    int val1 = 0, val2 = 0;
    scanf("%c", &ch);

    // todo check input (not operator only ascii characters)

    if (ch >= '0' && ch <= '9')
    {

        while ((ch >= '0' && ch <= '9'))
        {
            val1 = val1 * 10 + (int)(ch - '0');
            scanf("%c", &ch);
        }
    }
    else
    {
        val1 = ch;
        scanf("%c", &ch);
    }

    // todo check input (Its an operator only)
    op = ch;
    scanf("%c", &ch);
    // todo check input (not operator only ascii characters)

    if (ch > '0' && ch <= '9')
    {

        while ((ch >= '0' && ch <= '9'))
        {
            val2 = val2 * 10 + (ch - '0');

            scanf("%c", &ch);
        }
    }
    else
    {

        val2 = ch;
        scanf("%c", &ch);
    }

    // todo check input its an )
    return final(val1, op, val2);
}
int isOp(char ch)
{

    if (ch == '<' || ch == '>' || ch == '=' || ch == '|' || ch == '&')
        return 1;
    return 0;
}

int brain()
{
    int firstop = '|';
    int op = -1;
    int rst = 0;

    printf("Enter a logical statement:    ");
    while (1)
    {
        int not = 0;
        int val = 0;

        int input;
        scanf("%c", &input);

        // todo check input
        if (input == '\n')
        {
            // check for operator and add it

            return rst;
        }

        if (input == '~')
        {
            not = 1;
            scanf("%c", &input);
            // TODO CHECK for input '('
        }

        if (input == '(')
        {

            val = operator();

            if (val == -1)
            {
                return -1;
            }
            if (not )
            {
                val = !val;
            }
            // todo rst op val

            scanf("%c", &input);

            if (isOp(input))
            {

                if (op == -1)
                {
                    op = input;
                    rst = val;
                }
                else
                {
                    rst = final(rst, op, val);
                    op = input;
                }
            }
            else
            {
                if (op != -1)
                {
                    rst = final(rst, op, val);
                }
                else
                {

                    return val;
                }
            }
        }
    }
}

int main()

{
    printf("result = %d\n", brain());
}