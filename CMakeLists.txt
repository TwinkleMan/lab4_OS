cmake_minimum_required(VERSION 3.21)
project(lab4_OS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CXX_STANDARD_LIBRARIES}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

add_executable(lab4_OS_1 main.cpp)
add_executable(Writer Writer.cpp)
add_executable(Reader Reader.cpp)

add_executable(Client part2/Client.cpp)
add_executable(Server part2/Server.cpp)