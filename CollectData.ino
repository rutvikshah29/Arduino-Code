#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 5  // digital pin 5 for temperature sensor
#define SENSOR A0

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Temperatur sensor variables
float Celcius=0.0;
float Fahrenheit=0.0;
float cavg, favg;
float totalC = 0.0;
float totalF = 0.0;

//Turbidity sensor variables
float totalVoltage = 0.0;
float totalTurbidity = 0.0;
float voltage, turbidity, voltAvg, turbidityAvg;

void setup()
{
  
  Serial.begin(9600);

  if (Serial.available()){   // RPi to Arduino serial communication
    
    if(Serial.read() - '0' == 1){
      
      pinMode(SENSOR,INPUT);
      sensors.begin();
      
      for(int i=0;i<=200;i++){
        
        voltage = (5.0 / 1024.0)*analogRead(SENSOR);  //in V- convert the analog reading (0-1023) to a voltage (0 - 5V)
        turbidity =(-1120.4*(voltage+0.3)*(voltage+0.3))+(5742.3*(voltage+0.3))-4352.9;  //in NTU - convert the voltage to Nephelometric Turbidity unit.(0=clear; 3000= very turbid)
        totalVoltage += voltage;
        totalTurbidity += turbidity;
        //delay(5);
       }
       
       voltAvg = totalVoltage/200;
       turbidityAvg = totalTurbidity/200;
  
       if((voltAvg>=1.5)&(turbidityAvg>=0)) {
  
          Serial.println("Voltage="+String(voltAvg)+" V Turbidity="+String(turbidityAvg)+" NTU");  
          
          //delay(500);
       }
  
       for(int i=0; i<50;i++){
        
         sensors.requestTemperatures(); 
         Celcius = sensors.getTempCByIndex(0);
         Fahrenheit = sensors.toFahrenheit(Celcius);
         totalC += Celcius;
         totalF += Fahrenheit;
         delay(5); 
       }

       Serial.print("Temperature: ");
       Serial.print(totalC/50);
       Serial.print("*C  ");
       Serial.print(totalF/50);
       Serial.println("*F  ");


    }
  }
}


  
void loop(){
   
}
