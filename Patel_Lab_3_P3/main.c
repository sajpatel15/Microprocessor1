#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_gpio.h"

#define GREEN GPIO_PIN_3
#define BUTTON GPIO_PIN_4
#define BLUE GPIO_PIN_2
#define RED GPIO_PIN_1

void main(void)
{
    SysCtlClockSet(
    SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, RED | GREEN | BLUE);

    GPIOPinWrite(GPIO_PORTF_BASE, RED | GREEN | BLUE, 0x00);

    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, BUTTON);

    GPIOPadConfigSet(GPIO_PORTF_BASE, BUTTON, GPIO_STRENGTH_2MA,
    GPIO_PIN_TYPE_STD_WPU);

    while (1)
    {

        if (GPIOPinRead(GPIO_PORTF_BASE, BUTTON) == 0)
        {
            // turning on the R LED  only
            SysCtlDelay(2000000);
            GPIOPinWrite(GPIO_PORTF_BASE, RED | GREEN | BLUE, 0b00000010);

            // turns the R LED off
            SysCtlDelay(2000000);
            GPIOPinWrite(GPIO_PORTF_BASE, RED | GREEN | BLUE, 0b00000000);

            // turns the RG LEDs on
            SysCtlDelay(2000000);
            GPIOPinWrite(GPIO_PORTF_BASE, RED | GREEN | BLUE, 0b00000110);

            // turns the RG LEDs off
            SysCtlDelay(2000000);
            GPIOPinWrite(GPIO_PORTF_BASE, RED | GREEN | BLUE, 0b00000000);

            // turns the RGB LEDs on
            SysCtlDelay(2000000);
            GPIOPinWrite(GPIO_PORTF_BASE, RED | GREEN | BLUE, 0b00001110);

            // turns the RGB LEDs off
            SysCtlDelay(2000000);
            GPIOPinWrite(GPIO_PORTF_BASE, RED | GREEN | BLUE, 0b00000000);

            // turns the GB LEDs on
            SysCtlDelay(2000000);
            GPIOPinWrite(GPIO_PORTF_BASE, RED | GREEN | BLUE, 0b00001100);

            // turns the GB LEDs off
            SysCtlDelay(2000000);
            GPIOPinWrite(GPIO_PORTF_BASE, RED | GREEN | BLUE, 0b00000000);

            // turns the B LEDs on
            SysCtlDelay(2000000);
            GPIOPinWrite(GPIO_PORTF_BASE, RED | GREEN | BLUE, 0b00000100);

            // turns the B LEDs off
            SysCtlDelay(2000000);
            GPIOPinWrite(GPIO_PORTF_BASE, RED | GREEN | BLUE, 0b00000000);

            // turns the RB LEDs on
            SysCtlDelay(2000000);
            GPIOPinWrite(GPIO_PORTF_BASE, RED | GREEN | BLUE, 0b00000110);

            // turns the RB LEDs off
            SysCtlDelay(2000000);
            GPIOPinWrite(GPIO_PORTF_BASE, RED | GREEN | BLUE, 0b00000000);

        }

    }
}

