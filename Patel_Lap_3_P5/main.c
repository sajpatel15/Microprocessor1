#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_gpio.h"

#define RED GPIO_PIN_1
#define GREEN GPIO_PIN_3
#define BLUE GPIO_PIN_2
#define BUTTON_1 GPIO_PIN_4
#define BUTTON_2 GPIO_PIN_0

int oper_1[10] = { 1, 2, 3, 4, 1, 2, 3, 4, 1, 2 };
int oper_2[10] = { -2, 2, 3, 4, 1, 2, 3, 4, 1, 2 };
int result[10];
int count = 0;

void main(void)
{
    SysCtlClockSet(
    SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, RED | GREEN | BLUE);

    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, BUTTON_1);
    GPIOPadConfigSet(GPIO_PORTF_BASE, BUTTON_1, GPIO_STRENGTH_2MA,
    GPIO_PIN_TYPE_STD_WPU);

    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0x4C4F434B;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;

    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, BUTTON_2);
    GPIOPadConfigSet(GPIO_PORTF_BASE, BUTTON_2, GPIO_STRENGTH_2MA,
    GPIO_PIN_TYPE_STD_WPU);

    int i, j = 0;

    while (1)
    {
        if (GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4) == 0)
        {
            for (i = 0; i < 5000; i++)
            {
            } //Wait for 5000 iterations as a Software Debounce.
            if (GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4) != 0)
            { //If the button is released after the debounce period, turn on RED LED.
                count = count + 1;

            }
            if (count == 1)
            {
                GPIOPinWrite(GPIO_PORTF_BASE, RED | BLUE | GREEN, 0x00);
                GPIOPinWrite(GPIO_PORTF_BASE, RED, 0b00000010);
            }
            else if (count == 2)
            {
                GPIOPinWrite(GPIO_PORTF_BASE, RED | BLUE | GREEN, 0x00);
                GPIOPinWrite(GPIO_PORTF_BASE, GREEN, 0b00001000);
            }
            else if (count == 3)
            {
                GPIOPinWrite(GPIO_PORTF_BASE, RED | BLUE | GREEN, 0x00);
                GPIOPinWrite(GPIO_PORTF_BASE, GREEN | BLUE, 0b00001100);
            }

            if (count > 4)
            {
                count = 1;
            }

        }
        // PERFORM OPERATION
        if (GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0) == 0) //Read the initial button press of button 2.
        {
            for (i = 0; i < 5000; i++)
            {
            } //Wait for 5000 iterations as a Software Debounce.
            if (GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0) != 0) //Wait for the release of the button after the debounce period.
            {
                if (count == 1)
                {
                    result[j] = oper_1[j] + oper_2[j];
                    GPIOPinWrite(GPIO_PORTF_BASE, RED, 0x00);
                    j++;
                }
                else if (count == 2)
                {
                    result[j] = oper_1[j] - oper_2[j];
                    GPIOPinWrite(GPIO_PORTF_BASE, GREEN, 0x00);
                    j++;
                }
                else if (count == 3)
                {
                    result[j] = oper_1[j] * oper_2[j];
                    GPIOPinWrite(GPIO_PORTF_BASE, BLUE, 0x00);
                    j++;
                }
                else if (count == 4)
                {
                    result[j] = oper_1[j] / oper_2[j];
                    GPIOPinWrite(GPIO_PORTF_BASE, BLUE | GREEN, 0x00);
                    j++;
                }

                if (j == 10)
                {
                    GPIOPinWrite(GPIO_PORTF_BASE, RED | GREEN | BLUE,
                                 0b00001110);
                    break; // exit while(1)
                }

                count = 0;
            }
        }
    }
    while (1)
        ;
}
