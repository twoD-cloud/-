#ifdef __TB6612_H
#define __TB6612_H
#include "board.h"

void MOTOR_STOP(void);
void MOTOR_Control(bool dir, uint32_t speed);


#endif