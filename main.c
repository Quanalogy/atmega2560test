/*
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
        _delay_ms(500);
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
}*/


/********************************************
* MSYS, LAB 12                              *
* Test program for Interrupt driven UART    *
* driver.                                   *
*                                           *
* Henning Hargaard 13/11 2015               *
*********************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "uart_int.h"
#include "led.h"
#include "lm75.h"
#include "esp8266.h"

ISR (USART0_RX_vect)
{
    char modtaget_tegn;

    // Aflæs UART modtage-register
    modtaget_tegn = UDR0;
    // Reager kun på lovlige tegn
    if ((modtaget_tegn >= '0') && (modtaget_tegn <= '7'))
    {
        // Toggle aktuelle lysdiode
        toggleLED(modtaget_tegn - '0');
        // Send streng "LED nummer x er toggled"
        SendString("LED nummer ", 0);
        SendChar(modtaget_tegn, 0);
        SendString(" er toggled\r\n", 0);
    }
}

int main()
{
    int temp;

    // Initier UART (med RX interrupt enable)
    InitUART(9600, 8, 'N', 1, 0);
//    InitUART(9600, 8, 'N', 1, 1);

    // Global interrupt enable
    sei();
    // Initier LED port
//    initLEDport();
    // Initier temperatur sensor
//    LM75_init();
    SendString("Hello terminal\r\n", 0);
    initWiFi();
    while (1)
    {
        // Aflæs temperaturen (OBS: Enhed = halve grader)
        /*temp = LM75_temperature(0);
        // Vis i formatet "26,5 grader" (og linieskift)
        SendInteger(temp/2, 0);
        SendChar(',', 1);
        if (temp & 0b00000001)
            SendChar('5', 0);
        else
            SendChar('0', 0);
        SendString(" grader\r", 0);*/
        testWiFi();
        // Vent 1 sekund
        _delay_ms(5000);
    }
}