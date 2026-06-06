
#ifndef SRC_ST773R_H_
#define SRC_ST773R_H_
#endif



int InitializeDriver(SPI_HandleTypeDef *desiredSPI); //maybe make this return enum

void EnableCommandSend();
void EnableDataSend();

void SendCommand(SPI_HandleTypeDef *desiredSPI, uint8_t command);
void SendCommandWithParameters(SPI_HandleTypeDef *desiredSPI, uint8_t command, uint8_t parameters[]);
void SendDataParameter(SPI_HandleTypeDef *desiredSPI, uint8_t parameter);

void SendSleepOut(SPI_HandleTypeDef *desiredSPI);
void SendSleepIn(SPI_HandleTypeDef *desiredSPI);

void TurnDisplayOn(SPI_HandleTypeDef *desiredSPI);
void TurnDisplayOff(SPI_HandleTypeDef *desiredSPI);
void InversionOn(SPI_HandleTypeDef *desiredSPI);
void TurnInversionOff(SPI_HandleTypeDef *desiredSPI);
void TurnPartialModeOff(SPI_HandleTypeDef *desiredSPI);
void TurnPartialModeOn(SPI_HandleTypeDef *desiredSPI);
void GammaSetTEST(SPI_HandleTypeDef *desiredSPI);

void CycleReset();

void SelectTFT();
void UnselectTFT();

void SelectSD(); // for 1.8 inch adafruit lcd
void UnselectSD();

