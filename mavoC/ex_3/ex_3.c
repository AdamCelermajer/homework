/******************************************
 *Student name: adam celermajer
 *Student ID:332638592
 *Exercise name: ex1
 ******************************************/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define ZERO 0
#define TENBASE 10
#define FALSE -1
#define TRUE 1

/************************************************************************
 * function name: printMenu *
 * The Input: none *
 * The output: none *
 * The Function operation: print the menu *
 *************************************************************************/
void printMenu()
{
    printf("Choose an option:\n");
    printf("\t1: Logical Statement Calculator\n");
    printf("\t2: Count digit in a number\n");
    printf("\t3: GCD Calculator\n");
    printf("\t4: Exit\n");
}

/************************************************************************
 * function name: printExit *
 * The Input: none *
 * The output: none *
 * The Function operation: print the exit message *
 *************************************************************************/
void printExit()
{
    printf("So Long, and Thanks for All the Fish!\n");
}

/************************************************************************
 * function name: printError *
 * The Input: none *
 * The output: none *
 * The Function operation: print the error message *
 *************************************************************************/
void printError()
{
    printf("Fool of a Took!\n");
    printf("This is a serious journey, not a hobbit walking-party.\n");
    printf("Throw yourself in next time, and then you will be no further nuisance.\n");
}

void cleanBuffer()
{

    char buffer;
    scanf("%c", &buffer);
    while (buffer != ' ')
    {
        scanf("%c", &buffer);
    }
}

/************************************************************************
 * function name: final *
 * The Input: 3 integer variable  *
 * The output: integer value *
 * The Function operation: get 2 number or ascii value and an operator
 *                        return the value of the operation between the two value*
 *************************************************************************/
int final(int op1, int cmd, int op2)
{

    int diff = 'a' - 'A';
    if (op1 >= 'A' && op1 <= 'Z')
    {

        op1 = op1 + diff;
    }

    if (op2 >= 'A' && op2 <= 'Z')
    {

        op2 = op2 + diff;
    }

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
        return FALSE;
    }
}

/************************************************************************
 * function name: operator *
 * The Input: none *
 * The output: integer *
 * The Function operation: take the input from buffer until the end of
 * statement and return the result of statement*
 *************************************************************************/
