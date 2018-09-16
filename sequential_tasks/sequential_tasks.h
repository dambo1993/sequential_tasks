/*
 * sequential_tasks.h
 *
 *  Created on: 16.09.2018
 *      Author: Przemek
 */

#ifndef SEQUENTIAL_TASKS_SEQUENTIAL_TASKS_H_
#define SEQUENTIAL_TASKS_SEQUENTIAL_TASKS_H_

#include <inttypes.h>

typedef struct single_sequencial_task
{
	void (*function)(void);
	uint16_t time;
}single_sequencial_task;

void sequential_tasks_init(single_sequencial_task *wsk);

void sequential_tasks_start(void);

void sequential_tasks_stop(void);

void sequential_tasks_tick(void);

void sequential_tasks_events_check(void);

void sequential_tasks_tick_and_check_events(void);


#endif /* SEQUENTIAL_TASKS_SEQUENTIAL_TASKS_H_ */
