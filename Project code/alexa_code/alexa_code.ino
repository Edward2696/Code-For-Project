

#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <Espalexa.h>




#define Pin1 5  //D1
#define Pin2 4  //D2
#define Pin3 14 //D5
#define Pin4 12 //D6


void device1Changed(uint8_t brightness);
void device2Changed(uint8_t brightness);
void device3Changed(uint8_t brightness);
void device4Changed(uint8_t brightness);


void devFunc1Changed(uint8_t brightness);
void devFunc2Changed(uint8_t brightness);
void devFunc3Changed(uint8_t brightness);


String Device_1_Name = "Red light";
String Device_2_Name = "Green light";
String Device_3_Name = "Blue light";
String Device_4_Name = "Orange light";


String Dev_Func_1_Name = "Living Room";
String Dev_Func_2_Name = "Bed Room";
String Dev_Func_3_Name = "All Home Devices";

Espalexa espalexa;


boolean connectWifi();


const char* ssid = "GA_Apt_87";
const char* password = "gaaccess";

boolean wifiConnected = false;

void setup()
{
  Serial.begin(115200);

  pinMode(Pin1, OUTPUT);
  pinMode(Pin2, OUTPUT);
  pinMode(Pin3, OUTPUT);
  pinMode(Pin4, OUTPUT);

  
  wifiConnected = connectWifi();

  if (wifiConnected)
  {
    // Define your devices here.
    espalexa.addDevice(Device_1_Name, device1Changed);
    espalexa.addDevice(Device_2_Name, device2Changed);
    espalexa.addDevice(Device_3_Name, device3Changed);
    espalexa.addDevice(Device_4_Name, device4Changed);

    // Define your devices functions here.
    espalexa.addDevice(Dev_Func_1_Name, devFunc1Changed);
    espalexa.addDevice(Dev_Func_2_Name, devFunc2Changed);
    espalexa.addDevice(Dev_Func_3_Name, devFunc3Changed);

    espalexa.begin();
  }
  else
  {
    while (1)
    {
      Serial.println("Cannot connect to WiFi. Please check data and reset the ESP.");
      delay(2500);
    }
  }
}

void loop()
{
  espalexa.loop();
  delay(1);
}


void device1Changed(uint8_t brightness){

  
  if (brightness == 255)
    {
      digitalWrite(Pin1, HIGH);
      Serial.println("Device1 ON");
    }
  else if (brightness == 0)
  {
    digitalWrite(Pin1, LOW);
    Serial.println("Device1 OFF");
  }
  else
  {
    int brigh_perc = (brightness/255.)*100;
    analogWrite(Pin1, brightness);
    Serial.print("Device1 Brightness: ");
    Serial.print(brigh_perc);
    Serial.println("%");
    
  }
}

void device2Changed(uint8_t brightness)
{
   
  if (brightness == 255)
    {
      digitalWrite(Pin2, HIGH);
      Serial.println("Device2 ON");
    }
  else
  {
    digitalWrite(Pin2, LOW);
    Serial.println("Device2 OFF");
  }
}

void device3Changed(uint8_t brightness)
{
  
  if (brightness == 255)
    {
      digitalWrite(Pin3, HIGH);
      Serial.println("Device3 ON");
    }
  else
  {
    digitalWrite(Pin3, LOW);
    Serial.println("Device3 OFF");
  }
}

void device4Changed(uint8_t brightness)
{
   
  if (brightness == 255)
    {
      digitalWrite(Pin4, HIGH);
      Serial.println("Device4 ON");
    }
  else
  {
    digitalWrite(Pin4, LOW);
    Serial.println("Device4 OFF");
  }
}


void devFunc1Changed(uint8_t brightness)
{
  
  if (brightness == 255)
    {
      digitalWrite(Pin1, HIGH);
      digitalWrite(Pin2, HIGH);
      Serial.println("Living Room ON");
    }
  else
  {
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, LOW);
      Serial.println("Living Room OFF");
  }
}

void devFunc2Changed(uint8_t brightness)
{
  
  if (brightness == 255)
    {
      digitalWrite(Pin3, HIGH);
      digitalWrite(Pin4, HIGH);
      Serial.println("Bed Room ON");
    }
  else
  {
      digitalWrite(Pin3, LOW);
      digitalWrite(Pin4, LOW);
      Serial.println("Bed Room OFF");
  }
}

void devFunc3Changed(uint8_t brightness)
{
  
  if (brightness == 255)
    {
      digitalWrite(Pin1, HIGH);
      digitalWrite(Pin2, HIGH);
      digitalWrite(Pin3, HIGH);
      digitalWrite(Pin4, HIGH);
      Serial.println("All Home Devices ON");
    }
  else
  {
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, LOW);
      digitalWrite(Pin4, LOW);
      Serial.println("All Home Devices OFF");
  }
}


boolean connectWifi()
{
  boolean state = true;
  int i = 0;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20) {
      state = false; break;
    }
    i++;
  }
  Serial.println("");
  if (state) {
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("Connection failed.");
  }
  return state;
}
