cmake_minimum_required(VERSION 3.6.3)
project(atmega2560test)

set(CMAKE_C_STANDARD 11)


SET(MCU "atmega2560")
SET(F_CPU "16000000")

SET(CMAKE_C_COMPILER avr-gcc)
SET(CMAKE_CXX_COMPILER avr-g++)

SET(CMAKE_C_FLAGS "-mmcu=${MCU} -DF_CPU=${F_CPU} -Os")
SET(CMAKE_C_LINK_FLAGS "-mmcu=${MCU}")

#set(${CMAKE_PROJECT_NAME}_PORT /dev/ttyACM0)

SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set(SOURCE_FILES main.c led.c led.h lm75.c lm75.h uart_int.c uart_int.h i2c.c i2c.h esp8266.c esp8266.h)
add_executable(atmega2560test ${SOURCE_FILES})