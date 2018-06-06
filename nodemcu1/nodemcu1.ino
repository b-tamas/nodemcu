#include <ESP8266WiFi.h>
#include <Arduino.h>

#include "Wifikey.h"
//#####FILE TEMPLATE FOR Wifikey.h#######
//#define SSID "NAME-OF-WIFI-AP"
//#define PASSWORD "PASSWD-OF-THE-WIFI"
//#########################################

const char* ssid = SSID;
const char* password = PASSWORD;

int cnt=0;
 
//int ledPin = 13; // GPIO13
//#define ACTIVE 1;
//#define INACTIVE 0;

int ledPin = LED_BUILTIN;
#define ACTIVE 0
#define INACTIVE 1

unsigned long startTime = millis();
WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, INACTIVE);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");





 
}


WiFiServer telnetServer(23);
WiFiClient serverClient;
 
void loop() {









  
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
 
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  int value = INACTIVE;
  if (request.indexOf("/LED=ON") != -1)  {
    digitalWrite(ledPin, ACTIVE);
    value = ACTIVE;
  }
  if (request.indexOf("/LED=OFF") != -1)  {
    digitalWrite(ledPin, INACTIVE);
    value = INACTIVE;
  }
 
// Set ledPin according to the request
//digitalWrite(ledPin, value);
//////////////////////////////////////////////////////////////////

 client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
client.println("<head><style>body{font-size: 30px}</style></head>");
 
  client.println("<table style=\"height: 500px; border-color: Ffffff;\" border=\"1;\" width=\"80%;\" bgcolor=\"#707070\">");
  client.println("<tbody><tr><td >");
  
  client.println("<p>NodeMCU</p>");
  client.print("<p>IP:</p>");
  client.print(WiFi.localIP());

  client.println("</td><td>Action</td>");
  client.println("</tr> <tr> <td>");
  client.println("LED");
  client.println("</td><td>");
  
  if(value == ACTIVE) {
    client.print("On");
  } else {
    client.print("Off");
  }

client.print("</td><td><p>");
client.println("<a href=\"/LED=ON\"\"><button>Turn On </button></a>");
client.print("</p><p>");
client.println("<a href=\"/LED=OFF\"\"><button>Turn Off </button></a><br />"); 
client.print("</p></td></tr><tr><td>");

client.print("Sensor");
client.print("</td><td>&nbsp;</td><td>&nbsp;</td></tr><tr><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td></tr><tr><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td></tr></tbody></table>");




}
 
