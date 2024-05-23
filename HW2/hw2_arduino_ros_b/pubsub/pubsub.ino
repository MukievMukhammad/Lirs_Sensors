/*
 * rosserial PubSub Example
 * Prints "hello world!" and toggles led
 */

#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>

#define BLUE 8
#define GREEN 10
#define RED 12

ros::NodeHandle  nh;

void turnOffAll()
{
  digitalWrite(BLUE, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(RED, LOW);
}


void messageCb( const std_msgs::String& traffic_cmd_msg){
  String cmd = traffic_cmd_msg.data;
  if(cmd == "R" || cmd == "r")
  {
    turnOffAll();
    digitalWrite(RED, HIGH);
  }
  if(cmd == "G" || cmd == "g")
  {
    turnOffAll();
    digitalWrite(GREEN, HIGH);
  }
  if(cmd == "B" || cmd == "b")
  {
    turnOffAll();
    digitalWrite(BLUE, HIGH);
  }
}

ros::Subscriber<std_msgs::String> sub("/computer/traffic_light/cmd", messageCb );



void setup()
{
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
}

void loop()
{
  nh.spinOnce();
}
