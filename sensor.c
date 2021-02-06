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

#define MAX_TIME 7500

void delayMS(int ms) {
    SysCtlDelay( (SysCtlClockGet()/(3*1000))*ms ) ;
}

uint32_t measureD(void) {
    // Pull trigger high
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, GPIO_PIN_2);
    //wait appropriately
    SysCtlDelay(SysCtlClockGet()/(3*10)) ; //Delay 10uS
    // Pull trigger low
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, 0);
    // Monitor echo for rising edge
    while (GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_4) == 0) { }
    uint32_t counter = 0;
    
    // Loop counter checking for falling edge; MAX_TIME make sure we don't miss it
    while ((GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_4) != 0) && (counter < MAX_TIME)) { counter++; }
    
    //return value
    return counter;
   
}

void UARTIntHandler(void)
{
    uint32_t ui32Status;

    ui32Status = UARTIntStatus(UART0_BASE, true); //get interrupt status

    UARTIntClear(UART0_BASE, ui32Status); //clear the asserted interrupts


}

int main(void) {
	
	SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); //enable GPIO port for LED
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1); //enable pin for LED PF2
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2); //enable pin for LED PF2
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3); //enable pin for LED PF2
	
	
    GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_4);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);

    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
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
    UARTCharPut(UART0_BASE, ' ');
	UARTCharPut(UART0_BASE, '\n');
	UARTCharPut(UART0_BASE, '\r');

    while (1) //let interrupt handler do the UART echo function
    {
		if (measureD() < 750) { 
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2); 
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0);
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
			UARTCharPut(UART0_BASE, 'D');
    		UARTCharPut(UART0_BASE, 'E');
    		UARTCharPut(UART0_BASE, 'T');
    		UARTCharPut(UART0_BASE, 'E');
    		UARTCharPut(UART0_BASE, 'C');
    		UARTCharPut(UART0_BASE, 'T');	
			UARTCharPut(UART0_BASE, '\n');
			UARTCharPut(UART0_BASE, '\r');		


 			UARTCharPut(UART0_BASE, 'T');
 			UARTCharPut(UART0_BASE, 'U');
 			UARTCharPut(UART0_BASE, 'R');
 			UARTCharPut(UART0_BASE, 'N');
 			UARTCharPut(UART0_BASE, ' ');
 			UARTCharPut(UART0_BASE, 'L');
 			UARTCharPut(UART0_BASE, 'E');
 			UARTCharPut(UART0_BASE, 'F');
 			UARTCharPut(UART0_BASE, 'T');
 			UARTCharPut(UART0_BASE, '\n');
			 UARTCharPut(UART0_BASE, '\r');					 
		}
        else { 	
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);
			UARTCharPut(UART0_BASE, 'F');
			UARTCharPut(UART0_BASE, 'O');
			UARTCharPut(UART0_BASE, 'R');
			UARTCharPut(UART0_BASE, 'W');
			UARTCharPut(UART0_BASE, 'A'); 
			UARTCharPut(UART0_BASE, 'R');
			UARTCharPut(UART0_BASE, 'D');
			UARTCharPut(UART0_BASE, '\n');
			UARTCharPut(UART0_BASE, '\r');
 		
		} 
		
		delayMS(50); 

    }

}

