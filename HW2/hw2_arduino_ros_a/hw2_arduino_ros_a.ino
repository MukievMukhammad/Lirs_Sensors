/*
 * rosserial Publisher Example
 * Prints "hello world!"
 */

#include <ros.h>
#include <std_msgs/String.h>

ros::NodeHandle  nh;

std_msgs::String str_msg;
ros::Publisher chatter("arduino/led", &str_msg);

volatile bool lightStatus = true;

void setup()
{
  nh.initNode();
  nh.advertise(chatter);

  pinMode(2, INPUT_PULLUP);
  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);
  attachInterrupt(0, lightSwitch, CHANGE);
}

void lightSwitch() {
  if(lightStatus)
  {
    digitalWrite(8, LOW);
    lightStatus = false;
  } else {
    digitalWrite(8, HIGH);
    lightStatus = true;
  }
}

void loop()
{
  if(lightStatus)
    str_msg.data = "light on";
  else
    str_msg.data = "light off";
  chatter.publish( &str_msg );
  nh.spinOnce();
  delay(1000);
}
