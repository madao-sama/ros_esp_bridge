#ifndef MOTOR
#define MOTOR

// Motor pins
#define motor1_in1 (33)
#define motor1_in2 (32)
#define motor2_in1 (27)
#define motor2_in2 (26)
#define motor3_in1 (13)
#define motor3_in2 (12)
#define motor4_in1 (25)
#define motor4_in2 (22)

#define MAX_PWM    (255)  // Max PWM Value

// Struct for defining each motors infos
typedef struct {
  double TargetRPM;    // target speed in ticks per frame
  long Encoder;                  // encoder count
  String dir;
  long PrevEnc;                  // last encoder count
  double PrevRPM;                // last input
  double RealRPM;
  int ITerm;                    //integrated term
  long output;                    // last motor setting
  unsigned long PrevMicros;
} ts_motor_encoder_info;

// Creating Motor Objects
ts_motor_encoder_info motor1PID, motor2PID, motor3PID, motor4PID;

/* PID Parameters */
float Kp;
float Kd;
float Ki;
float Ko;

void updatePID();
void stopMotors();
void resetPID();
void print_motor_data();
#endif
