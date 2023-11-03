/*
 * SPI_Interface.h
 *
 *  Created on: Oct 1, 2023
 *      Author: AHMED
 */

#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

void SPI_voidMasterInit(void);
void SPI_voidSlaveInit(void);

u8 SPI_u8Receieve();

void SPI_voidTransmit(u8 Copy_u8Data);

u8 SPI_u8TransReceive( u8 Copy_u8Data );

void SPI_voidCallBack( void (*Ptr)(void) );

#endif 
