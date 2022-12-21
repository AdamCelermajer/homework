#include <stdio.h>

#define SIZE 64
#define SIDE_SIZE 4
#define END_OF_ARRAY -1
#define INITIALISATOR 1
#define ERROR -1
#define SEPARATIST 16
#define BASE_10_SEPARATOR 10
#define MAX_LENGH_SIDE_SIZE 3
#define MAX_LENGH_SIZE 63
#define TRUE 1
#define FALSE 0
#define NEW_LINE_CODE -2
#define SPACE_CODE -3
#define X_WON 1
#define X_TURN 0
#define O_TURN 1
#define O_WON 2
#define TIE 0
#define INPUT_LENGTH 5
#define ODD_CHECKER 2
#define THREE_RECIPIENT 1000

/************************************************************************
 * function name: inputCheck *
 * The Input: a pointer to integer array  *
 * The output: true or false *
 * The Function operation: parcour the array and check if a input has been
 *                         entered two times
 *
 *************************************************************************/
int inputCheck(int array[])
{

    int size = SIZE;

    // for each input check if its been entered two times
    for (int i = 0; array[i] != END_OF_ARRAY; i++)
    {
        for (int j = 0; array[j] != END_OF_ARRAY; j++)
        {
            if (j != i)
                if (array[j] == array[i])
                {
                    // found a anomaly return error code
                    return ERROR;
                }
        }
    }
    // life beens good return TRUE
    return TRUE;
}
/************************************************************************
 * function name: idxBounds *
 * The Input: a integer that represent a index  *
 * The output: true or false *
 * The Function operation: little function that return if the index is
 *                         bigger than the size of the array
 *
 *************************************************************************/
int idxBounds(int index)
{
    return index > SIZE;
}

/************************************************************************
 * function name: indexToNum *
 * The Input: a  integer that represent a index input  *
 * The output: a integer that represent my coordinate*
 * The Function operation: spliting the index in x y z coordinate and
 *                          return the result as a integer combination
 *
 *************************************************************************/
int indexToNum(int index)
{
    // split the index in x y z coordinate
    int z = index / SEPARATIST;
    int y = (index % SEPARATIST) / SIDE_SIZE;
    int x = (index % SEPARATIST) % SIDE_SIZE;

    // return a integer based on it
    return THREE_RECIPIENT + (z * BASE_10_SEPARATOR * BASE_10_SEPARATOR) + (y * BASE_10_SEPARATOR) + x;
}

/************************************************************************
 * function name: numToIndex *
 * The Input: three integer that represent x,y,z  or an error code*
 * The output: a integer that represent the index in the array*
 * The Function operation:combine x,y,z in a array index and return it
 *
 *************************************************************************/
int numToIndex(int x, int y, int z)
{

    // reverse calculation on the coordinate to an index
    int index = x + (y * SIDE_SIZE) + (z * SEPARATIST);
    // doing some check to see if its good
    if (index > MAX_LENGH_SIZE || x > MAX_LENGH_SIDE_SIZE || y > MAX_LENGH_SIDE_SIZE || z > MAX_LENGH_SIDE_SIZE)
        return ERROR;

    return index;
}

/************************************************************************
 * function name: isWinner *
 * The Input: a pointer to a char array and a char ta represent X or O *
 * The output: a integer that represent if win or not*
 * The Function operation:parcout the board and doing check to check win
 *
 *************************************************************************/
