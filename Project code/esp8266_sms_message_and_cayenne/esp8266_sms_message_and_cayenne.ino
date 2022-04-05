
#include <CayenneMQTTESP8266.h> 

#include <ESP8266WiFi.h> 


 

char ssid[] = "GA_Apt_87"; 


char password[]="gaaccess"; 


char username[] = "3c1d9c50-9edc-11ec-8c44-371df593ba58"; 

char mqtt_password[] = "22b0e581cc6c347b9183c63b5252bbe51b79b311"; 

char client_id[] = "d1021ef0-9f2b-11ec-8c44-371df593ba58"; 


const int PIRpin = D0;


int PIRval = 0; 



void setup()  

 {  


pinMode(PIRpin,INPUT);

  

Serial.begin(9600); 

Cayenne.begin(username,mqtt_password,client_id,ssid,password);  

 

  } 

void loop()  

{  

  Cayenne.loop();  

 

PIRval = digitalRead(PIRpin); 

Serial.println(PIRval); 




       Cayenne.virtualWrite(0,PIRval); 



}
