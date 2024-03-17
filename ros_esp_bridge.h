#ifndef ROS_ESP_BRIDGE
#define ROS_ESP_BRIDGE

#define PID_FREQ            (50)   // PID Frequency
#define EncoderPerCount     (600.0)   // Encoder count for a loop

#define PID_Period          ((80.0)/PID_FREQ)   // PID Periof in miliseconds

#define READ_ENCODERS  'e'
#define MOTOR_SPEEDS   'm'
#define RESET_ENCODERS 'r'
#define UPDATE_PID     'u'
#define STOP_MOTORS    's'
#define GET_PID_VALUES 'p'

char *udp_message = (char*)malloc(100 * sizeof(char));

char argv1[100];
int arg = 0;
int tx_index = 0;

unsigned char moving = 0;

#endif