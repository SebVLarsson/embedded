#include <stdio.h> // include for io operations
#include <stdlib.h> // include for atoi
#include <string.h> // include for strlen
#include <ctype.h> // include for isdigit function

// direction enum
enum DIRECTION {N,O,S,W};

// robot struct
typedef struct {
    int xpos;
    int ypos;
    enum DIRECTION dir;
} ROBOT;

/* FUNCTION INITIALIZATIONS START */
void move(ROBOT *robot, int *valid_move);
void turn(enum DIRECTION *dir);
void clear_buffer();
void print_simulation(int *robotx, int *roboty);
/* FUNCTION INITIALIZATIONS END */

int main() {
    // initializing our robot struct
    ROBOT robot;

    // initializing our while loop controlling integer, it will control whether the user gets to do another simulation round or exit the program
    int control_int = 1;

    //initializing our input_buffer to size 4 because want a third digit space to be able to error handle
    char input_buffer[4];


    while (control_int != 0) {
        printf("Select a starting x position for the robot (0-99)\n");

        // prompting for input from user taking 4 characters because we're looking for at most 2 numbers but also \n that comes with stdin and \0
        if (fgets(input_buffer, 4, stdin)) {

            // initializing a size_t int variable because we want to store the length of the user input string
            // TIL size_t is used for code readability if we ever want to store the size or length of something
            size_t len = strlen(input_buffer);

            // if length is greater than 0 and the last char of the string is not a \n we know its a faulty input because proper input; 
            // 1 or 2 digits, would leave \n in on the last space in strlen via stdin
            // in case of too many digit input
            if (len > 0 && input_buffer[len-1] != '\n') {
                printf("Invalid x coordinate\n");
                clear_buffer();
                return 0;
            } 

            // in case of no input
            if (len == 0) {
                printf("Invalid x coordinate\n");
                return 0;
            }

            // ensuring that all the input are digits for this stage so we loop through them from index 0 until we hit \n because we already ensured that \n will be the last "char" in the string above
            for (int i = 0; input_buffer[i] != '\n'; i++) {
                if (!isdigit(input_buffer[i])) {
                    printf("Invalid x coordinate\n");
                    return 0;
                }
            }
        }

        // updating the xpos with the users input using atoi to convert from ascii to int
        robot.xpos = atoi(input_buffer);


        printf("Select a starting y position for the robot (0-99)\n");
        // prompting for input from user
        if (fgets(input_buffer, 4, stdin)) {

            // initializing a size_t int variable because we want to store the length of the user input string
            // TIL size_t is used for code readability if we ever want to store the size or length of something
            size_t len = strlen(input_buffer);

            // if length is greater than 0 and the last char of the string is not a \n we know its a faulty input because proper input; 
            // 1 or 2 digits, would leave \n in on the last space in strlen via stdin
            // in case of too many digit input
            if (len > 0 && input_buffer[len-1] != '\n') {
                printf("Invalid x coordinate\n");
                clear_buffer();
                return 0;
            } 

            // in case of no input
            if (len == 0) {
                printf("Invalid x coordinate\n");
                return 0;
            }

            // ensuring that all the input are digits for this stage so we loop through them from index 0 until we hit \n because we already ensured that \n will be the last "char" in the string above
            for (int i = 0; input_buffer[i] != '\n'; i++) {
                if (!isdigit(input_buffer[i])) {
                    printf("Invalid x coordinate\n");
                    return 0;
                }
            }
        }

        // updating the xpos with the users input using atoi to convert from ascii to int
        robot.ypos = atoi(input_buffer);
        print_simulation(&robot.xpos, &robot.ypos);

        // because the robots starting direction should be North we set it to north before prompting for actions
        robot.dir = N;

        // initialize our string for commands
        char commands[32];
        while (1) {
            printf("You are allowed to move the robot by typing m and t as many times as you want for a maximum of 30 actions! e.g: mmttmmtmtmt\nAction input: ");

            // reading stdin for userinputs to a maximum of 30 characters, 31st will be reserved for our error-handle \n and 32nd is for \0
            fgets(commands, 32, stdin);

            // initializing a size_t int variable because we want to store the length of the user input string
            // TIL size_t is used for code readability if we ever want to store the size or length of something
            size_t len = strlen(commands);

            // if length is greater than 0 and the last char of the string is not a \n we know its a faulty input because proper input; 
            // 30 or less characters would leave \n in on the last space in strlen via stdin
            // in case of too many actions input
            if (len > 0 && commands[len-1] != '\n') {
                printf("Invalid action input\n");
                clear_buffer();
                return 0;
            } 

            // in case of no input
            if (len == 0) {
                printf("Invalid action input\n");
                return 0;
            }

            int valid_move = 1;

            // and this is our action loop, we go from left to right reading each action, calling the corresponding action to execute it
            // if the user misstyped an action we simply continue the loop
            for (int i = 0; commands[i] != '\n'; i++) {
                if (valid_move != 1) {
                    break;
                } else if (commands[i] == 'm') {
                    move(&robot, &valid_move);
                } else if (commands[i] == 't') {
                    turn(&robot.dir);
                } else {
                    continue;
                }
            }

            // printing finished position
            printf("xPos: %d\nyPos: %d\n", robot.xpos, robot.ypos);
            print_simulation(&robot.xpos, &robot.ypos);
            if (valid_move != 1) {
                printf("The truck hit a wall, exiting...\n");
                break;
            }
        }

        printf("Input any char or integer to continue or Exit '0'\n");
        // scanf awaiting new round or 0 for exit, because we set control_int to 1 earlier it doens't matter if user inputs a char into our %d because if they do it remains 1
        scanf("%d", &control_int);
        clear_buffer(); // clear buffer just in case
    }
}

// robot move function, takes the robot pointer to update its position
void move(ROBOT *robot, int *valid_move) {

    // switch case looking at what direction the robot is currently facing, then based on that either incrementing or decrementing the x or y pos
    // 0 = N, 1 = E, 2 = S, 3 = W
    // We also check if the move is in bounds, if it isn't, the move is simply skipped
    switch (robot->dir) {
        case 0: if (robot->ypos > 0) {
            robot->ypos--;
            break;
        } else {
            *valid_move = 0;
            break;
        }
        case 1: if (robot->xpos < 99) {
            robot->xpos++; 
            break;
        } else {
            *valid_move = 0;
            break;
        }
        case 2: if (robot->ypos < 99) {
            robot->ypos++; 
            break;
        } else {
            *valid_move = 0;
            break;
        }
        case 3: if (robot->xpos > 0) {
            robot->xpos--; 
            break;
        } else {
            *valid_move = 0;
            break;
        }
    }
}

// robot turn function, here we don't need to expose the function to the entire robot struct
// all it needs here is the direction
void turn(enum DIRECTION *dir) {
    // since incrementing an enum past its limit gives undefined behaviour, we need to check that the direction is not 3/west, if it isn't we just increment the direction
    if (*dir != 3) {
        (*dir)++;
    } else { // if it is 3/west, we set the direction back to N/0
        *dir = N;
    }
}

// clear inputbuffer function to avoid having to write the same lines of code twice
void clear_buffer() { 
    int buffer; // initialize a buffer int
    while ((buffer = getchar()) != '\n' && buffer != EOF); // while we dont run into a \n or EOF we keep going to successfully clear the buffer
}

void print_simulation(int *robotx, int *roboty) {
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            if (i == *roboty && j == *robotx) {
                printf("r ");
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }
}