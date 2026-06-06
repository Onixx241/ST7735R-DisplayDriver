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

#define InversionOn 0x21
#define InversionOff 0x20

#define PartialArea 0x30
#define PartialModeOn 0x12
#define PartialModeOff 0x13

#define GammaSet 0x26

#include "main.h"

void EnableCommandSend()
{
	DataCommand_GPIO_Port->BSRR = GPIO_BSRR_BR_10; //Command send active low, Data when high
}
void EnableDataSend()
{
	DataCommand_GPIO_Port->BSRR = GPIO_BSRR_BS_10;
}

void SendCommand(SPI_HandleTypeDef *desiredSPI, uint8_t command)
{

	SelectTFT();
	EnableCommandSend();

	HAL_SPI_Transmit(desiredSPI, &command, 1, 100);// change this to bare metal code

	UnselectTFT();

}
void SendDataParameter(SPI_HandleTypeDef *desiredSPI, uint8_t parameter)
{

	SelectTFT();
	EnableDataSend();

	HAL_SPI_Transmit(desiredSPI, &parameter, 1, 100);// change this to bare metal code

	UnselectTFT();

}
void SendCommandWithParameters(SPI_HandleTypeDef *desiredSPI, uint8_t command, uint8_t parameters[])
{
	SendCommand(desiredSPI, command);


	for(int i = 0; i <= sizeof(parameters); i++)
	{
		SendDataParameter(desiredSPI, parameters[i]);
	}

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

void TurnInversionOn(SPI_HandleTypeDef *desiredSPI)
{
	SendCommand(desiredSPI, InversionOn);
}
void TurnInversionOff(SPI_HandleTypeDef *desiredSPI)
{
	SendCommand(desiredSPI, InversionOff);
}

void TurnPartialModeOn(SPI_HandleTypeDef *desiredSPI)
{
	SendCommand(desiredSPI, PartialModeOn );
}
void TurnPartialModeOff(SPI_HandleTypeDef *desiredSPI)
{
	SendCommand(desiredSPI, PartialModeOff );
}

void GammaSetTEST(SPI_HandleTypeDef *desiredSPI)//implement curves 1 2 3 4 , in one method?
{
	uint8_t Params[] = {0x01};
	SendCommandWithParameters(desiredSPI, GammaSet, Params);

	HAL_Delay(2000);

	uint8_t Paramss[] = {0x02};
	SendCommandWithParameters(desiredSPI, GammaSet, Paramss);

	HAL_Delay(2000);

	uint8_t Paramsss[] = {0x04};
	SendCommandWithParameters(desiredSPI, GammaSet, Paramsss);

	HAL_Delay(2000);

	uint8_t Paramssss[] = {0x08};
	SendCommandWithParameters(desiredSPI, GammaSet, Paramssss);

	HAL_Delay(2000);
}

//End of Commands


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

