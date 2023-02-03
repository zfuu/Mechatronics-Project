#include <ArduinoMotorCarrier.h>
#include <SPI.h>
#include <WiFiNINA.h>
#include "arduino_secrets.h"

#define INTERRUPT_PIN 6
#define MAX_POWER 70.0

#define DRIVE_ADJUST 0.08
#define TURN_ADJUST 0.03

#define mA -0.5
#define mB -1.0
#define mC 0.5
#define mD -1.0


//Variable to store the battery voltage
static int batteryVoltage;

static float drive = 0.0;
static float turn = 0.0;

static float power_L = 0.0;
static float power_R = 0.0;

int cmd;

// bool w = false;
// bool a = false;
// bool s = false;
// bool d = false;


//Wifi setup
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
int keyIndex = 0;             // your network key Index number (needed only for WEP)

int led =  LED_BUILTIN;
int status = WL_IDLE_STATUS;

WiFiServer server(80);



void setup(){
  //Serial port initialization
  Serial.begin(115200);
  Serial.setTimeout(1);

  // //Establishing the communication with the Motor Carrier
  if (controller.begin()){
    Serial.print("Motor Carrier connected, firmware version ");
    Serial.println(controller.getFWVersion());
  }else{
    Serial.println("Couldn't connect! Is the red LED blinking? You may need to update the firmware with FWUpdater sketch");
    while (1);
  }

  // Reboot the motor controller; brings every value back to default
  Serial.println("reboot");
  controller.reboot();
  delay(500);

  int dutyInit = 0; // at 50 it works as expected, at 60 shift sides and is too small duty to move, at 70 is very big duty.
  M1.setDuty(dutyInit);
  M2.setDuty(dutyInit);
  Serial.print("Duty init: ");
  Serial.println(dutyInit);






  //Wifi setup
  Serial.println("Access Point Web Server");

  pinMode(led, OUTPUT);      // set the LED pin mode

  if (WiFi.status() == WL_NO_MODULE) {

    Serial.println("Communication with WiFi module failed!");
    while (true);
  }

  // by default the local IP address of will be 192.168.4.1
  // you can override it with the following:
  // WiFi.config(IPAddress(10, 0, 0, 1));
  // print the network name (SSID);
  
  // Create open network. Change this line if you want to create an WEP network:
  status = WiFi.beginAP(ssid, pass);

  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("PASS: ");
  Serial.println(pass);

  if (status != WL_AP_LISTENING) {
    Serial.println("Creating access point failed");
    while (true);
  }

  // wait for connection:
  // delay(100000); //100 seconds
  delay(3000);  //3 seconds

  server.begin(); //port 80
  printWiFiStatus();
}


// void loop() {

//   while (!Serial.available());
//   cmd = Serial.readString().toInt();
// }

void loop() {

  // Update client device data
  if (status != WiFi.status()) {
    status = WiFi.status();

    if (status == WL_AP_CONNECTED) {
      Serial.println("Device connected to AP");
    } else {
      Serial.println("Device disconnected from AP");
    }
  }


  WiFiClient client = server.available();
  if (client) {
    Serial.println("new client");
    String currentLine = "";
    while (client.connected()) {// loop while the client's connected
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            // the content of the HTTP response follows the header:
            client.print("Click <a href=\"/H\">here</a> to go forward<br>");
            client.print("Click <a href=\"/L\">here</a> to go backward<br>");
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          }else{      // if you got a newline, then clear currentLine:
            currentLine = "";
          }

        }else if (c != '\r') {    // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(led, HIGH);               // GET /H turns the LED on
          M1.setDuty(15);
          M2.setDuty(-15);
          Serial.print("currentLineRequest:    ");
          Serial.println(currentLine);
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(led, LOW);                // GET /L turns the LED off
          M1.setDuty(-15);
          M2.setDuty(15);
          Serial.print("currentLineRequest:    ");
          Serial.println(currentLine);
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disconnected");

  }
}




void printWiFiStatus() {

  // print the SSID of the network you're attached to:


  Serial.println("-----Printing Wi-Fi Status-----");
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:

  IPAddress ip = WiFi.localIP();

  Serial.print("IP Address: ");

  Serial.println(ip);

  // print where to go in a browser:

  Serial.print("To see this page in action, open a browser to http://");

  Serial.println(ip);

}
