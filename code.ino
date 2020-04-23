// 2-dimensional array of row pin numbers: const int row = {

2, 7, 19, 5, 13, 18, 12, 16
};

// 2-dimensional array of column pin numbers: const int col = {

6, 11, 10, 3, 17, 4, 8, 9
};

// 2-dimensional array of pixels: int pixels[8];

// cursor position: int x = 5; int y = 5;

void setup() {

// initialize the I/O pins as outputs iterate over the pins:
for (int thisPin = 0; thisPin < 8; thisPin++) {
  // initialize the output pins:
  pinMode(col[thisPin], OUTPUT);
  pinMode(row[thisPin], OUTPUT);
  // take the col pins (i.e. the cathodes) high to ensure that the LEDS are off:
  digitalWrite(col[thisPin], LOW);
}

// initialize the pixel matrix:
for (int x = 0; x < 8; x++) {
  for (int y = 0; y < 8; y++) {
    pixels[x][y] = LOW;
  }
}
}

unsigned long lidinn_timi = 0; int bidtimi = 100;

void loop() {

// read input:
int timi_nuna = millis();
if(timi_nuna - lidinn_timi > bidtimi) {
  readSensors();
  lidinn_timi = timi_nuna;
}

// draw the screen:
refreshScreen();
}

void readSensors() {

// endurskrifa
int xPosition = analogRead(A0);
int yPosition = analogRead(A1);
int buttonState = digitalRead(0);

if (xPosition > 700) {
  if(x<7){
    if(pixels[x][y] != 2) 
      pixels[x][y] = 0;
    x ++;
    if(pixels[x][y] != 2)
      pixels[x][y] = 1;
  }

}

if (xPosition < 200){
  if (x>0){
    if(pixels[x][y] != 2)
      pixels[x][y]=0;
    x --;
    if (pixels[x][y] !=2)
      pixels[x][y]=1;
  }

}
if (yPosition < 100){
  //pixels[x][y] = 1;
   if (y>0){
    if(pixels[x][y] != 2)
      pixels[x][y]=0;
    y --;
    if (pixels[x][y] !=2)
      pixels[x][y]=1;
   }

}
if (yPosition > 700){
  //pixels[x][y] = 2;
  if(y<7){
    if(pixels[x][y] != 2) 
      pixels[x][y] = 0;
    y ++;
    if(pixels[x][y] != 2)
      pixels[x][y] = 1;
  }

}
if (buttonState == HIGH){
  if(pixels[x][y] == 2)
    pixels[x][y] = 1;
}
else{
  pixels[x][y] = 2;
}
}

void refreshScreen() {

// iterate over the rows (anodes):
for (int thisRow = 0; thisRow < 8; thisRow++) {
  // take the row pin (anode) high:
  digitalWrite(row[thisRow], LOW);
  // iterate over the cols (cathodes):
  for (int thisCol = 0; thisCol < 8; thisCol++) {
    // get the state of the current pixel;
    int thisPixel = pixels[thisRow][thisCol];
    // when the row is HIGH and the col is LOW,
    // the LED where they meet turns on:
    digitalWrite(col[thisCol], thisPixel);
    // turn the pixel off:
    if (thisPixel > 0) {
      digitalWrite(col[thisCol], LOW);
    }
  }
  // take the row pin low to turn off the whole row:
  digitalWrite(row[thisRow], HIGH);
}
}
