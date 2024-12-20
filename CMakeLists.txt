cmake_minimum_required(VERSION 3.10)
project(Fluid)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

function(print_info MESSAGE_TEXT)
    message(STATUS "${MESSAGE_TEXT}")
endfunction()

if(DEFINED TYPES AND DEFINED SIZES)
    execute_process(
            COMMAND python3 Generator.py "${TYPES}" "${SIZES}"
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )

    add_executable(Fluid main.cpp)
    target_include_directories(Fluid PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

elseif(NOT DEFINED TYPES)
    message(FATAL_ERROR "TYPES variable is not defined. Use -DTYPES=<value> like in README.")
elseif(NOT DEFINED SIZES)
    message(FATAL_ERROR "SIZES variable is not defined. Use -DSIZES=<value> like in README.")
endif()