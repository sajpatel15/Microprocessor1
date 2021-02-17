#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

#define RED GPIO_PIN_1
#define GREEN GPIO_PIN_3
#define BLUE GPIO_PIN_2

char msg[] = "AAA BB CCC BB CCC AAA AAA CCC BB";
int i = 0;
int count = 0;

void main(void)
{
    SysCtlClockSet(
    SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, RED | GREEN | BLUE);

    GPIOPinWrite(GPIO_PORTF_BASE, RED | GREEN | BLUE, 0x00);

    // Detect Letters
    //******************
    while (msg[i] != 0x00 && msg[i + 2] != '\0')
    {
        if (msg[i] == 'A' && msg[i + 1] == 'A' && msg[i + 2] == 'A')
        {
            GPIOPinWrite(GPIO_PORTF_BASE, RED | GREEN | BLUE, 0b00001000);//0x04 turns on green
            count = count + 1;
        }
        else
        {
            GPIOPinWrite(GPIO_PORTF_BASE, RED | GREEN | BLUE, 0b00000010); //0x04 turns on RED
        }

        i++;
        SysCtlDelay(2000000);
    }

    GPIOPinWrite(GPIO_PORTF_BASE, RED | GREEN | BLUE, 0b00000000); //0x00 turns all LED's off
    while (1)
        ;

}
