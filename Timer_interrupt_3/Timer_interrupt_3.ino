// Lab 2 - Interrupt
// Exercise 3: Timer1 Compare match A interrupt


#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t ledState = 0;


int main(void)
{
  //LED pin setup
  //PB5 (Arduino D13) as output
  DDRB |= (1 << DD5);

  //Timer1 setup
  //1. CTC Mode (Clear timer on compare match)
  //WGM12 = 1, CTC mode
  TCCR1B |= (1 << WGM12);
  TCCR1A = 0;

  //2. Setting the prescaler to 1024 (CS12 = 1, CS10=1)
  TCCR1B |= (1 << CS12) | (1 << CS10);

  //3. Setting the compare value for 1 second interval
  //Timer tick = (Prescaler / f_CPU) = 1024/16 MHz = 64 ɥs per tick
  //1 second / 65 ɥs = 15625 ticks
  OCR1A = 15625; 

  //4. Enable Output compare A match Interrupt
  //OCIEA1A = Output Compare Register Interrupt Enable for register A, Timer1
  //This means that every second (as per OCR1Acalculation), an ISR (Interrupt service routine) Will run 
  TIMSK1 |= (1 << OCIE1A);




  //Enable global interrupts
  sei();

  while(1)
  {
    //We could put our program here.
  }
}



//We run this function every time when the Timer1 reaches the value of OCR1A
ISR(TIMER1_COMPA_vect)
{
  ledState = !ledState;

  //LED on
  if(ledState)
  {
    PORTB |= (1 << PORTB5);
  }

  //LED off

  else
  {
    PORTB &= ~(1 << PORTB5);
  }
}