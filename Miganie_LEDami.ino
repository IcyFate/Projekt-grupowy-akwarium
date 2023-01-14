const int redPin = 14;     // 14 corresponds to GPIO13
const int greenPin = 12;   // 12 corresponds to GPIO12
const int bluePin = 13;    // 14 corresponds to GPIO14
const int czujnik = A0;

const int resolution = 256;
int swiatlo = 0;
int lightFromSensor = 0;
int redLightConverted = 0;
int greenLightConverted = 0;
int blueLightConverted = 0;
int red = 0;
int green = 0;
int blue = 0;
int redS = 0;
int greenS = 0;
int blueS = 0;

void setup() {
  Serial.begin(9600);
  analogWriteRange(resolution);
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);

}

void loop() {
    lightFromSensor = analogRead(czujnik);
    redLightConverted = map(lightFromSensor, 0, 1024, redS, 0);
    greenLightConverted = map(lightFromSensor, 0, 1024, greenS,0);
    blueLightConverted = map(lightFromSensor, 0, 1024, blueS, 0);
    
    if(Serial.available() > 0){
      Serial.println("Podaj wartość R, G i B");
      
      redS = Serial.parseInt();
      greenS = Serial.parseInt();
      blueS = Serial.parseInt();
    }
  
    red = redS-redLightConverted;
    green = greenS-greenLightConverted;
    blue = blueS-blueLightConverted;
    
    analogWrite(redPin, red);
    analogWrite(greenPin, green);
    analogWrite(bluePin, blue);
    
}
