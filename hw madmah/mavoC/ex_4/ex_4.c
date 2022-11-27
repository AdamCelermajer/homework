#include <stdio.h>

void apply(char *board, char *input)
{
    int type = 0;
    int i = 0;
    int rst = 0;

    while (input[i] != '*')
    {

        if (type == 1)
        {
            board[input[i]] = 'O';
            type = 0;
        }
        else
        {
            board[input[i]] = 'X';
            type = 1;
        }
    }
}
void printBoard(char *board)
{

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

                int x = m;
                int y = j * 4;
                int z = i * 16;

                printf("%c", board[x + y + z]);
            }

            printf("\n");
        }
        printf("\n");
    }
}
int init(char *input)
{

    int index = 0;
    int rst = 0;
    char in = 0;
    while (in != 10)
    {

        for (int i = 0; i <= 4; i++)
        {
            scanf("%c", &in);
            if (in % 2 == 0)
            {
                // todo check number
                switch (i)
                {
                case 0:
                    rst += in;
                    break;
                case 2:
                    rst += in * 4;
                    break;
                case 4:
                    rst += in * 16;
                    break;
                }
            }
            else
            {
                // todoc check blackspace
            }
        }
        scanf("%c", &in); // todo check blankspace
        input[index] = rst;
        index++;
    }
    return 1;
}
void printArray(char *array)
{
    int size = sizeof(array) / sizeof(array[0]);

    for (int i = 0; i < size; i++)
    {
        printf("%d element is %c\n", i, array[i]);
    }
}
char *brain()
{
    char *a = {'1'};
    return a;
}
void main()
{
    char input[64] = {[0 ... 63] = '*'};
    char board[64] = {[0 ... 63] = '*'};

    char *parr = init(input);
    brain(parr);
    apply(board, parr);
    printBoard(board);

    // analyse();
}