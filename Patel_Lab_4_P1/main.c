#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_gpio.h" // Critical Function GPIO Protection
#include "driverlib/interrupt.h"

#define RED GPIO_PIN_1
#define GREEN GPIO_PIN_3
#define BLUE GPIO_PIN_2

#define BUTTON_1 GPIO_PIN_4
#define BUTTON_2 GPIO_PIN_0

volatile char isr_flag_1 = 0;
volatile char isr_flag_2 = 0;
int i;
int count = 0;

void GPIO_IRQHandler(void)
{

    if (GPIOIntStatus(GPIO_PORTF_BASE, 1) == 16)
    {
        // Clear Flag
        GPIOIntClear(GPIO_PORTF_BASE, BUTTON_1);
        for (i = 0; i < 5000; i++) //Blank for loop for delay
        {

        }
        /* Handler Code Below */
        if (GPIOPinRead(GPIO_PORTF_BASE, BUTTON_1) != 0) //Check if the button has been released to update the flag
            isr_flag_1 = 1;
    }

    if (GPIOIntStatus(GPIO_PORTF_BASE, 1) == 1)
    {
        // Clear Flag
        GPIOIntClear(GPIO_PORTF_BASE, BUTTON_2);
        for (i = 0; i < 5000; i++) //Blank for loop for delay
        {

        }
        /* Handler Code Below */
        if (GPIOPinRead(GPIO_PORTF_BASE, BUTTON_2) != 0) //Check if the button has been released to update the flag
            isr_flag_2 = 1;
    }

}

void configure_LEDs(void)
{
    //Enable Port F as GPIO
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    //Set PF(2,2,3) to outputs. On Board LEDs
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, RED | GREEN | BLUE);
    // Turn Off LEDs
    GPIOPinWrite(GPIO_PORTF_BASE, RED | GREEN | BLUE, 0x00);

    // Initialize Button 1
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

}

void configure_PF_Int()
{
    // Button 1
    GPIOIntTypeSet(GPIO_PORTF_BASE, BUTTON_1, GPIO_RISING_EDGE);
    GPIOIntTypeSet(GPIO_PORTF_BASE, BUTTON_2, GPIO_RISING_EDGE);

    GPIOIntRegister(GPIO_PORTF_BASE, GPIO_IRQHandler);
    GPIOIntEnable(GPIO_PORTF_BASE, BUTTON_1);
    GPIOIntEnable(GPIO_PORTF_BASE, BUTTON_2);

    IntEnable(INT_GPIOF);

    IntMasterEnable();
}

int main(void)
{
    //Set System clock to 40 MHz
    SysCtlClockSet(
    SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

    /* Configure LEDs */
    configure_LEDs();

    /* Configure Button1 as Interrupt */
    configure_PF_Int();

    while (1)
    {
        // PA4 - External Button Pressed
        if (isr_flag_1)
        {
            count++;
            isr_flag_1 = 0;
            if (count > 0)
            {
                GPIOPinWrite(GPIO_PORTF_BASE, RED | GREEN | BLUE, 0b00000000);
                GPIOPinWrite(GPIO_PORTF_BASE, RED, 0b00000010);
            }
            else if (count < 0)
            {
                GPIOPinWrite(GPIO_PORTF_BASE, GREEN | RED | BLUE, 0b00000000);
                GPIOPinWrite(GPIO_PORTF_BASE, GREEN, 0b00001000);
            }
            else if (count == 0)
            {
                GPIOPinWrite(GPIO_PORTF_BASE, GREEN | RED | BLUE, 0b00000000);
                GPIOPinWrite(GPIO_PORTF_BASE, BLUE, 0b00000100);
            }
        }
        else if (isr_flag_2)
        {
            count--;
            isr_flag_2 = 0;

            if (count > 0)
            {
                GPIOPinWrite(GPIO_PORTF_BASE, RED | GREEN | BLUE, 0b00000000);
                GPIOPinWrite(GPIO_PORTF_BASE, RED, 0b00000010);
            }
            else if (count < 0)
            {
                GPIOPinWrite(GPIO_PORTF_BASE, GREEN | RED | BLUE, 0b00000000);
                GPIOPinWrite(GPIO_PORTF_BASE, GREEN, 0b00001000);
            }
            else if (count == 0)
            {
                GPIOPinWrite(GPIO_PORTF_BASE, GREEN | RED | BLUE, 0b00000000);
                GPIOPinWrite(GPIO_PORTF_BASE, BLUE, 0b00000100);
            }

        }

    }

}

