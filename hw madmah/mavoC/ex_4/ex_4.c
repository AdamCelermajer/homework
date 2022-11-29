#include <stdio.h>

int inputCheck(int *array)
{
    int test;
    int size = 64;

    for (int i = 0; array[i] != -1; i++)
    {
        for (int j = 0; array[j] != -1; j++)
        {
            if (j != i)
                if (array[j] == array[i])
                {
                    return -1;
                }
        }
    }
    return 1;
}
int idxBounds(int index)
{
    return index > 64;
}

int indexToNum(int index)
{
    int z = index / 16;
    int y = (index % 16) / 4;
    int x = (index % 16) % 4;

    return 1000 + (z * 100) + (y * 10) + x;
}

int numToIndex(int x, int y, int z)
{

    int index = x + (y * 4) + (z * 16);

    if (index > 63 || x > 3 || y > 3 || z > 3)
        return -1;

    return index;
}
int isWinner(char *board, char who)
{
    int size = 64;
    int count = 1;
    int count2 = 1;
    int count3 = 1;
    int x = 0, y = 0, z = 0;
    int idx = 0;

    for (int i = 0; i < size; i++)
    {

        if (board[i] == who)
        {

            // todo fucking work
            idx = indexToNum(i);
            x = idx % 10;
            idx /= 10;
            y = idx % 10;
            idx /= 10;
            z = idx % 10;
            idx /= 10;

            // check x+j , y, z
            for (int j = 1; j < 4; j++)
            {
                if (x + j > 3)
                    break;
                if (board[numToIndex(x + j, y, z)] == who)
                    count++;

                if (y + j > 3)
                    break;

                if (board[numToIndex(x + j, y + j, z)] == who)
                    count2++;

                if (z + j > 3)
                    break;
                if (board[numToIndex(x + j, y + j, z + j)] == who)
                    count3++;

                if (count == 4 || count2 == 4 || count3 == 4)
                    return 1;
            }

            count = 1;
            count2 = 1;
            count3 = 1;
            // check x, y+m, z
            for (int m = 1; m < 4; m++)
            {
                if (y + m > 3)
                    break;
                if (board[numToIndex(x, y + m, z)] == who)
                    count++;

                if (z + m > 3)
                    break;
                if (board[numToIndex(x + m, y + m, z)] == who)
                    count2++;

                if (count == 4 || count2 == 4)
                    return 1;
            }

            count2 = 1;
            count = 1;

            // check x, y, z+n
            for (int n = 1; n < 4; n++)
            {
                if (z + n > 3)
                    break;
                if (board[numToIndex(x, y, z + n)] == who)
                    count++;

                if (count == 3)
                    return 1;
            }
        }
    }

    // do nothing who care about *

    return 0;
}

int getCh()
{
    int diff = '0';
    char var;
    char trash;
    char blankS;

    scanf("%c", &var);

    if (var == '\n')
        return -2;
    if (var == ' ')
        return -3;

    if (var >= '0' && var <= '3')
        return var - diff;

    return -1;
}

void printBoard(char *board)
{
    int x = 0;
    int y = 0;
    int z = 0;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                printf("(%d %d %d) ", i, j, k);
            }

            for (int m = 0; m < 4; m++)
            {

                x = m;
                y = j * 4;
                z = i * 16;

                printf("%c", board[x + y + z]);
            }

            printf("\n");
        }
        printf("\n");
    }
}

int init(int *input)
{

    int index = 0;
    int inCount = 0;
    int rst = 0;
    int in = 0;

    int x, y, z;

    while (in != -2)
    {
        x = 0;
        y = 0;
        z = 0;
        int rst = 0;

        for (int i = 0; i <= 5; i++)
        {

            in = getCh();

            if (in == -1)
            {
                return -1;
            }

            if (in == -2)
                if (i != 5)
                {
                    return -1;
                }
                else
                {
                    break;
                }
            if (i % 2 == 0)
            {
                switch (i)
                {
                case 0:
                    z = in;
                    break;
                case 2:
                    y = in;
                    break;
                case 4:
                    x = in;
                    break;
                }
            }
            else
            {
                if (!(in == -3))
                {
                    return -1;
                }
            }
        }
        rst = numToIndex(x, y, z);
        if (rst == -1)
            return -1;
        input[index] = rst;
        index++;
    }
    return 1;
}

void printArray(int *array)
{
    int size = 64;

    for (int i = 0; i < size; i++)
    {
        printf("%d element is %d\n", i, array[i]);
    }
}

int apply(char *board, int *input)
{
    int type = 0;
    int i = 0;
    int rst = 0;
    int win = 0;
    while (input[i] != -1)
    {
        if (type == 1)
        {

            board[input[i]] = 'O';
            win = isWinner(board, 'O');
            if (win)
            {
                return 2;
            }
            type = 0;
        }
        else
        {

            board[input[i]] = 'X';
            win = isWinner(board, 'X');

            if (win)
            {
                return 1;
            }
            type = 1;
        }
        i++;
    }
    return 0;
}

int brain(char *board, int *input)
{

    int tarr = init(input);
    if (tarr == -1)
    {
        return -1;
    }

    // todo check double in input array
    tarr = inputCheck(input);
    if (tarr == -1)
    {
        return -1;
    }

    int rst = apply(board, input);
    if (rst == -1)
    {
        return -1;
    }

    if (rst == 1)
    {
        printf("X is the Winner\n");
        printBoard(board);
    }
    if (rst == 0)
    {

        printf("its a tie\n");
    }
    if (rst == 2)
    {
        printf("O is the Winner\n");
        printBoard(board);
    }
}

void main()
{
    int rst;
    while (1)
    {

        int input[64] = {[0 ... 63] = -1};
        char board[64] = {[0 ... 63] = '*'};

        char choice;
        printf("would you like to start? (y/n)\n");
        scanf("%c", &choice);
        if (choice == 'n')
        {
            printf("YEET");
            break;
        }
        //  todo check choice
        scanf("%c", &choice);
        printf("Please enter your sequence.\n");

        rst = brain(board, input);

        if (rst == -1)
        {
            printf("Input incorrect.\n");
        }
    }
}