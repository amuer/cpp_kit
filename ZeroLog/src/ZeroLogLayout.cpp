/*
 * ZeroLogLayout.cpp
 *
 *  Created on: Dec 28, 2014
 *      Author: mark
 */

#include "ZeroLogLayout.h"
#include "log4cpp/FactoryParams.hh"
#include <log4cpp/Priority.hh>
#include <stdio.h>
#include <memory>
#include <pthread.h>


namespace log4cpp
{

	ZeroLogLayout::ZeroLogLayout() {
    }

	ZeroLogLayout::~ZeroLogLayout() {
    }

    std::string ZeroLogLayout::format(const LoggingEvent& event) {
        std::ostringstream message;

    char buff[64];
    time_t time = (time_t)event.timeStamp.getSeconds();

    struct tm newtime;
    localtime_r( &time, &newtime );

    int year    = newtime.tm_year+1900;
    int month   = newtime.tm_mon+1;
    int day     = newtime.tm_mday;
    int hour    = newtime.tm_hour;
    int minute  = newtime.tm_min;
    int seconds = newtime.tm_sec;
//    pthread_t pid = pthread_self();
    pthread_t pid = gettid();

    snprintf(buff, 64, "%04d-%02d-%02d %02d:%02d:%02d %u ", year, month, day, hour, minute, seconds, pid);

        const std::string& priorityName = Priority::getPriorityName(event.priority);
        message.width(Priority::MESSAGE_SIZE);message.setf(std::ios::left);
        message << buff << priorityName << " : " << event.message << std::endl;
        return message.str();
    }

   std::auto_ptr<Layout> create_simple_layout(const FactoryParams& params)
   {
      return std::auto_ptr<Layout>(new ZeroLogLayout);
   }
}
