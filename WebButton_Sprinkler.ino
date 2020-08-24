#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h> 
#include <ESP8266mDNS.h>

const char* ssid = "your_ssid"; // replace with your network information
const char* password = "your_password"; // replace with your network information

ESP8266WebServer server(80); //creates a webserver on port 80

int DA=0;//Direction A pin GPIO 0
int PWMA=5;//PWM A pin GPIO5
int valveState = LOW; //valve is closed to begin

void handleRoot();              //functions for handling http
void handleWatering();
void handleNotFound();

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(2000);
  pinMode(PWMA, OUTPUT);
  pinMode(DA, OUTPUT);
  // Wait for serial to initialize.
  while(!Serial) { }
  
  while(WiFi.status() != WL_CONNECTED){
    Serial.println("Connecting...");
    delay(200);
  }
   if (WiFi.status() == WL_CONNECTED) {
        Serial.println(WiFi.localIP()); //print local ip address
        if (MDNS.begin("water")) {              // start mDNS responder for water.local
        Serial.println("mDNS responder started");
        } else {
          Serial.println("Error! MDNS responder didn't start successfully");
        }
        server.on("/", HTTP_GET, handleRoot);     // Call handleroot when / is requested
        server.on("/Water", HTTP_POST, handleWatering);  // calss handleWatering when /Water request is made
        server.onNotFound(handleNotFound);        // when something unknown is requested call function "handleNotFound"
        server.begin();                           // start the server
        Serial.println("HTTP server started");
        }
        else{
          Serial.print("Error connecting to wifi");
    }
  }

void loop() {
  server.handleClient();  // Listen for HTTP requests from clients
  MDNS.update(); // updates the mDNS
}


void handleRoot() {                         // When URI / is requested, send website with button
  server.send(200, "text/html", "<form action=\"/Water\" method=\"POST\"><input type=\"submit\" value=\"Water Plant On/Off\"></form>");
}

void handleWatering() {  // If a POST request is made to URI /Water
  valveState = !valveState; //reverses the state of the valve
  digitalWrite(PWMA, valveState);      // opens or closes value based on reversed state above
  server.sendHeader("Location","/");        // Tells browser to go back to homepage
  server.send(303);                         // Sends http 303 for redirect
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 when anything else is sent
}
