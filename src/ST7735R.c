/*
 * ST773R.c
 *
 *  Created on: Jun 2, 2026
 *      Author: onixt
 */
//Write Commands ONLY

#include "ST7735R.h"

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

McuContext* MCU = 0;
//for util
#define ARRAY_LENGTH(x) (sizeof(x) / sizeof((x)[0]))


static void EnableCommandSend()
{
	MCU->SetDataCommandPinState(0);
}
static void EnableDataSend()
{
	MCU->SetDataCommandPinState(1);
}

static void SelectTFT()
{
	MCU->SetTFTChipSelectPinState(0);
}
static void UnselectTFT()
{
	MCU->SetTFTChipSelectPinState(1);
}

static void SelectSD()
{
	MCU->SetSDChipSelectPinState(0);
}
static void UnselectSD()
{
	MCU->SetSDChipSelectPinState(1);
}


static void SendCommand(McuContext *desiredSPI, uint8_t command)
{

	SelectTFT();
	EnableCommandSend();

	MCU->HalTransmit(command);

	UnselectTFT();

}


static void SendDataParameter(McuContext *desiredSPI, uint8_t parameter)
{

	SelectTFT();
	EnableDataSend();

	MCU->HalTransmit(parameter);

	UnselectTFT();

}
static void SendCommandWithParameters(McuContext *desiredSPI, uint8_t command, uint8_t parameters[])
{
	SendCommand(desiredSPI, command);


	for(int i = 0; i <= ARRAY_LENGTH(parameters); i++)
	{
		SendDataParameter(desiredSPI, parameters[i]);
	}

}


//Commmands

void NoOperation(McuContext *desiredSPI)
{
	SendCommand(desiredSPI, Nop);
}

void SoftwareReset(McuContext *desiredSPI)
{
	SendCommand(desiredSPI, SWReset);
}

void SendSleepOut(McuContext *desiredSPI)
{
	SendCommand(desiredSPI, SleepOut);
	MCU->Delay(120);
}
void SendSleepIn(McuContext *desiredSPI)
{
	SendCommand(desiredSPI, SleepIn);
	MCU->Delay(120);
}

void TurnDisplayOn(McuContext *desiredSPI)
{
	SendCommand(desiredSPI, DisplayOn);
}
void TurnDisplayOff(McuContext *desiredSPI)
{
	SendCommand(desiredSPI, DisplayOff);
}

void TurnInversionOn(McuContext *desiredSPI)
{
	SendCommand(desiredSPI, InversionOn);
}
void TurnInversionOff(McuContext *desiredSPI)
{
	SendCommand(desiredSPI, InversionOff);
}

void TurnPartialModeOn(McuContext *desiredSPI)
{
	SendCommand(desiredSPI, PartialModeOn );
}
void TurnPartialModeOff(McuContext *desiredSPI)
{
	SendCommand(desiredSPI, NormalDisplayModeOn );
}

void SetIdleModeOn(McuContext *desiredSPI)
{
	SendCommand(desiredSPI, IdleModeOn);
}
void SetIdleModeOff(McuContext *desiredSPI)
{
	SendCommand(desiredSPI, IdleModeOff);
}

void SetTearingModeOn(McuContext *desiredSPI, int mode)
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
void SetTearingModeOff(McuContext *desiredSPI)
{
	SendCommand(desiredSPI, TearingModeOff);
}

void SetBrightness(McuContext *desiredSPI, int brightness) //1-4
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

void SetColumnAddress(McuContext *desiredSPI, uint8_t ColumnData[]) //might have to change this to 16 bits
{
	SendCommandWithParameters(desiredSPI, ColumnAddressSet, ColumnData);
}

void SetRowAddress(McuContext *desiredSPI, uint8_t RowData[])
{
	SendCommandWithParameters(desiredSPI, RowAddressSet, RowData);
}

void WriteToMemory(McuContext *desiredSPI, uint8_t data[])
{
	SendCommandWithParameters(desiredSPI, MemoryWrite, data);
}

//End of Commands


void CycleReset()
{

	MCU->SetChipResetPinState(0);
	MCU->Delay(120);

	MCU->SetChipResetPinState(1);
	MCU->Delay(120);
}

int InitializeDriver(McuContext *desiredSPI)
{

	MCU = desiredSPI;

	CycleReset();
	SendSleepOut(desiredSPI); //chip starts in sleepin mode

	return 1; //write init check
}

enum LIBRARY_STATUS //unusedd, FOR NOW
{
	OPERATION_OK,
	OPERATION_FAILED
};

