#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


// -----typedefs -------
typedef struct {
    char firstname[20];
    char famname[20];
    char pers_number[13]; // yyyymmddnnnc
} PERSON;


// Function declaration (to be extend)
PERSON input_record(void); // Reads a person’s record.
char* first_name_input(char *buffer); // first name input function
char* last_name_input(char *buffer); // last name input function
char* person_nr_input(char *buffer); // person nummer input function
int verify_char_input(char *buffer); // verify character input
int verify_pnr_input(char *buffer); // verify person nummer input
void write_new_file(PERSON *inrecord); // Creates a file and writes the first record
void printfile(void); // Prints out all persons in the file
int search_menu(int *option); // search menu for choosing first or last name to search by
void search_by_firstname(char *name); // Prints out the person if in list
void search_by_lastname(char *name); // Prints out the person if in list
void append_file(PERSON *inrecord); // appends a new person to the file
void clear_buffer(void); // clear buffer
int main_menu(char *menu_buffer, __int8_t *input); // main menu



int main(void){
    // initialize input as 1 byte int to save space
    __int8_t input = 6;

    //initialize our menu_buffer input to 3, because we're only ever going to allow 1 digit (char) input
    char menu_buffer[3];

    // initialize a PERSON struct
    PERSON ppost;

    // Main program loop
    while (input != 5) {
        // if the return value code is anything but 0 we continue to next iteration
        // due to faulty input, giving the user another chance
        if (main_menu(menu_buffer, &input) != 0) continue;

        // exit key, we could also break here but it doesn't make a difference (i think?)
        if (input == 5) {
            printf("Bye\n"); 
            continue;
        }

        switch (input) {
            case 1: // delete old and create a new file
                write_new_file(&ppost);
                break;
            case 2: // append a new person, call input record to input all data first, then append to the file
                ppost = input_record();
                append_file(&ppost);
                break;
            case 3: // searching for a person in records, setting option by ptr inside search_menu to dictate which one we go to or if we break
                char name[20]; // initialize string buffer for name
                int option; // initialize option int that controls the if else
                search_menu(&option);
                if (option == 0) {
                    first_name_input(name);
                    search_by_firstname(name);
                } else if (option == 1) {
                    last_name_input(name);
                    search_by_lastname(name);
                }
                break;
            case 4: // print struct by struct from file
                printfile();
                break;
        }
    }
    return(0); // successfully reached the end of the program
}


PERSON input_record(void) {
    PERSON ppost = {0}; // initialize a PERSON ppost and set all its values to 0
    char buffer[20]; // initialize a an input buffer

    // strcpy the results of each input function into the structs string buffers
    strcpy(ppost.firstname, first_name_input(buffer));
    strcpy(ppost.famname, last_name_input(buffer));
    strcpy(ppost.pers_number, person_nr_input(buffer));

    // return the struct
    return ppost;
}


char* first_name_input(char *buffer) {
    // initialize a validity control variable to 8bit int because we dont need bigger
    __int8_t valid = 0;
    
    while (valid != 1) { // while valid is not 1 (signaling complete)
        printf("Write the persons first name, MAX 19 characters\n");
        if (fgets(buffer, 20, stdin) != NULL) { // read 20 characters from stdin
            size_t len = strlen(buffer); // initialize and set len to string length of buffer

            // if the last index of buffer is a \n we set it to \0 instead for our verification function
            if (len > 0 && buffer[len-1] == '\n') {
                buffer[len-1] = '\0';
            }

            // verify the input so that its correct, if it is we set valid to 1 to exit the while loop
            if (verify_char_input(buffer) == 0) valid = 1;
        }
    }
    return buffer; // return the buffer that contains the correct input first name
}


char* last_name_input(char *buffer) {
    // initialize a validity control variable to 8bit int because we dont need bigger
    __uint8_t valid = 0;

    while (valid != 1) { // while valid is not 1 (signaling complete)
        printf("Write the persons last name, MAX 19 characters\n");
        if (fgets(buffer, 20, stdin) != NULL) { // read 20 characters from stdin
            size_t len = strlen(buffer); // initialize and set len to string length of buffer

            // if the last index of buffer is a \n we set it to \0 instead for our verification function
            if (len > 0 && buffer[len-1] == '\n') {
                buffer[len-1] = '\0';
            }

            // verify the input so that its correct, if it is we set valid to 1 to exit the while loop
            if (verify_char_input(buffer) == 0) valid = 1;
        }
    }
    return buffer; // return the buffer that contains the correct input last name
}


