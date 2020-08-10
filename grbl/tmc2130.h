#ifndef TMC2130_H
#define TMC2130_H

#include "grbl.h"


#define CS1_PORT PORTB
#define CS1_DDR  DDRB
#define CS1_PIN    2  //     17      64  //chip select

#define CS2_PORT PORTC
#define CS2_DDR  DDRC
#define CS2_PIN    1  //     17      64  //chip select

#define CS3_PORT PORTC
#define CS3_DDR  DDRC
#define CS3_PIN    2  //     17      64  //chip select

#define CS4_PORT PORTC
#define CS4_DDR  DDRC
#define CS4_PIN    3  //     17      64  //chip select

void tmc_init_all(void);

#endif