#include <stdio.h>
#include "config.c"
#include "def_pinos.h"

// flag to trigger virtual switch
volatile unsigned char switch_trigger;
// virtual switch press counts
volatile unsigned char count = 0;

// handles serial input to set trigger flag of virtual switch
void int_serial(void) __interrupt 4 {
    if (RI0 == 1) {
        RI0 = 0;
        // only listen for '1' key
        if (SBUF0 == '1') {
            switch_trigger = 1;
        }
    }
}

// virtual switch behavior
void int_Timer3(void) __interrupt 14 { // Timer 3 configurado para um overflow a cada 5ms 
    static unsigned char t_ms;
    TF3 = 0;

    if (switch_trigger == 1) {
        switch (t_ms) {
            case 0: P1_2 = 0; break;
            case 5: P1_2 = 1; break;
            case 10: P1_2 = 0; break;
            case 160: P1_2 = 1; break;
            case 165: P1_2 = 0; break;
            case 170: 
                P1_2 = 1;
                t_ms = 0;
                switch_trigger = 0;
                break;
            default: break;
        }
    }
    
    if (switch_trigger != 0) {
        t_ms += 5;
    }
}

// handles our virtual switch presses
void int_key_press(void) __interrupt 0 {
    count++;
    IE0 = 0;
}

// handles printf
void putchar (unsigned char c) {
    SBUF0 = c;
    while (TI0 == 0);
    TI0 = 0;
}

void main (void) {
    unsigned char last = 99; // last count value that was printed

    Init_Device();
    SFRPAGE = LEGACY_PAGE;

    while(1) {
        // only print count if it has been updated
        if (last != count) {
            last = count;
            printf_fast_f("count = %03d\n", count);
        }
    }
}