volatile bool ledState = false; // must be volatile

void setup()
{
  pinMode(13, OUTPUT);
  pinMode(2, INPUT_PULLUP); //Enable internal pull-up resistor (active high)
  attachInterrupt(digitalPinToInterrupt(2), toggleLED, FALLING);

  digitalWrite(13,LOW);
}

void loop()
{
  // put your main code here, to run repeatedly:

}


void toggleLED()
{
  ledState = !ledState;
  digitalWrite(13, ledState);
}