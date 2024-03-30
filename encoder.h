#ifndef ENCODER
#define ENCODER

// Encoder pins

#define encoder1_c1 (15)
#define encoder1_c2 (19)
#define encoder2_c1 (16)
#define encoder2_c2 (17)
#define encoder3_c1 (21)
#define encoder3_c2 (4)
#define encoder4_c1 (5)
#define encoder4_c2 (18)

void shaft_moved_1();
void shaft_moved_2();
void shaft_moved_3();
void shaft_moved_4();
void print_encoder_values();
void resetEncoders();
#endif