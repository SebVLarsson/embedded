#include <stdio.h>
#include <unistd.h>

// typedef'ing the Week ENUM to Week for easier access
typedef enum {
    WEEK_1,
    WEEK_2,
    WEEK_3,
    WEEK_4,
    WEEK_5
} Week;

// typedef'ing the Day ENUM to Day for easier access
typedef enum {
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
    SUNDAY
} Day;

void clear_buffer(); // initializing clear_buffer function

// Main Function
int main(void) {
    int week_no; // int to hold our week number
    int day_no; // int to hold our day number
    scanf("%1d", &week_no); // scanf to take 1 digit and put it into week_no
    clear_buffer(); // clear buffer to clear potential \n's
    scanf("%1d", &day_no); // scanf to take 1 digit and put it into day_no
    clear_buffer(); // clear buffer to clear potential \n's

    // First checking if week_no AND day_no are invalid
    // Secondly checking if week_no is invalid
    // Thirdly checking if day_no is invalid
    if ((week_no < 1 || week_no > 5) && (day_no < 1 || day_no > 7)) {
        printf("invalid");
        return 0;
    } else if (week_no < 1 || week_no > 5) {
        printf("invalid week");
        return 0;
    } else if (day_no < 1 || day_no > 7) {
        printf("invalid day");
        return 0;
    }
    // Since enums are 0 index, we decrement day_no and week_no by 1
    day_no--;
    week_no--;
    
    
    /*For looping over the ENUMs
    For week (outer loop): 
    We simply start from whatever is in week_no and go until WEEK_5 is done
    Incrementing once per loop iteration

    For day (inner loop):
    We must initialize the loop as 0 since each outer loop iteration it will reset to that value
    If we didn't do this and simply put Day d = (Day)day_no then each loop would begin from that day

    Once inside the inner day loop we check if d == 0 and w == week_no to ensure this is the first iteration of the first iteration
    If it is, we set d to day_no, we must however cast it via to a Day first using (Day)day_no
    */
    for (Week w = (Week)week_no; w <= WEEK_5; w++) {
        for (Day d = 0; d <= SUNDAY; d++) {
            if (d == 0 && w == week_no) {
                d = (Day)day_no;
            }
            
            // We switch case w (outer loop) value to print the correct case
            // Since we cannot enter these loops with faulty input we don't need a default case
            switch (w) {
                case WEEK_1: printf("Week 1, "); break;
                case WEEK_2: printf("Week 2, "); break;
                case WEEK_3: printf("Week 3, "); break;
                case WEEK_4: printf("Week 4, "); break;
                case WEEK_5: printf("Week 5, "); break;
            }

            // We then switch case d (inner loop) value to print the correct case
            switch (d) {
                case MONDAY: printf("Monday\n"); break;
                case TUESDAY: printf("Tuesday\n"); break;
                case WEDNESDAY: printf("Wednesday\n"); break;
                case THURSDAY: printf("Thursday\n"); break;
                case FRIDAY: printf("Friday\n"); break;
                case SATURDAY: printf("Saturday\n"); break;
                case SUNDAY: printf("Sunday\n"); break;   
            }

            // Sleep for 1 second before continuing with the next iteration
            sleep(1);
        }
    }
}

void clear_buffer() { // clear inputbuffer function to avoid having to write the same lines of code twice
    int buffer; // initialize a buffer int
    while ((buffer = getchar()) != '\n' && buffer != EOF); // while we dont run into a \n or EOF we keep going to successfully clear the buffer
}