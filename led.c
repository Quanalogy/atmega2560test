//
// Created by munk on 3/16/17.
//

#include <avr/io.h>
#define MAX_LED_NR 7

void initLEDport(void) {
    DDRB = 0xFF;
    PORTB = 0;
}

void writeAllLEDs(unsigned char pattern) {
    // Hent parameteren og skriv til lysdioderne
    PORTB = pattern;
}

void turnOnLED(unsigned char led_nr) {
    // Lokal variabel
    unsigned char mask;
    // Vi skal kun lave noget, hvis led_nr < 8
    if (led_nr <= MAX_LED_NR) {
        // Dan maske på basis af parameteren (led_nr)
        mask = 0b00000001 << led_nr;
        // Tænd den aktuelle lysdiode (de andre ændres ikke)
        PORTB = PINB | mask;
    }
}

void turnOffLED(unsigned char led_nr) {
    if(led_nr <= MAX_LED_NR) {
        unsigned char mask;
        mask = ~(0b00000001 << led_nr);
        PORTB = PINB & mask;
    }
}

void toggleLED(unsigned char led_nr) {
    if(led_nr <= MAX_LED_NR) {
        unsigned char mask = 0b00000001 << led_nr;
        PORTB = PINB^mask;
    }
}