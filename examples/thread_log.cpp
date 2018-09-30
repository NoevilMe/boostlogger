#include "thread_log.h"
#include <boost_logger.h>

void thread_log()
{
    auto mLogger = global_logger::get();
    int c =100000;
    while(c-- >0) {
        LOG_TRACE(mLogger) << "a trace message";
        LOG_DEBUG(mLogger) << "a debug message";
        LOG_INFO(mLogger) << "an info message";
        LOG_WARN(mLogger) << "a warning message";
        LOG_ERROR(mLogger) << "an error message";
        LOG_FATAL(mLogger) << "a fatal message";
    }

}
