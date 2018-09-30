#include <boost_logger.h>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/filesystem.hpp>
#include <thread>
#include "thread_log.h"

namespace fs = boost::filesystem;
static logging::sources::severity_logger_mt<boost::log::trivial::severity_level> mLogger;

int main()
{
    init_file_logging("log5", "log_test", 3*1024*1024, 10);
    set_logging_level("trace");

    LOG_TRACE(mLogger) << "a trace message";
    LOG_DEBUG(mLogger) << "a debug message";
    LOG_INFO(mLogger) << "an info message";
    LOG_WARN(mLogger) << "a warning message";
    LOG_ERROR(mLogger) << "an error message";
    LOG_FATAL(mLogger) << "a fatal message";

    //set_logging_level(logging::trivial::info);
    //std::thread thd(&thread_log);
    

    int c =1000000;
    while(c-- >0) {
        LOG_TRACE(mLogger) << "a trace message";
        LOG_DEBUG(mLogger) << "a debug message";
        LOG_INFO(mLogger) << "an info message";
        LOG_WARN(mLogger) << "a warning message";
        LOG_ERROR(mLogger) << "an error message";
        LOG_FATAL(mLogger) << "a fatal message";
    }

    //if (thd.joinable())
        //thd.join();

    return 0;
}

