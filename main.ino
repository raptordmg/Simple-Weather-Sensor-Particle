// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_DHT.h>

#define DHTPIN 0         
#define DHTTYPE DHT22   
DHT dht(DHTPIN, DHTTYPE);
int analogPin = A1;
double temperature = 0;
double maxTemp = -100;
double minTemp = 100;
double humidity = 0;
int light = 0;
bool isDay = true;
int timeCheck = 0;

int readSensors(String Command){
    temperature = dht.getTempCelcius();
    humidity = dht.getHumidity();
    
    return 1;
}

void setup() {
    dht.begin();

    Particle.variable("maxTemp", maxTemp);
    Particle.variable("minTemp", minTemp);
    Particle.variable("isDay", isDay);
    Particle.variable("light", light);
    Particle.variable("temperature", temperature);
    Particle.variable("humidity", humidity);
}

void loop() {
    
    if (timeCheck + 86400000 < millis()){
        timeCheck = millis();
        minTemp = 100;
        maxTemp = -100;
    }
    
    readSensors("");
    
    if (temperature > maxTemp) {
        maxTemp = temperature;
    }
    
    if (temperature < minTemp){
        minTemp = temperature;
    }
    
    light = analogRead(analogPin);
    
    if (light < 4000) {
        isDay = true;
    } else {
        isDay = false;
    }
    
    delay(60000);
}
