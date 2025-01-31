#ifndef MOVENT_H
#define MOVENT_H

#include <stdlib.h>
#include "stm32f4xx_hal.h"
#include "main.h"
#include <stdlib.h>

// htim2 ve htim3 dışarıdan tanımlanmışsa, bunları dışarıya aktarırız
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

// Motor kontrol fonksiyonu
void MOVENT_Control(int speed, int angle);

#endif
