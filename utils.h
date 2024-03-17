#ifndef UTILS_H
#define UTILS_H

#define message_time_interval 1000

hw_timer_t *My_timer = NULL;
unsigned long long int last_message_time = 0;

void attachInterruptTask(void *pvParameters);
void IRAM_ATTR onTimer();
void runCommand(char *cmd); 
void resetCommand();

#endif