#include "spi.h"


void spi_init() {
  // prepare PORTB: 
  //  MOSI as output (PIN5)
  //  MISO as input  (PIN6)     
  //  SCK as output  (PIN7)
  //  CS  as output  (on SPI_CS)
  DDRB|=_BV(PB5) |_BV(PB3);

  
  // setup SPI as master, clock rate = f/128, sample on trailing edge
  // interrupt
  SPCR = _BV(SPE)| _BV(MSTR)|_BV(CPOL)|_BV(CPHA)|_BV(SPR1)|_BV(SPR0)| _BV(SPIE);
}


// Write to the SPI bus (MOSI pin) and also receive (MISO pin)
uint8_t spi_transfer(uint8_t data) {
    
    SPDR = data;
    /*
     * The following NOP introduces a small delay that can prevent the wait
     * loop form iterating when running at the maximum speed. This gives
     * about 10% more speed, even if it seems counter-intuitive. At lower
     * speeds it is unnoticed.
     */
    asm volatile("nop");
    while (!(SPSR & _BV(SPIF))) ; // wait
    return SPDR;
  }