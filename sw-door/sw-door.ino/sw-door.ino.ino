/*
File        : sw-door.ino
Authors     : Gustavo (guga) && Rafa Baninho
Description :   This code has the intention to open the front
only door, located 

*/

// Output bits  for the door
const int BIT_0 = 2;
const int BIT_1 = 3;
const int TimePerCycle_us  = 1536;
const int BIT_4 = 6;
const int BIT_5 = 7;
const int BIT_6 = 8;
const int BIT_7 = 9;
const int BIT_8 = 10;

//internal code
#define CAD_CLOSE 10
#define CAD_OPEN 11
#define uint unsigned int


//inputado da porta
int decode_number(uint input_read) {
}


void setup() {
  Serial.begin(9600);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(BIT_0, INPUT);
  pinMode(BIT_1, INPUT);
  // pinMode(BIT_2, INPUT);
  // pinMode(BIT_3, INPUT);

  //setup output pins
  pinMode(BIT_4, OUTPUT);
  pinMode(BIT_5, OUTPUT);
  pinMode(BIT_6, OUTPUT);
  pinMode(BIT_7, OUTPUT);
  pinMode(BIT_8, OUTPUT);
  digitalWrite(BIT_4, LOW);
  // Interruption pins
  attachInterrupt(digitalPinToInterrupt(BIT_0), test, FALLING);
}

void test() {
  digitalWrite(BIT_4, HIGH);
  delayMicroseconds(40);
  digitalWrite(BIT_4, LOW);
  
  delayMicroseconds(TimePerCycle_us);
  Serial.println("pressed");
  // digitalWrite(BIT_5, HIGH);
  // digitalWrite(BIT_5, LOW);
  
  // delayMicroseconds(TimePerCycle_us/4);
  // digitalWrite(BIT_6, HIGH);
  // digitalWrite(BIT_6, LOW);
  
  // delayMicroseconds(TimePerCycle_us/4);
  // digitalWrite(BIT_7, HIGH);
  // digitalWrite(BIT_7, LOW);

  // delayMicroseconds(TimePerCycle_us/4);
  // digitalWrite(BIT_8, HIGH);
  // digitalWrite(BIT_8, LOW);
}


unsigned char decode2output(uint number) {
  unsigned char output;
  switch (number) {
    case 1: output |= 1 << 3; break;
    case 2: output |= 1 << 2; break;
    case 3: output |= 1 << 1; break;
    case 4: output |= 1 << 3; break;
    case 5: output |= 1 << 2; break;
    case 6: output |= 1 << 1; break;
    case 7: output |= 1 << 3; break;
    case 8: output |= 1 << 2; break;
    case 9: output |= 1 << 1; break;
    case 10: output |= 1 << 3; break;  //cad close
    case 0: output |= 1 << 2; break;
    case 11: output |= 1 << 1; break;  //cad open
  }

  // Serial print to inform output and the number
  Serial.print("Number: ");
  Serial.print(number);
  Serial.print(" -> Output: ");
  Serial.println(output);

  return output;
}
void write2output(unsigned char input_digits) {
  digitalWrite(BIT_0, (input_digits >> 0) & 1);
  digitalWrite(BIT_1, (input_digits >> 1) & 1);
  // digitalWrite(BIT_2, (input_digits >> 2) & 1);
  // digitalWrite(BIT_3, (input_digits >> 3) & 1);
  // digitalWrite(BIT_4, (input_digits >> 4) & 1);
  // digitalWrite(BIT_5, (input_digits >> 5) & 1);
  // digitalWrite(BIT_6, (input_digits >> 6) & 1);
  // digitalWrite(BIT_7, (input_digits >> 7) & 1);
}

// the loop function runs over and over again forever
void loop() {}
