/*
 * SPI_Program.c
 *
 *  Created on: Oct 1, 2023
 *      Author: AHMED
 */

#include "../../LIB/STD_Types.h"
#include "../../LIB/Bit_Math.h"

#include "SPI_Register.h"
#include "SPI_Config.h"
#include "SPI_Private.h"
#include "SPI_Interface.h"

void (*Private_voidSPIFunc)(void) = NULL;

void SPI_voidMasterInit(void)
{
	/* Initialize Master */
	Set_Bit(SPCR, SPCR_MSTR);

#if 	INTERRUPT_MODE == ENABLE_INTERRUPT
	Set_Bit(SPCR, SPCR_SPIE);
#elif	INTERRUPT_MODE == DISABLE_INTERRUPT
	Clear_Bit(SPCR, SPCR_SPIE);
#else
#endif


#if 	DATA_ORDER == LSB_FIRST
	Set_Bit(SPCR, SPCR_DORD);
#elif	DATA_ORDER == MSB_FIRST
	Clear_Bit(SPCR, SPCR_DORD);
#else
#endif


#if 	CLOCK_POLARITY == IDLE_LOW
	Clear_Bit(SPCR, SPCR_CPOL);
#elif	CLOCK_POLARITY == IDLE_HIGH
	Set_Bit(SPCR, SPCR_CPOL);
#else
#endif


#if 	CLOCK_PHASE == ZERO
	Clear_Bit(SPCR, SPCR_CPHA);
#elif	CLOCK_PHASE == ONE
	Set_Bit(SPCR, SPCR_CPOL);
#else
#endif

#if 	SPI_FREQUENCY == QUARTER_FREQ
	Clear_Bit(SPCR, SPCR_SPR0);
	Clear_Bit(SPCR, SPCR_SPR1);
	Clear_Bit(SPSR, SPSR_SPI2X);
#elif	SPI_FREQUENCY == HALF_FREQ
	Clear_Bit(SPCR, SPCR_SPR0);
	Clear_Bit(SPCR, SPCR_SPR1);
	Set_Bit(SPSR, SPSR_SPI2X);
#else
#endif


	//	/* Prescaler ( /16 )  */
	//	Set_Bit(SPCR, SPCR_SPR0);
	//	Clear_Bit(SPCR, SPCR_SPR1);
	//	Clear_Bit(SPSR, SPSR_SPI2X);

	/* SPI Enable */
	Set_Bit(SPCR,SPCR_SPE);

}

void SPI_voidSlaveInit(void)
{
	/* Initialize Slave */
	Clear_Bit(SPCR, SPCR_MSTR);


#if 	INTERRUPT_MODE == ENABLE_INTERRUPT
	Set_Bit(SPCR, SPCR_SPIE);
#elif	INTERRUPT_MODE == DISABLE_INTERRUPT
	Clear_Bit(SPCR, SPCR_SPIE);
#else
#endif


#if 	DATA_ORDER == LSB_FIRST
	Set_Bit(SPCR, SPCR_DORD);
#elif	DATA_ORDER == MSB_FIRST
	Clear_Bit(SPCR, SPCR_DORD);
#else
#endif


	/* SPI Enable */
	Set_Bit(SPCR,SPCR_SPE);
}

u8 SPI_u8TransReceive( u8 Copy_u8Data )
{
	/* Send Data */
	SPDR = Copy_u8Data;

	/* Wait until transfer complete */
	while( Get_Bit(SPSR, SPSR_SPIF) == 0 );

	return SPDR;
}


u8 SPI_u8Receieve()
{
	return SPDR;
}

void SPI_voidTransmit(u8 Copy_u8Data)
{
	SPDR = Copy_u8Data;
}


void SPI_voidCallBack( void (*Ptr)(void) )
{
	if (Ptr != NULL)
	{
		Private_voidSPIFunc = Ptr;
	}
}


void __vector_12(void)__attribute__((signal,used,externally_visible));
void __vector_12(void)
{
	if( Private_voidSPIFunc != NULL )
	{
		Private_voidSPIFunc();
	}
}


