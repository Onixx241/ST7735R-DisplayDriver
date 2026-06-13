
#include <stdint.h>
#include "main.h"

#ifndef SRC_ST773R_H_
#define SRC_ST773R_H_
#endif

//TODO: IMPLEMENT MADCTL, Memory data access control and memory write color set commands

int InitializeDriver(SPI_HandleTypeDef *desiredSPI); //maybe make this return enum

void NoOperation(SPI_HandleTypeDef *desiredSPI);
void SoftwareReset(SPI_HandleTypeDef *desiredSPI);

void SendSleepOut(SPI_HandleTypeDef *desiredSPI);
void SendSleepIn(SPI_HandleTypeDef *desiredSPI);

void TurnDisplayOn(SPI_HandleTypeDef *desiredSPI);
void TurnDisplayOff(SPI_HandleTypeDef *desiredSPI);

void InversionOn(SPI_HandleTypeDef *desiredSPI);
void TurnInversionOff(SPI_HandleTypeDef *desiredSPI);

void TurnPartialModeOff(SPI_HandleTypeDef *desiredSPI);
void TurnPartialModeOn(SPI_HandleTypeDef *desiredSPI);

void SetTearingModeOn(SPI_HandleTypeDef *desiredSPI, int mode);
void SetTearingModeOff(SPI_HandleTypeDef *desiredSPI);

void SetIdleModeOn(SPI_HandleTypeDef *desiredSPI);
void SetIdleModeOff(SPI_HandleTypeDef *desiredSPI);

void SetBrightness(SPI_HandleTypeDef *desiredSPI, int brightness);

void SetColumnAddress(SPI_HandleTypeDef *desiredSPI, uint8_t ColumnData[]);
void SetRowAddress(SPI_HandleTypeDef *desiredSPI, uint8_t RowData[]);

void WriteToMemory(SPI_HandleTypeDef *desiredSPI, uint8_t data[]);

void CycleReset();

