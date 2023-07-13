/*

Creado por: Hugo Escalpelo
Fecha: 20230710

Este programa es para probar todos los sensores del detector de gases y el semaforo
a la vez. Este programa envìa el resultado via serial de la siguiente forma:
[mq6,mq135,semaforo]
[float,float,int]

El rango del semaforo es el siguiente:

0 = Rojo
1 = Amarillo
2 = Verde

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

ESP32CAM    MQ6
5v----------VCC
GND---------GND
GPIO14------A0

ESP32CAM    MQ135
5v----------VCC
GND---------GND
GPIO15------A0


*/

#define MQ6_PIN 14
#define MQ135_PIN 15
#define RED_LED_PIN 2
#define YELLOW_LED_PIN 13
#define GREEN_LED_PIN 12

float R0_MQ6 = 9.83; // Valor de la resistencia del sensor MQ6 en aire limpio
float R0_MQ135 = 398.63; // Valor de la resistencia del sensor MQ135 en aire limpio

unsigned long previousMillisMQ6 = 0;
unsigned long previousMillisMQ135 = 0;
const long interval = 1000;  // intervalo de actualización (1 segundo)

float ppm_mq6;
float ppm_mq135;

int semaphoreStatus = -1;

void setup() {
  Serial.begin(115200);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillisMQ6 >= interval) {
    previousMillisMQ6 = currentMillis;
    readAndCalculateMQ6();
  }

  if (currentMillis - previousMillisMQ135 >= interval) {
    previousMillisMQ135 = currentMillis;
    readAndCalculateMQ135();
  }
}

void readAndCalculateMQ6() {
  float sensor_volt = analogRead(MQ6_PIN);
  sensor_volt = sensor_volt/4095*3.3; // Conversion a voltaje
  float RS_gas = (5.0-sensor_volt)/sensor_volt; // Conversion a resistencia del sensor
  float ratio = RS_gas/R0_MQ6; // Calculo de la relación RS/R0
  
  float ppm_log = (log10(ratio)-2.3)/-1.36; // Fórmula de la hoja de datos para LPG
  ppm_mq6 = pow(10, ppm_log);

  updateTrafficLight();
}

void readAndCalculateMQ135() {
  float sensor_volt = analogRead(MQ135_PIN);
  sensor_volt = sensor_volt/4095*3.3; // Conversion a voltaje
  float RS_gas = (5.0-sensor_volt)/sensor_volt; // Conversion a resistencia del sensor
  float ratio = RS_gas/R0_MQ135; // Calculo de la relación RS/R0
  
  float ppm_log = (log10(ratio)-2.3)/-1.36; // Fórmula de la hoja de datos para el aire
  ppm_mq135 = pow(10, ppm_log);

  updateTrafficLight();
}

void updateTrafficLight() {
  digitalWrite(RED_LED_PIN, HIGH);
  digitalWrite(YELLOW_LED_PIN, HIGH);
  digitalWrite(GREEN_LED_PIN, HIGH);

  if (ppm_mq6 < 20 && ppm_mq135 < 400) {
    digitalWrite(GREEN_LED_PIN, LOW);
    semaphoreStatus = 2; // Verde
  } else if ((ppm_mq6 > 20 || ppm_mq135 > 400) && (ppm_mq6 < 50 || ppm_mq135 < 600)) {
    digitalWrite(YELLOW_LED_PIN, LOW);
    semaphoreStatus = 1; // Amarillo
  } else if (ppm_mq6 > 50 || ppm_mq135 > 600) {
    digitalWrite(RED_LED_PIN, LOW);
    semaphoreStatus = 0; // Rojo
  }

  sendSerialMessage();
}

void sendSerialMessage() {
  Serial.print(ppm_mq6);
  Serial.print(",");
  Serial.print(ppm_mq135);
  Serial.print(",");
  Serial.println(semaphoreStatus);
}