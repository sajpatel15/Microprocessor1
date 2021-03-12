#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_gpio.h"
#include "driverlib/timer.h"
#include "driverlib/comp.h"
#include <stdio.h>

#define RED GPIO_PIN_1
#define GREEN GPIO_PIN_3
#define BLUE GPIO_PIN_2
volatile char solp = 0;
volatile char batt = 0;

void comp0inthandler(void)
{
    ComparatorIntClear(COMP_BASE, 0);
    if (!ComparatorValueGet(COMP_BASE, 0))
    {
        // set the flag of solar power
        solp = 1;
        //the battery flag should be zero
        batt = 0;
    }
    if ((ComparatorValueGet(COMP_BASE, 0)))
    {
        //solar power flag = 0
        solp = 0;
        //if battery voltage is higher than solar set battery
        if (!ComparatorValueGet(COMP_BASE, 1))
        {
            batt = 1;
        }
        else
        {
            batt = 0;
        }
    }

}

void comp1inthandler(void)
{
    ComparatorIntClear(COMP_BASE, 1);

    if (ComparatorValueGet(COMP_BASE, 1))
    {
        batt = 0;

        if (ComparatorValueGet(COMP_BASE, 0))
        {
            solp = 0;
        }
        else
        {
            solp = 1;
        }

    }

    if ((!ComparatorValueGet(COMP_BASE, 1)))
    {
        if (ComparatorValueGet(COMP_BASE, 0))
        {
            batt = 1;
        }
        else
        {
            batt = 0;
        }
    }
}

void int_config()
{
    ComparatorIntRegister(COMP_BASE, 0, comp0inthandler);
    ComparatorIntRegister(COMP_BASE, 1, comp1inthandler);
    ComparatorIntEnable(COMP_BASE, 0);
    ComparatorIntEnable(COMP_BASE, 1);
    IntMasterEnable();
}

int main(void)
{

    //set up clock for the system
    SysCtlClockSet(
    SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    // enable comparator
    SysCtlPeripheralEnable(SYSCTL_PERIPH_COMP0);

    //set the internal reference voltage to 2.37 V
    ComparatorRefSet(COMP_BASE, COMP_REF_2_371875V);

    //configure comparator 0
    ComparatorConfigure(
            COMP_BASE,
            0,
            (COMP_TRIG_NONE | COMP_INT_BOTH | COMP_ASRCP_REF
                    | COMP_OUTPUT_NORMAL));

    // configure comparator 1
    ComparatorConfigure(
            COMP_BASE,
            1,
            (COMP_TRIG_NONE | COMP_INT_BOTH | COMP_ASRCP_PIN
                    | COMP_OUTPUT_NORMAL));

    // Enable and configure Peripheral F to use RGB LEDs
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,
    GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);

    int_config();

    while (1)
    {
        if (!solp && !batt)
        {
            GPIOPinWrite(GPIO_PORTF_BASE, RED | GREEN | BLUE, 0);
            GPIOPinWrite(GPIO_PORTF_BASE, RED | GREEN | BLUE, 0b00000010);
        }
        if (!solp && batt)
        {
            GPIOPinWrite(GPIO_PORTF_BASE, RED | GREEN | BLUE, 0);
            GPIOPinWrite(GPIO_PORTF_BASE, RED | GREEN | BLUE, 0b00000100);
        }

        if (solp && !batt)
        {
            GPIOPinWrite(GPIO_PORTF_BASE, RED | GREEN | BLUE, 0);
            GPIOPinWrite(GPIO_PORTF_BASE, RED | GREEN | BLUE, 0b00001000);
        }

    }

}

