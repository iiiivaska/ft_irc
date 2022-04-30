cmake_minimum_required(VERSION 3.22)
project(commands)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG")

add_executable(commands
        src/CommandParser.cpp
        src/Command.cpp

        utilities/utilities.cpp

        test/CommandParserTest.cpp)

