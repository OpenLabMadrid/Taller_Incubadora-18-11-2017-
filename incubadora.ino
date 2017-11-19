//-------------------------------OpenLabMadrid-------------------------------
#include <DHT.h>

#define DHTPIN 3    // Sensor connected to the pin 3

#define RELE 2  // Relay connected to the pin 3

#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

DHT dht(DHTPIN, DHTTYPE);

float e;  //error variable

float T; //Time that Light bulb is turned down in an interval of 5 seconds

int objetivo = 35; //target temperature

int v = 0;


//---------------------------------------------------------------------------

void setup() {

  Serial.begin(9600);

  dht.begin();

  pinMode(RELE,OUTPUT); 

  digitalWrite(RELE,HIGH);

}

//---------------------------------------------------------------------------


void loop() {

  //This fails if the sensor its not connected

  float t = dht.readTemperature();

    if (isnan(t)) {

    Serial.println("Failed to read from DHT sensor!");

    return;

  }
  e = (float)objetivo-t;

  T = (float)(1-(e/9));//The 9 has been fitted manually,probably you will need to modify it for your own system

  Serial.println(t);

  //Output function

  if (T < 0) T = 0;

  if (T<1)

  {

     digitalWrite(RELE,HIGH);

     delay(5000*(1-T));

     digitalWrite(RELE,LOW);

     delay(5000*T);

   }  else //If we are above the target temperature,the light bulb is turned down.

   {

    delay(2000);

    digitalWrite(RELE,LOW);

   }

}