int isWinner(char board[], char who)
{

    int size = SIZE;
    int count = INITIALISATOR;
    int count2 = INITIALISATOR;
    int count3 = INITIALISATOR;
    int x = 0, y = 0, z = 0;
    int idx = 0;

    // parcouring all the board
    for (int i = 0; i < size; i++)
    {

        // if we found a match we proceed to some checking

        if (board[i] == who)
        {
            // we reverse calculation our recipient to get coordinate

            idx = indexToNum(i);

            x = idx % BASE_10_SEPARATOR;
            idx /= BASE_10_SEPARATOR;
            y = idx % BASE_10_SEPARATOR;
            idx /= BASE_10_SEPARATOR;
            z = idx % BASE_10_SEPARATOR;
            idx /= BASE_10_SEPARATOR;

            count = INITIALISATOR;
            count2 = INITIALISATOR;
            count3 = INITIALISATOR;

            // check 2D horizontal/diagonal line  and 3D big diagonal
            for (int j = INITIALISATOR; j < SIDE_SIZE; j++)
            {

                // 2d check only horizontal line
                if (x + j > MAX_LENGH_SIDE_SIZE)
                {
                    break;
                }

                if (board[numToIndex(x + j, y, z)] == who)
                {

                    count++;
                }
                else
                {
                    count = INITIALISATOR;
                }

                if (y + j <= MAX_LENGH_SIDE_SIZE)
                {
                    // diagonal check in 2d
                    if (board[numToIndex(x + j, y + j, z)] == who)
                    {
                        count2++;
                    }
                    else
                    {
                        count2 = INITIALISATOR;
                    }
                }

                // big diagonal in space
                if (z + j <= MAX_LENGH_SIDE_SIZE)
                {

                    if (board[numToIndex(x + j, y + j, z + j)] == who)
                    {

                        count3++;
                    }
                    else
                    {
                        count3 = INITIALISATOR;
                    }
                }

                if (count == SIDE_SIZE || count2 == SIDE_SIZE || count3 == SIDE_SIZE)
                {

                    return TRUE;
                }
            }

            // we reinitialize our counter as it is a new check
            count = INITIALISATOR;
            count2 = INITIALISATOR;
            count3 = INITIALISATOR;

            for (int m = INITIALISATOR; m < SIDE_SIZE; m++)
            {
                // 2d check only vertical
                if (y + m > MAX_LENGH_SIDE_SIZE)
                    break;

                if (board[numToIndex(x, y + m, z)] == who)
                {
                    count++;
                }
                else
                {
                    count = INITIALISATOR;
                }
                if (count == SIDE_SIZE)
                {

                    return TRUE;
                }
            }

            // reinitialize for new check
            count2 = INITIALISATOR;
            count = INITIALISATOR;

            // check x, y, z+n
            for (int n = INITIALISATOR; n < SIDE_SIZE; n++)
            {
                if (z + n > MAX_LENGH_SIDE_SIZE)
                    break;
                // 3d horizontal line check
                if (board[numToIndex(x, y, z + n)] == who)

                    count++;
                else
                {
                    count = INITIALISATOR;
                }

                if (count == SIDE_SIZE)
                {

                    return TRUE;
                }
            }
            count = INITIALISATOR;

            // check reverse diagonal in 2D
            for (int n = INITIALISATOR; n < SIDE_SIZE; n++)
            {
                if (x != 0 || y != MAX_LENGH_SIDE_SIZE)
                    break;
                // 2d reverse diagonal line check
                if (board[numToIndex(x + n, y - n, z)] == who)
                    count++;

                if (count == SIDE_SIZE)
                {

                    return TRUE;
                }
            }
            count = INITIALISATOR;
            // check reverse diagonal in 3D
            for (int n = INITIALISATOR; n < SIDE_SIZE; n++)
            {
                if (x != 0 || z != MAX_LENGH_SIDE_SIZE || y != MAX_LENGH_SIDE_SIZE)
                    break;
                // 3d reverse diagonal line check
                if (board[numToIndex(x + n, y - n, z - n)] == who)
                    count++;

                if (count == SIDE_SIZE)
                {

                    return TRUE;
                }
            }
        }
        else
        {
            // do nothing who care about *
        }
    }

    return FALSE;
}

/************************************************************************
 * function name: getCh *
 * The Input: none *
 * The output: a number that represent a code*
 * The Function is doing a scanf() and return a specific based on input value
 *
 *************************************************************************/
int getCh()
{
    // we get the difference to convert ascii to integer
    int diff = '0';
    char var;

    scanf("%c", &var);

    if (var == '\n')
        return NEW_LINE_CODE;
    if (var == ' ')
        return SPACE_CODE;

    // we found an number so we convert to integer
    if (var >= '0' && var <= '3')
        return var - diff;

    // we found weird input thats bad
    return ERROR;
}

/************************************************************************
 * function name: printBoard *
 * The Input: pointer to char array *
 * The output: none*
 * The Function the function is printing the board based on the format
 *
 *************************************************************************/
void printBoard(char board[])
{
    int x = 0;
    int y = 0;
    int z = 0;

    for (int i = 0; i < SIDE_SIZE; i++)
    {
        for (int j = 0; j < SIDE_SIZE; j++)
        {
            // special for , used to print the coordinate
            for (int k = 0; k < SIDE_SIZE; k++)
            {
                // we print first the index of the board
                printf("(%d %d %d) ", i, j, k);
            }

            // special for , used to print value coordinate
            for (int m = 0; m < SIDE_SIZE; m++)
            {

                x = m;
                y = j * SIDE_SIZE;
                z = i * SEPARATIST;

                printf("%c ", board[x + y + z]);
            }
            // printf a newline feed after each row
            printf("\n");
        }
        // printf a newline feed after each dimensional 2d board
        printf("\n");
    }
}

/************************************************************************
 * function name: init *
 * The Input: pointer to int array *
 * The output: TRUE OR ERROR*
 * The Function: init the input array and take the input from the user
 *
 *************************************************************************/
