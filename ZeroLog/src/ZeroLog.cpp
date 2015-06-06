/*
 * ZeroLog.cpp
 *
 *  Created on: Dec 28, 2014
 *      Author: mark
 */

#include "ZeroLog.h"
#include <string.h>

ZeroLog::ZeroLog()
{
	// TODO Auto-generated constructor stub

}

ZeroLog::~ZeroLog()
{
	// TODO Auto-generated destructor stub
}

// 初始一种类型的日志
int InitLog( const char* vLogName, const char* vLogDir, LogLevel vPriority, unsigned int vMaxBackupIndex, bool vAppend)
{
    if ( NULL == vLogName || NULL == vLogDir )
    {
        return -1;
    }

    int maxFileSize = 300 * 1024 * 1024;
    // 已经存在该名称的实例
    log4cpp::Category* tpCategory = log4cpp::Category::exists( vLogName);
    if ( tpCategory != NULL )
    {
        // 1.删除所有的appender
        tpCategory->removeAllAppenders ();
        // 2.实例化一个layout 对象
        log4cpp::Layout* tpLayout = new log4cpp::ZeroLogLayout();
        // 3. 初始化一个appender 对象
        log4cpp::Appender* tpAppender = new log4cpp::RollingFileAppender(vLogName, vLogDir, maxFileSize, vMaxBackupIndex, vAppend );
        // 4. 把layout对象附着在appender对象上
        tpAppender->setLayout(tpLayout);
        // 5. 设置additivity为false，替换已有的appender
        tpCategory->setAdditivity(false);
        // 6. 把appender对象附到category上
        tpCategory->setAppender(tpAppender);
        // 7. 设置category的优先级，低于此优先级的日志不被记录
        tpCategory->setPriority( (log4cpp::Priority::PriorityLevel) vPriority );

        return 0;
    }

    // 1实例化一个layout 对象
    log4cpp::Layout* tpLayout = new log4cpp::ZeroLogLayout();
    // 2. 初始化一个appender 对象
    log4cpp::Appender* tpAppender = new log4cpp::RollingFileAppender(vLogName, vLogDir, maxFileSize, vMaxBackupIndex, vAppend );
    // 3. 把layout对象附着在appender对象上
    tpAppender->setLayout(tpLayout);
    // 4. 实例化一个category对象
    log4cpp::Category& trCategory = log4cpp::Category::getInstance(vLogName);
    // 5. 设置additivity为false，替换已有的appender
    trCategory.setAdditivity(false);
    // 6. 把appender对象附到category上
    trCategory.setAppender(tpAppender);
    // 7. 设置category的优先级，低于此优先级的日志不被记录
    trCategory.setPriority( (log4cpp::Priority::PriorityLevel) vPriority );

    return 0;

}

int ReInitLog( const char* vLogName, LogLevel vPriority, unsigned int  vMaxFileSize, unsigned int vMaxBackupIndex)
{
    if ( NULL == vLogName )
    {
        return -1;
    }

    // 已经存在该名称的实例
    log4cpp::Category* tpCategory = log4cpp::Category::exists( vLogName);
    if ( tpCategory != NULL )
    {
        log4cpp::RollingFileAppender* pAppender = (log4cpp::RollingFileAppender*) tpCategory->getAppender();
        if( pAppender == NULL )
        {
            return -1;
        }

        pAppender->setMaxBackupIndex( vMaxBackupIndex );
        pAppender->setMaximumFileSize( vMaxFileSize );

        tpCategory->setPriority( vPriority );
    }

    return 0;
}

int ShutdownAllLog()
{
    log4cpp::Category::shutdown( );
    return 0;
}

int log( const char* vLogName, int vPriority, const char* vFmt, ... )
{
    if ( NULL == vLogName )
    {
        return -1;
    }

    log4cpp::Category* tpCategory = log4cpp::Category::exists(vLogName);
    if ( NULL == tpCategory )
    {
        return -1;
    }

    va_list va;

    va_start(va, vFmt);
    tpCategory->logva ( (log4cpp::Priority::PriorityLevel)vPriority, vFmt, va);
    va_end(va);
    return 0;
}

int LoggerDebug( const char* vLogName, const char* vFmt, ... )
{
    if ( NULL == vLogName )
    {
        return -1;
    }

    log4cpp::Category* tpCategory = log4cpp::Category::exists(vLogName);
    if ( NULL == tpCategory )
    {
        return -1;
    }

    if (tpCategory->getPriority() < log4cpp::Priority::DEBUG)
    {
    	return -2;
    }

    va_list va;

    va_start(va, vFmt);
    tpCategory->logva ( log4cpp::Priority::DEBUG, vFmt, va);
    va_end(va);

    return 0;
}

int LoggerInfo( const char* vLogName, const char* vFmt, ... )
{
    if ( NULL == vLogName )
    {
        return -1;
    }

    log4cpp::Category* tpCategory = log4cpp::Category::exists(vLogName);
    if ( NULL == tpCategory )
    {
        return -1;
    }

    if (tpCategory->getPriority() < log4cpp::Priority::INFO)
    {
    	return -2;
    }

    va_list va;

    va_start(va, vFmt);
    tpCategory->logva ( log4cpp::Priority::INFO, vFmt, va);
    va_end(va);

    return 0;
}

