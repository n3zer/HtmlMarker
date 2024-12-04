#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "NeMarker.cpp"

#define ssid "HG-BEE"
#define password "1234567887654321"

IPAddress gateway(10,1,30,68);
IPAddress local_ip(10,1,30,252);
IPAddress subnet(255,255,255,0);


ESP8266WebServer server(80);

NeMarker neMarker;

void connectToWifi(){
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);

    WiFi.config(local_ip, gateway, subnet);

    Serial.print("Connecting to ");
    Serial.println(ssid);


    while(WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println("");

    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}


void setup() {
    Serial.begin(9600);
    neMarker = NeMarker();
    connectToWifi();


    server.on("/", HTTP_GET, []() {
        server.send(200, "text/html", neMarker.getHTML("index.html", "world", "completed"));
    });

    server.begin();
}

void loop() {
    server.handleClient();
}