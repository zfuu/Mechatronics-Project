#include <ArduinoMotorCarrier.h>
#include <WiFiNINA.h>
#include "arduino_secrets.h"


const char* ssid = "Ben's iPhone";
const char* password = "01234567";

WiFiUDP Udp;
unsigned int localPort = 8080;

void setup() {
  Serial.begin(115200);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Udp.begin(localPort);
}

void loop() {
  char incomingPacket[255];
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
    float num1, num2;
    sscanf(incomingPacket, "%f,%f", &num1, &num2);
    Serial.println("First number: " + String(num1));
    Serial.println("Second number: " + String(num2));
  }
}
