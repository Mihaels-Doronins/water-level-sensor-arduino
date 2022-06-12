/* Creared by Michael Doronin
 * https://github.com/Mihaels-Doronins
 * Water level sensor code
 * 22.06.2022
*/ 

const int squeaker = A4;   // Pin for sending signal to squeaker or light diode.
const int water = A5;     // Pin for signal reading grom water sensor.

int resval;                 // Value from water level sensor
int next_delay = 300;       // Delay for next check of water level on the start
int min_freq = 2;           // Minmal frequency
int max_freq = 200;         // Maximal frequency

// Uzreiz sarēķināsim periodus
int min_t = 1000 / max_freq;  // Minimal period: Simple math T = 1/f
int max_t = 1000 / min_freq;

void setup() {
  Serial.begin(9600);         
  pinMode(squeaker,OUTPUT);   
  }

void loop() {
  
  resval = analogRead(water); // Read data from water level sensor

  if (resval > 400) // If signal stronger than 400, we will turn of signalisation 
    {
    // Set frequency based on signal strenght
    int freq = map(resval - 400, 0, 310, min_freq, max_freq); 

    // Find period
    next_delay = map(freq, min_freq, max_freq, max_t, min_t); 

    // Retranslate signal to  
    analogWrite(squeaker,resval);                             
    }
  else // If signal weaker than 400, going back to default frequency and turning off signaisation
    {
    next_delay = 300;
    }
  
  Serial.println(resval);    
  delay(next_delay);         
  analogWrite(squeaker,0);   
  delay(next_delay);         
}
