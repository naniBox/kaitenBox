/*
	kaitenBox / naniBox
	Copyright (c) 2013
	david morris-oliveros // dmo@nanibox.com // naniBox.com

    This file is part of kaitenBox / naniBox.

    kaitenBox / naniBox is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    kaitenBox / naniBox is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <ch.h>
#include <hal.h>
#include <chprintf.h>

static void extcb(EXTDriver *extp, expchannel_t channel)
{
	(void) extp;
	(void) channel;
	chSysLockFromIsr();
	if (palReadPad(GPIOA, GPIOA_BTN1))
		pwmEnableChannelI(&PWMD1, 3, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, 500));
	else
		pwmEnableChannelI(&PWMD1, 3, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, 9500));
	chSysUnlockFromIsr();
}

static const EXTConfig extcfg =
{
	{
		{ EXT_CH_MODE_BOTH_EDGES | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOA, extcb },
		{ EXT_CH_MODE_DISABLED, NULL },
		{ EXT_CH_MODE_DISABLED, NULL },
		{ EXT_CH_MODE_DISABLED, NULL },
		{ EXT_CH_MODE_DISABLED, NULL },
		{ EXT_CH_MODE_DISABLED, NULL },
		{ EXT_CH_MODE_DISABLED, NULL },
		{ EXT_CH_MODE_DISABLED, NULL },
		{ EXT_CH_MODE_DISABLED, NULL },
		{ EXT_CH_MODE_DISABLED, NULL },
		{ EXT_CH_MODE_DISABLED, NULL },
		{ EXT_CH_MODE_DISABLED, NULL },
		{ EXT_CH_MODE_DISABLED, NULL },
		{ EXT_CH_MODE_DISABLED, NULL },
		{ EXT_CH_MODE_DISABLED, NULL },
		{ EXT_CH_MODE_DISABLED, NULL } 
	} 
};

static PWMConfig pwmcfg =
{
	1000000, 
	1000, 
	NULL,
	{
		{ PWM_OUTPUT_ACTIVE_HIGH, NULL },
		{ PWM_OUTPUT_DISABLED, NULL },
		{ PWM_OUTPUT_DISABLED, NULL },
		{ PWM_OUTPUT_ACTIVE_HIGH, NULL } 
	}, 
	0,
#if STM32_PWM_USE_ADVANCED
	0
#endif
};

#define  TIM_ICPolarity_Rising             ((uint16_t)0x0000)
void configEnc(stm32_tim_t * timer)
{
	timer->ARR = 65535;
	timer->SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1;
	timer->CCMR1 &= (uint16_t)(((uint16_t) ~((uint16_t) TIM_CCMR1_CC1S)) & (uint16_t)(~((uint16_t) TIM_CCMR1_CC2S)));
	timer->CCMR1 |= TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0;
	timer->CCER &= (uint16_t) ~((uint16_t)(TIM_CCER_CC1P | TIM_CCER_CC1NP))	& (uint16_t) ~((uint16_t)(TIM_CCER_CC2P | TIM_CCER_CC2NP));
	timer->CCER |= (uint16_t)(TIM_ICPolarity_Rising	| (uint16_t)(TIM_ICPolarity_Rising << (uint16_t) 4));
	timer->CR1 |= TIM_CR1_CEN;
}

int main(void)
{
	halInit();
	chSysInit();
	sdStart(&SD1, NULL);
	pwmStart(&PWMD1, &pwmcfg);
	pwmEnableChannel(&PWMD1, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, 7500));
	pwmEnableChannel(&PWMD1, 3, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, 2500));

	extStart(&EXTD1, &extcfg);

	palClearPad(GPIOB, GPIOB_ENC1_PWR);


	AFIO->MAPR |= AFIO_MAPR_TIM2_REMAP_PARTIALREMAP1;
	AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_JTAGDISABLE;

	rccEnableTIM3(FALSE);
	rccResetTIM3();
	rccEnableTIM2(FALSE);
	rccResetTIM2();
	rccEnableTIM4(FALSE);
	rccResetTIM4();

	configEnc(STM32_TIM2);
	configEnc(STM32_TIM3);
	configEnc(STM32_TIM4);

	BaseSequentialStream * prnt = (BaseSequentialStream *) &SD1;

	int32_t last2 = STM32_TIM2->CNT;
	int32_t last3 = STM32_TIM3->CNT;
	int32_t last4 = STM32_TIM4->CNT;
	while (TRUE)
	{
		int32_t diff2 = STM32_TIM2->CNT - last2;
		int32_t diff3 = STM32_TIM3->CNT - last3;
		int32_t diff4 = STM32_TIM4->CNT - last4;
		last2 = STM32_TIM2->CNT;
		last3 = STM32_TIM3->CNT;
		last4 = STM32_TIM4->CNT;
		chprintf(prnt, "%5d, %5d | %5d, %5d | %5d, %5d\n\r", STM32_TIM2->CNT,
				diff2, STM32_TIM3->CNT, diff3, STM32_TIM4->CNT, diff4);
		pwmEnableChannel(&PWMD1, 0,	PWM_PERCENTAGE_TO_WIDTH(&PWMD1,	(diff3 > 0 ? diff3 : -diff3) * 10));
		//pwmEnableChannel(&PWMD1, 3, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, 10000-(diff3>0?diff3:-diff3)*10));
		chThdSleepMilliseconds(50);
	}
}
