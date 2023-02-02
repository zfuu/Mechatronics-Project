#include <ArduinoMotorCarrier.h>
#include <WiFiNINA.h>

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

bool w = false;
bool a = false;
bool s = false;
bool d = false;


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

}


void loop() {

  while (!Serial.available());
  cmd = Serial.readString().toInt();
  // cmd = Serial.read();

  switch (cmd){
    case 0:
      w = false;
      a = false;
      s = false;
      d = false;
      break;
    case 1:
      w = true;
      a = false;
      s = false;
      d = false;
      break;
    case 2:
      w = false;
      a = true;
      s = false;
      d = false;
      break;
    case 3:
      w = false;
      a = false;
      s = true;
      d = false;
      break;
    case 4:
      w = false;
      a = false;
      s = false;
      d = true;
      break;
    case 5:
      w = true;
      a = true;
      s = false;
      d = false;
      break;
    case 6:
      w = true;
      a = false;
      s = true;
      d = false;
      break;
    case 7:
      w = true;
      a = false;
      s = false;
      d = true;
      break;
    case 8:
      w = false;
      a = true;
      s = true;
      d = false;
      break;
    case 9:
      w = false;
      a = true;
      s = false;
      d = true;
      break;
    case 10:
      w = false;
      a = false;
      s = true;
      d = true;
      break;
    case 11:
      w = true;
      a = true;
      s = true;
      d = false;
      break;
    case 12:
      w = true;
      a = true;
      s = false;
      d = true;
      break;
    case 13:
      w = true;
      a = false;
      s = true;
      d = true;
      break;
    case 14:
      w = false;
      a = true;
      s = true;
      d = true;
      break;
    case 15:
      w = true;
      a = true;
      s = true;
      d = true;
      break;
  }


  if (w){drive += DRIVE_ADJUST;}
  if (s){drive -= DRIVE_ADJUST;}
  if (a){turn += TURN_ADJUST;}
  if (d){turn -= TURN_ADJUST;}
  
  if (w && !a && !d){
    turn = 0;
    drive += DRIVE_ADJUST;
  }
  else if (s && !a && !d){
    turn = 0;
    drive -= DRIVE_ADJUST;
  }
  else if (a && !w && !s){
    drive = 0;
    turn += TURN_ADJUST;
  }
  else if (d && !w && !s){
    drive = 0;
    turn -= TURN_ADJUST;
  }

  if (!w && !a && !s && !d){
    drive = 0;
    turn = 0;
  }


  if (drive > 1){drive = 1;}
  if (drive < -1){drive = -1;}
  if (turn > 1){turn = 1;}
  if (turn < -1){turn = -1;}

  power_R = mA*drive + mB*turn;
  power_L = mC*drive + mD*turn;
  
  M1.setDuty(MAX_POWER*power_R);
  M2.setDuty(MAX_POWER*power_L);


  Serial.print("drive:  ");
  Serial.print(drive);
  Serial.print("   turn:  ");
  Serial.print(turn);
  
  Serial.print("  R power:  ");
  Serial.print(MAX_POWER*power_R);
  Serial.print("  L power:  ");
  Serial.print(MAX_POWER*power_L);


}
