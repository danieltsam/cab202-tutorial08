#include "timer.h"

#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t pb_debounced_state = 0xFF;

void buttons_init(void)
{
    // Enable pull-up resistors for PBs
    PORTA.PIN4CTRL = PORT_PULLUPEN_bm;
    PORTA.PIN5CTRL = PORT_PULLUPEN_bm;
    PORTA.PIN6CTRL = PORT_PULLUPEN_bm;
    PORTA.PIN7CTRL = PORT_PULLUPEN_bm;
}

void timer_init(void)
{
    cli();
    TCB1.CTRLB = TCB_CNTMODE_INT_gc; // Configure TCB1 in periodic interrupt mode
    TCB1.CCMP = 3333;                // Set interval for 1 ms (3333 clocks @ 3.333 MHz)
    TCB1.INTCTRL = TCB_CAPT_bm;      // CAPT interrupt enable
    TCB1.CTRLA = TCB_ENABLE_bm;      // Enable
    sei();
}

ISR(TCB1_INT_vect)
{
    // Sample pushbutton state
    uint8_t pb_sample = PORTA.IN;

    // This variable currently contains a raw sample of the pushbuttons.
    // Modify the code in this ISR to implement debouncing correctly.
    pb_debounced_state = pb_sample;

    TCB1.INTFLAGS = TCB_CAPT_bm;
}
