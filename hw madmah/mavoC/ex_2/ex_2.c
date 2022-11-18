/******************************************
 *Student name: adam celermajer
 *Student ID:332638592
 *Exercise name: ex1
 ******************************************/

#include <stdio.h>
#include <math.h>

int main()
{
    // exit variable that will be initialized at zero and later on switched to tell the program to stop
    int exit = 0;

    while (exit == 0)
    { // while exit==0  runn!

        // menu print
        printf("Choose an option:\n1. octal to hex\n2. binary addition\n3. print HI\n4. count bits\n5. decimal to binary\n6. Zig-Zag bits\n7. exit\n");

        // menu option choice input
        int choice;
        scanf("%d", &choice);

        switch (choice) // heart of the program will check the input and will do the suitable operation
        {
        case 1: // if 1 from octal to hex

            printf("Please enter number in octal base: ");

            int octalNum;
            scanf("%d", &octalNum);
            // get the number from user reversed

            // i dont want it to be reversed so we will reverse back the number
            int remain = 0;  // will be used to save the remain of modulo operation
            int reverse = 0; // will be used to save the real number after the reverse
            // reverse back the number
            int alert = 0;
            while (octalNum != 0)
            {

                remain = octalNum % 10;
                if (remain > 7) // checking for invalid input!
                {               // bad number its not octal
                    alert = 1;
                    break;
                }

                // left shift the reverse to allocate space for the remain
                reverse = reverse * 10 + remain;

                // decriment the number
                octalNum /= 10;
            }

            if (alert) // if my alert has been changed to 1 that means a wrong input has been received
            {

                printf("Invalid input!\n");
            }

            // transform it to decimal
            int decimalNum = 0;
            int resave;
            resave = reverse; // will be used to work with it
            int count = 0;    // will be used to count the place/index of the remain in the octal

            // take the number and trasnform it to decimal
            for (int i = 1; i < reverse; i = i * 10) // incriment the i by time 10
            {
                decimalNum += ((resave % 10) * (pow(8, count))); // num * 8^(his place in the decimal)
                resave /= 10;                                    // decriment the reversed number
                count++;                                         // increase by one according to index
            }

            int anum = '0';    // ascii number of '0'
            int ahex = 'A';    // ascii number of 'A'
            int tmp, hexd = 0; // temp will be used for a remain ,
            char hexRst;       // just used for the printing to convert from ascii number to a real letter

            for (int i = decimalNum; i > 0; i = i / 16) // for loop where i divise decimalNum each time by 16 until 0
            {

                tmp = i % 16; // get the remain of modulo to tmp

                if (tmp < 10)         // here im doing a check if its a letter or a number
                    tmp = tmp + anum; // its a leter so i get the ascii number of it by adding it to '0'
                else
                {
                    tmp = tmp - 10 + ahex; // equivalent in ascii is the diff between temp and 10 and add it and add it to ascii 'A'
                }
                hexd = hexd * 100 + tmp; // we make an indent of 00 as max ascii value dont depass 100 so we can add the new number safely
            }

            // so i curently have in hexd the whole number    each 2 letter corresponds to a ascii number

            for (int j = hexd; j > 0; j /= 100) // we do a for on the hexd
            {
                hexRst = j % 100;     // we take two digits by two digits because each two corresponds to a ascii number
                printf("%c", hexRst); // then we print the ascii value as a letter
            }

            printf("\n");
            break;
        case 2: // binary addition with two binary numbers

            printf("Please enter two binary numbers: ");
            unsigned long long bin1;
            unsigned long long bin2;

            scanf("%llu", &bin1);
            scanf("%llu", &bin2);

            unsigned long long max = bin1; // put max in bin1

            if (bin2 > max) // check if bin2 is greater than bin1 so max can be changed
            {
                max = bin2;
            }
            else // if bin2 is < than bin1 we will switch them so we can print them in the proper order
            {
                bin1 = bin2;
                bin2 = max;
                max = bin2;
            }
            unsigned long long temp = bin1; // will be used as a saving variable to work with

            // we are going to invert the binary numbers we just got to convert them more easily to decimal
            unsigned long long invBin1 = 1; // we initialize it at 1 so the zeroes that come at him will be saved
            unsigned long long invBin2 = 1;

            // quick check to see if they arent equals to zero as it mess up everything
            if (bin1 + bin2 == 0)
            {
                // they are equals to zero so we put them at 10 so it can follow the process
                invBin1 = 10;
                invBin2 = 10;
            }
            // checker  forinvalid input
            int fail = 0;

            /*
             we invert bin1 and put it in invBin1 and
             because invBin1 has been initialize at 1 at the leftest digit it will be a 1
             to protect the zero that might come
            */
            while (max)
            {
                max = max / 10;

                invBin1 = invBin1 * 10;
                if (temp % 10 > 1) // if bin1 has a digit bigger than 1 its not a binary number then its bad
                {

                    printf("Invalid input!\n");
                    fail++;
                    break;
                }
                invBin1 += temp % 10;
                temp = temp / 10;
            }
            if (fail) // quitting if it fails and we got a invalid input
            {
                break;
            }

            // redo max we lost it in the while
            max = bin1;
            if (bin2 > max)
            {
                max = bin2;
            }

            // redo temp we need it to work on the inversed bin2
            temp = bin2;

            /*
              we invert bin2 and put it in invBin2 and
              because invBin2 has been initialize at 1 at the leftest digit it will be a 1
              to protect the zero that might come
             */
            while (max)
            {
                max = max / 10;
                invBin2 = invBin2 * 10;
                if (temp % 10 > 1) // if bin2 has a digit bigger than 1 its not a binary number then its bad
                {
                    fail++;
                    printf("Invalid input!\n");
                    break;
                }
                invBin2 += temp % 10;
                temp = temp / 10;
            }
            if (fail) // quitting if it fails and we got a invalid input
                break;

            long dec1 = 0; // will be used now to get the decimal value of bin1
            long dec2 = 0; // will be used now to get the decimal value of bin2

            // print bin1 and getting decimal value of bin1
            while (invBin1 != 1) // we dont take the 1 that protect the zeroes , his job is finished
            {
                dec1 = dec1 << 1; /* shifting left (its like doing a multiplication by 2 )
                                    which is used to simulate the power of 2 .
                                    the first digit will be multiplyed by 2 the number of place he has been shifted
                                   */

                dec1 += invBin1 % 10;
                printf("%llu", invBin1 % 10); // printing digit digit inversed of invBin1 which is good because the output is bin1
                invBin1 = invBin1 / 10;
            }
            printf(" + ");

            // print bin2 and getting decimal value of bin2
            // same explication as invBin1
            while (invBin2 != 1)
            {

                dec2 = dec2 * 2;
                dec2 += invBin2 % 10;
                printf("%llu", invBin2 % 10);
                invBin2 = invBin2 / 10;
            }

            printf(" = ");

            // we add the decimal value then we will transform it back to binary
            max = dec1 + dec2;
            unsigned long long invbinRst = 1; // initialized to 1 to protect the zero again
            if (!max)                         // if max==0 its bad so we initialize it to "10" as it is a 1 protection and the value still 0
                invbinRst = 10;

            // transform decimal result to inverted binary representation
            while (max)
            {
                invbinRst = invbinRst * 10;
                invbinRst += max % 2;
                max = max / 2;
            }

            // invert binary result and print
            while (invbinRst != 1)
            {
                printf("%llu", invbinRst % 10);
                invbinRst = invbinRst / 10;
            }

            printf("\n");

            break;
        case 3:

            /*print a HI by getting a size

            we used a technique called a parser as we used the fixed format of the HI
            to print line by line

            digit 1 signify one instance of #
            digit 2 signify one instances of space " "
            digit 3 signify one instance of *
            digit 7 signify size time instances of space ""
            digit 9 signify size time instances of *
            digit 8 signify size time instances of #

            and the most right digit indicates if its a line that happening more than once 0=no 1=yes
            */
            printf("Please enter size: ");
            long long int line0 = 1812218171810; // its the format for line number 1 which is a lot of # and some space
            long long int line1 = 1912219171911; // its the format for line number 2 which happening more than once
            long long int line2 = 1912219181910;
            long long int line3 = 1912219393911;
            long long int line4 = 1912219181910;
            long long int line5 = 1912219171911;
            long long int line6 = 1812218171810;

            int size;
            scanf("%d", &size); // get size from user
            if (size < 1)       // check input
            {
                printf("Invalid input!\n");
                break;
            }

            while (line0) // until line0 is equals to zero , that will happen at the end of all the lines
            {
                int repeater = (size * (line0 % 10)); // if the line need to be repeated more than once

                if (!repeater) // if its zero we still want to run it once
                    repeater++;

                while (repeater--) // looping until no need to repeat
                {
                    long long int currentLine = line0 / 10; // we remove it now because first digit is only the repetition

                    while (currentLine) // runing the line until line is done
                    {
                        switch (currentLine % 10) // multiple option based on the format
                        {
                        case 1:
                            printf("#");
                            break;
                        case 2:
                            printf(" ");
                            break;
                        case 3:
                            printf("*");
                            break;
                        case 9:
                            for (int i = 0; i < size; i++)
                                printf("*");
                            break;
                        case 8:
                            for (int i = 0; i < size; i++)
                                printf("#");
                            break;
                        case 7:
                            for (int i = 0; i < size; i++)
                                printf(" ");
                            break;
                        default:
                            break;
                        }
                        currentLine /= 10; // decrement the current line
                    }
                    printf("\n"); // end of line we \n
                }
                // we finished one line so we push next line as line0
                line0 = line1;
                line1 = line2;
                line2 = line3;
                line3 = line4;
                line4 = line5;
                line5 = line6;
                line6 = 0; // and after all the line has been done , line0 will be zero and the while will quit
            }

            break;
        case 4:
            // how many 1 in a binary
            printf("please enter a binary number: ");
            int checker = -1; // an alert to check the input
            long long int binNum;
            scanf("%lld", &binNum);
            int counter = 0; // used to count the number of 1

            while (binNum != 0) // until the input is equals to zero
            {
                if (binNum % 10 == 1)
                    counter++;
                else if (binNum % 10 != 0) // if its not 1 and its not zero then its bad!
                {
                    printf("Invalid input!\n");
                    checker = 0;
                    break;
                }
                binNum /= 10; // decrement by /10
            }
            if (checker == -1)
            {
                printf("%d\n", counter);
            }

            break;
        case 5:

            // convert to binary
            printf("enter a non negative decimal number: ");

            int decNum, save;         // decNum is user input and save will be to save it for the printing
            long long int binRst = 0; // result where the binary representation will be
            int powcount = 0;         // we gonna use some power based on the index
            temp = 0;                 // as we already used temp above and was running out of name we just reuzed it
            int rem = 0;              // remain variable of the modulo
            scanf("%d", &decNum);
            save = decNum;

            if (decNum < 0) // quick check for non negative decimal
            {
                printf("Invalid input!\n");
                break;
            }

            // transform to binary representation
            while (decNum > 0)
            {
                rem = decNum % 2;
                temp = pow(10, powcount);       // we gonna shift the rem by using an exponent of 10 (like a left shift >>)
                binRst = binRst + (temp * rem); // shifting the remain so it can  enter on the most left place
                powcount++;                     // incrementing by 1 my exponent index
                decNum /= 2;
            }
            printf("%d => %lld\n", save, binRst);

            break;
        case 6:

            // zigzag
            printf("enter a non negative decimal number: ");
            rem = 0; // reusing the remain variable from option 5
            int mynum;
            int rst = -1;     // will be used as an alert to know if zigzag or not
            int lastone = -1; // will be used to check last digit
            scanf("%d", &mynum);

            if (mynum < 0) // quick check for non negative decimal
            {
                printf("Invalid input!\n");
                break;
            }

            // transform to binary representation
            while (mynum > 0)
            {
                rem = mynum % 2;
                if (lastone == -1) // first initialization of lastone we dont check
                {
                    lastone = rem;
                }
                else
                {
                    if (lastone == rem) // after first initialization we do check each 2 digit
                    {
                        printf("false\n");
                        rst = 0;
                        break;
                    }
                    else
                    {
                        lastone = rem;
                    }
                }

                mynum /= 2;
            }

            if (rst)
                printf("true\n");

            break;

        case 7:
            printf("Bye!\n");
            exit = 1;
            break;
        default:
            printf("invalid option: \n");
            continue;
            break;
        }
    }
}