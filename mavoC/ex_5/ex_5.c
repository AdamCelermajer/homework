#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define DIFFERENCE_TO_LOWER 32
#define DIFFERENCE_TO_INDEX 65
#define MALLOC_ERROR -5
#define PHONE_CODE -2
#define NAME_CODE -1
#define TRUE 1
#define FALSE 0

typedef struct Contact
{
    char *firstName;
    char *lastName;
    char *phoneNum;
    struct Contact *next;
} Contact;


void cleanBuffer()
{

    char trash = 'a';
    while ((trash != '\n') && (trash != 10))
    {

        scanf("%c", &trash);
    }
}

int checkNumber(Contact *phonebook[26], char *number)
{

    Contact *current = NULL;
    for (int i = 0; i < 26; i++)
    {
        current = phonebook[i];
        // printf("current is %d\n", current);

        while (current != NULL)
        {
            // printf("here i am %s vs %s\n", current->phoneNum, number);
            if (strcmp(current->phoneNum, number) == 0)
            {
                return 0;
            }
            current = current->next;
        }
    }

    return 1;
}

Contact *searchNumber(Contact *phonebook[26], char *number)
{

    Contact *current = NULL;
    for (int i = 0; i < 26; i++)
    {
        current = phonebook[i];
        // printf("current is %d\n", current);

        while (current != NULL)
        {
            // printf("here i am %s vs %s\n", current->phoneNum, number);
            if (strcmp(current->phoneNum, number) == 0)
            {
                return current;
            }
            current = current->next;
        }
    }

    return NULL;
}

int getIndex(char first)
{

    if (first >= 'a' && first <= 'z')
    {
        first = first - DIFFERENCE_TO_LOWER;
    }
    return first - DIFFERENCE_TO_INDEX;
}

void printMenu()
{
    printf("Welcome to the phone book manager! Choose an option:\n");

    printf("1.Add a new contact to the phone book.\n");
    printf("2.Delete a contact from the phone book.\n");
    printf("3.Find a contact in the phone book by phone number.\n");
    printf("4.Find a contact in the phone book by name.\n");
    printf("5.Update phone number for a contact.\n");
    printf("6.Print phone book.\n");
    printf("7.Exit.\n");
}

int parcourAndAdd(Contact *phonebook[26], char *firstName, char *lastName, char *number, int index)
{
    // printf("im here---------------\n");

    Contact *current = phonebook[index];

    if (checkNumber(phonebook, number) == 0)
    {
        // printf("return %d", PHONE_CODE);
        return PHONE_CODE;
    }

    if (current != NULL)
    {
        while (TRUE)
        {
            // printf("in while the check is %s to %s  and %s to %s and phone %s to %s \n", current->firstName, firstName, current->lastName, lastName, current->phoneNum, number);
            if (strcmp(current->firstName, firstName) == 0 && strcmp(current->lastName, lastName) == 0)
            {
                // printf("return %d\n", NAME_CODE);
                return NAME_CODE;
            }
            if (current->next == NULL)
                break;
            current = current->next;
        }
    }

    if (phonebook[index] == NULL)
    {

        phonebook[index] = malloc(sizeof(Contact));
        if (phonebook[index] == NULL)
        {
            return MALLOC_ERROR;
        }

        current = phonebook[index];
    }
    else
    {

        current->next = malloc(sizeof(Contact));
        if (current == NULL)
        {
            return MALLOC_ERROR;
        }
        current = current->next;
    }

    current->firstName = malloc(10);
    current->lastName = malloc(10);
    current->phoneNum = malloc(10);

    strcpy(current->firstName, firstName);
    strcpy(current->lastName, lastName);
    strcpy(current->phoneNum, number);
    current->next = NULL;

    // printf("its been done first name: %s , last name %s  phone num %s \n", current->firstName, current->lastName, current->phoneNum);

    return TRUE;
}

void addContact(Contact *phonebook[26])
{
    printf("Enter a contact details (<first name> <last name> <phone number>):\n");
    int index = 0;
    int code = 0;

    char buffer[100];
    cleanBuffer();
    fgets(buffer, 100, stdin);
    char *firstName = strtok(buffer, " ");
    char *lastName = strtok(NULL, " ");
    char *phoneNum = strtok(NULL, " ");

    // todo check input format

    index = getIndex(firstName[0]);

    // todo check index

    code = parcourAndAdd(phonebook, firstName, lastName, phoneNum, index);
    // printf("test de ouff index is %d \n ", index);
    switch (code)
    {
    case MALLOC_ERROR:
        printf("Out of memory\n");
        break;
    case PHONE_CODE:
        printf("The addition of the contact has failed, since the phone number %s already exists!\n", phoneNum);
        break;
    case NAME_CODE:
        printf("The addition of the contact has failed, since the contact %s %s already exists!\n", firstName, lastName);
        break;
    case TRUE:
        printf("The contact has been added successfully!\n");
    default:
        break;
    }

    printf("im done\n");
}

void printBook(Contact *phonebook[26])
{
    Contact *current = NULL;
    for (int i = 0; i < 26; i++)
    {
        current = phonebook[i];
        // printf("current is %d\n", current);

        while (current != NULL)
        {
            printf(" %s    %s   %s\n", current->firstName, current->lastName, current->phoneNum);
            current = current->next;
        }
    }
}

Contact *freeContact(Contact *contact)
{
    free(contact->firstName);
    free(contact->lastName);
    free(contact->phoneNum);
    if (contact->next == NULL)
    {
        return NULL;
    }
    else
    {

        return contact->next;
    }
}

