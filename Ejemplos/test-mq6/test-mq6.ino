#define MQ6_PIN 34

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
