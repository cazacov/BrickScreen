/*  
  Shows a picture on mechanical desply connected to Arduino 
  Display's LED connected to digital pins 2..9 via 150 Ohm resisitors
  Photoresistor connected to analog pin 0 and GND. It is also connected to 5V using 10 kOhm resistor.
*/  

void setup()
{
  for (int i = 2; i <= 9; i++)
  {
    pinMode(i, OUTPUT);
  }
}

// Bit map of the picture (right to left) that we are going to show
unsigned char Pivo[] = {
  B01111100,
  B10000010,
  B10000010,
  B10000010,
  B10000010,
  B01111100,
  B00000000,
  B00000000,  
  B01101100,
  B10010010, 
  B10010010,
  B11111110,
  B00000000,  
  B00000000,
  B11111110,
  B01000000,
  B00111000,
  B00000100,
  B11111110,
  B00000000,
  B00000000,
  B11111110,
  B10000000,
  B10000000,
  B10000000,
  B11111110 };


void loop()
{
  // Wait for the synchronization (photoresistor covered by the motor bar)
  waitForBegin();
  
  // Do not start from the imidiatelly as the LED beam is moving too slow in the first milliseconds
  delay(20);

  int del = 2300;  // pixel "length" in microseconds
  for(int i = 0; i < 26; i++)
  {
    showByte(Pivo[i], del);
  }
}

void waitForBegin()
{
  while (analogRead(0) > 650) 
  {
    delayMicroseconds(200);
  }
}  

void showByte(int info, long del)
{
  // Light LEDs if necessary
  for (int i = 2; i <= 9; i++)
  {
    digitalWrite(i, (info & 0x01) ? HIGH : LOW);          
    info >>= 1;
  }
  
  // Wait a little
  if (del < 30000)
  {
    delayMicroseconds(del);
  }
  else
  {  
    delay (del/1000);
  }
  
  // Turn LEDs off
  for (int i = 2; i <= 9; i++)
  {
    digitalWrite(i, LOW);          
  }
}