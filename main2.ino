// Basic serial communication with ESP8266
// Uses serial monitor for communication with ESP8266
//
//  Pins
//  Arduino pin 2 (RX) to ESP8266 TX
//  Arduino pin 3 to voltage divider then to ESP8266 RX
//  Connect GND from the Arduiono to GND on the ESP8266
//  Pull ESP8266 CH_PD HIGH
//
// When a command is entered in to the serial monitor on the computer 
// the Arduino will relay it to the ESP8266
//
 int ind1; // , locations
int ind2;
int ind3;
int ind4;
String ssid; //data String
String psword;
String api;
String duration;
#include <SoftwareSerial.h>
SoftwareSerial ESPserial(10, 11); // RX | TX
 
void setup() 
{
    Serial.begin(9600);     // communication with the host computer
    //while (!Serial)   { ; }
 
    // Start the software serial for communication with the ESP8266
    ESPserial.begin(9600);  
 
    Serial.println("");
    Serial.println("Remember to to set Both NL & CR in the serial monitor.");
    Serial.println("Ready");
    Serial.println("");    
}
 
void loop() 
{
    // listen for communication from the ESP8266 and then write it to the serial monitor
    if ( ESPserial.available() )   {  
    //  Serial.write( ESPserial.read() ); 
       if (ESPserial.find("+IPD,"))
          {
            String msg;
            ESPserial.find("/");
            msg = ESPserial.readStringUntil(' ');
            Serial.println(msg);
            ind1 = msg.indexOf(';');  //finds location of first ,
            ssid = msg.substring(0, ind1);   //captures first data String
            ind2 = msg.indexOf(';', ind1+1 );   //finds location of second ,
            psword = msg.substring(ind1+1, ind2+1);   //captures second data String
            ind3 = msg.indexOf(';', ind2+1 );
            api = msg.substring(ind2+1, ind3+1);
            ind4 = msg.indexOf(';', ind3+1 );
            duration = msg.substring(ind3+1); //captures remain part of data after last ,
             Serial.print("ssid = ");
             Serial.println(ssid); 
             Serial.print("password = ");
             Serial.println(psword);
              Serial.print("api = ");
             Serial.println(api);
             Serial.print("duration = ");
             Serial.println(duration);
             
      }
    }
    // listen for user input and send it to the ESP8266
    if ( Serial.available() )       {  ESPserial.write( Serial.read() );  }

    
}
