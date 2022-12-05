#include <SoftwareSerial.h>
#include <L298N_MotorDriver.h>
SoftwareSerial esp(2,3);
L298N_MotorDriver motor(2,3,4);
 
#define DEBUG true
#define IP “184.106.153.149”
String Api_key = “GET /update?key=YDM4LW9014WZFXZM”; //change it with your api key like “GET /update?key=Your Api Key”

Int error;
Const int sensor_pin = A0;
Float solar;  
Float output;  

Void setup()
{
  Serial.begin(9600);
  Esp.begin(9600);
  pinMode(sensor_pin,INPUT);
 
  send_command(“AT+RST\r\n”, 2000, DEBUG); //reset module
  send_command(“AT+CWMODE=1\r\n”, 1000, DEBUG); //set station mode
  send_command(“AT+CWJAP=\”SOHEL\”,\”Password\”\r\n”, 2000, DEBUG);   //connect wifi network
  while(!esp.find(“OK”)) { //wait for connection
  Serial.println(“Connected”);
   pinMode(13,OUTPUT);
  pinMode(8,OUTPUT);
   pinMode(9,OUTPUT);}
}

Void loop()
{
 
 
  Output=analogRead(sensor_pin);
  Solar =(output*500)/1023;
  Start: //label
  Error=0;
  Updatedata();
  If (error==1){
    Goto start; //go to label “start”
  }
  Delay(1000);
}

Void updatedata(){
  String command = “AT+CIPSTART=\”TCP\”,\””;
  Command += IP;
  Command += “\”,80”;
  Serial.println(command);
  Esp.println(command);
  Delay(2000);
  If(esp.find(“Error”)){
    Return;
  }
  Command = Api_key ;
  Command += “&field1=”;  
  Command += solar;
  Command += “\r\n”;
  Serial.print(“AT+CIPSEND=”);
  Esp.print(“AT+CIPSEND=”);
  Serial.println(command.length());
  Esp.println(command.length());
  If(esp.find(“>”)){
    Serial.print(command);
    Esp.print(command);
  }
  Else{
   
   Serial.println(“AT+CIPCLOSE”);
   Esp.println(“AT+CIPCLOSE”);
    //Resend…
    Error=1;
  }
  }

String send_command(String command, const int timeout, boolean debug)
{
  String response = “ ”;
  Esp.print(command);
  Long int time = millis();
  While ( (time + timeout) > millis())
  {
    While (esp.available())
    {
      Char c = esp.read();
      Response += c;
    }
  }
  If (debug)
  {
    Serial.print(response);
  }
  Return response;
}
