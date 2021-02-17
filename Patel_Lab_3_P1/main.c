#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

#define RED GPIO_PIN_1
#define GREEN GPIO_PIN_3
#define BLUE GPIO_PIN_2

char msg[] = "RBG GAME ARE MAKING LEDS BLINK";
int countR;
int countG;
int countB;
int i = 0;

void main(void)
{
    SysCtlClockSet(
    SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, RED | GREEN | BLUE);

    GPIOPinWrite(GPIO_PORTF_BASE, RED | GREEN | BLUE, 0x00);

    // Detect Letters
    //******************
    while (msg[i] != 0x00)
    {
        if (msg[i] == 'R')
        {
            GPIOPinWrite(GPIO_PORTF_BASE, RED | GREEN | BLUE, 0b00000010); //0x02 turns on red
            countR += 1;
        }
        else if (msg[i] == 'G')
        {
            GPIOPinWrite(GPIO_PORTF_BASE, RED | GREEN | BLUE, 0b00000100); //0x04 turns on green
            countG += 1;
        }
        else if (msg[i] == 'B')
        {
            GPIOPinWrite(GPIO_PORTF_BASE, RED | GREEN | BLUE, 0b0001000); //0x08 turns on blue
            countB += 1;
        }
        i++;
        SysCtlDelay(2000000);
        GPIOPinWrite(GPIO_PORTF_BASE, RED | GREEN | BLUE,  0x00);
    }

    while (1)
        ;

}
