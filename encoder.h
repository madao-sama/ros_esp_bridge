#ifndef ENCODER
#define ENCODER

// Encoder pins

int encoder1_c1 = 15;
int encoder1_c2 = 19;

int encoder2_c1 = 16;
int encoder2_c2 = 17;

int encoder3_c1 = 4;
int encoder3_c2 = 21;

int encoder4_c1 = 5;
int encoder4_c2 = 18;

void shaft_moved_1();
void shaft_moved_2();
void shaft_moved_3();
void shaft_moved_4();
void print_encoder_values();
void resetEncoders();
#endif