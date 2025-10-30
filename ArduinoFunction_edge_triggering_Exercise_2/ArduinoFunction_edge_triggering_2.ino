//Lab 2
//Exercise 2- interrupt (Arduino)


volatile bool ledState = false; // must be volatile

void setup()
{
  pinMode(13, OUTPUT);
  pinMode(8, INPUT_PULLUP); //Enable internal pull-up resistor (active high)


  attachInterrupt(digitalPinToInterrupt(8), toggleLED, FALLING);
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