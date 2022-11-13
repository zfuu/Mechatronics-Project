#include <ArduinoMotorCarrier.h>
#define INTERRUPT_PIN 6

//Variable to store the battery voltage
static int batteryVoltage;

//Variable to change the motor speed and direction
static int duty = 0;

int x;

bool w = false;
bool a = false;
bool s = false;
bool d = false;


void setup(){
  //Serial port initialization
  Serial.begin(115200);
  Serial.setTimeout(1);

  // //Establishing the communication with the Motor Carrier
  // if (controller.begin()){
  //   Serial.print("Motor Carrier connected, firmware version ");
  //   Serial.println(controller.getFWVersion());
  // }else{
  //   Serial.println("Couldn't connect! Is the red LED blinking? You may need to update the firmware with FWUpdater sketch");
  //   while (1);
  // }

  // // Reboot the motor controller; brings every value back to default
  // Serial.println("reboot");
  // controller.reboot();
  // delay(500);

  // int dutyInit = 0; // at 50 it works as expected, at 60 shift sides and is too small duty to move, at 70 is very big duty.
  // M1.setDuty(dutyInit);
  // M2.setDuty(dutyInit);
  // Serial.print("Duty init: ");
  // Serial.println(dutyInit);

}


void loop() {

  //Take the battery status
  // float batteryVoltage = (float)battery.getConverted();

  //Reset to the default values if the battery level is lower than 11 V
  // if (batteryVoltage < 11){
  //   Serial.println(" ");
  //   Serial.println("WARNING: LOW BATTERY");
  //   Serial.println("ALL SYSTEMS DOWN");
  //   M1.setDuty(0);
  //   M2.setDuty(0);
  //   while (batteryVoltage < 11){
  //     batteryVoltage = (float)battery.getConverted();
  //   }
  // }



  // M1.setDuty(69);
  // M2.setDuty(-69);

  while (!Serial.available());
  x = Serial.readString().toInt();
  // x = Serial.read();
  Serial.print(x);


  //Keep active the communication between Nano & Motor Carrier
  //Ping the SAMD11
  // controller.ping();
  //wait
  // delay(50);


}
