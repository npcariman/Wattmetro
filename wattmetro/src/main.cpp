#include <Arduino.h>
#include <SDFat.h>
#include <SPI.h>
#include <custom_dataLogger.h>

SdFat Sd;           // Instancia para trabajar con la SD
SdFile MyFile;      // Instancia para manipular datos
DataLogger dataLog; // Objeto DataLogger

#define pinVoltage PA2
#define pinCurrent PA3
#define N_BITS 12
#define PIN_SD PA2
#define PIN_ERROR_SD 

int N_volt, N_curr;
double volt, curr;

void setup() {
  Serial.begin(115200);
  Serial.println(F("Watmetro"));
  // put your setup code here, to run once:
  
  // Configuramos los pines de salida modulo SD y Ethernet mas selector de error
  pinMode(PIN_SD, OUTPUT);
  pinMode(PIN_ERROR_SD, OUTPUT);

  // Damos valores iniciales a dichos pines
  digitalWrite(PIN_ERROR_SD, LOW);        // SD sin error
  digitalWrite(PIN_SD, LOW);              // Activamos la SD
  
  // Iniciamos la SD
  if (!Sd.begin(PIN_SD, SPI_FULL_SPEED)){
    // En caso de encontrar un error, lo indicamos en el pin de salida
    digitalWrite(PIN_ERROR_SD, HIGH);
  }

}

void loop() {
  N_volt = analogRead(pinVoltage);
  volt = ((double) N_volt) * 0.004021743;
  Serial.print("N_voltage:"); Serial.print(N_volt); Serial.print(",");
  Serial.print("voltage:");   Serial.print(volt);   Serial.print(",");

  N_curr = analogRead(pinCurrent);
  curr = ((double) N_curr) * 0.00018;
  Serial.print("N_current:"); Serial.print(N_curr); Serial.print(",");
  Serial.print("current:");   Serial.print(curr);
  
  Serial.println("");
  delay(1);

}