// Lab 2
// Exercise 1 - interrupt (bare-metal)
// Button on D2 (INT0) toggles LED on D13 when pressed (falling edge)

#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t ledState = 0;

int main(void)
{
  //LED setup
  //set pin 13 (PB5) as output (LED)
  //start LED off
  DDRB |= (1 << DDB5);
  PORTB &= ~(1 << PORTB5);

  //Button setup
  //set pin 8 as input
  //Enable internal pull-up resistor (HIGH bt default)
  DDRB &= ~(1 << DDB0);
  PORTB |= (1 << PORTB0);

  //Pin change interrupt setup
  //Enable  pin change interrupt group 0 (PORTB)
  //Enable interupt on PB (pin 8)

  //PCIE = Interrupt Enable

  //PCIE0 = PORTB
  //PCIE1 = PORTC
  //PCIE2 = PORTD
  PCICR |= (1 << PCIE0);
  PCMSK0 |= (1 << PCINT0);

  //Clear any pending interrupt flag
  PCIFR |= (1 << PCIF0);

  //Enable global interrupts
  sei();


  while(1)
  {

  }
}

//ISR for pin change interrupt on PORTB (PB0-PB7)
ISR(PCINT0_vect)
{
  // Check if pin 8 (PB0) has gone LOW
  // If button pressed (LOW)
  if (!(PINB & (1 << PINB0)))
  {
    // Toggle LED state
    ledState = !ledState;      
    
    //ledState = 1?
    // LED ON
    if (ledState)
      PORTB |= (1 << PORTB5);
    
    //ledState = 0
    // LED OFF  
    else
      PORTB &= ~(1 << PORTB5); 
  }
}
