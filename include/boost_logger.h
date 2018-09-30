#ifndef __BOOST_LOGGER_
#define __BOOST_LOGGER_

#include <cstring>
#include <boost/log/common.hpp>
#include <boost/log/trivial.hpp>

#ifdef _WIN32
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

#define __LOGGING_FILE_LINE_

namespace logging = boost::log;

void init_file_logging(const std::string &log_dir, const std::string &file, int size = 10*1024*1024, int max_files = 100);

void set_logging_level(logging::trivial::severity_level);
void set_logging_level(const std::string &level);

void logging_flush();
void logging_finalize();

// this is global logger, could be got like this: static auto &lg = global_logger::get()
BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(global_logger, boost::log::sources::severity_logger_mt<logging::trivial::severity_level>)

/*
 * Severity Logging macros
 */
#ifdef __LOGGING_FILE_LINE_
#define LOG_TRACE(lg) BOOST_LOG_SEV(lg, logging::trivial::trace) << __FILENAME__ << ":" << __LINE__ << " - "
#define LOG_DEBUG(lg) BOOST_LOG_SEV(lg, logging::trivial::debug) << __FILENAME__ << ":" << __LINE__ << " - "
#define LOG_INFO(lg) BOOST_LOG_SEV(lg, logging::trivial::info) << __FILENAME__ << ":" << __LINE__ << " - "
#define LOG_WARN(lg) BOOST_LOG_SEV(lg, logging::trivial::warning) << __FILENAME__ << ":" << __LINE__ << " - "
#define LOG_ERROR(lg) BOOST_LOG_SEV(lg, logging::trivial::error) << __FILENAME__ << ":" << __LINE__ << " - "
#define LOG_FATAL(lg) BOOST_LOG_SEV(lg, logging::trivial::fatal) << __FILENAME__ << ":" << __LINE__ << " - "
#else
#define LOG_TRACE(lg) BOOST_LOG_SEV(lg, logging::trivial::trace)
#define LOG_DEBUG(lg) BOOST_LOG_SEV(lg, logging::trivial::debug)
#define LOG_INFO(lg) BOOST_LOG_SEV(lg, logging::trivial::info)
#define LOG_WARN(lg) BOOST_LOG_SEV(lg, logging::trivial::warning)
#define LOG_ERROR(lg) BOOST_LOG_SEV(lg, logging::trivial::error)
#define LOG_FATAL(lg) BOOST_LOG_SEV(lg, logging::trivial::fatal)
#endif

#endif
