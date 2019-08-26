// Program to to test getting a colour from TCS 3200 colour sensor

// Pins im using for the sensor
const int S0 = 2;
const int S1 = 4;
const int S2 = 7;
const int S3 = 12;
const int colourData = 13;

int colour = 0;
char input;
bool getColour = false;

void setup() {
  // S0-3 to set output frequency and colour
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(colourData, INPUT); // coming into the arduino

  // Set frequency to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  
  Serial.begin(9600);
  Serial.println("hi, welcome to my minecraft youtube channel");
}

void loop() {

  if (Serial.available()) {
    input = Serial.read();
    if(input == 0x63) {// c to start reading
      Serial.print("\ngetting colours\n");
      getColour = true;
    }
    else if(input == 0x6F) {// o to stop reading
      Serial.print("\nstopping colours\n");
      getColour = false;
    }
  }

  if(getColour) {
    //S2 and S3 to get which colour
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW); // both low for red
    colour = pulseIn(colourData, LOW); // get colour pulse
    
    //Print the colour value
    Serial.print("R ");
    Serial.print(colour);

    digitalWrite(S2, LOW);
    digitalWrite(S3, HIGH); // low high for blue
    colour = pulseIn(colourData, LOW);

    Serial.print(" B ");
    Serial.print(colour);

    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH); // high high green
    colour = pulseIn(colourData, LOW);

    Serial.print(" G ");
    Serial.println(colour);
    delay(800);
  }
}
