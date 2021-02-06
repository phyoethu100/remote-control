#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"

void UARTIntHandler(void);

void UARTIntHandler(void)
{
    uint32_t ui32Status;

    ui32Status = UARTIntStatus(UART0_BASE, true); //get interrupt status

    UARTIntClear(UART0_BASE, ui32Status); //clear the asserted interrupts

    switch (UARTCharGet(UART0_BASE))
	{

        case 'R':
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, GPIO_PIN_1);
        SysCtlDelay(SysCtlClockGet() / 6); 
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
 		UARTCharPut(UART0_BASE, 'R');
		UARTCharPut(UART0_BASE, 'I');
 		UARTCharPut(UART0_BASE, 'G');
 		UARTCharPut(UART0_BASE, 'H');
 		UARTCharPut(UART0_BASE, 'T');
		UARTCharPut(UART0_BASE, '\n');
		UARTCharPut(UART0_BASE, '\r');
        break;

        case 'L':
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, GPIO_PIN_2);
        SysCtlDelay(SysCtlClockGet() / 6); 
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
		UARTCharPut(UART0_BASE, 'L');
		UARTCharPut(UART0_BASE, 'E');
 		UARTCharPut(UART0_BASE, 'F');
 		UARTCharPut(UART0_BASE, 'T');
 		UARTCharPut(UART0_BASE, '\n');
 		UARTCharPut(UART0_BASE, '\r');
        break;

        case 'F':
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, GPIO_PIN_3);
        SysCtlDelay(SysCtlClockGet() / 6); 
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
 		UARTCharPut(UART0_BASE, 'F');
 		UARTCharPut(UART0_BASE, 'O');
 		UARTCharPut(UART0_BASE, 'R');
 		UARTCharPut(UART0_BASE, 'W');
 		UARTCharPut(UART0_BASE, 'A'); 
 		UARTCharPut(UART0_BASE, 'R');
 		UARTCharPut(UART0_BASE, 'D');
 		UARTCharPut(UART0_BASE, '\n');
 		UARTCharPut(UART0_BASE, '\r');
        break;

        case 'B':
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 6);
        SysCtlDelay(SysCtlClockGet() / 6); 
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
 		UARTCharPut(UART0_BASE, 'B');
 		UARTCharPut(UART0_BASE, 'A');
 		UARTCharPut(UART0_BASE, 'C');
		UARTCharPut(UART0_BASE, 'K');
		UARTCharPut(UART0_BASE, 'W');
 		UARTCharPut(UART0_BASE, 'A'); 
 		UARTCharPut(UART0_BASE, 'R');
 		UARTCharPut(UART0_BASE, 'D');
 		UARTCharPut(UART0_BASE, '\n');
 		UARTCharPut(UART0_BASE, '\r');
        break;

        case 'S':
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 14);
		UARTCharPut(UART0_BASE, 'S');
 		UARTCharPut(UART0_BASE, 'T');
 		UARTCharPut(UART0_BASE, 'O');
  		UARTCharPut(UART0_BASE, 'P');
 		UARTCharPut(UART0_BASE, '\n');
 		UARTCharPut(UART0_BASE, '\r');
        break;

    }
}

int main(void) {

	SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); //enable GPIO port for LED
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3); //enable pin for LED PF2

    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 9600,
        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    IntMasterEnable(); //enable processor interrupts
    IntEnable(INT_UART0); //enable the UART interrupt
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT); //only enable RX and TX interrupts

    UARTCharPut(UART0_BASE, 'E');
    UARTCharPut(UART0_BASE, 'n');
    UARTCharPut(UART0_BASE, 't');
    UARTCharPut(UART0_BASE, 'e');
    UARTCharPut(UART0_BASE, 'r');
    UARTCharPut(UART0_BASE, ' ');
    UARTCharPut(UART0_BASE, 'D');
    UARTCharPut(UART0_BASE, 'i');
    UARTCharPut(UART0_BASE, 'r');
    UARTCharPut(UART0_BASE, 'e');
    UARTCharPut(UART0_BASE, 'c');
    UARTCharPut(UART0_BASE, 't');
    UARTCharPut(UART0_BASE, 'i');
    UARTCharPut(UART0_BASE, 'o');
    UARTCharPut(UART0_BASE, 'n');
    UARTCharPut(UART0_BASE, ':');
    UARTCharPut(UART0_BASE, '\n');
    UARTCharPut(UART0_BASE, '\r');


    while (1) //let interrupt handler do the UART echo function
    {
    }

} 
