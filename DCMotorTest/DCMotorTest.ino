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

  // while (!Serial) {

  //   ; // wait for serial port to connect. Needed for native USB port only

  // }


  // if (WiFi.status() == WL_NO_MODULE) {

  //   Serial.println("Communication with WiFi module failed!");
  //   while (true);

  // }

  // String fv = WiFi.firmwareVersion();

  // if (fv < WIFI_FIRMWARE_LATEST_VERSION) {

  //   Serial.println("Please upgrade the firmware");

  // }

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

    // Split the received message into two float numbers
    // float num1, num2;
    // sscanf(incomingPacket, "%f,%f", &num1, &num2);
    // Serial.println("First number: " + String(num1));
    // Serial.println("Second number: " + String(num2));

    char *token;

    token = strtok(incomingPacket, ",");
    while(token != NULL) {
      Serial.println(token);   
      token = strtok(NULL, ",");
   }
   Serial.println(incomingPacket);  // Proof that original string is chopped up

    

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