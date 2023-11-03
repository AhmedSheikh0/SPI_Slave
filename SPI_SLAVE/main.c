/*
 * main.c
 *
 *  Created on: Oct 30, 2023
 *      Author: AHMED
 */


#include "LIB/STD_TYPES.h"

#include "HAL/LCD2/LCD_Interface.h"
#include "HAL/KeyPad/KPD_Interface.h"


#include "MCAL/DIO/DIO_Interface.h"
#include "MCAL/Port/Port_Interface.h"
#include "MCAL/ADC/NTI_ADC_Interface.h"
#include "MCAL/GIE/GIE_Interface.h"
#include "MCAL/SPI/SPI_Interface.h"
#include "MCAL/TMR1/TMR1_Interface.h"

#define DELAY_TIME		4.8f
#define EXIN_PORT_PIN	DIO_u8PORTC, DIO_u8PIN_0
#define SENS_PORT_PIN	DIO_u8PORTC, DIO_u8PIN_1

u8 volatile TimerFlag = 0;
u8 volatile SPIFlag = 1;
u8 volatile TimerCounter = 0;

u8 volatile ADC_Read = 0;

// SLAVE

void Data_Read()
{
	SPIFlag = 1;
	TimerCounter = 0;
}

void Time_Fun()
{
	TimerCounter++;

	if( TimerCounter == ( DELAY_TIME * 10 ))
	{
		TimerCounter = 0;
		TimerFlag = 1;
	}
}

// SLAVE

void ADC_READ_DATA()
{
	ADC_Read = ADC_u16ReadADCInMV()/10;
	LCD_voidGoToPosition(1,0);
	LCD_voidWriteIntData(ADC_Read);
	ADC_voidStartInterruptConversion(0);
}

int main(void)
{

	PORT_voidInit();
	LCD_voidInit();
	GIE_voidEnable();

	ADC_SetCallback(ADC_READ_DATA);
	ADC_voidInit();
	ADC_voidEnable();

	SPI_voidCallBack(Data_Read);
	SPI_voidSlaveInit();

	TMR1_voidTimer1CTCSetCallBack(Time_Fun);
	TMR1_voidInit();

	LCD_voidGoToPosition(0,0);
	LCD_voidWriteString((u8*)"Slave Screen.");
	LCD_voidGoToPosition(1,0);


	ADC_voidInterrputEnable();
	ADC_voidStartInterruptConversion(0);



	while(1)
	{
		DIO_u8SetPinValue(EXIN_PORT_PIN, DIO_u8PIN_HIGH);


		if( SPIFlag == 1 )
		{
			SPIFlag = 0;
		}

		if( ADC_Read >= 40)
		{
			SPI_voidTransmit(ADC_Read);
			DIO_u8SetPinValue(EXIN_PORT_PIN, DIO_u8PIN_LOW);
			DIO_u8SetPinValue(SENS_PORT_PIN, DIO_u8PIN_LOW);
		}
		else if( TimerFlag == 1)
		{
			SPI_voidTransmit(ADC_Read);
			TimerFlag = 0;
		}
		else
		{
			DIO_u8SetPinValue(SENS_PORT_PIN, DIO_u8PIN_HIGH);
		}


	}

	return 0;
}
