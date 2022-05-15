cmake_minimum_required(VERSION 3.22)
project(ft_irc)

set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG") #98
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") #11

include_directories(.)
include_directories(Channel)
include_directories(commands/includes)
include_directories(commands/utilities)
include_directories(Server)
include_directories(User)

add_executable(ft_irc
        Channel/Channel.cpp
        Channel/Channel.hpp
        commands/includes/Command.hpp
        commands/includes/CommandParser.hpp
        commands/src/Command.cpp
        commands/src/CommandParser.cpp
#        commands/test/CommandParserTest.cpp
        commands/utilities/utilities.cpp
        commands/utilities/utilities.hpp
        Server/Server.cpp
        Server/Server.hpp
        User/User.cpp
        User/User.hpp
        main.cpp
        utils.hpp)
