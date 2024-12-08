/*
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License.
 If not, see <http://www.gnu.org/licenses/>.

 
 Although this file is named softSPI I tried to use hardware SPI here.
 */
 
#include <SPI.h>
#include "iface_nrf24l01.h"
#define NOP() __asm__ __volatile__("nop")
void  asm_delay(const uint8_t d){
	  uint8_t dd = d;
	  do NOP(); while(dd--);
}
//#define my_delay(dt)  asm_delay((dt*4.0) - 3 );



SPIClass SPIH(HSPI);
void SPIH_Begin()
{
  SPIH.begin(SCK_pin, MISO_pin, MOSI_pin, CS_pin);
}

void trb__(){
  SPIH.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));
  digitalWrite(CS_pin, LOW);
  asm_delay(10);
  //delayMicroseconds(1);
}

void tre__(){
  digitalWrite(CS_pin, HIGH);
  asm_delay(10);
  //delayMicroseconds(1);
  SPIH.endTransaction();
}

/*uint8_t Read_Packet(uint8_t *data, uint8_t length) 
{
  uint8_t status;
  uint8_t* current = reinterpret_cast<uint8_t*>(data);
  CS_off;
  status = spi_write(R_RX_PAYLOAD);
  while ( length-- ) {
    *current++ = spi_read();
  }
  CS_on;
  return status;
}*/

uint8_t spi_write(uint8_t command) 
{
    return SPIH.transfer(command);
}

/*void spi_write_address(uint8_t address, uint8_t data) 
{
    CS_off;
    spi_write(address);
    NOP();
    spi_write(data);
    CS_on;
}*/

// read one byte from MISO
uint8_t spi_read()
{
    return SPIH.transfer(0xFF);
}

/*uint8_t spi_read_address(uint8_t address) 
{
    uint8_t result;
    CS_off;
    spi_write(address);
    result = spi_read();
    CS_on;
    return(result);
}*/
