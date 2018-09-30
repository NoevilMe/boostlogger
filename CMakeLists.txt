cmake_minimum_required(VERSION 3.0)

project(boostlogger_example)

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -o3")

# for boost， which was built ./b2 --prefix=/opt --build-type=complete --layout=versioned toolset=gcc runtime-link=shared link=static threading=multi install
set(BOOST_ROOT /opt)
set(Boost_DEBUG ON)
set(BOOST_LIBRARYDIR /opt/lib)

if(LINK_AGAINST_STATIC_BOOST)
    set(Boost_USE_STATIC_LIBS ON)
else()
    add_definitions(-DBOOST_LOG_DYN_LINK)
endif()

if(USE_BOOST_LAYOUT_VERSIONED)
    set(Boost_USE_MULTITHREADED ON)
    set(Boost_COMPILER -gcc54)
    set(Boost_ADDITIONAL_VERSIONS "1.64")
endif()

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

ADD_SUBDIRECTORY(include)
ADD_SUBDIRECTORY(examples)
