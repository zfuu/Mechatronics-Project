#include <ArduinoMotorCarrier.h>
#include <SPI.h>
#include <WiFiNINA.h>
#include <WiFiUdp.h>
#include "arduino_secrets.h"

int status = WL_IDLE_STATUS;

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
int keyIndex = 0;

unsigned int localPort = 2390;

char incomingPacket[256];

WiFiUDP Udp;

void setup() {

  Serial.begin(115200);

  //Connecting to wifi
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(1000);
  }

  Serial.println("Connected to wifi");
  printWifiStatus();
  Serial.println("\nStarting connection to server...");

  Udp.begin(localPort);

  int dutyInit = 0; // at 50 it works as expected, at 60 shift sides and is too small duty to move, at 70 is very big duty.
  M1.setDuty(dutyInit);
  M2.setDuty(dutyInit);
  Serial.print("Duty init: ");
  Serial.println(dutyInit);
}

void loop() {

  int packetSize = Udp.parsePacket();

  if (packetSize) {
    // read the packet into packetBufffer
    int len = Udp.read(incomingPacket, 255);
    if (len > 0) {
      incomingPacket[len] = 0;
    }
    // print out the received message
    Serial.println("Received packet: " + String(incomingPacket));

    char *token;
    int left, right = 0;
    token = strtok(incomingPacket, ",");

    left = atoi(token);
    token = strtok(NULL, ",");
    right = atoi(token); 
    Serial.print(left);
    Serial.println(right);

    M1.setDuty(left);
    M2.setDuty(right);

  }
}

void printWifiStatus() {

  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  // print the received signal strength:

  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}