int LoggerNotice( const char* vLogName, const char* vFmt, ... )
{
    if ( NULL == vLogName )
    {
        return -1;
    }

    log4cpp::Category* tpCategory = log4cpp::Category::exists(vLogName);
    if ( NULL == tpCategory )
    {
        return -1;
    }

    if (tpCategory->getPriority() < log4cpp::Priority::NOTICE)
    {
    	return -2;
    }

    va_list va;

    va_start(va, vFmt);
    tpCategory->logva ( log4cpp::Priority::NOTICE, vFmt, va);
    va_end(va);

    return 0;
}

int LoggerWarn( const char* vLogName, const char* vFmt, ... )
{
    if ( NULL == vLogName )
    {
        return -1;
    }

    log4cpp::Category* tpCategory = log4cpp::Category::exists(vLogName);
    if ( NULL == tpCategory )
    {
        return -1;
    }

    if (tpCategory->getPriority() < log4cpp::Priority::WARN)
    {
    	return -2;
    }

    va_list va;

    va_start(va, vFmt);
    tpCategory->logva ( log4cpp::Priority::WARN, vFmt, va);
    va_end(va);

    return 0;
}

int LoggerError( const char* vLogName, const char* vFmt, ... )
{
    if ( NULL == vLogName )
    {
        return -1;
    }

    log4cpp::Category* tpCategory = log4cpp::Category::exists(vLogName);
    if ( NULL == tpCategory )
    {
        return -1;
    }

    if (tpCategory->getPriority() < log4cpp::Priority::ERROR)
    {
    	return -2;
    }

    va_list va;

    va_start(va, vFmt);
    tpCategory->logva ( log4cpp::Priority::ERROR, vFmt, va);
    va_end(va);

    return 0;
}

int LoggerFatal( const char* vLogName, const char* vFmt, ... )
{
    if ( NULL == vLogName )
    {
        return -1;
    }

    log4cpp::Category* tpCategory = log4cpp::Category::exists(vLogName);
    if ( NULL == tpCategory )
    {
        return -1;
    }

    if (tpCategory->getPriority() < log4cpp::Priority::FATAL)
    {
    	return -2;
    }

    va_list va;

    va_start(va, vFmt);
    tpCategory->logva ( log4cpp::Priority::FATAL, vFmt, va);
    va_end(va);

    return 0;
}

int LogDebug_va ( const char* vLogName, const char* vFmt, va_list ap)
{
    if ( NULL == vLogName )
    {
        return -1;
    }

    log4cpp::Category* tpCategory = log4cpp::Category::exists(vLogName);
    if ( NULL == tpCategory )
    {
        return -1;
    }

    tpCategory->logva ( log4cpp::Priority::DEBUG, vFmt, ap);

    return 0;
}

int LogNotice_va( const char* vLogName, const char* vFmt, va_list ap)
{
    if ( NULL == vLogName )
    {
        return -1;
    }

    log4cpp::Category* tpCategory = log4cpp::Category::exists(vLogName);
    if ( NULL == tpCategory )
    {
        return -1;
    }

    tpCategory->logva ( log4cpp::Priority::NOTICE, vFmt, ap);

    return 0;
}

int LogInfo_va( const char* vLogName, const char* vFmt, va_list ap )
{
    if ( NULL == vLogName )
    {
        return -1;
    }

    log4cpp::Category* tpCategory = log4cpp::Category::exists(vLogName);
    if ( NULL == tpCategory )
    {
        return -1;
    }

    tpCategory->logva ( log4cpp::Priority::INFO, vFmt, ap);

    return 0;
}

int LogWarn_va      ( const char* vLogName, const char* vFmt, va_list ap )
{
    if ( NULL == vLogName )
    {
        return -1;
    }

    log4cpp::Category* tpCategory = log4cpp::Category::exists(vLogName);
    if ( NULL == tpCategory )
    {
        return -1;
    }

    tpCategory->logva ( log4cpp::Priority::WARN, vFmt, ap);

    return 0;
}

int LogError_va ( const char* vLogName, const char* vFmt, va_list ap )
{
    if ( NULL == vLogName )
    {
        return -1;
    }

    log4cpp::Category* tpCategory = log4cpp::Category::exists(vLogName);
    if ( NULL == tpCategory )
    {
        return -1;
    }

    tpCategory->logva ( log4cpp::Priority::ERROR, vFmt, ap);

    return 0;
}

int LogFatal_va ( const char* vLogName, const char* vFmt, va_list ap )
{
    if ( NULL == vLogName )
    {
        return -1;
    }

    log4cpp::Category* tpCategory = log4cpp::Category::exists(vLogName);
    if ( NULL == tpCategory )
    {
        return -1;
    }

    tpCategory->logva ( log4cpp::Priority::FATAL, vFmt, ap);

    return 0;
}

int log_va( const char* vLogName, int vPriority, const char* vFmt, va_list ap )
{
    if ( NULL == vLogName )
    {
        return -1;
    }

    log4cpp::Category* tpCategory = log4cpp::Category::exists(vLogName);
    if ( NULL == tpCategory )
    {
        return -1;
    }

    tpCategory->logva ( vPriority, vFmt, ap);

    return 0;
}

void Log_bin( const char* vLogName, void* vBin, int vBinLen )
{
    char* pBuffer = (char*)vBin;
    char tmpBuffer[60000] = {0};
    char strTemp[32] = {0};

    for (int i = 0; i < vBinLen; i++ )
    {
        if ( !(i % 16) )
        {
            sprintf(strTemp, "\n%04d>    ", i / 16 + 1);
            strcat(tmpBuffer, strTemp);
        }
        sprintf(strTemp, "%02X ", (unsigned char)pBuffer[i]);
        strcat(tmpBuffer, strTemp);
    }

    LoggerDebug( vLogName, tmpBuffer );
}
