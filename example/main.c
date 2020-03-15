/*
 * Example to demonstrate the use of interrupts and EMLIB
 * by toggling a pin in a SysTick handler.
 */

#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_gpio.h"

#define LED_PIN                  (12U)
#define LED_PORT                 (gpioPortB)


void SysTick_Handler(void)
{
	GPIO_PinOutToggle(LED_PORT, LED_PIN);
}


int main()
{
	CHIP_Init();
	CMU_ClockEnable(cmuClock_GPIO, true);
	GPIO_PinModeSet(LED_PORT, LED_PIN, gpioModePushPull, 1);

	SysTick_Config(1000000);
	NVIC_EnableIRQ(SysTick_IRQn);

	for (;;) {
		__WFI();
	}
}
