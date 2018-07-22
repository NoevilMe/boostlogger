#include "thread_log.h"
#include <boost_logger.h>

void thread_log()
{
    auto mLogger = global_logger::get();
    int c =100000;
    while(c-- >0) {
        BST_LOG_TRACE(mLogger) << "a trace message";
        BST_LOG_DEBUG(mLogger) << "a debug message";
        BST_LOG_INFO(mLogger) << "an info message";
        BST_LOG_WARN(mLogger) << "a warning message";
        BST_LOG_ERROR(mLogger) << "an error message";
        BST_LOG_FATAL(mLogger) << "a fatal message";
    }

}
