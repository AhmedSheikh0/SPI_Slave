/*
 * SPI_Interface.h
 *
 *  Created on: Oct 1, 2023
 *      Author: AHMED
 */

#ifndef SPI_REGISTER_H_
#define SPI_REGISTER_H_

#define SPCR 		*((volatile u8 *) 0x2D)	// SPI Control Register
/* SPCR Pins */
#define SPCR_SPIE		7	//SPI Interrupt Enable
#define SPCR_SPE		6	//SPI Enable
#define SPCR_DORD		5
#define SPCR_MSTR		4	// Master Bit
#define SPCR_CPOL		3
#define SPCR_CPHA		2
#define SPCR_SPR1		1	// Prescaler Bit 1
#define SPCR_SPR0		0	// Prescaler Bit 1

#define SPSR 		*((volatile u8 *) 0x2E) // SPI Status Register
/* SPSR bits */
#define SPSR_SPIF		7 	// SPI Interrupt Flag
#define SPSR_WCOL		6
#define SPSR_SPI2X		0	// Prescaler Bit 2

#define SPDR		*((volatile u8 *) 0x2F) // SPI Data Register
#define SPDR_MSB	7
#define SPDR_LSB	0



#endif