int init(int input[])
{

    int index = 0;
    int inCount = 0;
    int rst = 0;
    int in = 0;

    int x, y, z;

    // until we dont see a newline we continue
    while (in != NEW_LINE_CODE)
    {
        x = 0;
        y = 0;
        z = 0;
        rst = 0;

        // we parcour a little for in the input that represent one input from one user
        for (int i = 0; i <= INPUT_LENGTH; i++)
        {
            // call of the getCH function that get the number or a code
            in = getCh();

            if (in == ERROR)
            {
                return ERROR;
            }

            if (in == NEW_LINE_CODE)
                if (i != INPUT_LENGTH)
                {
                    return -1;
                }
                else
                {
                    break;
                }
            // we got a number so now we need to now how to save it
            if (i % ODD_CHECKER == 0)
            {
                // its an odd number thats mean its a number and not a space
                // so based on i index we know if its x,y,z
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
                if (!(in == SPACE_CODE))
                {
                    return ERROR;
                }
            }
        }
        // we create an index based on x,y,z
        rst = numToIndex(x, y, z);

        if (rst == ERROR)
            return ERROR;

        input[index] = rst;
        index++;
    }
    return TRUE;
}

/************************************************************************
 * function name: apply *
 * The Input: pointer to int array and pointer to char array *
 * The output: INTEGER that represent a winning code or a error*
 * The Function: manage multiple function and return a winner based on input
 *
 *************************************************************************/
int apply(char board[], int input[])
{
    int type = 0;
    int i = 0;
    int rst = 0;
    int win = 0;

    /* input is initialized with -1 that means that until you dont see
      a -1 that means its actual input and continue to work
    */
    while (input[i] != END_OF_ARRAY)
    {

        // based on which one turn we work on the input
        if (type == O_TURN)
        {

            board[input[i]] = 'O';
            // we check if based on this input maybe O won
            win = isWinner(board, 'O');
            if (win)
            {
                return O_WON;
            }
            // O turn is finished next turn is X_TURN
            type = X_TURN;
        }
        else
        {

            board[input[i]] = 'X';

            win = isWinner(board, 'X');

            if (win)
            {
                return X_WON;
            }
            type = O_TURN;
        }
        i++;
    }
    // we didnt see any winner even after all the moves , we declare a tie
    return TIE;
}

/************************************************************************
 * function name: brain *
 * The Input: pointer to int array and pointer to char array *
 * The output: INTEGER that represent a winning code or a error*
 * The Function: manage multiple function and return a winner based on input
 *
 *************************************************************************/
int brain(char board[], int input[])
{
    // we call init function to initialize input array
    int tarr = init(input);
    if (tarr == ERROR)
    {
        return ERROR;
    }

    // input check the array for multiple same moves
    tarr = inputCheck(input);
    if (tarr == ERROR)
    {
        return ERROR;
    }

    // apply the moves on the board and get winner or tie
    int rst = apply(board, input);
    if (rst == ERROR)
    {
        return ERROR;
    }

    // we got X winner
    if (rst == X_WON)
    {
        printf("X is the winner.\n");
        printBoard(board);
    }
    // we got tie code
    if (rst == TIE)
    {

        printf("its a tie\n");
    }
    // we got O winner
    if (rst == O_WON)
    {
        printf("O is the winner.\n");
        printBoard(board);
    }
}

/************************************************************************
 * function name: cleanBuffer *
 * The Input: none *
 * The output: none*
 * The Function: scanf() the shit of the buffer until its see a linefeed
 *
 *************************************************************************/
void cleanBuffer()
{

    char trash = 'a';
    while (trash != '\n')
    {
        // until you find a new line continue to take input
        scanf("%c", &trash);
    }
}

/************************************************************************
 * function name: main *
 * The Input: none *
 * The output: none*
 * The Function:executable function called that manage the program
 *************************************************************************/
void main()
{
    char choice;
    int rst;
    int fail = 0;
    while (TRUE)
    {
        // init the boards at -1 and at *
        int input[SIZE] = {[0 ... MAX_LENGH_SIZE] = END_OF_ARRAY};
        char board[SIZE] = {[0 ... MAX_LENGH_SIZE] = '*'};

        // if its not the first time we print the second message
        if (!fail)
            printf("Would you like to start? (y/n)\n");
        else
            printf("Would you like to continue? (y/n)\n");

        // take choice from user
        scanf("%c", &choice);
        if (choice == 'n')
        {
            printf("YEET");
            break;
        }
        if (choice != 'y')
        {
            printf("YEET");
            break;
        }

        printf("Please enter your game sequence.\n");
        scanf("%c", &choice);

        // lets go we call brain to do all the work and get an error
        // if it happens
        rst = brain(board, input);
        fail = 1;
        if (rst == ERROR)
        {
            printf("Input incorrect.\n");

            // we cleanBuffer after an incorrect answer to not mess next time
            cleanBuffer();
        }
    }
}