cmake_minimum_required(VERSION 4.1)
project(taiwanfrp_launcher)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

#find_package(OpenSSL REQUIRED)

add_executable(taiwanfrp_launcher main.cpp
        cli.cpp
        cli.h)

#target_link_libraries(taiwanfrp_launcher OpenSSL::SSL OpenSSL::Crypto)