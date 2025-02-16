/*
 * scheduler.c
 *
 *  Created on: Nov 24, 2024
 *      Author: ADMIN
 */

#include "scheduler.h"
#include "main.h"


sTask SCH_tasks_G [SCH_MAX_TASKS];

void SCH_Init(void) {
	unsigned char i;
	for (i=0;i<SCH_MAX_TASKS;i++) {
		SCH_tasks_G[i].pTask = 0x0000;
		SCH_tasks_G[i].Delay = 0;
		SCH_tasks_G[i].Period = 0;
		SCH_tasks_G[i].RunMe = 0;
		SCH_tasks_G[i].TaskID = -1;
	}
}

uint32_t SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD) {
	unsigned char index=0;
	while ((SCH_tasks_G[index].pTask != 0x0000) && (index < SCH_MAX_TASKS)) {
		index++;
	}
	if (index>=SCH_MAX_TASKS) {
		return -1;
	}
	SCH_tasks_G[index].pTask = pFunction;
	SCH_tasks_G[index].Delay = DELAY;
	SCH_tasks_G[index].Period = PERIOD;
	SCH_tasks_G[index].RunMe = 0;
	SCH_tasks_G[index].TaskID = index;
	return index;
}

void SCH_Update(void) {
	unsigned char index;
	for (index=0; index < SCH_MAX_TASKS; index++) {
		if(SCH_tasks_G[index].Delay > 0){
			SCH_tasks_G[index].Delay--;
		}
		else{
			SCH_tasks_G[index].Delay = SCH_tasks_G[index].Period;
			SCH_tasks_G[index].RunMe += 1;
		}
	}
}

void SCH_Dispatch_Task(void) {
	int index;
	for (index = 0; index < SCH_MAX_TASKS; index++) {
		if(SCH_tasks_G[index].RunMe > 0){
			SCH_tasks_G[index].RunMe--;
			(*SCH_tasks_G[index].pTask)();
		}

	}
}

uint32_t SCH_Delete_Task(uint32_t index) {
	if (index < 0 || index >= SCH_MAX_TASKS) {
		return -1;
	}
	if (SCH_tasks_G[index].pTask==0x0000) {
		return -1;
	}
	SCH_tasks_G[index].pTask = 0x0000;
	SCH_tasks_G[index].Delay = 0;
	SCH_tasks_G[index].Period = 0;
	SCH_tasks_G[index].RunMe = 0;
	SCH_tasks_G[index].TaskID = -1;
	return index;
}
