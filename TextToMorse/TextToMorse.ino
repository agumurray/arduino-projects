const int ledMorse = 8; // Pin digital para el LED de Morse
const int ledLetra = 9; // Pin digital para el LED de letra
const int beeper = 7; // Pin digital para el beeper
String userInput = "";

int dotDuration = 100; // Duración de un punto en milisegundos
int barDuration = dotDuration * 3; // Duración de una barra (3 veces la duración de un punto)

// Mapa de código Morse para letras
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
  ".-..",  // 
  
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
  pinMode(ledMorse, OUTPUT);
  pinMode(ledLetra, OUTPUT);
  pinMode(beeper, OUTPUT);
  Serial.begin(9600); // Inicializar la comunicación con el monitor serial
}

void loop() {
  Serial.println("Programa iniciado. Esperando texto (EN MAYUSCULA)...");
  if (Serial.available()) {
    userInput = Serial.readString();
    userInput.trim();

    for (int i = 0; i < userInput.length(); i++) {
      char letra = userInput.charAt(i);
      if (letra >= 'A' && letra <= 'Z') {
        emitirMorse(letra);
        digitalWrite(ledLetra, HIGH);
        delay(dotDuration * 7); // Pausa entre letras (7 veces la duración de un punto)
        digitalWrite(ledLetra, LOW);
      }
      else {
        // Caracter no válido
        for (int i = 0; i < 9; i++) {
          digitalWrite(ledMorse, HIGH);
          delay(100);
          digitalWrite(ledMorse, LOW);
        }
      }
    }
  }

  // Otras tareas del programa
}

void emitirMorse(char letra) {
  int alphabetSize = sizeof(morseAlphabet) / sizeof(morseAlphabet[0]);
  int indice = letra - 'A'; // Indice correspondiente en el arreglo morseAlphabet
  
  if (indice >= 0 && indice < alphabetSize) {
    String morseCode = morseAlphabet[indice];
  
    for (int i = 0; i < morseCode.length(); i++) {
      if (morseCode.charAt(i) == '.') {
        digitalWrite(ledMorse, HIGH);
        digitalWrite(beeper, HIGH);
        delay(dotDuration);
        digitalWrite(ledMorse, LOW);
        digitalWrite(beeper, LOW);
      }
      else {
        digitalWrite(ledMorse, HIGH);
        digitalWrite(beeper, HIGH);
        delay(barDuration);
        digitalWrite(ledMorse, LOW);
        digitalWrite(beeper, LOW);
      }
      delay(dotDuration); // Pausa entre elementos del código Morse (1 vez la duración de un punto)
    }
  }
}

