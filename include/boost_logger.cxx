#include "boost_logger.h"

#include <boost/log/core.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/attributes/timer.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>


namespace sinks = boost::log::sinks;
namespace attrs = boost::log::attributes;
namespace srcs = boost::log::sources;
namespace exprs = boost::log::expressions;
namespace keywords = boost::log::keywords;

namespace fs = boost::filesystem;

static auto core = logging::core::get();

void init_file_logging(const std::string &log_dir, const std::string &file, int size, int max_files)
{
    fs::path fs_dir(log_dir);
    if (!fs::exists(fs_dir)) {
        fs::create_directories(fs_dir);
    }

    fs::path fs_file(file);
    std::string log_file_name = fs_file.stem().string() + ".%N";
    if (fs_file.has_extension()) {
        log_file_name.append(fs_file.extension().string());
    }
    
    // register severity_level as attribute "Severity", which would be used in the format string.
    logging::register_simple_formatter_factory< boost::log::trivial::severity_level, char >("Severity");

	// https://www.boost.org/doc/libs/1_67_0/libs/log/doc/html/log/detailed/sink_backends.html#log.detailed.sink_backends.text_file
	logging::add_file_log (
			keywords::file_name = log_file_name,
			keywords::target = fs_dir.string(),
			keywords::open_mode = std::ios::app,
			keywords::rotation_size = size,
			//keywords::max_size = 20 * 1024 * 1024,
            keywords::max_files = max_files,
			//keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point(0, 0, 0),
			keywords::format ="%TimeStamp% %ThreadID% [%Severity%] %Message%",
			keywords::auto_flush = true
			);

    logging::add_common_attributes();
    // common attributes, which include:
    //LineID - logging records counter with value type unsigned int
    //TimeStamp - local time generator with value type boost::posix_time::ptime
    //ProcessID - current process identifier with value type attributes::current_process_id::value_type
    //ThreadID - in multithreaded builds, current thread identifier with value type attributes::current_thread_id::value_type

	//BOOST_LOG_SCOPED_THREAD_TAG("ThreadID", boost::this_thread::get_id());
    //logging::core::get()->add_global_attribute("ThreadID", attrs::current_thread_id());

    //placeholder
    //BOOST_LOG_ATTRIBUTE_KEYWORD(line_id, "LineID", unsigned int)
    //BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", severity_level)
    //BOOST_LOG_ATTRIBUTE_KEYWORD(tag_attr, "Tag", std::string)
    //BOOST_LOG_ATTRIBUTE_KEYWORD(scope, "Scope", attrs::named_scope::value_type)
    //BOOST_LOG_ATTRIBUTE_KEYWORD(timeline, "Timeline", attrs::timer::value_type)
}


void set_logging_level(logging::trivial::severity_level level)
{
    //使用的是Boost.Phoenix lambda表达式; 表达式的左边参数描述一个等待被校验的属性, 表达式的右边是需要被校验的值;
    core->set_filter(logging::trivial::severity >= level);
    //logging::core::get()->set_filter(exprs::attr< severity_level >("Severity") >= level);
}

void set_logging_level(const std::string &level)
{
    if (boost::iequals(level, "trace")) {
        set_logging_level(logging::trivial::trace);
    }
    else if (boost::iequals(level, "debug")) {
        set_logging_level(logging::trivial::debug);
    }
    else if (boost::iequals(level, "info")) {
        set_logging_level(logging::trivial::info);
    }
    else if (boost::iequals(level, "warning") || boost::iequals(level, "warn")) {
        set_logging_level(logging::trivial::warning);
    }
    else if (boost::iequals(level, "error")) {
        set_logging_level(logging::trivial::error);
    }
    else if (boost::iequals(level, "error")) {
        set_logging_level(logging::trivial::fatal);
    }

}

void logging_flush()
{
	core->flush();
}

void logging_finalize()
{
	logging_flush();
	core->remove_all_sinks();
}
