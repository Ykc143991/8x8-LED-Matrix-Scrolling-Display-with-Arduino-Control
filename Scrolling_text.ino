byte characters[5][8] = {
  // H
  {B10000001,
   B10000001,
   B10000001,
   B11111111,
   B10000001,
   B10000001,
   B10000001,
   B10000001},
  // E
  {B11111111,
   B10000000,
   B10000000,
   B11111110,
   B10000000,
   B10000000,
   B10000000,
   B11111111},
  // L
  {B10000000,
   B10000000,
   B10000000,
   B10000000,
   B10000000,
   B10000000,
   B10000000,
   B11111111},
  // L (repeated)
  {B10000000,
   B10000000,
   B10000000,
   B10000000,
   B10000000,
   B10000000,
   B10000000,
   B11111111},
  // O
  {B01111110,
   B10000001,
   B10000001,
   B10000001,
   B10000001,
   B10000001,
   B10000001,
   B01111110}
};

byte column_pin[8] = { 6, 7, 8, 9, 10, 11, 12, 13 };
#define SER_PIN 3
#define SCK_PIN 5
#define RCK_PIN 4

void setup() {
  // Turn everything to low
  for(int i = 0; i < 8; i++) {
    pinMode(column_pin[i], OUTPUT);
  }
  pinMode(SER_PIN, OUTPUT);
  pinMode(SCK_PIN, OUTPUT);
  pinMode(RCK_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  static int position = 0; // Position of the scrolling text
  for(int i = 0; i < 8; i++) {
    displayCharacter(position, i);
    delay(2); // Adjust speed of scrolling
  }
  position++; // Move to the next column

  if (position >= 8 * 5) { // Reset position after complete scroll
    position = 0;
  }
}

void displayCharacter(int position, int row) {
  int charIndex = position / 8; // Determine which character to display
  int columnShift = position % 8; // Determine the column shift

  for(int col = 0; col < 8; col++) {
    // Write the shifted character to the matrix
    int characterColumn = (characters[charIndex][row] >> columnShift) & 0x01;
    digitalWrite(column_pin[7 - col], characterColumn ? LOW : HIGH);
  }
  
  writerow(0x80 >> row); // Write the row data
}

void writerow(byte data) {
  digitalWrite(RCK_PIN, LOW);
  shiftOut(SER_PIN, SCK_PIN, LSBFIRST, data);
  digitalWrite(RCK_PIN, HIGH);
}
