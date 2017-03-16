//
// Created by munk on 3/16/17.
//

#ifndef ATMEGA2560TEST_LED_H
#define ATMEGA2560TEST_LED_H
void initLEDport(void);
void writeAllLEDs(unsigned char pattern);
void turnOnLED(unsigned char led_nr);
void turnOffLED(unsigned char led_nr);
void toggleLED(unsigned char led_nr);
#endif //ATMEGA2560TEST_LED_H
