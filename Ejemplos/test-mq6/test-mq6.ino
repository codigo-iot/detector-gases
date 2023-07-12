/*

Creado por: Hugo Escalpelo
Fecha: 20230710

Este programa es para probar el sensor de gas MQ-6, el cual es sensible
a gas LP. Es muy importante notar que este programa no parte de un método
de calibración, por lo que debe ser ajustado segun las condiciones
indicadas en el datasheet del fabricante.

Conexiones:

ESP32CAM    MQ6
5v----------VCC
GND---------GND
GPIO14------A0
*/

#define MQ6_PIN 14

float R0 = 9.83; // Valor de la resistencia del sensor en aire limpio

void setup() {
  Serial.begin(115200);
}

void loop() {
  float sensor_volt;
  float RS_gas; // Valor de la resistencia del sensor en presencia de gas
  float ratio; // Relación RS/R0
  float ppm_log;
  float ppm;

  sensor_volt = analogRead(MQ6_PIN);
  sensor_volt = sensor_volt/4095*3.3; // Conversion a voltaje
  RS_gas = (5.0-sensor_volt)/sensor_volt; // Conversion a resistencia del sensor
  ratio = RS_gas/R0; // Calculo de la relación RS/R0
  
  ppm_log = (log10(ratio)-2.3)/-1.36; // Fórmula de la hoja de datos para LPG
  ppm = pow(10, ppm_log);
  
  Serial.print("RS/R0 = ");
  Serial.print(ratio);
  Serial.print("\t PPM = ");
  Serial.println(ppm);

  delay(1000);
}
