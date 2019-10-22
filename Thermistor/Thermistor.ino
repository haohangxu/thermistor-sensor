// Analog pin
int THERMISTOR_PIN = 0;

// LED pins
int RED_LED = 12;
int GREEN_LED = 11;
int BLUE_LED = 10;

// Constants
float R_known = 10000; // 10K series resistor
float A = 1.0e-03, B = 2.47e-04, C = 2.0e-07; // calibration parameters
int ON = HIGH, OFF = LOW; // nicer semantics
float V_source = 1023.0; // analog to digital full range value is 1023.0

// Variables for temperature computation
int V_thermistor;
float logR, R_thermistor, T_kelvin, T_celsius, T_fahrenheit;

void setup()
{
  // Initialize serial output
  Serial.begin(9600);

  // Initialize LED pins as digital output
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
}

void set_RGB(int red, int green, int blue)
{
  digitalWrite(RED_LED, red);
  digitalWrite(GREEN_LED, green);
  digitalWrite(BLUE_LED, blue);
}

void loop ()
{
  // Compute resistance of thermistor
  V_thermistor = analogRead(THERMISTOR_PIN);
  R_thermistor = R_known * (V_source / (float) V_thermistor - 1.0);

  // https://en.wikipedia.org/wiki/Steinhart%E2%80%93Hart_equation
  logR = log(R_thermistor);
  T_kelvin = (1.0 / (A + B * logR + C * logR * logR * logR));
  T_celsius = T_kelvin - 273.15;
 
  // LED display for temperature ranges
  if (T_celsius > 75)
  {
    set_RGB(ON, OFF, OFF);
  }
  else if (T_celsius > 70)
  {
    set_RGB(OFF, ON, OFF);
  }
  else
  {
    set_RGB(OFF, OFF, ON);
  }

  // Output to screen
  Serial.print("Potential: ");
  Serial.print(V_thermistor);
  Serial.print(" (Volts)\t");
  
  Serial.print("Temperature: ");
  Serial.print(T_celsius, 4);
  Serial.print(" (Celsius)\n");

  delay(500);
}
