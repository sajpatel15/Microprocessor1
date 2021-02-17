#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_gpio.h"

#define BUTTON_1 GPIO_PIN_4
#define BUTTON_2 GPIO_PIN_0

int counter = 0;

void main(void)
{
    SysCtlClockSet(
            SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ
                    | SYSCTL_OSC_MAIN);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, BUTTON_1);
    GPIOPadConfigSet(GPIO_PORTF_BASE, BUTTON_1, GPIO_STRENGTH_2MA,
                     GPIO_PIN_TYPE_STD_WPU);

    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0x4C4F434B;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;

    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, BUTTON_2);
    GPIOPadConfigSet(GPIO_PORTF_BASE, BUTTON_2, GPIO_STRENGTH_2MA,
                     GPIO_PIN_TYPE_STD_WPU);

    int i;
    while (1)
    {
        if (GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4) == 0)
        {
            for (i = 0; i < 5000; i++)
            {
            } //Wait for 5000 iterations as a Software Debounce.
            if (GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4) != 0) //If the button is released after the debounce, count up.
                counter = counter + 1;
        }

        if (GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0) == 0)
        {
            for (i = 0; i < 5000; i++)
            {
            } //Wait for 5000 iterations as a Software Debounce.
            if (GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0) != 0) //If the button is released after the debounce period, count down.
                counter = counter - 1;
        }
    }

}
