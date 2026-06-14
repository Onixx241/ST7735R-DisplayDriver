
#include <stdint.h>

#ifndef ST7735R_H
#define ST7735R_H
#endif

//TODO: IMPLEMENT MADCTL, Memory data access control and memory write color set commands

typedef struct
{
	void* SPIContext;

	void (*SendCommand)(uint8_t cmd);
	void (*SendData)(uint8_t cmd);
	void (*SetDataCommandPinState)(uint8_t state);
	void (*SetTFTChipSelectPinState)(uint8_t state);
	void (*SetSDChipSelectPinState)(uint8_t state);
	void (*SetChipResetPinState)(uint8_t state);
	void (*Delay)(int ms);

	//for testing
	void (*HalTransmit)(uint8_t command);
} McuContext;


int InitializeDriver(McuContext *desiredSPI); //maybe make this return enum

void NoOperation(McuContext *desiredSPI);
void SoftwareReset(McuContext *desiredSPI);

void SendSleepOut(McuContext *desiredSPI);
void SendSleepIn(McuContext *desiredSPI);

void TurnDisplayOn(McuContext *desiredSPI);
void TurnDisplayOff(McuContext *desiredSPI);

void InversionOn(McuContext *desiredSPI);
void TurnInversionOff(McuContext *desiredSPI);

void TurnPartialModeOff(McuContext *desiredSPI);
void TurnPartialModeOn(McuContext *desiredSPI);

void SetTearingModeOn(McuContext *desiredSPI, int mode);
void SetTearingModeOff(McuContext *desiredSPI);

void SetIdleModeOn(McuContext *desiredSPI);
void SetIdleModeOff(McuContext *desiredSPI);

void SetBrightness(McuContext *desiredSPI, int brightness);

void SetColumnAddress(McuContext *desiredSPI, uint8_t ColumnData[]);
void SetRowAddress(McuContext *desiredSPI, uint8_t RowData[]);

void WriteToMemory(McuContext *desiredSPI, uint8_t data[]);

void CycleReset();

