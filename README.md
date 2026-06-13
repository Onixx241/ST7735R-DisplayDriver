# STM32 ST7735R Display Driver

[![Language: C](https://img.shields.io/badge/language-C-blue.svg)]()
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)]()
[![Platform: STM32](https://img.shields.io/badge/platform-STM32-lightgrey.svg)]()

## About
Lightweight WIP C driver for STM32 Nucleo Boards (can be repurposed for other boards just fork and open a PR)

## Usage
Edit Macros in ST773R to match your ports/pins and for communication set your desired SPI in function calls.
```
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
#define SDChipSelectHigh GPIO_BSRR_BS_10
 ```
