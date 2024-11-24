/*
 * button.c
 *
 *  Created on: Nov 24, 2024
 *      Author: ADMIN
 */

#include "button.h"

int keyReg0[NO_BUTTONS + 1];
int keyReg1[NO_BUTTONS + 1];
int keyReg2[NO_BUTTONS + 1];

int keyReg3[NO_BUTTONS + 1]; // store the old value

int button_flag[NO_BUTTONS + 1];
int button_counter[NO_BUTTONS + 1]; // 2 seconds

void initButton() {
	for (int buttonNo = 1; buttonNo <= NO_BUTTONS; buttonNo++) {
		keyReg0[buttonNo] = NORMAL_STATE;
		keyReg1[buttonNo] = NORMAL_STATE;
		keyReg2[buttonNo] = NORMAL_STATE;
		keyReg3[buttonNo] = NORMAL_STATE; // store the old value
		button_flag[buttonNo] = 0;
		//button_counter[buttonNo] = 200; // 2 seconds
	}
}

void getOneKeyInput(int buttonNo, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {
	keyReg0[buttonNo] = keyReg1[buttonNo];
	keyReg1[buttonNo] = keyReg2[buttonNo];
	keyReg2[buttonNo] = HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);
	if ((keyReg0[buttonNo] == keyReg1[buttonNo]) && (keyReg1[buttonNo] == keyReg2[buttonNo])) {
		if (keyReg3[buttonNo] != keyReg2[buttonNo]) {
			keyReg3[buttonNo] = keyReg2[buttonNo];
			if (keyReg2[buttonNo] == PRESSED_STATE) {
				//TODO
				subKeyProcess(buttonNo);
				button_counter[buttonNo] = 200;
			}
		}
		else{
				button_counter[buttonNo]--;
				if (button_counter[buttonNo] == 0){
				keyReg3[buttonNo] = NORMAL_STATE;
				}
		}
	}
}

void getKeyInput() {
	getOneKeyInput(1, BUT1_GPIO_Port, BUT1_Pin);
	getOneKeyInput(2, BUT2_GPIO_Port, BUT2_Pin);
	getOneKeyInput(3, BUT3_GPIO_Port, BUT3_Pin);
}

int isButtonPressed(int buttonNo) {
	if (buttonNo > NO_BUTTONS)
		return 0;

	if (button_flag[buttonNo] == 1) {
		button_flag[buttonNo] = 0;
		return 1;
	}
	return 0;
}

void subKeyProcess(int buttonNo) {
	button_flag[buttonNo] = 1;
}
