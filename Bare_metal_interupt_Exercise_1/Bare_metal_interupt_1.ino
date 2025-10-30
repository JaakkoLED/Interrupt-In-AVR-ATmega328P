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
  DDRB |= (1 << DDB5);

  //Button setup
  //set pin D2 (PD2 / INT0) as input
  //Enable internal pull-up resistor (activve high)
  DDRD &= ~(1 << DDD2);
  PORTD |= (1 << PORTD2);

  //Interrupt configuration
  //INT0 triggers on falling edge (ISC01=1, ISC00 = 0)
  EICRA |= (1 << ISC01);
  EICRA |= (1 << INT0);

  //Clear any pending interrupt flag
  //Enable INT0 interrupt
  EIFR |= (1 << INTF0);
  EIMSK |= (1 << INT0);

  //Enable global interrupts (sets I-bit in SREG)
  sei();


  while(1)
  {

  }
}

//interrupt service routine for INT0
ISR(INT0_vect)
{
  //toggle state variable
  ledState = !ledState;

  //turn LED on
  if(ledState)
  {
    PORTB |= (1 << PORTB5);
  }

  //Turb LED off
  else
  {
    PORTB &= ~(1 << PORTB5);
  }
}



//1. EICRA - Määrittää millainen signaali laukaisee keskeytyksen (esim. FALLING EDGE)
//2. EIMSK - Sallii mikä keskeytyslinja on käytössä (esim. INT0 = 1)
//SREG - Globaali keskeytyssallinta, I-Bitti = 1 (komennolla sei())

//Jos yksikin näistä on väärässä tilassa, keskeytys ei toimi.
