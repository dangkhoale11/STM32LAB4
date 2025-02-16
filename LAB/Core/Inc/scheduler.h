/*
 * scheduler.h
 *
 *  Created on: Nov 24, 2024
 *      Author: ADMIN
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <main.h>

#define SCH_MAX_TASKS	40



typedef struct {
	void (* pTask)(void);
	uint32_t Delay;
	uint32_t Period;
	uint8_t RunMe;
	uint32_t TaskID;
} sTask;


void SCH_Init(void);
void SCH_Update(void);
uint32_t SCH_Add_Task(void (* pFunction)(), uint32_t DELAY, uint32_t PERIOD);
void SCH_Dispatch_Task(void);
uint32_t SCH_Delete_Task(const uint32_t TASK_INDEX);


#endif /* INC_SCHEDULER_H_ */
