#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "led.h"

// Prototyper
void initExtInts();
void initTimer0();
void initTimer1();

// Global variabel, der tæller antal Timer0 overflows
unsigned int antal_overflows = 0;

//--------------------------------------

int main(void) {
    // Klargoer LED port driver
    initLEDport();
    // Klargoer INT0 og INT1
    initExtInts();
    // Klargoer Timer0
    initTimer0();
    // Klargoer Timer 1
    initTimer1();
    // Global interrupt enable
    sei();
    // Main-loop: Toggle LED7 hvert sekund
    while(1) {
        toggleLED(7);
        _delay_ms(100);
    }
}

//--------------------------------------

// Interrupt service rutine for INT2
ISR (INT2_vect) {
    toggleLED(2);
}

// Interrupt service rutine for INT3
ISR (INT3_vect) {
    toggleLED(3);
}

// Interrupt service rutine for Timer0 overflow
ISR(TIMER0_OVF_vect) {
    // LED6 toggles, når der har vaeret 62500 interrupts
    // = hvert sekund, da 16000000/1/256 = 1
    antal_overflows++;
    if (antal_overflows == 62500) {
        toggleLED(6);
        antal_overflows = 0;
    }
}

// Interrupt service rutine for Timer1 Compare Match (A-system)
ISR (TIMER1_COMPA_vect) {
    toggleLED(5);
}

//--------------------------------------

void initExtInts() {
    // INT2:Falling edge, INT3:Rising edge
    EICRA = 0b11100000;
    // Enable extern interrupts INT2 og INT3
    EIMSK |= 0b00001100;
}

void initTimer0() {
    // Timer0: Normal mode, PS = 1 (= "No prescaling")
    TCCR0A = 0b00000000;
    TCCR0B = 0b00000001;
    // Enable Timer0 overflow interrupt
    TIMSK0 |= 0b00000001;
}

void initTimer1() {
    // Timer1: CTC mode (mode=4), no waveforms, PS = 256
    TCCR1A = 0b00000000;
    TCCR1B = 0b00001100;
    // Match frekvens = 16000000/256/15625 = 4 (gange per sekund)
    OCR1A = 15625;
    // Enable Timer1 Compare Match interrupt (A-system)
    TIMSK1 |= 0b00000010;
}