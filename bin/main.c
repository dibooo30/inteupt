#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define DataPort	PORTA	// Using PortC as our Dataport
#define DataDDR		DDRA
//Interrupt Service Routine for INT0
ISR(INT0_vect)
{
	unsigned char i, temp;
	_delay_ms(500); // Software debouncing control
	temp = DataPort;	// Save current value on DataPort
	/* This for loop blink LEDs on Dataport 5 times*/
	for(i = 0; i<10; i++)
	{
		DataPort = 0x00;
		_delay_ms(100);	// Wait 5 seconds
		DataPort = 0xFF;
		_delay_ms(100);	// Wait 5 seconds
	}
	DataPort = temp;	//Restore old value to DataPort
}

int main(void)
{
	DDRD = 0b00100000;	// Set PD2 as input (Using for interupt INT0)
	PORTD = 0b00100000;		// Enable PD2 pull-up resistor
	DataDDR = 0xFF;		// Configure Dataport as output
	DataPort = 0x00;	// Initialise Dataport to 1
	GICR = 1<<INT0;					// Enable INT0
	MCUCR = 1 << ISC01 | 0 <<ISC00;	// Trigger INT0 on rising edge
	sei();				//Enable Global Interrupt
    while(1)
    {
//		if(DataPort == 0xFF)
//			DataPort = 0x00;
//		else
			DataPort = 0xFF;	// Shift to the left
//		_delay_ms(1000);	// Wait 5 seconds
    }
}
