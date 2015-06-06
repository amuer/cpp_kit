/*
 * main.cpp
 *
 *  Created on: Dec 28, 2014
 *      Author: mark
 */
#include "ZeroLog.h"
#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* print_xs(void* unused)
{
	for (int i = 0; i < 10000000; i++)
	{
		usleep(1);
		LOGGER_INFO("default", "thread %d", i);
	}
}

int main()
{
	std::cout << "hello" << std::endl;
	INIT_ROLLINGFILE_LOG("default", "/home/mark/default.log", (LogLevel)600, 200);
	LOGGER_DEBUG("default","hello");
	pthread_t thread_id;
	pthread_create(&thread_id, NULL, &print_xs, NULL);

	for (int i = 0; i < 1000000; i++)
	{
		usleep(1);
		LOGGER_INFO("default", "main %d", i);
	}
	pthread_join(thread_id, NULL);
}
