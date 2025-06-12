// Código para Navidad: Luces y Música con Arduino

//   - Buzzer pasivo: pin 8 a GND
//   - LEDs: pines 2,3,4,5,6 a GND (con resistencias de 220Ω)

#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784

//#include "pitches.h"  // Librería de notas musicales

// Definición de notas para "Jingle Bells"
int melody[] = {
  NOTE_E5, NOTE_E5, NOTE_E5, 
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_G5, NOTE_C5, NOTE_D5,
  NOTE_E5,
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
  NOTE_F5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_D5, NOTE_D5, NOTE_E5,
  NOTE_D5, NOTE_G5
};

int durations[] = {
  8, 8, 4,
  8, 8, 4,
  8, 8, 8, 8,
  2,
  8, 8, 8, 8,
  8, 8, 8, 16, 16,
  8, 8, 8, 8,
  4, 4
};

const int buzzerPin = 8;
const int ledCount = 5;
int ledPins[] = {2, 3, 4, 5, 6};

void setup() {
  for (int i = 0; i < ledCount; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  playJingleBells();
  twinkleLights(500);  // Efecto especial entre canciones
}

void playJingleBells() {
  int tempo = 180;  // Velocidad de la melodía
  
  for (int i = 0; i < sizeof(melody)/sizeof(int); i++) {
    // Calcular duración de la nota
    int duration = 1000 / durations[i];
    
    // Tocar nota
    tone(buzzerPin, melody[i], duration);
    
    // Controlar LEDs
    digitalWrite(ledPins[i % ledCount], HIGH);
    delay(duration * 1.2);  // Pequeña pausa
    digitalWrite(ledPins[i % ledCount], LOW);
    
    // Pequeña pausa entre notas
    noTone(buzzerPin);
    delay(duration / 4);
  }
}

void twinkleLights(int duration) {
  for (int i = 0; i < 20; i++) {
    int led = random(ledCount);
    digitalWrite(ledPins[led], HIGH);
    delay(duration / 10);
    digitalWrite(ledPins[led], LOW);
    delay(duration / 20);
  }
}
