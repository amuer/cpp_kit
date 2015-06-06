/*
 * ZeroLog.h
 *
 *  Created on: Dec 28, 2014
 *      Author: mark
 */

#ifndef ZEROLOG_H_
#define ZEROLOG_H_

#include "log4cpp/Category.hh"
#include "log4cpp/RollingFileAppender.hh"
#include "ZeroLogLayout.h"

#define INIT_ROLLINGFILE_LOG     InitLog
#define LOG_SHUTDOWN_ALL         ShutdownAllLog()
#define LOGGER_DEBUG		LoggerDebug
#define LOGGER_INFO	 		LoggerInfo
#define LOGGER_WARN	 		LoggerWarn
#define LOGGER_ERROR		LoggerError
#define LOGGER_FATAL		LoggerFatal

//  日志等级
// NOTSET <  DEBUG < INFO  < WARN < LEVEL_NOTICE < ERROR  < FATAL
enum LogLevel
{
    LEVEL_FATAL  = 0,
    LEVEL_ERROR  = 300,
    LEVEL_WARN   = 400,
    LEVEL_NOTICE = 500,
    LEVEL_INFO   = 600,
    LEVEL_DEBUG  = 700,
    LEVEL_NOTSET = 800,
};

int LoggerDebug( const char* vLogName, const char* vFmt, ... );
int LoggerInfo( const char* vLogName, const char* vFmt, ... );
int LoggerNotice( const char* vLogName, const char* vFmt, ... );
int LoggerWarn( const char* vLogName, const char* vFmt, ... );
int LoggerError( const char* vLogName, const char* vFmt, ... );
int LoggerFatal( const char* vLogName, const char* vFmt, ... );
int log( const char* vLogName, int vPriority, const char* vFmt, ... );

int LogDebug_va( const char* vLogName, const char* vFmt, va_list ap);
int LogNotice_va( const char* vLogName, const char* vFmt, va_list ap);
int LogInfo_va( const char* vLogName, const char* vFmt, va_list ap );
int LogWarn_va( const char* vLogName, const char* vFmt, va_list ap );
int LogError_va( const char* vLogName, const char* vFmt, va_list ap );
int LogFatal_va( const char* vLogName, const char* vFmt, va_list ap );
int log_va( const char* vLogName, int vPriority, const char* vFmt, va_list ap );

int InitLog( const char*    vLogName,                       /*日志类型的名称(关键字,由此定位到日志文件)*/
            const char*     vLogDir,                        /*文件名称(路径)*/
            LogLevel        vPriority = LEVEL_NOTSET,       /*日志等级*/
            unsigned int    vMaxBackupIndex = 1,            /*回卷文件个数*/
            bool            vAppend = true);                /*是否截断(默认即可)*/

int ReInitLog( const char* vLogName,
              LogLevel      vPriority = LEVEL_NOTSET,       /*日志等级*/
              unsigned int  vMaxFileSize = 10*1024*1024,    /*回卷文件最大长度*/
              unsigned int  vMaxBackupIndex = 1);           /*回卷文件个数*/

int ShutdownAllLog();

class ZeroLog
{
public:
	ZeroLog();
	virtual ~ZeroLog();
};

#endif /* ZEROLOG_H_ */