int operator()
{
    char ch, op = ZERO;
    int val1 = ZERO, val2 = ZERO;
    scanf("%c", &ch);

    if (!((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')))
    {

        return FALSE;
    }

    if (ch == ')')
    {
        return FALSE;
    }
    if (ch >= '0' && ch <= '9')
    {

        while ((ch >= '0' && ch <= '9'))
        {
            val1 = val1 * TENBASE + (int)(ch - '0');
            scanf("%c", &ch);
        }
    }
    else
    {
        val1 = ch;
        scanf("%c", &ch);
    }

    // todo operator
    op = ch;
    scanf("%c", &ch);

    if (!((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')))
    {

        return FALSE;
    }

    if (ch >= '0' && ch <= '9')
    {

        while ((ch >= '0' && ch <= '9'))
        {
            val2 = val2 * TENBASE + (int)(ch - '0');

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

/************************************************************************
 * function name: isOp *
 * The Input: a char *
 * The output: integer *
 * The Function operation: get a char and return 1 if the char is an operator
 * else it return 0*
 *************************************************************************/
int isOp(char ch)
{

    if (ch == '<' || ch == '>' || ch == '=' || ch == '|' || ch == '&')
        return TRUE;
    return ZERO;
}

/************************************************************************
 * function name: brain *
 * The Input: none *
 * The output:  an integer *
 * The Function operation: do the calculation on all the input from user
 * and return the value of it 1 for true 0 for false *
 *************************************************************************/
int brain()
{
    int firstop = '|';
    int op = FALSE;
    int rst = ZERO;
    int input = 'd';
    while (TRUE)
    {
        int not = ZERO;
        int val = ZERO;

        scanf(" %c", &input);

        // todo check input
        if (input == ' ')
        {

            return rst;
        }

        if (input == '~')
        {
            not = TRUE;
            scanf("%c", &input);
        }

        if (input == '(')
        {

            val = operator();

            if (val == FALSE)
            {
                cleanBuffer();
                return FALSE;
            }
            if (not )
            {
                val = !val;
            }
            scanf("%c", &input);

            if (isOp(input))
            {

                if (op == FALSE)
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
                if (op != FALSE)
                {
                    rst = final(rst, op, val);
                    return rst;
                }
                return val;
            }
        }
        else
        {
            return FALSE;
        }
    }
}

/************************************************************************
 * function name: checkit *
 * The Input: 2 integer *
 * The output: an integer *
 * The Function operation: recursively check the number of time variable
 *  dig is in num
 *************************************************************************/
int checkit(int num, int dig)
{

    if (num == ZERO)
        return ZERO;
    if (dig == num % TENBASE)
        return checkit(num / TENBASE, dig) + 1;
    return checkit(num / TENBASE, dig);
}

/************************************************************************
 * function name: printTwo *
 * The Input: none *
 * The output: an integer *
 * The Function operation: get the input from user and check the input
 * then call for checkit and return 1
 *************************************************************************/
int printTwo()
{
    long long int num = ZERO;
    int digit = ZERO;
    int testNum = ZERO;
    int testDig = ZERO;
    printf("Enter a number and a digit: ");

    if (!scanf("%lld", &num) || !scanf("%d", &digit) || num < ZERO || digit < ZERO || digit > 9)
    {
        return ZERO;
    }

    int rst;
    if (num == ZERO && digit == ZERO)
    {
        rst = 1;
    }
    else
    {
        rst = checkit(num, digit);
    }

    printf("The digit %d appears %d times in the number %d\n", digit, rst, num);
    return TRUE;
}

/************************************************************************
 * function name: modulo *
 * The Input: 2 integer *
 * The output: none *
 * The Function operation: get input from user and print the modulo result
 * and the the result of division
 *************************************************************************/
void modulo(int a, int b)
{

    int remain = a % b;
    int div = a / b;

    printf("%d*%d+%d = %d (num1=%d, num2=%d)\n", b, div, remain, a, a, b);
}

/************************************************************************
 * function name: recgcd *
 * The Input: 2 integer *
 * The output: an integer *
 * The Function operation: get two number and recursively check whats their
 * GCD then return it
 *************************************************************************/
int recgcd(int a, int b)
{
    if (b != ZERO)
    {
        modulo(a, b);
        return recgcd(b, a % b);
    }
    else
        return a;
}

void main()
{
    int exit = TRUE;

    while (exit)
    {
        printMenu();

        int choice;
        int reader = scanf("%d", &choice);
        switch (choice)
        {
        case 1:

            printf("\nPlease write your logical statement: ");
            int print = brain();

            if (print == TRUE)
            {
                printf("The statement is true.\n");
            }
            else if (print == ZERO)
            {
                printf("The statement is false.\n");
            }
            else

                printf("You have a syntax error in your statement.\n");
            break;

        case 2:

            printf("\n");
            int ret = printTwo();
            if (ret == ZERO)
            {

                printf("You should stay positive, and so should your input.\n");
            }
            break;

        case 3:
            printf("\nEnter two positive numbers: ");
            int num1, num2;

            if (!scanf("%d", &num1) || !scanf("%d", &num2) || num1 < ZERO || num2 < ZERO)
            {

                printf("You should stay positive, and so should your input.\n");
                break;
            }

            if (num1 > num2)
            {
                printf("GCD = %d\n", recgcd(num1, num2));
            }
            else
            {
                printf("GCD = %d\n", recgcd(num2, num1));
            }
            break;

        case 4:
            exit = ZERO;
            printExit();
            break;

        default:
            if (!reader)
                scanf("%c", &choice);
            printError();
            break;
        }
    }
}