char* person_nr_input(char *buffer) {
    // initialize a validity control variable to 8bit int because we dont need bigger
    __uint8_t valid = 0;

    while (valid != 1) { // while valid is not 1 (signaling complete)
        printf("Write the persons personnummer, 12 characters\n");
        if (fgets(buffer, 20, stdin) != NULL) { // read 20 characters from stdin
            size_t len = strlen(buffer); // initialize and set len to string length of buffer

            // if the last index of buffer is a \n we set it to \0 instead for our verification function
            if (len > 0 && buffer[len-1] == '\n') {
                buffer[len-1] = '\0';
            }

            // verify the input so that its correct, if it is we set valid to 1 to exit the while loop
            if (verify_pnr_input(buffer) == 0) valid = 1;
        }
    }
    return buffer; // return the buffer that contains the correct input person nr
}


int verify_char_input(char *buffer) {
    // initialize len and set it to strlen of buffer
    size_t len = strlen(buffer);

    // if len is 0 OR 20 characters or more (we're reserving 1 spot of the buffer for \0!)
    if (len == 0 || len >= 20) {
        printf("Invalid input\n");
        return 1; // returning 1 to previous function to signal error
    }

    // until we run into the \0 we iterate over, ensuring that none of the chars are digits
    for (int i = 0; buffer[i] != '\0'; i++) {
        if (isdigit(buffer[i])) {
            printf("Invalid input\n");
            return 1; // returning 1 to previous function to signal error
        }
    }
    return 0; // return successful to previous function
}


int verify_pnr_input(char *buffer) {
    // initialize len and set it to strlen of buffer
    size_t len = strlen(buffer);
    
    // if len is NOT 12, then the format of the input is incorrect for person nummer, therefor its invalid
    if (len != 12) {
        printf("Invalid input\n");
        return 1; // returning 1 to previous function to signal error
    }

    // until we run into \0 we iterate over, ensuring that all chars are infact digits
    for (int i = 0; buffer[i] != '\0'; i++) {
        if (!isdigit(buffer[i])) {
            printf("Invalid input\n");
            return 1; // returning 1 to previous function to signal error
        }
    }
    return 0;// return successful to previous function
}


void write_new_file(PERSON *inrecord) {
    // initialize a file pointer
    FILE *pFilePtr;

    // If we can open pFile.bin then it exists so we close the file and delete it.
    // also note that to read binary we have to specify that its a binary file with the b following r/w
    if ((pFilePtr = fopen("pFile.bin", "rb")) != NULL) {
        fclose(pFilePtr); // close file
        remove("pFile.bin"); // delete file
    }

    // since fopen will create a file if it does not already exist, we can simply check for NULL
    // if NULL is returned then we know that for some reason we cannot create the file
    // also note that to read binary we have to specify that its a binary file with the b following r/w
    if ((pFilePtr = fopen("pFile.bin", "wb")) == NULL) {
        printf("File could not be created");
    } else { // else we go ahead and add our dummy data by strcpy our dummy variables into the struct variables
        strcpy(inrecord->firstname, "Bob");
        strcpy(inrecord->famname, "Bobson");
        strcpy(inrecord->pers_number, "198401015544");
        fwrite(inrecord, sizeof(PERSON), 1, pFilePtr); // write the struct into our file
        fclose(pFilePtr); // close the file!!!
    }
}


void printfile(void) {
    // initialize our file pointer
    FILE *pFilePtr;
    // initialize a temporary PERSON struct we can read into
    PERSON tempp;

    // if fopen returns NULL, file does not exist
    // also note that to read binary we have to specify that its a binary file with the b following r/w
    if ((pFilePtr = fopen("pFile.bin", "rb")) == NULL) {
        printf("File does not exist\n");
        return;
    } else {
        // here we read struct by struct by specifying the size of PERSON and that we will read 1 at the time
        while (fread(&tempp, sizeof(PERSON), 1, pFilePtr) == 1) {
            // print the data
            printf("%s %s\nPnr: %s\n", tempp.firstname, tempp.famname, tempp.pers_number);
        }
    }
}


int search_menu(int *option) {
    // initialize a menu_buffer
    char menu_buffer[3];

    printf("1 Search by First name\n2 Search by Last name\n");

    // read 3 chars from stdin
    fgets(menu_buffer, 3, stdin);

    // initalize len and store strlen of menu_buffer into it
    size_t len = strlen(menu_buffer);

    // if the last char is not a \n and len is greater than 0 the input was wrong
    if (len > 0 && menu_buffer[len-1] != '\n') {
        printf("Invalid choice\n");
        clear_buffer();
        *option = 2; // assign 2 to option by dereferencing
    } else if (len == 0 || menu_buffer[0] == '\n') { // if len is 0 or index0 is \n its faulty input aswell
        printf("Invalid choice\n");
        *option = 2; // assign 2 to option by dereferencing
    } else if (menu_buffer[0] != '1' && menu_buffer[0] != '2') { // if index0 of menu_buffer is not '1' or '2' faulty input
        printf("Invalid choice\n");
        *option = 2; // assign 2 to option by dereferencing
    }

    // if else tree to figure out if we're going to assign 0 or 1 to option (first or last name)
    if (menu_buffer[0] == '1') {
        *option = 0;
    } else if (menu_buffer[0] == '2') {
        *option = 1;
    }
}


