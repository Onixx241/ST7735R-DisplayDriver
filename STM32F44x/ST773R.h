
#ifndef SRC_ST773R_H_
#define SRC_ST773R_H_
#endif



int InitializeDriver(SPI_HandleTypeDef *desiredSPI); //maybe make this return enum

void SendCommand(SPI_HandleTypeDef *desiredSPI, uint8_t command);

void SendSleepOut(SPI_HandleTypeDef *desiredSPI);
void SendSleepIn(SPI_HandleTypeDef *desiredSPI);

void TurnDisplayOn(SPI_HandleTypeDef *desiredSPI);
void TurnDisplayOff(SPI_HandleTypeDef *desiredSPI);

void CycleReset(void);

void SelectTFT(void);
void UnselectTFT(void);

void SelectSD(void); // for 1.8 inch adafruit lcd
void UnselectSD(void);

void EnableCommandSend(void);
void EnableDataSend(void);
