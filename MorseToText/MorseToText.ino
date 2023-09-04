const int ledPunto = 8; // Pin digital para el LED
const int ledBarra = 9;
const int buttonPin = 4; // Pin del pulsador

int dotDuration = 100; // Duración de un punto en milisegundos

// Estructura de datos para almacenar los patrones de código Morse
const int MORSE_PAUSE = 100; // Pausa entre pulsaciones
const int MORSE_DELAY = 300; // Pausa entre letras

// Mapa de código Morse para letras y números
const char* morseAlphabet[] = {
  ".-",    // A
  "-...",  // B
  "-.-.",  // C
  "-..",   // D
  ".",     // E
  "..-.",  // F
  "--.",   // G
  "....",  // H
  "..",    // I
  ".---",  // J
  "-.-",   // K
  ".-..",  // L
  "--",    // M
  "-.",    // N
  "---",   // O
  ".--.",  // P
  "--.-",  // Q
  ".-.",   // R
  "...",   // S
  "-",     // T
  "..-",   // U
  "...-",  // V
  ".--",   // W
  "-..-",  // X
  "-.--",  // Y
  "--.."   // Z
};

void setup() {
  pinMode(ledPunto, OUTPUT);
  pinMode(ledBarra, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600); // Inicializar la comunicación con el monitor serial
  Serial.println("Programa iniciado. Esperando pulsaciones...");
}

void loop() {
  int buttonState = digitalRead(buttonPin);
  
  if (buttonState == HIGH) {
    String morseCode = ""; // Variable para almacenar el código Morse
    
    while (digitalRead(buttonPin) == HIGH) {
      int duration = measureDuration(); // Medir la duración de la pulsación
      
      if (duration <= dotDuration) {
        // Punto
        morseCode += ".";
        digitalWrite(ledPunto, HIGH); // Encender el LED
        delay(dotDuration); // Duración del punto
        digitalWrite(ledPunto, LOW); // Apagar el LED
        delay(MORSE_PAUSE); // Pausa entre pulsaciones
      } else {
        // Barra
        morseCode += "-";
        digitalWrite(ledBarra, HIGH); // Encender el LED
        delay(duration); // Duración de la barra
        digitalWrite(ledBarra, LOW); // Apagar el LED
        delay(MORSE_PAUSE); // Pausa entre pulsaciones
      }
    }
    
    if (morseCode != "") {
      char decodedChar = decodeMorse(morseCode);
      if (decodedChar != '\0') {
        Serial.println(decodedChar);
      } else {
        Serial.println("Código Morse no reconocido");
      }
      delay(MORSE_DELAY); // Pausa entre letras
    }
  }
  
  delay(10); // Pequeña pausa para estabilidad en la lectura del pulsador
}

int measureDuration() {
  unsigned long startTime = millis(); // Tiempo inicial
  
  while (digitalRead(buttonPin) == HIGH) {
    // Esperar hasta que se suelte el pulsador
  }
  
  unsigned long endTime = millis(); // Tiempo final
  
  return endTime - startTime; // Duración en milisegundos
}

char decodeMorse(String morseCode) {
  int alphabetSize = sizeof(morseAlphabet) / sizeof(morseAlphabet[0]);
  
  for (int i = 0; i < alphabetSize; i++) {
    if (morseCode == morseAlphabet[i]) {
      return 'A' + i;
    }
  }
  
  return '\0'; // Código Morse no reconocido
}