#include <stdio.h> // import for io operations
#include <string.h> // import for strtok (splitting strings)
#include <ctype.h> // import for isdigit
#include <stdlib.h> // import for atoi

int validate_size_input(char *input_buffer, int *rows, int *columns); // validate the users size input
int validate_matrix_input(char *input_buffer, int expected); // validate the users matrix numbers input
int** setup_matrix(char *input_buffer, int *rows, int *columns); // setup the matrices

int main() {
    // initialize an input_buffer to 64, wasn't sure how big numbers we should support so I just picked 64
    // and 64 is a lovely number that fits atleast a 2 digit 4x4 matrix (32 numbers + 16 spaces)
    char input_buffer[64];

    // initialize rows and columns ints
    int rows = 0;
    int columns = 0;
    
    // while "true" loop
    while (1) {
        printf("Input the size:\n");
        fgets(input_buffer, sizeof(input_buffer), stdin); // take input from user
        if (validate_size_input(input_buffer, &rows, &columns) == 1) return 0;  // if invalid input, just exit the program

        printf("Input matrix1:\n");
        fgets(input_buffer, sizeof(input_buffer), stdin); // take input from user for matrix1

        // sending the input buffer together with the rows * column (to get maximum amount of cells) into the validate function to control that input is ok
        if (validate_matrix_input(input_buffer, rows * columns) == 1) return 0; // invalid input, exit program
        int **matrix1 = setup_matrix(input_buffer, &rows, &columns); // initialize and setup matrix in the setup_matrix function

        printf("Input matrix2:\n");
        fgets(input_buffer, sizeof(input_buffer), stdin); // take input from user for matrix2

        // sending the input buffer together with the rows * column (to get maximum amount of cells) into the validate function to control that input is ok
        if (validate_matrix_input(input_buffer, rows * columns) == 1) { // invalid input, exit program... BUT!
            for (int i = 0; i < rows; i++) free(matrix1[i]); // first loop through matrix1 and free memory
            free(matrix1); // and free more memory
            return 0; // then we exit the program
        }
        int **matrix2 = setup_matrix(input_buffer, &rows, &columns); // initialize and setup matrix 2

        
        /*
        I was considering making a third matrix (2d array)
        However there's no reason not to just add matrix2 to matrix1 and use that as the result
        So that's what we're doing, we're looping through rows and columns, adding the corresponding numbers in matrix2 to matrix1
        */
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                matrix1[i][j] += matrix2[i][j];
            }
        }

        /*
        Looping through rows and columns of matrix 1 to print
        */
        printf("The sum is:\n");
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                if (j == columns - 1) { // if we're on the last column we need to print a \n
                    printf("%d\n", matrix1[i][j]);
                } else { // otherwise just print %d with a space after
                    printf("%d ", matrix1[i][j]);
                }
            }
        }

        // free all the memory
        for (int i = 0; i < rows; i++) { // looping through the outer array and freeing all the memory from the nested arrays
            free(matrix1[i]); // free matrix1
            free(matrix2[i]); // free matrix2
        }
        free(matrix1); // free the outer arrays
        free(matrix2); // free the outer arrays
    }
}

int validate_size_input(char *input_buffer, int *rows, int *columns) { // validate the size input
    // control int to to ensure we have the right amount of numbers
    int digit_count = 0; 
    for (int i = 0; input_buffer[i] != '\n' && input_buffer[i] != '\0'; i++) { // loop until we hit \n or \0
        if (i % 2 == 0) { // if i modulo 2 is 0, we know its a number "spot" since index 0 will be the first number, and subsequent numbers is a space away so 2
            if (!isdigit(input_buffer[i])) { // if its not a digit we return 1 (error/exit code)
                printf("Invalid input\n");
                return 1;
            }
            digit_count++; // increment the digit_count to compare to our mag
        } else if (input_buffer[i] != ' ') { // if its not modulo 2, then the char needs to be a space, so if it isnt, we exit with error code 1 here aswell
            printf("Invalid input\n");
            return 1;
        }
    }
    if (digit_count != 2) {  // since we only allow 2d matrices, if its not 2, its invalid
        printf("Invalid input\n");
        return 1;
    }

    // dereferencing the pointers to set their correct values
    *rows = input_buffer[0] - '0'; // since atoi only works for strings, we just do ascii arithmetics to get the correct int valueo
    *columns = input_buffer[2] - '0'; // since atoi only works fr strings, we just do ascii arithmetics to get the correct int value
    if (*rows < 2 || *rows > 4 || *columns < 2 || *columns > 4) { // quick check that the size inputs were not too big or too small
        printf("Invalid input\n");
        return 1;
    }
    return 0; // successful return
}


// validate matrix number input
int validate_matrix_input(char *input_buffer, int expected) {
    int numbers = 0; // the amount of numbers we've added
    int i = 0; // index int to iterate our while loop
    
    while (input_buffer[i] != '\n' && input_buffer[i] != '\0') {
        if (input_buffer[i] == ' ') {
            // just let this slide without loop continue since we need to increment at the end of the loop
        } else if (isdigit(input_buffer[i]) || input_buffer[i] == '-') { // if its a number OR a minus
            numbers++; // iterate numbers found
            if (input_buffer[i] == '-') i++; // if we find a minus sign, we increment to find the numbers 
            if (!isdigit(input_buffer[i])) { // if the next step is NOT a number, then its faulty input, so we exit with return 1 (error)
                printf("Invalid input\n");
                return 1;
            }
            while (isdigit(input_buffer[i])) i++; // if the digit is 2digit we skip the second one
            i--; // decrement ONCE after we found the end of the multidigit number since the outer loop will ++ aswell
        } else { // if its not a space and not a number, its invalid input so we exit with return 1
            printf("Invalid input\n");
            return 1;
        }
        i++; // increment for next iteration
    }
    
    if (numbers != expected) { // if we didn't find the same amount of numbers as we're expecting (i.e size), we're returning 1 (error)
        printf("Invalid input\n");
        return 1;
    }
    return 0; // valid input
}

/*
Setting up the matrix, allocating memory, adding our numbers to the arrays
int** is an array of pointers, in this case int pointers
The reason being is that in each slot in the original array we're putting another array
And since an array is from my understanding just a block of memory and an array declaration points to that block of memory
the array itself is, in a wierd way just a pointer
*/
int** setup_matrix(char *input_buffer, int *rows, int *columns) {
    int **matrix = malloc(*rows * sizeof(int *)); // dereference pointer and allocate the "outer" matrix or the x matrix (rows)
    for (int i = 0; i < *rows; i++) { // loop over and add another array in each of the cells in the array
        matrix[i] = malloc(*columns * sizeof(int)); // dereference pointer and malloc columns times the size of an int
    }

    int row_index = 0; // control int for row_index looping
    int column_index = 0; // control int for column_index looping
    char *token = strtok(input_buffer, " \n"); // initial string setup for the strtok function
    
    while (token != NULL && row_index < *rows) { // loop until token is null or rows are filled
        matrix[row_index][column_index] = atoi(token); // add the token after atoi (ascii to int) to the current matrix spot
        column_index++; // increment the column index
        
        if (column_index == *columns) { // if we hit the last column
            column_index = 0; // reset column
            row_index++; // increment row
        }
        token = strtok(NULL, " \n"); // get the next number
    }

    return matrix; // return the newly made matrix
}