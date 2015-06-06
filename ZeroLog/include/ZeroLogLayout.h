/*
 * ZeroLogLayout.h
 *
 *  Created on: Dec 28, 2014
 *      Author: mark
 */

#ifndef ZEROLOGLAYOUT_H_
#define ZEROLOGLAYOUT_H_

#include <log4cpp/Layout.hh>

namespace log4cpp
{

class ZeroLogLayout : public Layout
{
public:
	ZeroLogLayout();
	virtual ~ZeroLogLayout();

	virtual std::string format(const LoggingEvent& event);
};

}
#endif /* ZEROLOGLAYOUT_H_ */