void search_by_firstname(char *name) {
    // initialize a file pointer
    FILE *pFilePtr;

    // initialize a temporary PERSON struct we can read into
    PERSON tempp;

    // validity variable
    int found = 0;

    // if fopen returns NULL, file does not exist
    // also note that to read binary we have to specify that its a binary file with the b following r/w
    if ((pFilePtr = fopen("pFile.bin", "rb")) == NULL) {
        printf("File does not exist\n");
        return;
    } else {

        // we read struct by struct by specifying the size of PERSON and that we will read 1 at the time
        while (fread(&tempp, sizeof(PERSON), 1, pFilePtr) == 1) {
            if (strcmp(tempp.firstname, name) == 0) { // if strcmp returns 0 we found a match
                printf("Found %s %s\nPnr: %s\n", tempp.firstname, tempp.famname, tempp.pers_number);
                found = 1;
            }
        }
    }

    // if found is 0 we didn't find a person
    if (!found) {
        printf("Person not found\n");
    }

    // close the file!!
    fclose(pFilePtr);
}


void search_by_lastname(char *name) {
    // initialize a file pointer
    FILE *pFilePtr;

    // initialize a temporary PERSON struct we can read into
    PERSON tempp;

    // validity variable
    int found = 0;

    // if fopen returns NULL, file does not exist
    // also note that to read binary we have to specify that its a binary file with the b following r/w
    if ((pFilePtr = fopen("pFile.bin", "rb")) == NULL) {
        printf("File does not exist\n");
        return;
    } else {

        // we read struct by struct by specifying the size of PERSON and that we will read 1 at the time
        while (fread(&tempp, sizeof(PERSON), 1, pFilePtr) == 1) {
            if (strcmp(tempp.famname, name) == 0) {
                printf("Found %s %s\nPnr: %s\n", tempp.firstname, tempp.famname, tempp.pers_number);
                found = 1;
            }
        }
    }

    // if found is 0 we didn't find a person
    if (!found) {
        printf("Person not found\n");
    }

    // close the file!!
    fclose(pFilePtr);
}


void append_file(PERSON *inrecord) {
    // initialize a file pointer
    FILE *pFilePtr;

    // if fopen returns NULL the file doesn't exist, so we error handle for that
    // since we want to append (a) to a binary (b) we need to put ab
    // when trying to figure out how this works I didn't know if we had to read something first so I used ab+
    // ab allows write only whilst ab+ is read and write
    if ((pFilePtr = fopen("pFile.bin", "ab")) != NULL) {
        // write the struct inrecord into the file
        // we ensure we write the correct amount of data via sizeof(PERSON)
        // and the 1 is because we want to write 1 struct at the time
        fwrite(inrecord, sizeof(PERSON), 1, pFilePtr);
        fclose(pFilePtr); // CLOSE THE FILE!
    } else {
        printf("File does not exist.");
    }
}


void clear_buffer(void) {  // clear buffer function
    int buffer; // initialize a buffer int
    while ((buffer = getchar()) != '\n' && buffer != EOF); // while we dont run into a \n or EOF we keep going to successfully clear the buffer
}


int main_menu(char *menu_buffer, __int8_t *input) { // main menu
    printf("1 Create a new and delete the old file\n2 Add a new person to the file.\n3 Search for a person in the file.\n4 Print out all in the file.\n5 Exit the program.\n");
    
    // read 3 inputs from stdin and store in menu_buffer
    fgets(menu_buffer, 3, stdin);

    // initialize and set len to strlen of menu_buffer
    size_t len = strlen(menu_buffer);

    // if len is greater than 0 but the last char is not a \n the input was too long
    if (len > 0 && menu_buffer[len-1] != '\n') {
        printf("Invalid choice\n");
        clear_buffer();
        return 1;
    } else if (len == 0 || menu_buffer[0] == '\n') { // no input/enter
        printf("Invalid choice\n");
        return 1;
    } else if (menu_buffer[0] < 49 || menu_buffer[0] > 53) { // input was not between 1-5
        printf("Invalid choice\n");
        return 1;
    }

    // store the now correct input into input via the pointer dereference
    *input = atoi(menu_buffer);
    return 0; // return 0 because any other return forces the program loop in while to continue (to re-prompt input)
}