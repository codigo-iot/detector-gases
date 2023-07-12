/*

Creado por: Hugo Escalpelo
Fecha: 20230710

Este programa es para probar el semáforo que se usará en el circuito
para tener una forma local y no dependiente de WiFi para conocer el
estado de la calidad del aire. Se debe realizar una conexión en modo
drain, lo que significa que para cada led, se conectará una resistencia
de 220 ohms a 5v, a esa resistencia se conectará la terminal positiva
del led y la terminal negativa de cada led se conectará al pin GPIO
correspondiente en el micro controlador.

Conexiones:

 5v
----
  |
  |
  R220
  |
  |
  +
  LED
  -
  |
  |
  GPIO

ESP32CAM    Catodo-Led
GPIO02------Rojo
GPIO13------Amarillo
GPIO12------Verde

*/

#define RED_LED_PIN 2
#define YELLOW_LED_PIN 13
#define GREEN_LED_PIN 12

void setup() {
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);

  // Inicializar los LEDs en estado apagado
  digitalWrite(RED_LED_PIN, HIGH);
  digitalWrite(YELLOW_LED_PIN, HIGH);
  digitalWrite(GREEN_LED_PIN, HIGH);
}

void loop() {
  digitalWrite(RED_LED_PIN, LOW); // Encender LED rojo
  delay(1000); // Esperar un segundo
  digitalWrite(RED_LED_PIN, HIGH); // Apagar LED rojo

  digitalWrite(YELLOW_LED_PIN, LOW); // Encender LED amarillo
  delay(1000); // Esperar un segundo
  digitalWrite(YELLOW_LED_PIN, HIGH); // Apagar LED amarillo

  digitalWrite(GREEN_LED_PIN, LOW); // Encender LED verde
  delay(1000); // Esperar un segundo
  digitalWrite(GREEN_LED_PIN, HIGH); // Apagar LED verde
}