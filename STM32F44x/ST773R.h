
#define CS_TFT_LOW 1

#ifndef SRC_ST773R_H_
#define SRC_ST773R_H_
#endif



int PowerOn();
void CycleReset();


void SendCommand();
void SendData();

void SendSleepOut();
void SendSleepIn();


enum LIBRARY_STATUS
{
	OPERATION_OK,
	OPERATION_FAILED
};
