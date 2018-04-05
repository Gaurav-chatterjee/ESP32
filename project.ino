#include<WiFi.h>
#include<HTTPClient.h>
int voutq1=0;
int voutq2=0;
float vin=3.3,vout1,vout2;
float R1=2200,R2;
float R3=2200,R4;

const char * ssid ="Campus Connect CUK";
const char * password="cuk2828";

void setup()
{
  Serial.begin(9600);
  delay(1000);
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(500);
    Serial.println("Connecting...");
  }
  Serial.print("Connect to the network with IP:");
  Serial.println(WiFi.localIP());
}

void loop()
{
  voutq1=analogRead(32);
  vout1=vin*voutq1/4096;
  R2=R1*((vin)/(vout1)-1.0);
  String a= String (R2);

  voutq2=analogRead(32);
  vout2=vin*voutq2/4096;
  R4=R3*((vin)/(vout2)-1.0);
  String b= String (R4);

  if(WiFi.status()==WL_CONNECTED)
  {
    HTTPClient http;

    http.begin("http://10.58.6.86:8090/");
    http.addHeader("Content-Type","text/plain");

    int httpResponseCode1= http.POST("Hello CUK this is from ESP32");
    int httpResponseCode2= http.POST(a);
    int httpResponseCode3= http.POST(b);

    if(httpResponseCode1>0&&httpResponseCode2>0&&httpResponseCode3>0)
    {
      String response= http.getString();
      Serial.println(httpResponseCode1);
      Serial.println(httpResponseCode2);
      Serial.println(httpResponseCode3);
      Serial.println(response);
    }
    else
    {
      Serial.print("Error on sending request");
      Serial.println(httpResponseCode1);
    }
    http.end();
  }
  else
  {
    Serial.println("Error in WiFi Connection");
  }
  delay(1000);
}

