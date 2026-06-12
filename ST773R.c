/*
 * ST773R.c
 *
 *  Created on: Jun 2, 2026
 *      Author: onixt
 */

//Write Commands ONLY
#define Nop 0x00
#define SWReset 0x01

#define SleepOut 0x11
#define SleepIn 0x10

#define DisplayOn 0x29
#define DisplayOff 0x28

#define InversionOn 0x21
#define InversionOff 0x20

#define PartialArea 0x30
#define PartialModeOn 0x12
#define NormalDisplayModeOn 0x13

#define GammaSet 0x26

#define IdleModeOn 0x39
#define IdleModeOff 0x38

#define TearingModeOn 0x35
#define TearingModeOff 0x34

#define ColumnAddressSet 0x2A
#define RowAddressSet 0x2B

#define MemoryWrite 0x2C


//change this to whatever gpio alias/port you're using
#define DataCommand DataCommand_GPIO_Port
#define TFT_CS TFT_ChipSelect_GPIO_Port
#define SD_CS SD_ChipSelect_GPIO_Port
#define Reset ChipReset_GPIO_Port
//

//Change this to whatever pins you're using

#define DataCommandPinLow GPIO_BSRR_BR_10
#define DataCommandPinHigh GPIO_BSRR_BS_10

#define TFTChipSelectLow GPIO_BSRR_BR_8
#define TFTChipSelectHigh GPIO_BSRR_BS_8

#define SDChipSelectLow GPIO_BSRR_BR_10
#define SDChipSelectHigh GPIO_BSRR_BS_10  //test if nested macros work later
//

//for util
#define ARRAY_LENGTH(x) (sizeof(x) / sizeof((x)[0]))


#include "main.h"

void EnableCommandSend()
{
	DataCommand_GPIO_Port->BSRR = DataCommandPinLow; //Command send active low, Data when high
}
void EnableDataSend()
{
	DataCommand_GPIO_Port->BSRR = DataCommandPinHigh;
}

void SelectTFT()
{
	TFT_ChipSelect_GPIO_Port->BSRR = TFTChipSelectLow; //Select active low
}
void UnselectTFT()
{
	TFT_ChipSelect_GPIO_Port->BSRR = TFTChipSelectHigh;
}

void SelectSD()
{
	SD_ChipSelect_GPIO_Port->BSRR = SDChipSelectLow; //Select active low
}
void UnselectSD()
{
	SD_ChipSelect_GPIO_Port->BSRR = SDChipSelectHigh;
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


	for(int i = 0; i <= ARRAY_LENGTH(parameters); i++)
	{
		SendDataParameter(desiredSPI, parameters[i]);
	}

}


//Commmands

void NoOperation(SPI_HandleTypeDef *desiredSPI)
{
	SendCommand(desiredSPI, Nop);
}

void SoftwareReset(SPI_HandleTypeDef *desiredSPI)
{
	SendCommand(desiredSPI, SWReset);
}

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
	SendCommand(desiredSPI, NormalDisplayModeOn );
}

void SetIdleModeOn(SPI_HandleTypeDef *desiredSPI)
{
	SendCommand(desiredSPI, IdleModeOn);
}
void SetIdleModeOff(SPI_HandleTypeDef *desiredSPI)
{
	SendCommand(desiredSPI, IdleModeOff);
}

void SetTearingModeOn(SPI_HandleTypeDef *desiredSPI, int mode)
{
	switch(mode)
	{
	case 0:
		SendCommandWithParameters(desiredSPI, TearingModeOn, (uint8_t){0x00} );
		break;
	case 1:
		SendCommandWithParameters(desiredSPI, TearingModeOn, (uint8_t){0x01} ); //v and h blanking
		break;
	}
}
void SetTearingModeOff(SPI_HandleTypeDef *desiredSPI)
{
	SendCommand(desiredSPI, TearingModeOff);
}

void SetBrightness(SPI_HandleTypeDef *desiredSPI, int brightness) //1-4
{
	switch(brightness)
	{
	case 1:
		SendCommandWithParameters(desiredSPI, GammaSet, (uint8_t){0x01});
		break;
	case 2:
		SendCommandWithParameters(desiredSPI, GammaSet, (uint8_t){0x02});
		break;
	case 3:
		SendCommandWithParameters(desiredSPI, GammaSet, (uint8_t){0x04});
		break;
	case 4:
		SendCommandWithParameters(desiredSPI, GammaSet, (uint8_t){0x08});
		break;
	}
}

void SetColumnAddress(SPI_HandleTypeDef *desiredSPI, uint8_t ColumnData[])
{
	SendCommandWithParameters(desiredSPI, ColumnAddressSet, ColumnData);
}

void SetRowAddress(SPI_HandleTypeDef *desiredSPI, uint8_t RowData[])
{
	SendCommandWithParameters(desiredSPI, RowAddressSet, RowData);
}

void WriteToMemory(SPI_HandleTypeDef *desiredSPI, uint8_t data[])
{
	SendCommandWithParameters(desiredSPI, MemoryWrite, data);
}
//End of Commands


void CycleReset()
{

	ChipReset_GPIO_Port->BSRR = GPIO_BSRR_BR_5;
	HAL_Delay(120);
	ChipReset_GPIO_Port->BSRR = GPIO_BSRR_BS_5;
	HAL_Delay(120);
}

int InitializeDriver(SPI_HandleTypeDef *desiredSPI)
{

	CycleReset();
	SendSleepOut(desiredSPI); //chip starts in sleepin mode

	return 1; //write init check
}

enum LIBRARY_STATUS //unusedd, FOR NOW
{
	OPERATION_OK,
	OPERATION_FAILED
};

