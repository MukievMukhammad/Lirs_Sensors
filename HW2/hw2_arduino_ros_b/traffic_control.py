import rospy
from std_msgs.msg import String

import sys, select, os
if os.name == 'nt':
  import msvcrt, time
else:
  import tty, termios

msg = """
Control Your TrafficLight!
---------------------------
Commands:
R - switch to Red Light
G - switch to Green Light
B - switch to Blue Light

CTRL-C to quit
"""

def getKey():
    """Возвращает значение нажатой на клавиатуре кнопки; 
       реализацию взял из turtlebot3_teleop_key"""
    if os.name == 'nt':
        timeout = 0.1
        startTime = time.time()
        while(1):
            if msvcrt.kbhit():
                if sys.version_info[0] >= 3:
                    return msvcrt.getch().decode()
                else:
                    return msvcrt.getch()
            elif time.time() - startTime > timeout:
                return ''

    tty.setraw(sys.stdin.fileno())
    rlist, _, _ = select.select([sys.stdin], [], [], 0.1)
    if rlist:
        key = sys.stdin.read(1)
    else:
        key = ''

    termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
    return key

def traffic_control():
    rospy.init_node("traffic_light", anonymous=False)
    pub = rospy.Publisher("/computer/traffic_light/cmd", 
                            String, queue_size=10)
    light_cmd = String()

    while not rospy.is_shutdown():
        key = getKey()
        if(key == '\x03'):
            break
        light_cmd.data = key
        if(key in "rgbRGB" and key != ""):
            pub.publish(light_cmd)

if __name__ == "__main__":
    if os.name != 'nt':
        settings = termios.tcgetattr(sys.stdin)
    try:
        print(msg)
        traffic_control()
    except rospy.ROSInterruptException:
        pass
