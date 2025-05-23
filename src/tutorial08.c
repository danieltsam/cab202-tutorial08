#include "timer.h"

uint8_t pb_falling_edge = 0;

/** Tutorial 8

INTRODUCTION:

In this week's tutorial you will implement pushbutton debouncing and
implement a state machine using an enumerated type and switch-case
statements.

The Tutorial 8 exercises should implement the state machine depicted in
state_machine_tut8.png.
*/

/** EX: 8.0

TASK: Declare an enumerated type (enum) that can hold the values of each
state required to implement the state machine in state_machine_tut8.png.

Use meaningful names for each enum value.

TIP: Use the "typedef" keyword to create a type alias for your enum.
*/

typedef enum {
    OFF,
    CONFIRM_ON,
    ON,
    CONFIRM_OFF
} led_state; 

/** CODE: Write your code for Ex 8.0 above this line. */

int main(void)
{
    buttons_init();
    timer_init();

    /** EX: 8.1

    TASK: Declare a variable of the enumerated type you declared above.

    Initialise this variable with the initial state of the state machine.
    */
    led_state my_state = OFF;

    /** CODE: Write your code for Ex 8.1 above this line. */

    while (1)
    {
        /** EX: 8.2

        The code in "timer.c" uses periodic interrupts to sample the
        state of the pushbuttons in the variable "pb_debounced_state".

        TASK: Write code to detect pushbutton press events for S1-S4
        by detecting falling edges in "pb_debounced_state" across any
        two iterations of this while loop.

        Store the output of this detection in the flag variable
        "pb_falling_edge", where for each bit, 1 indicates a falling
        edge and 0 indicates no falling edge.

        HINT: To detect a falling edge, you will need to keep track of
        the previous state of the pushbuttons. This will require you to
        declare an additional variable whose value is preserved between
        iterations of this while loop.
        */

        static uint8_t previous_pb_state = 0xFF;

        pb_falling_edge = (previous_pb_state ^ pb_debounced_state) & previous_pb_state;

        previous_pb_state = pb_debounced_state;

        /** CODE: Write your code for Ex 8.2 above this line. */

        /** EX: 8.3

        TASK: Write a switch-case statement below that implements the
        state machine in state_machine_tut8.png.

        The switch statement should test the value of the variable
        declared in Ex 8.1 and a case should be defined for every state
        in the state machine (every enumerator in the enum you declared
        in Ex 8.0).

        Use the "pb_falling_edge" variable from Ex 8.2 to trigger the
        appropriate transitions between states.

        The switch statement should also contain a default case to
        handle invalid states. This default case must reset the state
        machine to the initial state and reset any outputs to their
        default values.
        */
        /** EX: 8.3 */

            switch (my_state) {
        case OFF:
            if (pb_falling_edge & (1 << 4)) { // S1 pressed
                my_state = CONFIRM_ON;
            }
            break;

        case CONFIRM_ON:
            if (pb_falling_edge & (1 << 5)) { // S2 pressed
                my_state = ON;
            } else if (pb_falling_edge & ((1 << 4) | (1 << 6) | (1 << 7))) { // S1, S3, or S4 pressed
                my_state = OFF;
            }
            break;

        case ON:
            if (pb_falling_edge & (1 << 6)) { // S3 pressed
                my_state = CONFIRM_OFF;
            }
            break;

        case CONFIRM_OFF:
            if (pb_falling_edge & (1 << 7)) { // S4 pressed
                my_state = OFF;
            } else if (pb_falling_edge & ((1 << 4) | (1 << 5) | (1 << 6))) { // S1, S2, or S3 pressed
                my_state = ON;
            }
            break;

        default:
            my_state = OFF;
            break;
        }

        /** CODE: Write your code for Ex 8.3 above this line. */
    }

    /** EX: 8.4

    TASK: Modify the code in "timer.c" so that the variable
    "pb_debounced_state" holds a debounced version of the pushbutton's
    state, rather than a raw sample of PORTA.IN.

    Ensure that the correct number of samples are taken at an
    appropriate interval.
    */

    /** CODE: Write your code for Ex 8.4 in timer.c. */
}
