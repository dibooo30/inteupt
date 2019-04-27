#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define DataPort	PORTA	// Using PortC as our Dataport
#define DataDDR		DDRA
//Interrupt Service Routine for INT0
ISR(INT0_vect){
	unsigned char i, temp;
	_delay_ms(500); // Software debouncing control
	temp = DataPort;	// Save current value on DataPort
	/* This for loop blink LEDs on dataport 10 times*/
	for(i = 0; i<10; i++) {
		DataPort = 0x00;
		_delay_ms(100);	// Wait 5 seconds
		DataPort = 0x01;
		_delay_ms(100);	// Wait 5 seconds
	} // end fo loop
	DataPort = temp;	//Restore old value to DataPort
} // END Interrupt Service Routine for INT0

//Interrupt Service Routine for INT1
ISR(INT1_vect){
	unsigned char i, temp;
	_delay_ms(500); // Software debouncing control
	temp = DataPort;	// Save current value on DataPort
	/* This for loop blink LEDs on Dataport 5 times*/
	for(i = 0; i<10; i++)
	{
		DataPort = 0x00;
		_delay_ms(300);	// Wait 5 seconds
		DataPort = 0x08;
		_delay_ms(300);	// Wait 5 seconds
	}
	DataPort = temp;	//Restore old value to DataPort
}// END Interrupt Service Routine for INT1

//Interrupt Service Routine for INT2
ISR(INT2_vect){
	unsigned char i, temp;
	_delay_ms(500); // Software debouncing control
	temp = DataPort;	// Save current value on DataPort
	/* This for loop blink LEDs on Dataport 5 times*/
	for(i = 0; i<10; i++)
	{
		DataPort = 0x00;
		_delay_ms(100);	// Wait 5 seconds
		DataPort = 0x09;
		_delay_ms(100);	// Wait 5 seconds
	}
	DataPort = temp;	//Restore old value to DataPort
}// END Interrupt Service Routine for INT2

int main(void) {
	DDRD = 0b00110000;	// Set PD2 as input (Using for interupt INT0)
	DDRB = 0b01000000;
	PORTD = 0b00110000;
	PORTB = 0b00100000;		// Enable PD2 pull-up resistor
// Enable PD2 pull-up resistor
	DataDDR = 0xFF;		// Configure Dataport as output
	DataPort = 0x00;	// Initialise Dataport to 1
	GICR =0xE0;					// Enable INT0
	MCUCR = 0x0A;	// Trigger INT0 on faling edge
	MCUCSR = 0x40;	// Trigger INT0 on faling edge

	sei();				//Enable Global Interrupt
    while(1)
    {
    	DataPort = 0xFF;	// Shift to the left
    }// end while loop
}// end main fuction
