

add_executable(example main.cpp thread_log.cpp)
target_link_libraries(example boost_logger ${Boost_LIBRARIES} -pthread)
