#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct Contact
{
    char *firstName;
    char *lastName;
    char *phoneNum;
    struct Contact *next;
} Contact;

void main()
{

    Contact *phonebook[26] = {[0 ... 25] = NULL};

    for (int i = 0; i < 26; i++)
    {

        printf("is it innit %s\n", (phonebook[i]));
    }

    phonebook[0] = malloc(sizeof(Contact));
    phonebook[0]->firstName = "adam";
    printf("p------------------%s\n", phonebook[0]->firstName);
    phonebook[0]->next = malloc(sizeof(Contact));
    (phonebook[0]->next)->firstName = "noam";
    printf("p------------------%s\n", (phonebook[0]->next)->firstName);
}