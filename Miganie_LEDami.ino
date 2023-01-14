#define greenPin 12  // 12 oznacza pin D5
#define bluePin 13   // 13 oznacza pin D6
#define redPin 14    // 14 oznacza pin D7

#define lightSensor A0   // A0 oznacza wejście analogowe do którego podłączony jest czujnik światła

const int resolution = 256;   // Zmienna przechowująca maksymalną wartość dla sygnału PWM

int lightFromSensor = 0;      // Zmienna przechowująca wartość sygnału analogowego podanego przez czujnik światła
int redLightConverted = 0;    // Zmienna przechowująca przekonwertowany sygnał z czujnika światła na wartość zmiany jasności światła czerwonego
int greenLightConverted = 0;  // Zmienna przechowująca przekonwertowany sygnał z czujnika światła na wartość zmiany jasności światła zielonego
int blueLightConverted = 0;   // Zmienna przechowująca przekonwertowany sygnał z czujnika światła na wartość zmiany jasności światła niebieskiego

int red = 0;    // Zmienne przechowujące aktualną wartość dla danego koloru
int green = 0;
int blue = 0;

int redS = 0;   // Zmienne przechowujące wartości wpisane przez użytkownika przez port szeregowy
int greenS = 0;
int blueS = 0;

void setup() {
  Serial.begin(9600);   // Prędkość komunikacji między ESP a portem szeregowym
  analogWriteRange(resolution);   // Zmiana zakresu wyjścia analogowego PWM z 1024 na 256
  analogWrite(redPin, 0);   // Początkowe wyłączenie LED
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);

}

void loop() {
    lightFromSensor = analogRead(lightSensor);    // Odebranie aktualnego stanu z czujnika światła
    redLightConverted = map(lightFromSensor, 0, 1024, redS, 0);     // Przekonwertowanie informacji z czujnika na wartości, o które będzie można skorygować jasność świecenia LEDów
    greenLightConverted = map(lightFromSensor, 0, 1024, greenS,0);
    blueLightConverted = map(lightFromSensor, 0, 1024, blueS, 0);
    
    if(Serial.available() > 0){     // Jeśli port szeregowy jest dostępny
      Serial.println("Podaj wartość R, G, B po przecinku");   // Informacja dla użytkownika
      
      redS = Serial.parseInt();   // Zapisanie wartości podanej przez użytkownika do zmiennej przechowującej wartość danego koloru (pominięcie wszystkich następnych znaków po natrafieniu na znak inny niż liczba, np. przecinek
      greenS = Serial.parseInt();
      blueS = Serial.parseInt();
    }
  
    red = redS - redLightConverted;   // Obliczenie aktualnej jasności na podstawie danych sczytanych z czujnika światła
    green = greenS - greenLightConverted;
    blue = blueS - blueLightConverted;
    
    analogWrite(redPin, red);   // Nadanie odpowiedniej wartości poprzez sygnał PWM do odpowiednich wyprowadzeń R, G i B paska LED
    analogWrite(greenPin, green);
    analogWrite(bluePin, blue);
    
}
