float temp(){
  float tempC;  
  tempC = analogRead(Temp_Pin);           //read the value from the sensor
  tempC = (5.0 * tempC * 100.0)/1024.0;  //convert the analog data to temperature
  return tempC;
}

int luz(){  
  int photocellReading;     // the analog reading from the analog resistor divider
   photocellReading = analogRead(LDR_Pin);  
  return photocellReading;
}

