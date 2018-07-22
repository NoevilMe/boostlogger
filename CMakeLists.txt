cmake_minimum_required(VERSION 3.0)

project(boostlogger_example)

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")

SET(BOOST_ROOT /opt)

find_package(Boost REQUIRED
  COMPONENTS
    filesystem
    log_setup
    log
    system
    thread)

 #g++ log.cpp -DBOOST_LOG_DYN_LINK -lboost_log_setup-mt -lboost_log-mt  -I/opt/include -L/opt/lib -Wl,-rpath=/opt/lib -lboost_system-mt -lboost_thread-mt -pthread
if(NOT Boost_FOUND)
    message(FATAL_ERROR "Not found Boost")
else()
    message("Found boost " ${Boost_VERSION})
    include_directories(${Boost_INCLUDE_DIRS})
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)

include_directories(${PROJECT_SOURCE_DIR}/include)
add_definitions(-DBOOST_LOG_DYN_LINK)

ADD_SUBDIRECTORY(include)
ADD_SUBDIRECTORY(examples)
