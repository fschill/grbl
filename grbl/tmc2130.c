#include "tmc2130.h"
#include "spi.h"
#include "TMC2130_registers.h"


// write to a register
uint8_t tmc_write_REG(volatile uint8_t *cs_port, uint8_t cs_pin, uint8_t address, uint32_t data)
{
  //digitalWrite(_csPin, LOW);
  *cs_port &= ~_BV(cs_pin); 
  // write address
  int _status = spi_transfer(address|TMC_WRITE);

  // write data
  spi_transfer((data>>24UL)&0xFF);
  spi_transfer((data>>16UL)&0xFF);
  spi_transfer((data>> 8UL)&0xFF);
  spi_transfer((data>> 0UL)&0xFF);

  //digitalWrite(_csPin, HIGH);
  *cs_port |= _BV(cs_pin); 

  return _status;
}


//////////
// IHOLD_IRUN
//////////

uint8_t tmc_set_IHOLD_IRUN(volatile uint8_t *cs_port, uint8_t cs_pin, uint8_t ihold, uint8_t irun, uint8_t iholddelay)
{
  uint32_t data;
  // adding ihold
  data = (( (uint32_t)ihold&TMC_IHOLD_MASK )<<TMC_IHOLD );
  // adding irun
  data |= (( (uint32_t)irun&TMC_IRUN_MASK )<<TMC_IRUN );
  // adding iholddelay
  data |= (( (uint32_t)iholddelay&TMC_IHOLDDELAY_MASK )<<TMC_IHOLDDELAY );

  // writing data
  int _status = tmc_write_REG(cs_port, cs_pin, TMC_REG_IHOLD_IRUN, data);

  return _status;
}



void tmc_init(volatile uint8_t *cs_port, uint8_t cs_pin) {

    // initialisation example from datasheet
    // Chopconf: TOFF=3, HSTRT=4, HEND=1, TBL=2, CHM=0 (spreadCycle)
    tmc_write_REG(cs_port, cs_pin, TMC_REG_CHOPCONF, 0x000100C3);

    // I hold, I run
    tmc_set_IHOLD_IRUN(cs_port, cs_pin, 5, 8, 6);
    
    //  TPOWERDOWN=10: Delay before power down in stand still
    tmc_write_REG(cs_port, cs_pin, TMC_REG_TPOWERDOWN, 0x0000000A);

    
    // EN_PWM_MODE=1 enables stealthChop (with default PWM_CONF)
    tmc_write_REG(cs_port, cs_pin, TMC_REG_GCONF, 0x00000004);

    // TPWM_THRS=500 yields a switching velocity about 35000 = ca. 30RPM
    tmc_write_REG(cs_port, cs_pin, TMC_REG_TPWMTHRS, 0x000001F4);
    
    // PWM_CONF: AUTO=1, 2/1024 Fclk, Switch amplitude limit=200, Grad=1
    tmc_write_REG(cs_port, cs_pin, TMC_REG_PWMCONF, 0x000401C8);
    
}

void tmc_init_all(void) {
    // set all chip selects to high
    CS1_PORT |= _BV(CS1_PIN);
    CS2_PORT |= _BV(CS2_PIN);
    CS3_PORT |= _BV(CS3_PIN);
    CS4_PORT |= _BV(CS4_PIN);

    // configure SPI CS pins as output
    CS1_DDR |= _BV(CS1_PIN);
    CS2_DDR |= _BV(CS2_PIN);
    CS3_DDR |= _BV(CS3_PIN);
    CS4_DDR |= _BV(CS3_PIN);
    
    
    tmc_init(&CS1_PORT, CS1_PIN);
    tmc_init(&CS2_PORT, CS2_PIN);
    
    
}