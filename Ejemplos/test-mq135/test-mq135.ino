#define MQ135_PIN 35

float R0 = 398.63; // Valor de la resistencia del sensor en aire limpio

void setup() {
  Serial.begin(115200);
}

void loop() {
  float sensor_volt;
  float RS_gas; // Valor de la resistencia del sensor en presencia de gas
  float ratio; // Relación RS/R0
  float ppm_log;
  float ppm;

  sensor_volt = analogRead(MQ135_PIN);
  sensor_volt = sensor_volt/4095*3.3; // Conversion a voltaje
  RS_gas = (5.0-sensor_volt)/sensor_volt; // Conversion a resistencia del sensor
  ratio = RS_gas/R0; // Calculo de la relación RS/R0
  
  ppm_log = (log10(ratio)-0.42)/-0.42; // Fórmula de la hoja de datos para CO2
  ppm = pow(10, ppm_log);
  
  Serial.print("RS/R0 = ");
  Serial.print(ratio);
  Serial.print("\t PPM = ");
  Serial.println(ppm);

  delay(1000);
}
