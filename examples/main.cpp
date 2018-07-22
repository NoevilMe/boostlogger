#include <boost_logger.h>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;
static logging::sources::severity_logger<boost::log::trivial::severity_level> mLogger;

int main()
{
    init_file_logging("/home/wick/study/boostlogger/build/log4", "log_test", 3*1024*1024, 10);
    set_logging_level("trace");

    BST_LOG_TRACE(mLogger) << "a trace message";
    BST_LOG_DEBUG(mLogger) << "a debug message";
    BST_LOG_INFO(mLogger) << "an info message";
    BST_LOG_WARN(mLogger) << "a warning message";
    BST_LOG_ERROR(mLogger) << "an error message";
    BST_LOG_FATAL(mLogger) << "a fatal message";

    //set_logging_level(logging::trivial::info);

    int c =100000;
    while(c-- >0) {
        BST_LOG_TRACE(mLogger) << "a trace message";
        BST_LOG_DEBUG(mLogger) << "a debug message";
        BST_LOG_INFO(mLogger) << "an info message";
        BST_LOG_WARN(mLogger) << "a warning message";
        BST_LOG_ERROR(mLogger) << "an error message";
        BST_LOG_FATAL(mLogger) << "a fatal message";
    }
    return 0;
}

