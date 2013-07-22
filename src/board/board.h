/*
    ChibiOS/RT - Copyright (C) 2006-2013 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef _BOARD_H_
#define _BOARD_H_

/*
 * Board identifier.
 */
#define BOARD_NANIBOX_COM__KAITENBOX_V01
#define BOARD_NAME              "naniBox.com / kaitenBox_v01"

/*
 * Board oscillators-related settings.
 */
#if !defined(STM32_LSECLK)
#define STM32_LSECLK                32768
#endif

#if !defined(STM32_HSECLK)
#define STM32_HSECLK                16000000
#endif

/*
 * Board voltages.
 * Required for performance limits calculation.
 */
#define STM32_VDD                   300

/*
 * MCU type, supported types are defined in ./os/hal/platforms/hal_lld.h.
 */
#define STM32F10X_MD

/*
 * IO pins assignments.
 */
#define GPIOA_BTN1                      0
#define GPIOA__PA01                     1
#define GPIOA__PA02                     2
#define GPIOA__PA03                     3
#define GPIOA__PA04                     4
#define GPIOA__PA05                     5
#define GPIOA_ENC1_A                    6
#define GPIOA_ENC1_B                    7

#define GPIOA_LED1                      8
#define GPIOA_USART1_TX                 9
#define GPIOA_USART1_RX                 10
#define GPIOA_LED2                      11
#define GPIOA_USART1_VALID              12
#define GPIOA_SWDAT                     13
#define GPIOA_SDCLK                     14
#define GPIOA_ENC3_A                    15

#define GPIOB_ENC1_PWR                  0
#define GPIOB__PB01                     1
#define GPIOB__PB02                     2
#define GPIOB_ENC3_B                    3
#define GPIOB_ENC3_PWR                  4
#define GPIOB_ENC2_PWR                  5
#define GPIOB_ENC2_A                    6
#define GPIOB_ENC2_B                    7

#define GPIOB__PB08                     8
#define GPIOB__PB09                     9
#define GPIOB__PB10                     10
#define GPIOB__PB11                     11
#define GPIOB__PB12                     12
#define GPIOB__PB13                     13
#define GPIOB__PB14                     14
#define GPIOB__PB15                     15

#define GPIOC__PC13                     13
#define GPIOB__PC14                     14
#define GPIOB__PC15                     15

#define GPIOD_OSC_IN                    0
#define GPIOD_OSC_OUT                   1



/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 *
 * The digits have the following meaning:
 *   0 - Analog input.
 *   1 - Push Pull output 10MHz.
 *   2 - Push Pull output 2MHz.
 *   3 - Push Pull output 50MHz.
 *   4 - Digital input.
 *   5 - Open Drain output 10MHz.
 *   6 - Open Drain output 2MHz.
 *   7 - Open Drain output 50MHz.
 *   8 - Digital input with PullUp or PullDown resistor depending on ODR.
 *   9 - Alternate Push Pull output 10MHz.
 *   A - Alternate Push Pull output 2MHz.
 *   B - Alternate Push Pull output 50MHz.
 *   C - Reserved.
 *   D - Alternate Open Drain output 10MHz.
 *   E - Alternate Open Drain output 2MHz.
 *   F - Alternate Open Drain output 50MHz.
 * Please refer to the STM32 Reference Manual for details.
 */

/*
 * Port A setup.
PA00    :   BTN1            Input Floating
PA01    :   --
PA02    :   --
PA03    :   --

PA04    :   --
PA05    :   --
PA06    :   ENC1_A          TIM3_CH1    / AF Input Floating
PA07    :   ENC1_B          TIM3_CH2    / AF Input Floating



PA08    :   LED1            TIM1_CH1    / AF Output PP 
PA09    :   USART1_TX       USART1_TX   / AF Output PP 
PA10    :   USART1_RX       USART1_RX   / AF Input Floating
PA11    :   LED2            TIM1_CH4    / AF Output PP 

PA12    :   USART1_VALID    Input Floating
PA13    :   SWDAT           SWDAT
PA14    :   SWCLK           SWCLK
PA15    :   ENC3_A          TIM2_CH1    / AF Input Floating

 */
#define VAL_GPIOACRL            0x44888884      /*  PA7...PA0 */
#define VAL_GPIOACRH            0x4444B4BB      /* PA15...PA8 */
#define VAL_GPIOAODR            0xFFFFFFFF

/*
 * Port B setup.
PB00    :   ENC1_PWR        Output HIGH
PB01    :   --
PB02    :   --
PB03    :   ENC3_B          TIM2_CH1    / AF Input Floating
PB04    :   ENC3_PWR        Output HIGH
PB05    :   ENC2_PWR        Output HIGH
PB06    :   ENC2_A          TIM4_CH1    / AF Input Floating
PB07    :   ENC2_B          TIM4_CH2    / AF Input Floating

PB08    :   --
PB09    :   --
PB10    :   --
PB11    :   --
PB12    :   --
PB13    :   --
PB14    :   --
PB15    :   --

 */
#define VAL_GPIOBCRL            0x44334883      /*  PB7...PB0 */
#define VAL_GPIOBCRH            0x88888888      /* PB15...PB8 */
#define VAL_GPIOBODR            0xFFFFFFFF

/*
 * Port C setup.
PC13    :   --
PC14    :   --
PC15    :   --
 */
#define VAL_GPIOCCRL            0x88888888      /*  PC7...PC0 */
#define VAL_GPIOCCRH            0x88888888      /* PC15...PC8 */
#define VAL_GPIOCODR            0xFFFFFFFF

/*
 * Port D setup.
PD00    :   OSC_IN
PD01    :   OSC_OUT
 */
#define VAL_GPIODCRL            0x88888844      /*  PD7...PD0 */
#define VAL_GPIODCRH            0x88888888      /* PD15...PD8 */
#define VAL_GPIODODR            0xFFFFFFFF

/*
 * Port E setup.
 */
#define VAL_GPIOECRL            0x88888888      /*  PE7...PE0 */
#define VAL_GPIOECRH            0x88888888      /* PE15...PE8 */
#define VAL_GPIOEODR            0xFFFFFFFF

/*
 * USB bus activation macro, required by the USB driver.
 */
#define usb_lld_connect_bus(usbp) palClearPad(GPIOC, GPIOC_USB_DISC)

/*
 * USB bus de-activation macro, required by the USB driver.
 */
#define usb_lld_disconnect_bus(usbp) palSetPad(GPIOC, GPIOC_USB_DISC)

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* _BOARD_H_ */
