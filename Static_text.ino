byte character[3][8]={{B00001110,//Character to be written
          		          B00000100,
                       	B00000100,
                       	B00000100,
                       	B00000100,
                       	B01000100,
                       	B00100100,
                       	B00011100},
                   {B10000001,//Character to be written
                   B01000010,
                   B00100100,
                   B00011000,
                   B00001000,
                   B00001000,
                   B00001000,
                   B00001000},
 	                {B01111110,
                   B00000010,
                   B00000100,
                   B00001000,
                   B00010000,
                   B00100000,
                   B01000000,
                   B01111110}};
byte column_pin[8]={ 6, 7, 8, 9, 10, 11, 12, 13};
#define SER_PIN 3
#define SCK_PIN 5
#define RCK_PIN 4


void setup() 
{
  // Turn everything to low
  for(int i=0; i<8; i++) {
    pinMode(column_pin[i],OUTPUT);
  }
  pinMode(SER_PIN, OUTPUT);
  pinMode(SCK_PIN, OUTPUT);
  pinMode(RCK_PIN, OUTPUT);
  Serial.begin(9600);
}                   

void loop() 
{
  // iterate each row
  int rowbits = 0x80;
  static int g=0;
  for(int row=0; row<8; row++) 
  {
    for(int k=0; k<8; k++) 
      digitalWrite(column_pin[k],HIGH); // Cleanup cols
    writerow(rowbits); // prepare to write the row
    for(int col=0; col<8; col++)
    { 
      digitalWrite(column_pin[7-col], character[(g/100)%3][row] & 1 << col ? LOW : HIGH);
    }
    delay(1);
    writerow(0);
    rowbits >>= 1; 
  }
  g=g+1;
}                                

void writerow(byte data) 
{
  digitalWrite(RCK_PIN, LOW);
  shiftOut(SER_PIN, SCK_PIN, LSBFIRST, data);
  digitalWrite(RCK_PIN, HIGH);
}