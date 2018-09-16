/*
 * sequential_tasks.c
 *
 *  Created on: 16.09.2018
 *      Author: Przemek
 */


#include "sequential_tasks.h"

static uint8_t sequentials_tasks_tick_flag = 0;

static uint8_t sequentials_tasks_actual_position = 0;

static uint8_t sequentials_task_state = 0;

static uint16_t sequentials_task_actual_counter = 0;

//! wskaznik na aktualnie obslugiwana tablice z sekwencyjnymi taskami
static single_sequencial_task *sequential_tasks_array;

void sequential_tasks_init(single_sequencial_task *wsk)
{
	sequential_tasks_array = wsk;
}

void sequential_tasks_start(void)
{
	sequentials_task_state = 1;
}

void sequential_tasks_stop(void)
{
	sequentials_task_state = 0;
}

void sequential_tasks_tick(void)
{
	sequentials_tasks_tick_flag = 1;
}

static void inline sequential_tasks_check_event_time_and_run(void)
{
	// jesli nadszedl czas na aktualny task:
	if(sequential_tasks_array[sequentials_tasks_actual_position].time == sequentials_task_actual_counter)
	{
		sequentials_task_actual_counter = 0;

		sequential_tasks_array[sequentials_tasks_actual_position].function();

		sequentials_tasks_actual_position++;
		if(sequential_tasks_array[sequentials_tasks_actual_position].function == 0)
		{
			sequentials_task_state = 0;
		}
	}
}

void sequential_tasks_events_check(void)
{
	// Jesli obsluga taskow jest wlaczona - obsluz maszyne stanow
	// jesli juz sie zakonczyla/jest wylaczona to nic nie rob
	if(sequentials_task_state)
	{
		// jesli wystapilo tykniecie:
		if(sequentials_tasks_tick_flag)
		{
			sequentials_tasks_tick_flag = 0;

			sequential_tasks_check_event_time_and_run();
		}
	}
}

void sequential_tasks_tick_and_check_events(void)
{
	sequential_tasks_tick();
	sequential_tasks_events_check();
}
