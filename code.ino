int xPin = A1;
int yPin = A0;

int xPosition = 0;
int yPosition = 0;


const int row[8] = {
  2, 7, 19, 5, 13, 18, 12, 16
};

// 2-dimensional array of column pin numbers:
const int col[8] = {
  6, 11, 10, 3, 17, 4, 8, 9
};

// 2-dimensional array of pixels:
int pixels[8][8];



void setup() {
  // initialize the I/O pins as outputs iterate over the pins:
  for (int yPin = 0; xPin < 8; yPin++) {
    // initialize the output pins:
    pinMode(col[yPin], OUTPUT);
    pinMode(row[xPin], OUTPUT);
    // take the col pins (i.e. the cathodes) high to ensure that the LEDS are off:
    digitalWrite(col[yPin], HIGH);
  }
   Serial.begin(9600); 

  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  // initialize the pixel matrix:
  for (int xPosition = 0; xPosition < 8; xPosition++) {
    for (int yPosition = 0; yPosition < 8; yPosition++) {
      pixels[xPosition][yPosition] = HIGH;
    }
  }
}

void loop() {
  // read input:
  readSensors();
  xPosition = analogRead(xPin);
  yPosition = analogRead(yPin);
  // draw the screen:
  refreshScreen();
}

void readSensors() {
  // turn off the last position:
  pixels[xPosition][yPosition] = HIGH;
  // read the sensors for X and Y values:
  xPosition = 7 - map(analogRead(A0), 0, 1023, 0, 7);
  yPosition = map(analogRead(A1), 0, 1023, 0, 7);
  // set the new pixel position low so that the LED will turn on in the next
  // screen refresh:
  pixels[xPosition][yPosition] = LOW;

}

void refreshScreen() {
  // iterate over the rows (anodes):
  for (int thisRow = 0; thisRow < 8; thisRow++) {
    // take the row pin (anode) high:
    digitalWrite(row[thisRow], HIGH);
    // iterate over the cols (cathodes):
    for (int thisCol = 0; thisCol < 8; thisCol++) {
      // get the state of the current pixel;
      int thisPixel = pixels[thisRow][thisCol];
      // when the row is HIGH and the col is LOW,
      // the LED where they meet turns on:
      digitalWrite(col[thisCol], thisPixel);
// turn the pixel off:
      if (thisPixel == LOW) {
        digitalWrite(col[thisCol], HIGH);
      }
    }
    // take the row pin low to turn off the whole row:
    digitalWrite(row[thisRow], LOW);
  }
}
