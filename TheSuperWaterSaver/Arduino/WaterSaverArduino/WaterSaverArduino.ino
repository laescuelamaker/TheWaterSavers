/*
 * Programa para la creación de nuestro prototipo TheSuperWaterSaver (SWS)
 * medición en tiempo real del consumo de agua en una casa, mostrandolo por una pantalla lcd. 
 * 
 * Creado por La Escuela Maker
 * Licencia GPL
 */

// Incluimos la librería para poder usar la pantalla
#include <LiquidCrystal.h>

const int sensorPin = 2;            // Conectamos el caudalímetro al pin digital 2 (D2)
const int measureInterval = 2500;
volatile int pulseConter;

// YF-S201                          // Especificamos el modelo de nuestro caudalímetro por su factor K
const float factorK = 7.5;

// FS300A
//const float factorK = 5.5;

// FS400A
//const float factorK = 3.5;


void ISRCountPulse()
{
  pulseConter++;
}

float GetFrequency()
{
  pulseConter = 0;

  interrupts();
  delay(measureInterval);
  noInterrupts();

  return (float)pulseConter * 1000 / measureInterval;
}

LiquidCrystal lcd(7, 8, 9, 10, 11 , 12);


void setup()
{
  Serial.begin(9600);  
    lcd.begin(16, 2);
    lcd.setCursor(0,0);
    lcd.write("The Super Water Saver");
    delay(3000);
  attachInterrupt(digitalPinToInterrupt(sensorPin), ISRCountPulse, RISING);
}

void loop()
{
  // obtener frecuencia en Hz
  float frequency = GetFrequency();

  // calcular caudal L/min
  float flow_Lmin = frequency * factorK;c

  Serial.print("Frecuencia: ");
  Serial.print(frequency, 0);
  Serial.print(" (Hz)\tCaudal: ");
  Serial.print(flow_Lmin, 3);
  Serial.println(" (L/min)");
 
}
