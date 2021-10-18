#include <Arduino.h>
#include "ESP32Wiimote.h"

ESP32Wiimote wiimote;
#include <ESP32Servo.h>

Servo x_servo;  // create servo object to control a servo
Servo y_servo;
// 16 servo objects can be created on the ESP32

int x_pos= 0;
int y_pos = 0;    // variable to store the servo position

// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33
int y_servoPin = 18;
int x_servoPin = 19;

void setup()
{
  x_servo.setPeriodHertz(50);    // standard 50 hz servo
  x_servo.attach(x_servoPin, 100, 2400);
  y_servo.setPeriodHertz(50);    // standard 50 hz servo
  y_servo.attach(y_servoPin, 100, 2400);
  Serial.begin(115200);
  wiimote.init();
//    wiimote.addFilter(ACTION_IGNORE, FILTER_NUNCHUK_ACCEL);
}


void loop()
{
  wiimote.task();
  if (wiimote.available() > 0) {
      uint16_t button = wiimote.getButtonState();
      Serial.printf("%04x\n", button);

      NunchukState nunchuk = wiimote.getNunchukState();
      Serial.printf("nunchuk:");
      Serial.printf(" X-Stick: %d", nunchuk.xStick);
      Serial.printf(" Y-Stick: %d", nunchuk.yStick);
      Serial.printf(" X-Axis: %d", nunchuk.xAxis);
      Serial.printf(" Y-Axis: %d", nunchuk.yAxis);
      Serial.printf(" Z-Axis: %d", nunchuk.zAxis);
      Serial.printf(" C-Button: %02x", nunchuk.cBtn);
      Serial.printf(" Z-Button: %02x", nunchuk.zBtn);
      Serial.printf("\n");
      int y=90+int(nunchuk.xAxis)-127;
      int x=200-int(nunchuk.yAxis);
      if(x>0 && y>0 && x<180 && y<180){
        y_servo.write(y);
        x_servo.write(x);
      }
  }
  delay(5);
}