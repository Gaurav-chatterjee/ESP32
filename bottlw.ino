#include <WiFi.h>
#include <HTTPClient.h>

int voutq=0,voutq1=0;
float vin=3.3,vout;
float R1=1000,R2,R3=12000,R4;
 
const char* ssid = "Campus Connect CUK";
const char* password =  "cuk2828";
 
void setup() {
 
  Serial.begin(9600);
  delay(4000);   
 
  WiFi.begin(ssid, password); 
 
  while (WiFi.status() != WL_CONNECTED) { //Check for the connection
    delay(500);
    Serial.println("Connecting..");
  }
 
  Serial.print("Connected to the WiFi network with IP: ");
  Serial.println(WiFi.localIP());
}
 
void loop() {
  voutq=analogRead(32);
  vout=vin*voutq/4096;
  R2=R1*((vin)/(vout)-1.0);
  String a=String (R2);

  voutq1=analogRead(35);
  vout=vin*voutq1/4096;
  R4=R3*((vin)/(vout)-1.0);
  String b=String (R4);
 
 if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
 
   HTTPClient http;   
 
   http.begin("http://10.58.6.86:8090/");  //Specify destination for HTTP request
   http.addHeader("Content-Type", "text/plain");             //Specify content-type header
 
   int httpResponseCode1 = http.POST("Hello CUK this is from ESP32");
   int httpResponseCode2 = http.POST(a); //Send the actual POST request
   int httpResponseCode3 = http.POST(b); 
 
   if(httpResponseCode1>0&&httpResponseCode2>0&&httpResponseCode3>0){

    String response=http.getString();
    Serial.println(httpResponseCode1);
    Serial.println(httpResponseCode2);//Print return code
    Serial.println(httpResponseCode3);
    Serial.println(response);
 
   }else{
 
    Serial.print("Error on sending request: ");
    Serial.println(httpResponseCode1);
 
   }
 
   http.end();  //Free resources
 
 }else{
 
    Serial.println("Error in WiFi connection");   
 
 }
 
  delay(5000);  //Send a request every 5 seconds
 
}
