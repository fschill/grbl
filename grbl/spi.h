#ifndef SPI_H
#define SPI_H

#include "grbl.h"

/** initialise SPI peripheral. The CS lines are not initialised here, need to be set up elsewhere
 */
void spi_init();

/**
* Write to the SPI bus (MOSI pin) and also receive (MISO pin)
*/
uint8_t spi_transfer(uint8_t data);



#endif