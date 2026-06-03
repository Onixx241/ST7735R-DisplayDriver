/*
 * ST773R.c
 *
 *  Created on: Jun 2, 2026
 *      Author: onixt
 */

//commandz
#define SleepOut 0x11
#define SleepIn 0x10
#define DisplayOn 0x29
#define DisplayOff 0x28

#include "main.h"

void EnableCommandSend()
{
	DataCommand_GPIO_Port->BSRR = GPIO_BSRR_BR_10; //Command send active low, Data when high
}
void EnableDataSend()
{
	DataCommand_GPIO_Port->BSRR = GPIO_BSRR_BS_10;
}



void SelectTFT()
{
	TFT_ChipSelect_GPIO_Port->BSRR = GPIO_BSRR_BR_8; //Select active low
}
void UnselectTFT()
{
	TFT_ChipSelect_GPIO_Port->BSRR = GPIO_BSRR_BS_8;
}

void SelectSD()
{
	SD_ChipSelect_GPIO_Port->BSRR = GPIO_BSRR_BR_10; //Select active low
}
void UnselectSD()
{
	SD_ChipSelect_GPIO_Port->BSRR = GPIO_BSRR_BS_10;
}

//Commmands

void SendSleepOut(SPI_HandleTypeDef *desiredSPI)
{
	SendCommand(desiredSPI, SleepOut);
	HAL_Delay(120);
}
void SendSleepIn(SPI_HandleTypeDef *desiredSPI)
{
	SendCommand(desiredSPI, SleepIn);
	HAL_Delay(120);
}

void TurnDisplayOn(SPI_HandleTypeDef *desiredSPI)
{
	SendCommand(desiredSPI, DisplayOn);
}
void TurnDisplayOff(SPI_HandleTypeDef *desiredSPI)
{
	SendCommand(desiredSPI, DisplayOff);
}


//End of Commands

void SendCommand(SPI_HandleTypeDef *desiredSPI, uint8_t command)
{

	SelectTFT();
	EnableCommandSend();

	HAL_SPI_Transmit(desiredSPI, &command, 1, 100);// change this to bare metal code

	UnselectTFT();

}

void CycleReset()
{

	ChipReset_GPIO_Port->BSRR = GPIO_BSRR_BR_5;
	HAL_Delay(120);
	ChipReset_GPIO_Port->BSRR = GPIO_BSRR_BS_5;
	HAL_Delay(120); // is hal delay good? or should i implement my own delay

}

int InitializeDriver(SPI_HandleTypeDef *desiredSPI)
{
	CycleReset();
	SendSleepOut(desiredSPI); //chip starts in sleepin mode

	return 1; //write init check
}

enum LIBRARY_STATUS
{
	OPERATION_OK,
	OPERATION_FAILED
};

