#include "movent.h"

void motorController(int power){
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, power);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, power);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, power);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, power);
}

void directionController(int dir){
	if(dir == 1){
		HAL_GPIO_WritePin(RIGHT_FRONT_MOTOR_F_GPIO_Port, RIGHT_FRONT_MOTOR_F_Pin, dir);
		HAL_GPIO_WritePin(RIGHT_BACK_MOTOR_F_GPIO_Port, RIGHT_BACK_MOTOR_F_Pin, dir);
		HAL_GPIO_WritePin(LEFT_FRONT_MOTOR_F_GPIO_Port, LEFT_FRONT_MOTOR_F_Pin, dir);
		HAL_GPIO_WritePin(LEFT_BACK_MOTOR_F_GPIO_Port, LEFT_BACK_MOTOR_F_Pin, dir);

		HAL_GPIO_WritePin(RIGHT_FRONT_MOTOR_B_GPIO_Port, RIGHT_FRONT_MOTOR_B_Pin, !dir);
		HAL_GPIO_WritePin(RIGHT_BACK_MOTOR_B_GPIO_Port, RIGHT_BACK_MOTOR_B_Pin, !dir);
		HAL_GPIO_WritePin(LEFT_FRONT_MOTOR_B_GPIO_Port, LEFT_FRONT_MOTOR_B_Pin, !dir);
		HAL_GPIO_WritePin(LEFT_BACK_MOTOR_B_GPIO_Port, LEFT_BACK_MOTOR_B_Pin, !dir);
	}
	else if(dir == 0){
		HAL_GPIO_WritePin(RIGHT_FRONT_MOTOR_F_GPIO_Port, RIGHT_FRONT_MOTOR_F_Pin, !dir);
		HAL_GPIO_WritePin(RIGHT_BACK_MOTOR_F_GPIO_Port, RIGHT_BACK_MOTOR_F_Pin, !dir);
		HAL_GPIO_WritePin(LEFT_FRONT_MOTOR_F_GPIO_Port, LEFT_FRONT_MOTOR_F_Pin, !dir);
		HAL_GPIO_WritePin(LEFT_BACK_MOTOR_F_GPIO_Port, LEFT_BACK_MOTOR_F_Pin, !dir);

		HAL_GPIO_WritePin(RIGHT_FRONT_MOTOR_B_GPIO_Port, RIGHT_FRONT_MOTOR_B_Pin, dir);
		HAL_GPIO_WritePin(RIGHT_BACK_MOTOR_B_GPIO_Port, RIGHT_BACK_MOTOR_B_Pin, dir);
		HAL_GPIO_WritePin(LEFT_FRONT_MOTOR_B_GPIO_Port, LEFT_FRONT_MOTOR_B_Pin, dir);
		HAL_GPIO_WritePin(LEFT_BACK_MOTOR_B_GPIO_Port, LEFT_BACK_MOTOR_B_Pin, dir);
	}
}

void steeringController(int power){
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, power);
}

long map(long x, long in_min, long in_max, long out_min, long out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int getAngleToPower(int angle){
	if(angle > 0){
		return 250;
	}
	else if(angle < 0){
		return 1250;
	}
	return 575;
}

void MOVENT_Control(int speed, int angle){
	int dir = (speed > 0) ? 1 : (speed < 0 ? 0 : 1);
	int power = map(abs(speed), 0, 250, 3000, 4200);
	int servoPower= getAngleToPower(angle);

	directionController(dir);
	motorController(power);
	steeringController(servoPower);
}
