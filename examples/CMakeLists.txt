

add_executable(example main.cpp)
target_link_libraries(example boost_logger ${Boost_LIBRARIES} -pthread)