int deleteContact(Contact *phonebook[26], char *firstName, char *lastName)
{
    int index = getIndex(firstName[0]);
    Contact *contact = phonebook[index];
    Contact *prev = contact;
    if (contact == NULL)
        return 0;

    if (contact->next == NULL && strcmp(contact->firstName, firstName) == 0 && strcmp(contact->lastName, lastName) == 0)
    {
        freeContact(contact);
        free(contact);
        phonebook[index] = NULL;
        return 1;
    }
    if (contact->next == NULL)
    {
        return 0;
    }

    while (contact != NULL)
    {

        // printf("im here firstname compare is %d, firstName is -%s- and arr is -%s- \n", strcmp(contact->firstName, firstName), firstName, contact->firstName);

        if (strcmp(contact->firstName, firstName) == 0 && strcmp(contact->lastName, lastName) == 0)
        {
            if (prev == contact)
            {
                phonebook[index] = freeContact(contact);
            }
            else
            {
                prev->next = freeContact(contact);
            }
            free(contact);
            return 1;
        }

        if (prev != contact)
        {
            prev = contact;
            contact = contact->next;
        }
        else
        {
            contact = contact->next;
        }
    }

    return 0;
}

Contact *searchFunct(Contact *phonebook[26], char *input, char *lastName, int code)
{
    if (code = 1)
    {
        return searchNumber(phonebook, input);
    }

    int index = getIndex(input[0]);
    Contact *current = phonebook[index];

    while (TRUE)
    {

        if (strcmp(current->firstName, input) == 0 && strcmp(current->lastName, lastName) == 0)
        {

            return current;
        }
        if (current->next == NULL)
            break;
        current = current->next;
    }
    return NULL;
}
Contact *ManageSearch(Contact *phonebook[26], int code)
{

    if (code == 1)
    {
        printf("Enter a phone number:");
        char buffer[100];
        cleanBuffer();
        fgets(buffer, 100, stdin);
        char *phoneNum = strtok(buffer, "\n");
        Contact *rst = searchFunct(phonebook, phoneNum, NULL, 1);
        if (rst != NULL)
        {
            printf("The following contact was found: %s %s %s\n", rst->firstName, rst->lastName, rst->phoneNum);
            return rst;
        }
        else
        {
            printf("No contact with a phone number %s was found in the phone book\n", phoneNum);
            return NULL;
        }
    }
    else
    {

        printf("Enter a contact name (<first name> <last name>):");
        char buffer[100];
        cleanBuffer();
        fgets(buffer, 100, stdin);
        char *firstName = strtok(buffer, " ");
        char *lastName = strtok(NULL, " ");

        Contact *rst = searchFunct(phonebook, firstName, lastName, 1);
        if (rst != NULL)
        {
            printf("The following contact was found: %s %s %s\n", rst->firstName, rst->lastName, rst->phoneNum);
            return rst;
        }
        else
        {
            printf("No contact with a name %s %s was found in the phone book\n", firstName, lastName);
            return NULL;
        }
    }
}
void ManageDelContact(Contact *phonebook[26])
{
    printf("Enter a contact name (<first name> <last name>): ");
    char buffer[100];
    cleanBuffer();
    fgets(buffer, 100, stdin);
    char *firstName = strtok(buffer, " ");
    char *lastName = strtok(NULL, "\n");
    printf("Are you sure? (y/n) ");
    char choice;
    scanf(" %c", &choice);
    if (choice != 'y')
    {
        printf("The deletion of the contact has been canceled.\n");
        return;
    }
    int rst = 0;

    rst = deleteContact(phonebook, firstName, lastName);
    if (rst)
    {

        printf("The contact has been deleted successfully!\n");
    }
    else
    {
        printf("The deletion of the contact has failed!\n");
    }
}

int ManageUpdateContact(Contact *phonebook[26])
{
    Contact *rst = ManageSearch(phonebook, 2);
    printf("Enter the new phone number:");

    cleanBuffer();
    char *phoneNum;
    scanf("%s", &phoneNum);

    if (checkNumber(phonebook, phoneNum))
    {
        strcpy(rst->phoneNum, phoneNum);
        printf("The contact has been updated successfully!\n");
        return TRUE;
    }
    else
    {
        printf("he update of the contact has failed, since the phone number %s already exists!\n", phoneNum);
        return FALSE;
    }
}
void freeingNodes(Contact *phonebook[26])
{

    // Contact *rst;
    // Contact *prev;
    // Contact *current;

    for (int i = 0; i < 26; i++)
    {

        while (phonebook[i] != NULL)
        {
            phonebook[i] = freeContact(phonebook[i]);
        }
    }
}
void main()
{

    Contact *phonebook[26] = {[0 ... 25] = NULL};
    int choice;
    int rst = 0;
    while (1)
    {

        printMenu();

        scanf(" %d", &choice);

        switch (choice)
        {
        case 1:
            addContact(phonebook);

            break;
        case 2:
            ManageDelContact(phonebook);
            break;
        case 3:
            ManageSearch(phonebook, 1);
            break;
        case 4:

            ManageSearch(phonebook, 2);
            break;
        case 5:
            ManageUpdateContact(phonebook);
            break;
        case 6:
            printBook(phonebook);
            break;
        case 7:
            freeingNodes(phonebook);
            printf("Bye!");
            exit(0);
            break;

        default:
            printf("Wrong option, try again:");
            continue;
            break;
        }
    }
}