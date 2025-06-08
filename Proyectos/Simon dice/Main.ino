// Definición de pines
const int buzzerPin = 9;
const int leds[] = {2, 3, 4, 5};    // LEDs en pines 2-5
const int botones[] = {6, 7, 8, 10}; // Botones en pines 6-8 y 10
const int tonos[] = {262, 330, 392, 494}; // Tonos para cada botón (C, E, G, B)

// Variables del juego
int secuencia[100]; // Almacena la secuencia
int nivel = 1;      // Nivel actual
int velocidad = 500; // Velocidad inicial entre luces

void setup() {
  // Inicializar LEDs como salidas
  for (int i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
  }
  
  // Inicializar botones como entradas con pull-up
  for (int i = 0; i < 4; i++) {
    pinMode(botones[i], INPUT_PULLUP);
  }
  
  // Inicializar buzzer
  pinMode(buzzerPin, OUTPUT);
  
  // Semilla aleatoria
  randomSeed(analogRead(0));
  
  // Secuencia inicial aleatoria
  for (int i = 0; i < 100; i++) {
    secuencia[i] = random(0, 4);
  }
  
  // Esperar a que se presione un botón para empezar
  esperarInicio();
}

void loop() {
  // Mostrar secuencia
  mostrarSecuencia();
  
  // Leer secuencia del jugador
  leerSecuencia();
  
  // Aumentar nivel y velocidad
  nivel++;
  velocidad = max(100, velocidad - 20); // Reducir tiempo entre luces, mínimo 100ms
  
  // Pequeña pausa antes del siguiente nivel
  delay(500);
}

void esperarInicio() {
  // Todos los LEDs parpadean
  for (int i = 0; i < 4; i++) {
    digitalWrite(leds[i], HIGH);
  }
  tone(buzzerPin, 392, 200);
  delay(1000);
  for (int i = 0; i < 4; i++) {
    digitalWrite(leds[i], LOW);
  }
  delay(500);
  
  // Esperar a que se presione cualquier botón
  boolean esperando = true;
  while (esperando) {
    for (int i = 0; i < 4; i++) {
      if (digitalRead(botones[i]) == LOW) {
        esperando = false;
        // Feedback visual y sonoro
        digitalWrite(leds[i], HIGH);
        tone(buzzerPin, tonos[i], 200);
        delay(300);
        digitalWrite(leds[i], LOW);
        delay(200);
        break;
      }
    }
  }
}

void mostrarSecuencia() {
  for (int i = 0; i < nivel; i++) {
    int led = secuencia[i];
    digitalWrite(leds[led], HIGH);
    tone(buzzerPin, tonos[led], velocidad);
    delay(velocidad);
    digitalWrite(leds[led], LOW);
    delay(100);
  }
}

void leerSecuencia() {
  for (int i = 0; i < nivel; i++) {
    boolean esperando = true;
    while (esperando) {
      for (int j = 0; j < 4; j++) {
        if (digitalRead(botones[j]) == LOW) {
          // Botón presionado
          digitalWrite(leds[j], HIGH);
          tone(buzzerPin, tonos[j], 100);
          delay(200);
          digitalWrite(leds[j], LOW);
          
          // Verificar si es el botón correcto
          if (j != secuencia[i]) {
            juegoTerminado();
            return;
          }
          
          esperando = false;
          break;
        }
      }
    }
  }
}

void juegoTerminado() {
  // Secuencia de game over
  tone(buzzerPin, 196, 300);
  for (int i = 0; i < 4; i++) {
    digitalWrite(leds[i], HIGH);
    delay(100);
  }
  for (int i = 0; i < 4; i++) {
    digitalWrite(leds[i], LOW);
  }
  delay(500);
  
  // Mostrar puntuación
  for (int i = 0; i < nivel; i++) {
    digitalWrite(leds[0], HIGH);
    tone(buzzerPin, 262, 100);
    delay(200);
    digitalWrite(leds[0], LOW);
    delay(200);
  }
  
  // Reiniciar juego
  nivel = 1;
  velocidad = 500;
  delay(1000);
  esperarInicio();
}