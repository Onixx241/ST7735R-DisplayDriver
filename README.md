# STM32 ST7735R Display Driver

[![Language: C](https://img.shields.io/badge/language-C-blue.svg)]()
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)]()
[![Platform: STM32](https://img.shields.io/badge/platform-STM32-lightgrey.svg)]()

## About
Platform agnostic lightweight C Driver for ST7735R based LCD's

## Usage

Implement Methods then set them in a new McuContext struct.
```
McuContext MCU =
	{
			.SPIContext = &hspi1,
			.HalTransmit = HalTransmit,
			.SetDataCommandPinState = SetDataCommandPinState,
			.SetTFTChipSelectPinState = SetTFTChipSelectPinState,
			.SetSDChipSelectPinState = SetSDChipSelectPinState,
			.SetChipResetPinState = SetChipResetPinState,
			.SendCommand = SendCommand,
			.SendData = SendData,
			.Delay = Delay
	};
```
- SPIContext: Reference to your desired SPI handle
- HalTransmit: Your implemented method to transmit via SPI
- SetDataCommandPinState: Your implemented method to toggle your desired data command pin
- SetTFTChipSelectPinState: Your implemented method to toggle your desired TFT Chip Select pin
- SetSDChipSelectPinState: Your implemented method to toggle your desired SD Chip Select pin
- SendCommand: Your implemented method to send commands to the screen driver (Usually in conjunction with HalTransmit)
- SendData: Your implemented method to send data/parameters to the screen driver (Usually in conjunction with HalTransmit)
- Delay: Your implemented delay method
