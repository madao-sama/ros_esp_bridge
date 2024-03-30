# ESP32 ROS2 BRIDGE
Bridge between ROS2 and ESP32 via UDP.

### Starts
Uses ESP32 as motor controller using PID.<br />
UDP version of https://github.com/hbrobotics/ros_arduino_bridge.<br />
Also added som specs as saving PID values on EEPROM. Changed PID algorithm's ticks per loop to RPM. <br />
Repo is developing, not final version. Control it well before using. <br />

---
### Hardware:
  I used ESP32 WROOM32 as MC. Alternatives can be used by pin configuration.\
  Motor driver L298N. Other options can be used by editing "motor.ino".\
  Motors are geared TT motor that can rotate up to 150 RPM.\
  Encoders are simple hall encoder connected to motor directly.\
  Schematic will be added asap.
  
---
### Communication:

  Communicate over UDP. Just change SSID and PASSWORD in "udp.h". Device will auto connect to UDP and able to communicate.\
  Device is connected to 8080 port.
  ##### Messages:
    Shared messages:
      Continuous messages:
        1: Multicast encoder values.
           Format is: "encoder1 encoder2 encoder3 encoder4", seems like "254 345 064 3593"
  #####  Commands:
      Periodic commands:
        1: Motor target RPM. This message should be shared continuously with period under 1s. After 1 second controller stops motor automatically.
           Values are x100. So if you want to set parameter to 12.3, send 1230 as parameter.
           Format is: "m-motor1RPM motor2RPM motor3RPM motor4RPM", seems like "m-30 30 50 50>" 
        2: Stop motors. This message directly stops motors without PID.
           Format is: "s>"
      One-time commands:
        1.command: Chage PID parameters. This connds changes PID parameters and store them in EEPROM. So eventhough robot restarted, changed parameters can still be used.
                   Values are x100. So if you want to set parameter to 12.3, send 1230 as parameter.
                   Format is: "u:Kp Kd Ki Ko>", seems like: "u:1000 3400 2942 4999>"
    !!! 1.response: Values are x100. So if you see parameter 1230, the parameter used is 12.3. 
                    Format is: "pid-Kp Kd Ki Ko>", seems like: "pid:1000 3400 2942 4999>"         
        2.command: Reset encoder values. This command resets encoders to 0.
                   Format is: "r>"
    !!! 2.response: "resetencoder>"
        3.command: Get PID Parameters. This shows current parameters.
                   Format is: "p>"
    !!! 3.response: Values are x100. So if you want to set parameter to 12.3, send 1230 as parameter.
                    "pid:1000 3400 2942 4999>" 
  

### Ota 
OTA is available. You can upload binary files through device IP address.<br />
To export binary in Arduino IDE, sketch/export compiled bianry. You can find bin file in build folder at the same folder with code.
open browser then go "192.168.xxx.xxx" (esp ip). If it says "Hi! I am ESP32 inside ros_esp_bridge." you are in correct place.  <br />
Go "192.168.xxx.xxx/update" then in firmware section, click select bin. After finished, you can go back. 
!!! means this spec is not added yet. It is planned and will be added in next update.\
    You can check current parameters on Serial port. 3.command's response is shared on serial port now. Values are not x100 on serial port. UDP will be added in next update too.
